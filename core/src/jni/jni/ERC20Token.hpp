// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from erc20.djinni

#ifndef DJINNI_GENERATED_ERC20TOKEN_HPP_JNI_
#define DJINNI_GENERATED_ERC20TOKEN_HPP_JNI_

#include "../../api/ERC20Token.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class ERC20Token final {
public:
    using CppType = ::ledger::core::api::ERC20Token;
    using JniType = jobject;

    using Boxed = ERC20Token;

    ~ERC20Token();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    ERC20Token();
    friend ::djinni::JniClass<ERC20Token>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("co/ledger/core/ERC20Token") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V") };
    const jfieldID field_name { ::djinni::jniGetFieldID(clazz.get(), "name", "Ljava/lang/String;") };
    const jfieldID field_symbol { ::djinni::jniGetFieldID(clazz.get(), "symbol", "Ljava/lang/String;") };
    const jfieldID field_contractAddress { ::djinni::jniGetFieldID(clazz.get(), "contractAddress", "Ljava/lang/String;") };
    const jfieldID field_numberOfDecimal { ::djinni::jniGetFieldID(clazz.get(), "numberOfDecimal", "I") };
};

}  // namespace djinni_generated
#endif //DJINNI_GENERATED_ERC20TOKEN_HPP_JNI_