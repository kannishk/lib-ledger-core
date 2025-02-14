/*
 *
 * RippleLikeTransactionParser
 *
 * Created by El Khalil Bellakrid on 07/01/2019.
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

#include "RippleLikeTransactionParser.h"

#include <wallet/currencies.hpp>
#include <wallet/ripple/utils/Time.hpp>

#define PROXY_PARSE(method, ...)                 \
    auto &currentObject = _hierarchy.top();      \
    if (currentObject == "block") {              \
        return _blockParser.method(__VA_ARGS__); \
    } else

namespace ledger {
    namespace core {

        const uint64_t XRP_EPOCH_SECONDS_FROM_UNIX_EPOCH = 946684800;

        bool RippleLikeTransactionParser::Key(const rapidjson::Reader::Ch *str, rapidjson::SizeType length, bool copy) {
            PROXY_PARSE(Key, str, length, copy) {
                return true;
            }
        }

        bool RippleLikeTransactionParser::StartObject() {
            if (_arrayDepth == 0) {
                _hierarchy.push(_lastKey);
            }

            if (_lastKey == "Memo") {
                // add a new empty RippleLikeMemo to the transaction (it’ll be filled in later by
                // the parser)
                _transaction->memos.push_back(api::RippleLikeMemo());
            }

            return true;
        }

        bool RippleLikeTransactionParser::EndObject(rapidjson::SizeType memberCount) {
            auto &currentObject = _hierarchy.top();
            if (_arrayDepth == 0) {
                _hierarchy.pop();
            }
            return true;
        }

        bool RippleLikeTransactionParser::StartArray() {
            if (_arrayDepth == 0) {
                _hierarchy.push(_lastKey);
            }
            _arrayDepth += 1;
            return true;
        }

        bool RippleLikeTransactionParser::EndArray(rapidjson::SizeType elementCount) {
            _arrayDepth -= 1;
            if (_arrayDepth == 0) {
                _hierarchy.pop();
            }
            return true;
        }

        bool RippleLikeTransactionParser::Null() {
            PROXY_PARSE(Null) {
                return true;
            }
        }

        bool RippleLikeTransactionParser::Bool(bool b) {
            PROXY_PARSE(Bool, b) {
                return true;
            }
        }

        bool RippleLikeTransactionParser::Int(int i) {
            return Uint64(i);
        }

        bool RippleLikeTransactionParser::Uint(unsigned i) {
            return Uint64(i);
        }

        bool RippleLikeTransactionParser::Int64(int64_t i) {
            return Uint64(i);
        }

        bool RippleLikeTransactionParser::Uint64(uint64_t i) {
            PROXY_PARSE(Uint64, i) {
                return true;
            }
        }

        bool RippleLikeTransactionParser::Double(double d) {
            PROXY_PARSE(Double, d) {
                return true;
            }
        }

        bool RippleLikeTransactionParser::RawNumber(const rapidjson::Reader::Ch *str, rapidjson::SizeType length, bool copy) {
            PROXY_PARSE(RawNumber, str, length, copy) {
                std::string number(str, length);
                BigInt value = BigInt::fromString(number);
                if (_lastKey == "confirmations") {
                    _transaction->confirmations = value.toUint64();
                } else if (_lastKey == "ledger_index") {
                    RippleLikeBlockchainExplorer::Block block;
                    block.height        = value.toUint64();
                    block.currencyName  = currencies::RIPPLE.name;
                    // Ledger index is not really a hash but since XRP doesn't have reorg
                    // it's safe to use ledger index as a unique hash.
                    block.hash          = number;
                    _transaction->block = block;
                } else if (_lastKey == "DestinationTag") {
                    _transaction->destinationTag = Option<int64_t>(value.toInt64());
                } else if (_lastKey == "date" && currentObject != "transaction") {
                    _transaction->receivedAt = xrp_utils::toTimePoint<std::chrono::system_clock>(value.toUint64());
                    if (_transaction->block.hasValue()) {
                        _transaction->block.getValue().time = _transaction->receivedAt;
                    }
                }

                return true;
            }
        }

        bool RippleLikeTransactionParser::String(const rapidjson::Reader::Ch *str, rapidjson::SizeType length, bool copy) {
            PROXY_PARSE(String, str, length, copy) {
                std::string value(str, length);

                if (_lastKey == "hash") {
                    _transaction->hash = value;
                } else if (_lastKey == "Account" && (currentObject == "tx" || currentObject == "transaction")) {
                    _transaction->sender = value;
                } else if (_lastKey == "Destination") {
                    _transaction->receiver = value;
                } else if (_lastKey == "Amount") {
                    BigInt valueBigInt  = BigInt::fromString(value);
                    _transaction->value = valueBigInt;
                } else if (_lastKey == "Fee") {
                    BigInt valueBigInt = BigInt::fromString(value);
                    _transaction->fees = value;
                } else if (_lastKey == "Sequence") {
                    _transaction->sequence = BigInt::fromString(value);
                } else if (_lastKey == "MemoData" && !_transaction->memos.empty()) {
                    _transaction->memos.back().data = value;
                } else if (_lastKey == "MemoFormat" && !_transaction->memos.empty()) {
                    _transaction->memos.back().fmt = value;
                } else if (_lastKey == "MemoType" && !_transaction->memos.empty()) {
                    _transaction->memos.back().ty = value;
                } else if (_lastKey == "TransactionResult") {
                    _transaction->status = value == "tesSUCCESS" ? 1 : 0;
                }
                return true;
            }
        }

        RippleLikeTransactionParser::RippleLikeTransactionParser(std::string &lastKey) : _lastKey(lastKey), _blockParser(lastKey) {
            _arrayDepth = 0;
        }

        void RippleLikeTransactionParser::init(RippleLikeBlockchainExplorerTransaction *transaction) {
            _transaction = transaction;
        }

    } // namespace core
} // namespace ledger
