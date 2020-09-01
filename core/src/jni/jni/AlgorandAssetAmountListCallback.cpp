// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from callback.djinni

#include "AlgorandAssetAmountListCallback.hpp"  // my header
#include "AlgorandAssetAmount.hpp"
#include "Error.hpp"
#include "Marshal.hpp"

namespace djinni_generated {

AlgorandAssetAmountListCallback::AlgorandAssetAmountListCallback() : ::djinni::JniInterface<::ledger::core::api::AlgorandAssetAmountListCallback, AlgorandAssetAmountListCallback>() {}

AlgorandAssetAmountListCallback::~AlgorandAssetAmountListCallback() = default;

AlgorandAssetAmountListCallback::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

AlgorandAssetAmountListCallback::JavaProxy::~JavaProxy() = default;

void AlgorandAssetAmountListCallback::JavaProxy::onCallback(const std::experimental::optional<std::vector<::ledger::core::api::AlgorandAssetAmount>> & c_result, const std::experimental::optional<::ledger::core::api::Error> & c_error) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::AlgorandAssetAmountListCallback>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_onCallback,
                           ::djinni::get(::djinni::Optional<std::experimental::optional, ::djinni::List<::djinni_generated::AlgorandAssetAmount>>::fromCpp(jniEnv, c_result)),
                           ::djinni::get(::djinni::Optional<std::experimental::optional, ::djinni_generated::Error>::fromCpp(jniEnv, c_error)));
    ::djinni::jniExceptionCheck(jniEnv);
}

}  // namespace djinni_generated