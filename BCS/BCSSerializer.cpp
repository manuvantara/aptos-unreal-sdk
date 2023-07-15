#include "BCSSerializer.h"

BCS::BCSSerializer::BCSSerializer() {
    buffer = std::vector<uint8_t>();
}

BCS::BCSSerializer::~BCSSerializer() {
}

// the implementation of the serealiazation functions

/**
 * @brief serialize an 8 bit unsigned integer
 * @param value
 */
void BCS::BCSSerializer::serializeU8(unsigned char value) {
    buffer.push_back(value);
}

/**
 * @brief serialize a 16 bit unsigned integer
 * @param value
 */
void BCS::BCSSerializer::serializeU16(unsigned short value) {
    buffer.push_back(value & 0xFF);
    buffer.push_back((value >> 8) & 0xFF);
}

/**
 * @brief serialize a 32 bit unsigned integer
 * @param value
 */
void BCS::BCSSerializer::serializeU32(unsigned int value) {
    buffer.push_back(value & 0xFF);
    buffer.push_back((value >> 8) & 0xFF);
    buffer.push_back((value >> 16) & 0xFF);
    buffer.push_back((value >> 24) & 0xFF);
}

/**
 * @brief serialize a 64 bit unsigned integer
 * @param value
 */
void BCS::BCSSerializer::serializeU64(unsigned long long value) {
    for(int i = 0; i < 8; i++) {
        buffer.push_back((value >> (i * 8)) & 0xFF);
    }
}

/**
 * @brief serialize a 128 bit unsigned integer
 * @param value
 */
void BCS::BCSSerializer::serializeU128(__uint128_t value) {
    for(int i = 0; i < 16; i++) {
        buffer.push_back((value >> (i * 8)) & 0xFF);
    }
}

/**
 * @brief serialize a string
 * @param value
 */
void BCS::BCSSerializer::serializeString(std::string& value) {
    serializeU32AsUleb128(value.size());
    buffer.insert(buffer.end(), value.begin(), value.end());
}

/**
 * @brief serialize a boolean
 * @param value
 */
void BCS::BCSSerializer::serializeBool(bool value) {
    buffer.push_back(value ? 1 : 0);
}

/**
 * @brief serialize a 32 bit unsigned integer as a ULEB128
 * @param value
 */
void BCS::BCSSerializer::serializeU32AsUleb128(unsigned int value) {
    do {
        unsigned char byte = value & 0x7F;
        value >>= 7;
        if(value != 0) {
            byte |= 0x80;
        }
        buffer.push_back(byte);
    } while(value != 0);
}

/**
 * @brief serialize a vector of bytes
 * @param value
 */
void BCS::BCSSerializer::serializeBytes(std::vector<unsigned char>& value) {
    serializeU32AsUleb128(value.size());
    buffer.insert(buffer.end(), value.begin(), value.end());
}

/**
 * @brief serialize a byte array
 * @param value
 * @param size
 */
void BCS::BCSSerializer::serializeBytes(unsigned char* value, unsigned int size) {
    serializeU32AsUleb128(size);
    buffer.insert(buffer.end(), value, value + size);
}

/**
 * @brief serialize a vector of bytes without the length (if the length is known)
 * @param value
 */
void BCS::BCSSerializer::serializeFixedBytes(std::vector<unsigned char>& value) {
    buffer.insert(buffer.end(), value.begin(), value.end());
}

/**
 * @brief serialize a byte array without the length (if the length is known)
 * @param value
 * @param size
 */
void BCS::BCSSerializer::serializeFixedBytes(unsigned char* value, unsigned int size) {
    buffer.insert(buffer.end(), value, value + size);
}

// the implementation of the complex types serialization functions

/**
 * @brief serialize a vector of any type
 * @param value
 */
template<typename T>
void BCS::BCSSerializer::serialize(std::vector<T>& value) {
    serializeU32AsUleb128(value.size());
    for(auto& element : value) {
        serialize(element);
    }
}

/**
 * @brief serialize a tuple of any type
 * @param value
 */
template<typename... T>
void BCS::BCSSerializer::serialize(std::tuple<T...>& value) {
    std::apply([&](auto&&... args) { (serialize(args), ...); }, value);
}
