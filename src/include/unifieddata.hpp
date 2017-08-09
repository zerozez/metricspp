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

#ifndef UNIFIEDDATA_HPP
#define UNIFIEDDATA_HPP

#include <map>

namespace timestamp {
using StringKeyValue = std::map<std::string, std::string>;

class UnifiedData {
 public:
  UnifiedData();
  UnifiedData(const std::string &measurement,
              const StringKeyValue &keys = StringKeyValue(),
              const StringKeyValue &tags = StringKeyValue(),
              const std::string &db = std::string());

  virtual ~UnifiedData();

  auto db() const -> std::string;
  auto measurement() const -> std::string;
  auto tags() const -> StringKeyValue;
  auto keys() const -> StringKeyValue;
  auto timestamp() const -> long long;

  auto keys(const std::map<std::string, std::string> &keys) -> void;

 private:
  long long m_stamp;
  std::string m_db;
  std::string m_measurement;
  StringKeyValue m_tags;
  StringKeyValue m_keys;

  auto restamp() -> void;
};
}
#endif  // UNIFIEDDATA_HPP
