/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Assert.hpp"

#include <cstdint>

namespace EDF {

class SPIController {
public:
    enum class Response : uint8_t{
        Ok,
        ErrorBusy,
        ErrorOverrun,
        Error,
        ErrorTimeout,
    };
    class ResponseData {
    private:
        uint16_t value;
    public:
        constexpr ResponseData( Response r, uint8_t data = 0 ) :
            value(
                static_cast<uint16_t>((static_cast<uint16_t>(r) << 8)) |
                data
            )
        {}
        constexpr Response response() const {
            return static_cast<Response>(value >> 8);
        }
        constexpr uint8_t data() const {
            EDF_ASSERTD( response() == Response::Ok, "Response must be Ok to extract value");
            return static_cast<uint8_t>(value);
        }
        /* implicitly convert to a Response. Need to call data() explicitly to obtain value */
        constexpr operator Response () const { return response(); }
    };
public:
    virtual ~SPIController() = default;
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual ResponseData transfer( uint8_t data ) = 0;
    virtual Response transfer( uint8_t* dataInOut, std::size_t n ) = 0;
};

} /* EDF */