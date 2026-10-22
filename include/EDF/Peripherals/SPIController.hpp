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
    // tag::spi_controller_response[]
    enum class Response : std::uint8_t{
        Ok,
        ErrorBusy,
        ErrorOverrun,
        Error,
        ErrorTimeout,
    };
    // end::spi_controller_response[]
    // tag::spi_controller_response_data[]
    class ResponseData {
    private:
        std::uint16_t value;
    public:
        constexpr ResponseData( Response r, std::uint8_t data ) :
            value(
                static_cast<std::uint16_t>((static_cast<std::uint16_t>(r) << 8)) |
                data
            )
        {}
        constexpr Response response() const {
            return static_cast<Response>(value >> 8);
        }
        constexpr std::uint8_t data() const {
            EDF_ASSERTD( response() == Response::Ok, "Response must be Ok to extract value");
            return static_cast<std::uint8_t>(value);
        }
        /* implicitly convert to a Response. Need to call data() explicitly to obtain value */
        constexpr operator Response () const { return response(); }
    };
    // end::spi_controller_response_data[]
public:
    virtual ~SPIController() = default;
    virtual void select() = 0;
    virtual void deselect() = 0;
    virtual ResponseData transfer( std::uint8_t data ) = 0;
    virtual Response transfer( std::uint8_t* dataInOut, std::size_t n ) = 0;
};

} /* EDF */