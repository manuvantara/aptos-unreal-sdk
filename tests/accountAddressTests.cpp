#include "../lib/catch.hpp"

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#endif

#include "../aptos_types/account_address.h"
#include "../BCS/BCSSerializer.h"
#include "../BCS/BCSDeserializer.h"

#include <vector>

// test the AccountAddress functions
TEST_CASE("AccountAddress", "[AccountAddress]") {
    SECTION("fromHex") {
        AccountAddress address = AccountAddress::fromHex("0x01020304");
        REQUIRE(address.toHexString() == "0x0000000000000000000000000000000000000000000000000000000001020304");
    }

    SECTION("isValid") {
        REQUIRE(AccountAddress::isValid("0x01020304"));
        REQUIRE(AccountAddress::isValid("01020304"));
    }

    SECTION("toHexString") {
        AccountAddress address = AccountAddress::fromHex("0x01020304");
        REQUIRE(address.toHexString() == "0x0000000000000000000000000000000000000000000000000000000001020304");
    }

    SECTION("serialize/deserialize") {
        AccountAddress address = AccountAddress::fromHex("0x01020304");
        BCS::BCSSerializer serializer;
        address.serialize(serializer);
        std::vector<uint8_t> buffer = serializer.getBuffer();

        BCS::BCSDeserializer deserializer(buffer);
        AccountAddress deserializedAddress = AccountAddress::deserialize(deserializer);
        REQUIRE(deserializedAddress.toHexString() == "0x0000000000000000000000000000000000000000000000000000000001020304");
    }

    SECTION("standardizeAddress") {
        REQUIRE(AccountAddress::standardizeAddress("0x01020304") == "0x0000000000000000000000000000000000000000000000000000000001020304");
        REQUIRE(AccountAddress::standardizeAddress("01020304") == "0x0000000000000000000000000000000000000000000000000000000001020304");
    }

    SECTION("constructor") {
        // 32 byte address
        std::vector<uint8_t> buffer = {0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x00, 
                                       0x00, 0x00, 0x00, 0x01, 
                                       0x02, 0x03, 0x04, 0x05};
        AccountAddress address = AccountAddress(buffer);
        REQUIRE(address.toHexString() == "0x0000000000000000000000000000000000000000000000000000000102030405");
    }
}