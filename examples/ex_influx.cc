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

#include <metricspp/metricspp.hpp>

int main(int argc, char** argv) {
  auto ms = metricspp::create_connection("http://127.0.0.1:8086/write?db=test",
                                         metricspp::Tag{"server", "server01"},
                                         metricspp::Tag{"region", "eu-east"});

  // Simple usage with different measurements
  ms << "eth0" << 53;

  // Add custom values
  ms << "eth1"
     << "load"
     << "41"
     << "ploss" << 41221;

  auto param1 = metricspp::create_measurement("cpu");
  auto param2 = metricspp::create_measurement("ssd", "sda", "sdb", "sdc");

  ms << param1 << 0.92;  // automatic sends value=0.92

  ms << param2 << 15.4 << 123.3 << 19.31;  // Fill-up all values
  ms << param2 << 15.4 << 123.3;           // Fill all excepct last one

  ms << param2 << "sdc" << 1.3 << "sda" << 3.3;  // Fill  only specified values

  return 0;
}
