/*
 *
 * DurationsMap.hpp
 * ledger-core
 *
 * Created by Pierre Pollastri on 23/12/2020.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Ledger
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

#ifndef LEDGER_CORE_DURATIONSMAP_HPP
#define LEDGER_CORE_DURATIONSMAP_HPP

#include <api/DurationMetric.hpp>
#include <chrono>
#include <mutex>
#include <unordered_map>

namespace ledger {
    namespace core {
        class DurationsMap {
          public:
            void record(const std::string &name,
                        const std::chrono::high_resolution_clock::duration &duration);
            const std::unordered_map<std::string, api::DurationMetric> &getMetrics();

            static DurationsMap &getInstance();

          private:
            std::unordered_map<std::string, api::DurationMetric> _metrics;
            std::mutex _mutex;
        };
    } // namespace core
} // namespace ledger

#endif // LEDGER_CORE_DURATIONSMAP_HPP
