/*
 * Copyright (c) 2024, Adam Veazey
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "EDF/Peripherals/I2CController.hpp"

#include <queue>
#include <vector>

class I2CControllerMock : public EDF::I2CController {
public:
    class MockResponse {
    private:
        Response response;
        std::vector<uint8_t> dataOut;
    public:
        MockResponse(
            Response response,
            std::initializer_list<uint8_t> data = {}
        ) :
            response(response),
            dataOut(data)
        {}
        void copyDataOut( uint8_t* data, std::size_t expectedLen );
        Response getResponse() const { return response; }
    };
private:
    std::queue<MockResponse> responses;
public:
    void addResponse(
        Response response,
        std::initializer_list<uint8_t> data = {}
    ) { responses.emplace(response, data); }

    Response transfer(
        uint8_t address_7bit,
        const uint8_t* txData = nullptr, std::size_t txLen = 0,
        uint8_t* rxData = nullptr, std::size_t rxLen = 0
    ) override;
};