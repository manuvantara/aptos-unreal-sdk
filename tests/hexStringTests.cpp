#include "../lib/catch.hpp"

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#endif

#include "../utils/hex_string.h"

// test the HexString functions
TEST_CASE("HexString", "[HexString]") {
    SECTION("fromBuffer") {
        std::vector<uint8_t> buffer = {0x01, 0x02, 0x03, 0x04};
        HexString hexString = HexString::fromBuffer(buffer);
        REQUIRE(hexString.hex() == "0x01020304");
    }

    SECTION("fromUint8Array") {
        std::vector<uint8_t> arr = {0x01, 0x02, 0x03, 0x04};
        HexString hexString = HexString::fromUint8Array(arr);
        REQUIRE(hexString.hex() == "0x01020304");
    }

    SECTION("ensure") {
        HexString hexString = HexString::ensure("0x01020304");
        REQUIRE(hexString.hex() == "0x01020304");
    }

    SECTION("constructor") {
        HexString hexString = HexString("0x01020304");
        REQUIRE(hexString.hex() == "0x01020304");
    }

    SECTION("noPrefix") {
        HexString hexString = HexString("0x01020304");
        REQUIRE(hexString.noPrefix() == "01020304");
    }

    SECTION("toShortString") {
        HexString hexString = HexString("0x0001020304");
        REQUIRE(hexString.toShortString() == "0x1020304");
    }

    SECTION("toUint8Array") {
        HexString hexString = HexString("0x01020304");
        std::vector<uint8_t> arr = hexString.toUint8Array();
        REQUIRE(arr[0] == 0x01);
        REQUIRE(arr[1] == 0x02);
        REQUIRE(arr[2] == 0x03);
        REQUIRE(arr[3] == 0x04);
    }
}