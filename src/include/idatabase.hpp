#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>

#include <unifieddata.hpp>
#include <connection_types.hpp>


namespace timestamp
{
    class IDatabase
    {
    public:
        IDatabase() {}
        virtual ~IDatabase() {}

        virtual std::string format(const UnifiedData &data,
                                   ConnectionType type = ConnectionType::HTTP_API) const = 0;
    };
}

#endif // IDATABASE_H

