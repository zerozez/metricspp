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

#ifndef CFACTORY_HPP
#define CFACTORY_HPP

#include <map>
#include <string>
#include <memory>

#include <unifieddata.hpp>


/**
 * Pre-registered connection is influx.upd by string value
 */
namespace timestamp
{
    class IDatabase;
    class Connection;

    template<class T> class Counter;


    class CFactory : public std::enable_shared_from_this<CFactory>
    {
    public:
        virtual ~CFactory();

        template<class ... T>
        static std::shared_ptr<CFactory> create( T&& ... input);

        auto registerConnection(const std::string &regName,
                                const IDatabase *db,
                                const Connection *connection) -> void;


        auto setupConnection(const std::string &address,
                             const int port,
                             const std::string &regName) -> void;

        template<class T>
        auto counter(const std::string &measurement,
                     const std::map<std::string, std::string> tags = {},
                     const std::string &db = "internal"
                     ) -> std::shared_ptr<Counter<T> >;

    private:
        std::map<std::string, std::string>  m_regs;

        std::shared_ptr<IDatabase>          m_db;
        std::shared_ptr<Connection>         m_connect;

    private:
        CFactory();
        CFactory(const CFactory &f) = default;

        auto send(const UnifiedData &data) -> void;


        template<class T>
        friend class Counter;
    };

    template<class ... T>
    std::shared_ptr<CFactory> CFactory::create( T&& ... input)
    {
        return std::shared_ptr<CFactory>(new CFactory(std::forward<T>(input)...));
    }

    template<class T>
    auto CFactory::counter(const std::string &measurement,
                           const std::map<std::string, std::string> tags,
                           const std::string &db
                 ) -> std::shared_ptr<Counter<T> >
    {
        return std::shared_ptr<Counter<T> >(
                    new Counter<T>(new UnifiedData(measurement, {}, tags, db),
                                   shared_from_this()));
    }
}

#endif // CFACTORY_HPP

