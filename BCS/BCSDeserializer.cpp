#include <BCSDeserializer.h>

BCS::BCSDeserializer::BCSDeserializer(std::vector<uint8_t> buffer) {
    this->buffer = buffer;
    index = 0;
}

BCS::BCSDeserializer::~BCSDeserializer() {
}

// the implementation of the deserealiazation functions

/**
 * @brief deserialize an 8 bit unsigned integer
 * @return deserialized integer
 */
unsigned char BCS::BCSDeserializer::deserializeU8() {
    return buffer[index++];
}

/**
 * @brief deserialize a 16 bit unsigned integer
 * @return deserialized integer
 */
unsigned short BCS::BCSDeserializer::deserializeU16() {
    unsigned short value = 0;
    value |= buffer[index++];
    value |= buffer[index++] << 8;
    return value;
}

/**
 * @brief deserialize a 32 bit unsigned integer
 * @return deserialized integer
 */
unsigned int BCS::BCSDeserializer::deserializeU32() {
    unsigned int value = 0;
    value |= buffer[index++];
    value |= buffer[index++] << 8;
    value |= buffer[index++] << 16;
    value |= buffer[index++] << 24;
    return value;
}

/**
 * @brief deserialize a 64 bit unsigned integer
 * @return deserialized integer
 */
unsigned long long BCS::BCSDeserializer::deserializeU64() {
    unsigned long long value = 0;
    for(int i = 0; i < 8; i++) {
        value |= (unsigned long long)buffer[index++] << (i * 8);
    }
    return value;
}

/**
 * @brief deserialize a 128 bit unsigned integer
 * @return deserialized integer
 */
__uint128_t BCS::BCSDeserializer::deserializeU128() {
    __uint128_t value = 0;
    for(int i = 0; i < 16; i++) {
        value |= (__uint128_t)buffer[index++] << (i * 8);
    }
    return value;
}

/**
 * @brief deserialize a string
 * @return deserialized string
 */
std::string BCS::BCSDeserializer::deserializeString() {
    unsigned int length = deserializeU32();
    std::string value(buffer.begin() + index, buffer.begin() + index + length);
    index += length;
    return value;
}

/**
 * @brief deserialize a boolean
 * @return true if the value is 1, false otherwise
 */
bool BCS::BCSDeserializer::deserializeBool() {
    return deserializeU8() == 1;
}