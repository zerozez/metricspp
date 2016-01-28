#ifndef UNIFIEDDATA_HPP
#define UNIFIEDDATA_HPP

#include <map>


namespace timestamp
{
    using StringKeyValue = std::map<std::string, std::string>;

    class UnifiedData
    {
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
        long long       m_stamp;
        std::string     m_db;
        std::string     m_measurement;
        StringKeyValue  m_tags;
        StringKeyValue  m_keys;

        auto restamp() -> void;
    };
}
#endif // UNIFIEDDATA_HPP

