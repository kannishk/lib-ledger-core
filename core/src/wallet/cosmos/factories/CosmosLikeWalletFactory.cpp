/*
 *
 * CosmosLikeWalletFactory
 *
 * Created by El Khalil Bellakrid on 14/06/2019.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ledger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <api/BlockchainExplorerEngines.hpp>
#include <api/ConfigurationDefaults.hpp>
#include <api/CosmosConfigurationDefaults.hpp>
#include <api/KeychainEngines.hpp>
#include <api/SynchronizationEngines.hpp>
#include <database/migrations.hpp>
#include <wallet/cosmos/CosmosLikeWallet.hpp>
#include <wallet/cosmos/CosmosNetworks.hpp>
#include <wallet/cosmos/explorers/GaiaCosmosLikeBlockchainExplorer.hpp>
#include <wallet/cosmos/factories/CosmosLikeKeychainFactory.hpp>
#include <wallet/cosmos/factories/CosmosLikeWalletFactory.hpp>

#define STRING(key, def) entry.configuration->getString(key).value_or(def)

namespace ledger {
    namespace core {
        CosmosLikeWalletFactory::CosmosLikeWalletFactory(
            const api::Currency &currency,
            const std::shared_ptr<WalletPool> &pool) : AbstractWalletFactory(currency, pool) {
            _keychainFactories = {
                {api::KeychainEngines::BIP49_P2SH, std::make_shared<CosmosLikeKeychainFactory>()}};
        }

        std::shared_ptr<AbstractWallet> CosmosLikeWalletFactory::build(const WalletDatabaseEntry &entry) {
            auto pool = getPool();
            pool->logger()->info(
                "Building wallet instance '{}' for {} with parameters: {}",
                entry.name,
                entry.currencyName,
                entry.configuration->dump());
            // Get currency
            auto isSupportedCurrency = [entry](const api::CosmosLikeNetworkParameters &networkParameters) {
                return entry.currencyName == networkParameters.Identifier;
            };

            if (std::none_of(
                    std::begin(networks::ALL_COSMOS),
                    std::end(networks::ALL_COSMOS),
                    isSupportedCurrency)) {
                throw make_exception(
                    api::ErrorCode::UNSUPPORTED_CURRENCY, "Unsupported currency '{}'.", entry.currencyName);
            }

            // Configure keychain
            auto keychainFactory = _keychainFactories.find(
                STRING(api::Configuration::KEYCHAIN_ENGINE, api::KeychainEngines::BIP49_P2SH));
            if (keychainFactory == _keychainFactories.end()) {
                throw make_exception(
                    api::ErrorCode::UNKNOWN_KEYCHAIN_ENGINE,
                    "Engine '{}' is not a supported keychain engine.",
                    STRING(api::Configuration::KEYCHAIN_ENGINE, "undefined"));
            }
            // Configure explorer
            auto explorer = getExplorer(entry.currencyName, entry.configuration);
            if (explorer == nullptr)
                throw make_exception(
                    api::ErrorCode::UNKNOWN_BLOCKCHAIN_EXPLORER_ENGINE,
                    "Engine '{}' is not a supported explorer engine.",
                    STRING(api::Configuration::BLOCKCHAIN_EXPLORER_ENGINE, "undefined"));
            // Configure synchronizer
            Option<CosmosLikeAccountSynchronizerFactory> synchronizerFactory;
            {
                auto engine =
                    entry.configuration->getString(api::Configuration::SYNCHRONIZATION_ENGINE)
                        .value_or(api::SynchronizationEngines::BLOCKCHAIN_EXPLORER_SYNCHRONIZATION);
                if (engine == api::SynchronizationEngines::BLOCKCHAIN_EXPLORER_SYNCHRONIZATION) {
                    std::weak_ptr<WalletPool> p = pool;
                    synchronizerFactory         = Option<CosmosLikeAccountSynchronizerFactory>([p, explorer]() {
                        auto pool = p.lock();
                        return std::make_shared<CosmosLikeAccountSynchronizer>(pool, explorer);
                    });
                }
            }

            if (synchronizerFactory.isEmpty())
                throw make_exception(
                    api::ErrorCode::UNKNOWN_SYNCHRONIZATION_ENGINE,
                    "Engine '{}' is not a supported synchronization engine.",
                    STRING(api::Configuration::SYNCHRONIZATION_ENGINE, "undefined"));
            // Sets the derivation scheme
            DerivationScheme scheme(STRING(
                api::Configuration::KEYCHAIN_DERIVATION_SCHEME,
                "44'/<coin_type>'/<account>'/<node>/<address>"));
            // Build wallet

            return std::make_shared<CosmosLikeWallet>(
                entry.name,
                explorer,
                keychainFactory->second,
                synchronizerFactory.getValue(),
                pool,
                getCurrency(),
                entry.configuration,
                scheme);
        }

        std::shared_ptr<CosmosLikeBlockchainExplorer> CosmosLikeWalletFactory::getExplorer(
            const std::string &currencyName,
            const std::shared_ptr<api::DynamicObject> &configuration) {
            auto it = _runningExplorers.begin();
            while (it != _runningExplorers.end()) {
                auto explorer = it->lock();
                if (explorer != nullptr) {
                    if (explorer->match(configuration))
                        return explorer;
                    it++;
                } else {
                    it = _runningExplorers.erase(it);
                }
            }

            auto pool   = getPool();
            auto engine = configuration->getString(api::Configuration::BLOCKCHAIN_EXPLORER_ENGINE)
                              .value_or(api::BlockchainExplorerEngines::COSMOS_NODE);
            std::shared_ptr<CosmosLikeBlockchainExplorer> explorer = nullptr;
            if (engine == api::BlockchainExplorerEngines::COSMOS_NODE) {
                auto http    = pool->getHttpClient(fmt::format(
                       "{}",
                       configuration->getString(api::Configuration::BLOCKCHAIN_EXPLORER_API_ENDPOINT)
                           .value_or(api::CosmosConfigurationDefaults::COSMOS_DEFAULT_API_ENDPOINT)));
                auto context = pool->getDispatcher()->getSerialExecutionContext(
                    api::BlockchainExplorerEngines::COSMOS_NODE);
                auto &networkParams = getCurrency().cosmosLikeNetworkParameters.value();

                explorer            = std::make_shared<GaiaCosmosLikeBlockchainExplorer>(
                    context, http, networkParams, std::dynamic_pointer_cast<DynamicObject>(configuration));
            } else {
                throw Exception(
                    api::ErrorCode::IMPLEMENTATION_IS_MISSING,
                    "CosmosLikeWalletFactory using non supported explorer");
            }
            if (explorer) {
                _runningExplorers.push_back(explorer);
                return explorer;
            }
            throw Exception(
                api::ErrorCode::IMPLEMENTATION_IS_MISSING,
                "CosmosLikeWalletFactory using non supported explorer");
        }

    } // namespace core
} // namespace ledger
