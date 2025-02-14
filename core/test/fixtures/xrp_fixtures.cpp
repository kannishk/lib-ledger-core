// This file was GENERATED by command:
//     generate_fixtures.py
// DO NOT EDIT BY HAND!!!
#include "xrp_fixtures.h"

namespace ledger {
    namespace testing {
        namespace xrp {
            core::api::AccountCreationInfo XPUB_INFO(
                0,
                {"xrp"},
                {"44'/144'/0'"},
                {ledger::core::hex::toByteArray("024819f9d4bd29318226e3c807cdd2da84161abaf5619c5d2bbfe5be63c74cc9ed")},
                {ledger::core::hex::toByteArray("b4f8427e7e19f284dfe7b99f107c55d00b3eae56df9569f0c4d56722742a5d71")});
            std::shared_ptr<core::RippleLikeAccount> inflate(const std::shared_ptr<core::WalletPool> &pool, const std::shared_ptr<core::AbstractWallet> &wallet) {
                auto account = std::dynamic_pointer_cast<core::RippleLikeAccount>(uv::wait(wallet->newAccountWithInfo(XPUB_INFO)));
                std::vector<core::Operation> operations;
                account->interpretTransaction(*core::JSONUtils::parse<core::RippleLikeTransactionParser>(TX_1), operations);
                account->bulkInsert(operations);
                return account;
            }
            const std::string TX_1 = "{\"status\": \"success\", \"Account\": \"rsvAf4P8Tx6tBUdWPNesMngXDmbZ2LMVF8\", \"Fee\": \"10\", \"hash\": \"AF4BB95DE86A640B90B2AF3C696EF26EFE7DD71864CC959D8030B448DD48E756\", \"ledger_index\": 44196232, \"LastLedgerSequence\": 44196239, \"Sequence\": 1, \"SigningPubKey\": \"0215A9EE08A4B4747E27F348365F93BEB5897FA7E8776BEDAE2CB56917DCDBBF2F\", \"Destination\": \"rMspb4Kxa3EwdF4uN5TMqhHfsAkBit6w7k\", \"date\": 600017851, \"Amount\": \"22000000\", \"meta\": {\"TransactionResult\": \"tesSUCCESS\", \"delivered_amount\": \"22000000\", \"TransactionIndex\": 1, \"AffectedNodes\": [{\"CreatedNode\": {\"NewFields\": {\"Account\": \"rMspb4Kxa3EwdF4uN5TMqhHfsAkBit6w7k\", \"Balance\": \"22000000\", \"Sequence\": 1}, \"LedgerEntryType\": \"AccountRoot\", \"LedgerIndex\": \"5AF22704F03359EC7B35095324F071B04A361CAB5BE44D03122E33143FE9343E\"}}, {\"ModifiedNode\": {\"LedgerEntryType\": \"AccountRoot\", \"PreviousTxnID\": \"B02920CA663943E272886C9216CB779028C82492EE9C4DD73BAA12C3190E9F10\", \"FinalFields\": {\"OwnerCount\": 0, \"Account\": \"rsvAf4P8Tx6tBUdWPNesMngXDmbZ2LMVF8\", \"Balance\": \"35169770\", \"Flags\": 0, \"Sequence\": 2}, \"LedgerIndex\": \"699C329231D8720F61CEC57756413A9967C822CE073FA3C8BEC305FAF1AB363E\", \"PreviousTxnLgrSeq\": 43216867, \"PreviousFields\": {\"Balance\": \"57169780\", \"Sequence\": 1}}}]}, \"Flags\": 2147483648, \"TxnSignature\": \"3045022100F2AB61EC941462D692514BFDDB00BC0D31BA7DA66981193E67A04E90578C18B1022064A2375ECB5A68C22EE3038B783BE6A9E1F2C882A8E8BBEE43C4CFA93B536926\", \"inLedger\": 44196232, \"validated\": true, \"TransactionType\": \"Payment\"}";
        } // namespace xrp
    }     // namespace testing
} // namespace ledger
