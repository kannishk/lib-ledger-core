/*
 *
 * transaction_test_helper
 * ledger-core
 *
 * Created by El Khalil Bellakrid on 16/05/2018.
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

#include "transaction_test_helper.h"

#include "api/BitcoinLikeInput.hpp"
#include "api/BitcoinLikeOutput.hpp"

// Examples taken from https://github.com/bitcoin/bips/blob/master/bip-0143.mediawiki
// Serialized signed segwit transactions, first has 2 inputs with witnesses, second has 2 inputs and only one of them has a witness
const std::vector<std::string> rawSegwitTxs{
    "01000000000102e9b542c5176808107ff1df906f46bb1f2583b16112b95ee5380665ba7fcfc0010000000000ffffffff80e68831516392fcd100d186b3c2c7b95c80b53c77e77c35ba03a66b429a2a1b0000000000ffffffff0280969800000000001976a914de4b231626ef508c9a74a8517e6783c0546d6b2888ac80969800000000001976a9146648a8cd4531e1ec47f35916de8e259237294d1e88ac02483045022100f6a10b8604e6dc910194b79ccfc93e1bc0ec7c03453caaa8987f7d6c3413566002206216229ede9b4d6ec2d325be245c5b508ff0339bf1794078e20bfe0babc7ffe683270063ab68210392972e2eb617b2388771abe27235fd5ac44af8e61693261550447a4c3e39da98ac024730440220032521802a76ad7bf74d0e2c218b72cf0cbc867066e2e53db905ba37f130397e02207709e2188ed7f08f4c952d9d13986da504502b8c3be59617e043552f506c46ff83275163ab68210392972e2eb617b2388771abe27235fd5ac44af8e61693261550447a4c3e39da98ac00000000",
    "01000000000102fe3dc9208094f3ffd12645477b3dc56f60ec4fa8e6f5d67c565d1c6b9216b36e000000004847304402200af4e47c9b9629dbecc21f73af989bdaa911f7e6f6c2e9394588a3aa68f81e9902204f3fcf6ade7e5abb1295b6774c8e0abd94ae62217367096bc02ee5e435b67da201ffffffff0815cf020f013ed6cf91d29f4202e8a58726b1ac6c79da47c23d1bee0a6925f80000000000ffffffff0100f2052a010000001976a914a30741f8145e5acadf23f751864167f32e0963f788ac000347304402200de66acf4527789bfda55fc5459e214fa6083f936b430a762c629656216805ac0220396f550692cd347171cbc1ef1f51e15282e837bb2b30860dc77c8f78bc8501e503473044022027dc95ad6b740fe5129e7e62a75dd00f291a2aeb1200b84b09d9e3789406b6c002201a9ecd315dd6a0e632ab20bbb98948bc0c6fb204f2c286963bb48517a7058e27034721026dccc749adc2a9d0d89497ac511f760f45c47dc5ed9cf352a58ac706453880aeadab210255a9626aebf5e29c0e6538428ba0d1dcf6ca98ffdf086aa8ced5e0d0215ea465ac00000000"};
// KO: P2SH-P2WPKH
// 01000000000101db6b1b20aa0fd7b23880be2ecbd4a98130974cf4748fb66092ac4d3ceb1a5477010000001716001479091972186c449eb1ded22b78e40d009bdf0089feffffff02b8b4eb0b000000001976a914a457b684d7f0d539a46a45bbc043f35b59d0d96388ac0008af2f000000001976a914fd270b1ee6abcaea97fea7ad0402e8bd8ad6d77c88ac02473044022047ac8e878352d3ebbde1c94ce3a10d057c24175747116f8288e5d794d12d482f0220217f36a485cae903c713331d877c1f64677e3622ad4010726870540656fe9dcb012103ad1d8e89212f0b92c74d23bb710c00662ad1470198ac48c43f7d6f93a2a2687392040000
// KO: P2WPKH (normally not used, to check)
// 01000000000102fff7f7881a8099afa6940d42d1e7f6362bec38171ea3edf433541db4e4ad969f00000000494830450221008b9d1dc26ba6a9cb62127b02742fa9d754cd3bebf337f7a55d114c8e5cdd30be022040529b194ba3f9281a99f2b1c0a19c0489bc22ede944ccf4ecbab4cc618ef3ed01eeffffffef51e1b804cc89d182d279655c3aa89e815b1b309fe287d9b2b55d57b90ec68a0100000000ffffffff02202cb206000000001976a9148280b37df378db99f66f85c95a783a76ac7a6d5988ac9093510d000000001976a9143bde42dbee7e4dbe6a21b2d50ce2f0167faa815988ac000247304402203609e17b84f6a7d30c80bfa610b5b4542f32a8a0d5447a12fb1366d7f01cc44a0220573a954c4518331561406f90300e8f3358f51928d43c212a8caed02de67eebee0121025476c2e83188368da1ff3e292e7acafcdb3566bb0ad253f62fc70f07aeee635711000000

std::shared_ptr<api::BitcoinLikeTransaction> BitcoinMakeBaseTransaction::createTransaction(const std::vector<OutputDescr> &outputs) {
    auto builder = tx_builder();

    for (const OutputDescr &od : outputs) {
        if (od._addr.empty())
            continue;

        builder->sendToAddress(
            std::make_shared<ledger::core::Amount>(
                currency,
                0,
                std::dynamic_pointer_cast<api::BigIntImpl>(od._amount)->backend()),
            od._addr);
    }

    builder->pickInputs(api::BitcoinLikePickingStrategy::DEEP_OUTPUTS_FIRST, 0xFFFFFFFF, optional<int32_t>());
    builder->setFeesPerByte(api::Amount::fromLong(currency, 61));

    auto f                                          = builder->build();
    std::shared_ptr<api::BitcoinLikeTransaction> tx = uv::wait(f);
    return tx;
}

bool BitcoinMakeBaseTransaction::verifyTransactionInputs(std::shared_ptr<api::BitcoinLikeTransaction> tx,
                                                         const std::vector<InputDescr> &inputs) {
    if (inputs.size() != tx->getInputs().size())
        return false;

    std::set<size_t> inputs_matched;
    for (size_t i = 0; i < inputs.size(); ++i) {
        for (size_t j = 0; j < inputs.size(); ++j) {
            if (inputs_matched.end() != inputs_matched.find(j)) {
                continue;
            }

            std::shared_ptr<api::BitcoinLikeInput> txin = tx->getInputs()[j];
            if (txin->getValue()->toBigInt()->compare(inputs[i]._amount) == 0 && txin->getPreviousTxHash().value_or("no hash") == inputs[i]._tx_hash && txin->getPreviousOutputIndex().value_or(-1) == inputs[i]._out_idx) {
                inputs_matched.insert(j);
                break;
            }
        }
    }

    return inputs.size() == inputs_matched.size();
}

bool BitcoinMakeBaseTransaction::verifyTransactionOutputs(std::shared_ptr<api::BitcoinLikeTransaction> tx,
                                                          const std::vector<OutputDescr> &outputs) {
    if (outputs.size() != tx->getOutputs().size())
        return false;

    std::set<size_t> outputs_matched;
    for (size_t i = 0; i < outputs.size(); ++i) {
        for (size_t j = 0; j < outputs.size(); ++j) {
            if (outputs_matched.end() != outputs_matched.find(j)) {
                continue;
            }

            std::shared_ptr<api::BitcoinLikeOutput> txout = tx->getOutputs()[j];
            if (txout->getValue()->toBigInt()->compare(outputs[i]._amount) == 0 && txout->getScript() == outputs[i]._script) {
                outputs_matched.insert(j);
                break;
            }
            std::cerr << hex::toString(txout->getScript()) << std::endl;
        }
    }

    return outputs.size() == outputs_matched.size();
}

bool BitcoinMakeBaseTransaction::verifyTransaction(std::shared_ptr<api::BitcoinLikeTransaction> tx,
                                                   const std::vector<InputDescr> &inputs,
                                                   const std::vector<OutputDescr> &outputs) {
    return verifyTransactionInputs(tx, inputs) && verifyTransactionOutputs(tx, outputs);
}

void BitcoinMakeBaseTransaction::createAndVerifyTransaction(const std::vector<InputDescr> &inputs,
                                                            const std::vector<OutputDescr> &outputs) {
    std::shared_ptr<api::BitcoinLikeTransaction> generatedTx = createTransaction(outputs);

    std::cerr << "generated tx: " << std::endl
              << hex::toString(generatedTx->serialize()) << std::endl;

    EXPECT_TRUE(verifyTransaction(generatedTx, inputs, outputs));

    std::vector<uint8_t> tx_bin = generatedTx->serialize();

    auto parsedTx               = BitcoinLikeTransactionBuilder::parseRawUnsignedTransaction(wallet->getCurrency(),
                                                                                             tx_bin, 0);

    EXPECT_TRUE(verifyTransactionOutputs(parsedTx, outputs));
    // Values in inputs are missing after parsing. Here we can test only outputs.

    EXPECT_EQ(tx_bin, parsedTx->serialize());
}
