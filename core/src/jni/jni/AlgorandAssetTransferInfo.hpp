// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from idl.djinni

#ifndef DJINNI_GENERATED_ALGORANDASSETTRANSFERINFO_HPP_JNI_
#define DJINNI_GENERATED_ALGORANDASSETTRANSFERINFO_HPP_JNI_

#include "../../api/AlgorandAssetTransferInfo.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class AlgorandAssetTransferInfo final {
public:
    using CppType = ::ledger::core::api::AlgorandAssetTransferInfo;
    using JniType = jobject;

    using Boxed = AlgorandAssetTransferInfo;

    ~AlgorandAssetTransferInfo();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    AlgorandAssetTransferInfo();
    friend ::djinni::JniClass<AlgorandAssetTransferInfo>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("co/ledger/core/AlgorandAssetTransferInfo") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V") };
    const jfieldID field_assetId { ::djinni::jniGetFieldID(clazz.get(), "assetId", "Ljava/lang/String;") };
    const jfieldID field_amount { ::djinni::jniGetFieldID(clazz.get(), "amount", "Ljava/lang/String;") };
    const jfieldID field_recipientAddress { ::djinni::jniGetFieldID(clazz.get(), "recipientAddress", "Ljava/lang/String;") };
    const jfieldID field_closeAddress { ::djinni::jniGetFieldID(clazz.get(), "closeAddress", "Ljava/lang/String;") };
    const jfieldID field_clawedBackAddress { ::djinni::jniGetFieldID(clazz.get(), "clawedBackAddress", "Ljava/lang/String;") };
    const jfieldID field_closeAmount { ::djinni::jniGetFieldID(clazz.get(), "closeAmount", "Ljava/lang/String;") };
};

}  // namespace djinni_generated
#endif //DJINNI_GENERATED_ALGORANDASSETTRANSFERINFO_HPP_JNI_