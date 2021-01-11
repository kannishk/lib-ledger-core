// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from core.djinni

#ifndef DJINNI_GENERATED_DURATIONMETRIC_HPP
#define DJINNI_GENERATED_DURATIONMETRIC_HPP

#include <cstdint>
#include <iostream>
#include <utility>

namespace ledger { namespace core { namespace api {

struct DurationMetric final {
    /** Total number of milliseconds */
    int64_t total_ms;
    /** Number of records. */
    int32_t count;

    DurationMetric(int64_t total_ms_,
                   int32_t count_)
    : total_ms(std::move(total_ms_))
    , count(std::move(count_))
    {}

    DurationMetric(const DurationMetric& cpy) {
       this->total_ms = cpy.total_ms;
       this->count = cpy.count;
    }

    DurationMetric() = default;


    DurationMetric& operator=(const DurationMetric& cpy) {
       this->total_ms = cpy.total_ms;
       this->count = cpy.count;
       return *this;
    }

    template <class Archive>
    void load(Archive& archive) {
        archive(total_ms, count);
    }

    template <class Archive>
    void save(Archive& archive) const {
        archive(total_ms, count);
    }
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_DURATIONMETRIC_HPP