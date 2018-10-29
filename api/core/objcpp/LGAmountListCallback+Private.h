// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from callback.djinni

#include "AmountListCallback.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol LGAmountListCallback;

namespace djinni_generated {

class AmountListCallback
{
public:
    using CppType = std::shared_ptr<::ledger::core::api::AmountListCallback>;
    using CppOptType = std::shared_ptr<::ledger::core::api::AmountListCallback>;
    using ObjcType = id<LGAmountListCallback>;

    using Boxed = AmountListCallback;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
