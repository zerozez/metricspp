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

