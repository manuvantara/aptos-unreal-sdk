#include "BCSSerializer.h"
#include "BCSDeserializer.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; else std::cout << __FUNCTION__ << " passed on line " << __LINE__ << std::endl; }

int main() {

    // insert test data
    BCS::BCSSerializer serializer;
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

    BCS::BCSDeserializer deserializer(serializer.getBuffer());
    // assert that the data is correct
    IS_TRUE(deserializer.deserializeU8() == 0x01);
    IS_TRUE(deserializer.deserializeU16() == 0x0203);
    IS_TRUE(deserializer.deserializeU32() == 0x04050607);
    IS_TRUE(deserializer.deserializeU64() == 0x08090A0B0C0D0E0F);
    IS_TRUE(deserializer.deserializeU128() == 0x08090A0B0C0D0E0F);
    IS_TRUE(deserializer.deserializeString() == "Hello World!");
    IS_TRUE(deserializer.deserializeBool() == true);
    IS_TRUE(deserializer.deserializeUleb128AsU32() == 0x04030201);
    IS_TRUE(deserializer.deserializeBytesVector() == bytesVector);
    unsigned char* bytesArray2 = deserializer.deserializeBytesArray();
    IS_TRUE(bytesArray2[0] == 0x05);
    IS_TRUE(bytesArray2[1] == 0x06);
    IS_TRUE(bytesArray2[2] == 0x07);
    IS_TRUE(bytesArray2[3] == 0x08);
    IS_TRUE(deserializer.deserializeFixedBytesVector(4) == fixedBytesVector);
    unsigned char* fixedBytesArray2 = deserializer.deserializeFixedBytesArray(4);
    IS_TRUE(fixedBytesArray2[0] == 0x0D);
    IS_TRUE(fixedBytesArray2[1] == 0x0E);
    IS_TRUE(fixedBytesArray2[2] == 0x0F);
    IS_TRUE(fixedBytesArray2[3] == 0x10);

    // test complex types
    // std::vector<unsigned int> bytesVector2 = {0x01020304, 0x05060708, 0x090A0B0C};
    // serializer.serialize<unsigned int>(bytesVector2);
    // IS_TRUE(deserializer.deserializeVector<unsigned int>() == bytesVector2);
    
    // std::tuple<unsigned int, unsigned int, unsigned int> bytesTuple = {0x01020304, 0x05060708, 0x090A0B0C};
    // serializer.serialize(bytesTuple);
    // std::tuple tuple2 = deserializer.deserializeTuple<unsigned int, unsigned int, unsigned int>();
    // IS_TRUE(std::get<0>(tuple2) == 0x01020304);
    // IS_TRUE(std::get<1>(tuple2) == 0x05060708);
    // IS_TRUE(std::get<2>(tuple2) == 0x090A0B0C);
}