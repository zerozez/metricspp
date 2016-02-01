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
 */

#include <stdexcept>

#include "influxdb.h"


namespace timestamp
{
    InfluxDB::InfluxDB()
        : IDatabase()
    {

    }

    InfluxDB::~InfluxDB()
    {

    }

    auto InfluxDB::format(const UnifiedData &data,
                          ConnectionType type) const -> std::string
    {
        std::string formatted = "";

        switch (type) {
        case ConnectionType::UDP:
            // FIXME: unified to influx line format
            formatted = data.measurement();

            for(auto &tag: data.tags())
            {
                formatted.append( "," + tag.first + "=" + tag.second);
            }

            formatted.append(" ");

            for(auto &key: data.keys())
            {
                if(*data.keys().begin() != key)
                {
                    formatted.append(",");
                }

                formatted.append(key.first + "=" + key.second);
            }

            formatted.append(" ");

            formatted.append( std::to_string(data.timestamp()));
            break;

        case ConnectionType::HTTP_API:
            // FIXME: currently is not set
            formatted = "";
            //break;

        default:
            throw std::invalid_argument("[InfluxDB] format is not exists");
        }

        return formatted;
    }
}

