/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Petr Orlov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <chrono>
#include <string>

#include <unifieddata.hpp>

namespace timestamp {

using namespace std::chrono;

UnifiedData::UnifiedData() : m_db(""), m_measurement(""), m_tags(), m_keys() {
  this->restamp();
}

UnifiedData::UnifiedData(const std::string &measurement,
                         const StringKeyValue &keys, const StringKeyValue &tags,
                         const std::string &db)
    : UnifiedData{} {
  m_db = db;
  m_measurement = measurement;
  m_tags = tags;
  m_keys = keys;
}

UnifiedData::~UnifiedData() {}

auto UnifiedData::db() const -> std::string { return m_db; }

auto UnifiedData::measurement() const -> std::string { return m_measurement; }

auto UnifiedData::tags() const -> StringKeyValue { return m_tags; }

auto UnifiedData::keys() const -> StringKeyValue { return m_keys; }

auto UnifiedData::timestamp() const -> long long { return m_stamp; }

void UnifiedData::keys(const std::map<std::string, std::string> &keys) {
  m_keys.clear();
  m_keys.insert(keys.begin(), keys.end());
  this->restamp();
}

auto UnifiedData::restamp() -> void {
  m_stamp = duration_cast<nanoseconds>(system_clock::now().time_since_epoch())
                .count();
}
}
