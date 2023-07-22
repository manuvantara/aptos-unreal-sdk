#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#include "../lib/catch.hpp"

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#endif

#include "../BCS/BCSSerializer.h"
#include "../BCS/BCSDeserializer.h"

using namespace BCS;

// testing the BCS functions
TEST_CASE("BCS UInt", "[BCS]") {
    BCS::BCSSerializer serializer;
    BCS::BCSDeserializer deserializer(serializer.getBuffer());

    SECTION("Unsigned Integers") {
        serializer.serializeU8(0x01);
        serializer.serializeU16(0x0203);
        serializer.serializeU32(0x04050607);
        serializer.serializeU64(0x08090A0B0C0D0E0F);
        serializer.serializeU128(0x08090A0B0C0D0E0F);
        std::string str = "Hello World!";
        serializer.serializeString(str);
        serializer.serializeBool(true);
        serializer.serializeU32AsUleb128(0x04030201);
        std::vector<unsigned char> bytesVector = {0x01, 0x02, 0x03, 0x04};
        serializer.serializeBytes(bytesVector);
        unsigned char bytesArray[] = {0x05, 0x06, 0x07, 0x08};
        serializer.serializeBytes(bytesArray, 4);
        std::vector<unsigned char> fixedBytesVector = {0x09, 0x0A, 0x0B, 0x0C};
        serializer.serializeFixedBytes(fixedBytesVector);
        unsigned char fixedBytesArray[] = {0x0D, 0x0E, 0x0F, 0x10};
        serializer.serializeFixedBytes(fixedBytesArray, 4);

        deserializer.updateBuffer(serializer.getBuffer());
        // assert that the data is correct
        REQUIRE(deserializer.deserializeU8() == 0x01);
        REQUIRE(deserializer.deserializeU16() == 0x0203);
        REQUIRE(deserializer.deserializeU32() == 0x04050607);
        REQUIRE(deserializer.deserializeU64() == 0x08090A0B0C0D0E0F);
        REQUIRE(deserializer.deserializeU128() == 0x08090A0B0C0D0E0F);
        REQUIRE(deserializer.deserializeString() == "Hello World!");
        REQUIRE(deserializer.deserializeBool() == true);
        REQUIRE(deserializer.deserializeUleb128AsU32() == 0x04030201);
        REQUIRE(deserializer.deserializeBytesVector() == bytesVector);
        unsigned char* bytesArray2 = deserializer.deserializeBytesArray();
        REQUIRE(bytesArray2[0] == 0x05);
    }
}

TEST_CASE("BCS Str Bool Uleb", "[BCS]") {
    BCS::BCSSerializer serializer;
    BCS::BCSDeserializer deserializer(serializer.getBuffer());

    SECTION("String, Bool, Uleb128") {
        serializer.clearBuffer();

        std::string str = "Hello World!";
        serializer.serializeString(str);
        serializer.serializeBool(true);
        serializer.serializeU32AsUleb128(0x04030201);

        deserializer.updateBuffer(serializer.getBuffer());
        REQUIRE(deserializer.deserializeString() == "Hello World!");
        REQUIRE(deserializer.deserializeBool() == true);
        REQUIRE(deserializer.deserializeUleb128AsU32() == 0x04030201);
    }
}

TEST_CASE("BCS Byte arrays", "[BCS]") {
    BCS::BCSSerializer serializer;
    BCS::BCSDeserializer deserializer(serializer.getBuffer());

    SECTION("Byte arrays") {
        serializer.clearBuffer();

        std::vector<unsigned char> bytesVector = {0x01, 0x02, 0x03, 0x04};
        serializer.serializeBytes(bytesVector);
        unsigned char bytesArray[] = {0x05, 0x06, 0x07, 0x08};
        serializer.serializeBytes(bytesArray, 4);
        std::vector<unsigned char> fixedBytesVector = {0x09, 0x0A, 0x0B, 0x0C};
        serializer.serializeFixedBytes(fixedBytesVector);
        unsigned char fixedBytesArray[] = {0x0D, 0x0E, 0x0F, 0x10};
        serializer.serializeFixedBytes(fixedBytesArray, 4);

        deserializer.updateBuffer(serializer.getBuffer());
        REQUIRE(deserializer.deserializeBytesVector() == bytesVector);
        unsigned char* bytesArray2 = deserializer.deserializeBytesArray();
        REQUIRE(bytesArray2[0] == 0x05);
        REQUIRE(bytesArray2[1] == 0x06);
        REQUIRE(bytesArray2[2] == 0x07);
        REQUIRE(bytesArray2[3] == 0x08);
        REQUIRE(deserializer.deserializeFixedBytesVector(4) == fixedBytesVector);
        unsigned char* fixedBytesArray2 = deserializer.deserializeFixedBytesArray(4);
        REQUIRE(fixedBytesArray2[0] == 0x0D);
        REQUIRE(fixedBytesArray2[1] == 0x0E);
        REQUIRE(fixedBytesArray2[2] == 0x0F);
        REQUIRE(fixedBytesArray2[3] == 0x10);
    }
}

TEST_CASE("BCS Complex types", "[BCS]") {
    BCS::BCSSerializer serializer;
    BCS::BCSDeserializer deserializer(serializer.getBuffer());

    SECTION("Complex types") {
        serializer.clearBuffer();

        std::vector<unsigned int> vector2 = {0x01, 0x02, 0x03, 0x323, 0x0311};
        serializer.serialize<unsigned int>(vector2);

        std::tuple<unsigned int, unsigned int, std::string> tuple = {0x04, 0x05, "test"};
        serializer.serialize(tuple);

        enum class TestEnum : unsigned int {
            TEST1 = 0x01,
            TEST2 = 0x02,
            TEST3 = 0x03
        };

        serializer.serializeEnum<TestEnum>(TestEnum::TEST2);

        deserializer.updateBuffer(serializer.getBuffer());

        std::vector<unsigned int> vector3 = deserializer.deserializeVector<unsigned int>();
        REQUIRE(vector3 == vector2);
        
        std::tuple tuple3 = deserializer.deserializeTuple<unsigned int, unsigned int, std::string>();
        REQUIRE(std::get<0>(tuple3) == 0x04);
        REQUIRE(std::get<1>(tuple3) == 0x05);
        REQUIRE(std::get<2>(tuple3) == "test");

        TestEnum testEnum = deserializer.deserializeEnum<TestEnum>();
        REQUIRE(testEnum == TestEnum::TEST2);
    }
}