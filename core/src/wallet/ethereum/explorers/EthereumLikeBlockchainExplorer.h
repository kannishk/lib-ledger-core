/*
 *
 * EthereumLikeBlockchainExplorer
 *
 * Created by El Khalil Bellakrid on 14/07/2018.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ledger
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

#ifndef LEDGER_CORE_ETHEREUMBLOCKCHAINEXPLORER_H
#define LEDGER_CORE_ETHEREUMBLOCKCHAINEXPLORER_H

#include <api/DynamicObject.hpp>
#include <api/EthereumGasLimitRequest.hpp>
#include <api/EthereumLikeNetworkParameters.hpp>
#include <api/ExecutionContext.hpp>
#include <api/Operation.hpp>
#include <async/DedicatedContext.hpp>
#include <collections/DynamicObject.hpp>
#include <math/BigInt.h>
#include <net/HttpClient.hpp>
#include <string>
#include <utils/ConfigurationMatchable.h>
#include <utils/Option.hpp>
#include <wallet/common/Block.h>
#include <wallet/common/explorers/AbstractBlockchainExplorer.h>
#include <wallet/ethereum/keychains/EthereumLikeKeychain.hpp>
namespace ledger {
    namespace core {

        struct ERC20Transaction {
            std::string from;
            std::string to;
            std::string contractAddress;
            BigInt value;
            api::OperationType type;
        };

        struct InternalTx {
            std::string from;
            std::string to;
            BigInt value;
            BigInt gasLimit;
            Option<BigInt> gasUsed;
            api::OperationType type;
            std::vector<uint8_t> inputData;
        };

        struct EthereumLikeBlockchainExplorerTransaction {
            std::string hash;
            std::chrono::system_clock::time_point receivedAt;
            BigInt value;
            BigInt gasPrice;
            BigInt gasLimit;
            Option<BigInt> gasUsed;
            std::string receiver;
            std::string sender;
            uint64_t nonce;
            Option<Block> block;
            uint64_t confirmations;
            std::vector<uint8_t> inputData;
            uint64_t status;
            std::vector<InternalTx> internalTransactions;
            std::vector<ERC20Transaction> erc20Transactions;
            EthereumLikeBlockchainExplorerTransaction() {
                nonce         = 0;
                confirmations = 0;
                status        = 0;
            }

            EthereumLikeBlockchainExplorerTransaction(const EthereumLikeBlockchainExplorerTransaction &cpy) {
                this->block                = cpy.block;
                this->hash                 = cpy.hash;
                this->receivedAt           = cpy.receivedAt;
                this->confirmations        = cpy.confirmations;
                this->gasUsed              = cpy.gasUsed;
                this->gasLimit             = cpy.gasLimit;
                this->gasPrice             = cpy.gasPrice;
                this->inputData            = cpy.inputData;
                this->receiver             = cpy.receiver;
                this->sender               = cpy.sender;
                this->nonce                = cpy.nonce;
                this->value                = cpy.value;
                this->status               = cpy.status;
                this->internalTransactions = cpy.internalTransactions;
                this->erc20Transactions    = cpy.erc20Transactions;
            }
        };

        class EthereumLikeBlockchainExplorer : public ConfigurationMatchable,
                                               public AbstractBlockchainExplorer<EthereumLikeBlockchainExplorerTransaction> {
          public:
            typedef ledger::core::Block Block;
            using Transaction = EthereumLikeBlockchainExplorerTransaction;

            EthereumLikeBlockchainExplorer(const std::shared_ptr<ledger::core::api::DynamicObject> &configuration,
                                           const std::vector<std::string> &matchableKeys);

            virtual Future<std::shared_ptr<BigInt>> getNonce(const std::string &address)                                                       = 0;
            virtual Future<std::shared_ptr<BigInt>> getBalance(const std::vector<EthereumLikeKeychain::Address> &addresses)                    = 0;
            virtual Future<std::shared_ptr<BigInt>> getGasPrice()                                                                              = 0;
            virtual Future<std::shared_ptr<BigInt>> getEstimatedGasLimit(const std::string &address)                                           = 0;
            virtual Future<std::shared_ptr<BigInt>> getDryRunGasLimit(const std::string &address, const api::EthereumGasLimitRequest &request) = 0;
            virtual Future<std::shared_ptr<BigInt>> getERC20Balance(const std::string &address,
                                                                    const std::string &erc20Address)                                           = 0;
            virtual Future<std::vector<BigInt>> getERC20Balances(const std::string &address,
                                                                 const std::vector<std::string> &erc20Addresses)                               = 0;
        };
    } // namespace core
} // namespace ledger

#endif // LEDGER_CORE_ETHEREUMBLOCKCHAINEXPLORER_H
