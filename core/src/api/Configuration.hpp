// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from configuration.djinni

#ifndef DJINNI_GENERATED_CONFIGURATION_HPP
#define DJINNI_GENERATED_CONFIGURATION_HPP

#include <string>
#ifndef LIBCORE_EXPORT
    #if defined(_MSC_VER)
       #include <libcore_export.h>
    #else
       #define LIBCORE_EXPORT
    #endif
#endif

namespace ledger { namespace core { namespace api {

/** Overall configuration. */
class LIBCORE_EXPORT Configuration {
public:
    virtual ~Configuration() {}

    /** Selects the keychain engine (P2PKH, P2SH...). */
    static std::string const KEYCHAIN_ENGINE;

    /** Sets the derivation scheme for the KEYCHAIN (defaults 44'/<coin_type>'/<account>'/<node>/<address>). */
    static std::string const KEYCHAIN_DERIVATION_SCHEME;

    /** Sets the observable range for HD keychains (BIP32 based). */
    static std::string const KEYCHAIN_OBSERVABLE_RANGE;

    /** Selects the blockchain explorer engine (Ledger's API, Electrum server, RPC): */
    static std::string const BLOCKCHAIN_EXPLORER_ENGINE;

    /** Sets the API endpoint for API based engine (Ledger's API). */
    static std::string const BLOCKCHAIN_EXPLORER_API_ENDPOINT;

    /** Sets the API key if one is required */
    static std::string const BLOCKCHAIN_EXPLORER_API_KEY;

    /** Sets the API version. */
    static std::string const BLOCKCHAIN_EXPLORER_VERSION;

    /** Sets the API port (e.g. for XRP it is 51234) */
    static std::string const BLOCKCHAIN_EXPLORER_PORT;

    /** Selects the blockchain observer engine (Ledger's API) */
    static std::string const BLOCKCHAIN_OBSERVER_ENGINE;

    /** Selects the blockchain observer engine (Ledger's API; Websocket version). */
    static std::string const BLOCKCHAIN_OBSERVER_WS_ENDPOINT;

    /** Selects the synchronization engine. */
    static std::string const SYNCHRONIZATION_ENGINE;

    /** Sets the half batch size (default: 20). */
    static std::string const SYNCHRONIZATION_HALF_BATCH_SIZE;

    /** Operation trust. */
    static std::string const TRUST_LIMIT;

    /** Time to Live for block cache */
    static std::string const TTL_CACHE;

    /** Syncronization token deactivation */
    static std::string const DEACTIVATE_SYNC_TOKEN;

    /**
     * Grace period (in seconds) during which no "missing" transactions on-chain should trigger
     * deletion from database
     */
    static std::string const MEMPOOL_GRACE_PERIOD_SECS;

    /** Allow the generation of the P2TR (Taproot) outputs */
    static std::string const ALLOW_P2TR;
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_CONFIGURATION_HPP
