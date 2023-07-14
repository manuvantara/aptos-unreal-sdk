#include <BCSSerializer.h>

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
void BCS::BCSSerializer::serealizeU8(unsigned char value) {
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