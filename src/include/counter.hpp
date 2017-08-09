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

#ifndef TIMESTAMP_COUNTER_HPP
#define TIMESTAMP_COUNTER_HPP

#include <memory>

#include <cfactory.hpp>
#include <unifieddata.hpp>

namespace timestamp {
enum class CounterType { AGGREGATION, SINGLE_VALUE };

template <class T>
class Counter {
 public:
  Counter(const CounterType type = CounterType::SINGLE_VALUE);
  Counter(const UnifiedData *pattern, std::shared_ptr<CFactory> parent,
          const CounterType type = CounterType::SINGLE_VALUE);
  virtual ~Counter();

  auto value() const noexcept -> T;
  auto value(const T &value) noexcept -> T;

  auto send() -> void;

 private:
  T m_value;
  CounterType m_type;
  UnifiedData m_pattern;
  std::shared_ptr<CFactory> m_parent;
};

template <class T>
Counter<T>::Counter(const CounterType type) : m_type(type) {}

template <class T>
Counter<T>::Counter(const UnifiedData *pattern,
                    std::shared_ptr<CFactory> parent, const CounterType type)
    : Counter{} {
  m_type = type;
  m_pattern = *pattern;
  m_parent = parent;
}

template <class T>
Counter<T>::~Counter() {}

template <class T>
auto Counter<T>::value() const noexcept -> T {
  return m_value;
}

template <class T>
auto Counter<T>::value(const T &value) noexcept -> T {
  switch (m_type) {
    case CounterType::AGGREGATION:
      m_value += value;
      break;

    case CounterType::SINGLE_VALUE:
      m_value = value;
      this->send();

      break;
  }

  return m_value;
}

template <class T>
void Counter<T>::send() {
  // TODO: test if value can be morph to string
  m_pattern.keys({{"value", std::to_string(m_value)}});
  m_value = T();
  m_parent->send(m_pattern);
}
}

#endif  // TIMESTAMP_COUNTER_HPP
