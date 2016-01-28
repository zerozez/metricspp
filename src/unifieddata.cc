#include <string>
#include <chrono>

#include <unifieddata.hpp>


namespace timestamp
{

    using namespace std::chrono;

    UnifiedData::UnifiedData()
        : m_db("")
        , m_measurement("")
        , m_tags()
        , m_keys()
    {
        this->restamp();
    }

    UnifiedData::UnifiedData(const std::string &measurement, const StringKeyValue &keys,
                           const StringKeyValue &tags, const std::string &db)
        : UnifiedData{}
    {
        m_db = db;
        m_measurement = measurement;
        m_tags = tags;
        m_keys = keys;
    }

    UnifiedData::~UnifiedData()
    {}

    auto UnifiedData::db() const -> std::string
    {
        return m_db;
    }

    auto UnifiedData::measurement() const -> std::string
    {
        return m_measurement;
    }

    auto UnifiedData::tags() const -> StringKeyValue
    {
        return m_tags;
    }

    auto UnifiedData::keys() const -> StringKeyValue
    {
        return m_keys;
    }

    auto UnifiedData::timestamp() const -> long long
    {
        return m_stamp;
    }

    void UnifiedData::keys(const std::map<std::string, std::string> &keys)
    {
        m_keys.clear();
        m_keys.insert(keys.begin(), keys.end());
        this->restamp();
    }

    auto UnifiedData::restamp() -> void
    {
        m_stamp = system_clock::now().time_since_epoch().count();
    }
}

