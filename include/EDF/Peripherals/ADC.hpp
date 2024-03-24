/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"

#include <iterator>
#include <cstdint>

namespace EDF {

class ADC {
public:
    enum class Response : uint8_t{
        Ok,
        ErrorBusy,
        ErrorOverrun,
        Error,
        ErrorTimeout,
    };
public:
    virtual ~ADC() = default;
};

class ADCChannel {
public:
    using Response = ADC::Response;
    class ResponseData {
    private:
        Response resp;
        int32_t value;
    public:
        constexpr ResponseData( Response r, int32_t data = 0 ) : resp(r), value(data) {}
        constexpr Response response() const { return resp; }
        constexpr int32_t data() const {
            EDF_ASSERTD( response() == Response::Ok, "Response must be Ok to extract value");
            return value;
        }
        /* implicitly convert to a Response. Need to call data() explicitly to obtain value */
        constexpr operator Response () const { return response(); }
    };
    using Callback = void (*)(void* self, ResponseData value);
public:
    virtual ~ADCChannel() = default;
    virtual Response start( const Callback& cb = Callback() ) = 0;
    virtual ResponseData getSingleConversion() = 0;
};

class ADCScanGroup {
public:
    using Response = ADC::Response;
    class ResponseData {
    public:
        using Iterator = int32_t*;
        using ConstIterator = const int32_t*;
        using ReverseIterator = std::reverse_iterator<Iterator>;
        using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
    private:
        Response resp;
        int32_t* values;
        std::size_t n;
    public:
        constexpr ResponseData( Response r, int32_t* values = nullptr, std::size_t n = 0 ) :
            resp(r), values(values), n(n)
        {}
        constexpr Response response()                       const { return resp; }
        constexpr int32_t* data() const {
            EDF_ASSERTD( response() == Response::Ok, "Response must be Ok to extract value");
            return values;
        }
        constexpr std::size_t length()                      const { return n; }
        /* implicitly convert to a Response. Need to call data() explicitly to obtain value */
        constexpr operator Response ()                      const { return response(); }

        constexpr Iterator begin()                                { return Iterator( data() ); }
        constexpr ConstIterator begin()                     const { return ConstIterator( data() ); }
        constexpr ConstIterator cbegin()                    const { return ConstIterator( data() ); }

        constexpr Iterator end()                                  { return Iterator( data() + n ); }
        constexpr ConstIterator end()                       const { return ConstIterator( data() + n ); }
        constexpr ConstIterator cend()                      const { return ConstIterator( data() + n ); }

        constexpr ReverseIterator rbegin()                        { return ReverseIterator( end() ); }
        constexpr ConstReverseIterator rbegin()             const { return ConstReverseIterator( end() ); }
        constexpr ConstReverseIterator crbegin()            const { return ConstReverseIterator( end() ); }

        constexpr ReverseIterator rend()                          { return ReverseIterator( begin() ); }
        constexpr ConstReverseIterator rend()               const { return ConstReverseIterator( begin() ); }
        constexpr ConstReverseIterator crend()              const { return ConstReverseIterator( begin() ); }
    };
    using Callback = void (*)(void* self, ResponseData values);
public:
    virtual ~ADCScanGroup() = default;
    virtual Response start( const Callback& cb = Callback() ) = 0;
    virtual Response getSamples( const Callback& cb ) = 0;
};

} /* EDF */