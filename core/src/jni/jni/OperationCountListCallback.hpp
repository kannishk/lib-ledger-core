// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from callback.djinni

#ifndef DJINNI_GENERATED_OPERATIONCOUNTLISTCALLBACK_HPP_JNI_
#define DJINNI_GENERATED_OPERATIONCOUNTLISTCALLBACK_HPP_JNI_

#include "../../api/OperationCountListCallback.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class OperationCountListCallback final : ::djinni::JniInterface<::ledger::core::api::OperationCountListCallback, OperationCountListCallback> {
public:
    using CppType = std::shared_ptr<::ledger::core::api::OperationCountListCallback>;
    using CppOptType = std::shared_ptr<::ledger::core::api::OperationCountListCallback>;
    using JniType = jobject;

    using Boxed = OperationCountListCallback;

    ~OperationCountListCallback();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<OperationCountListCallback>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<OperationCountListCallback>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    OperationCountListCallback();
    friend ::djinni::JniClass<OperationCountListCallback>;
    friend ::djinni::JniInterface<::ledger::core::api::OperationCountListCallback, OperationCountListCallback>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::ledger::core::api::OperationCountListCallback
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void onCallback(const std::experimental::optional<std::vector<::ledger::core::api::OperationCount>> & result, const std::experimental::optional<::ledger::core::api::Error> & error) override;

    private:
        friend ::djinni::JniInterface<::ledger::core::api::OperationCountListCallback, ::djinni_generated::OperationCountListCallback>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("co/ledger/core/OperationCountListCallback") };
    const jmethodID method_onCallback { ::djinni::jniGetMethodID(clazz.get(), "onCallback", "(Ljava/util/ArrayList;Lco/ledger/core/Error;)V") };
};

}  // namespace djinni_generated
#endif //DJINNI_GENERATED_OPERATIONCOUNTLISTCALLBACK_HPP_JNI_