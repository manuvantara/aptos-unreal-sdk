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
    unsigned int length = deserializeUleb128AsU32();
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

/**
 * @brief deserialize a 32 bit unsigned integer encoded as a uleb128
 * @return deserialized integer
 */
unsigned int BCS::BCSDeserializer::deserializeUleb128AsU32() {
    unsigned int value = 0;
    unsigned int shift = 0;
    unsigned char byte = 0x80;
    while(byte & 0x80) {
        byte = deserializeU8();
        value |= (byte & 0x7F) << shift;
        shift += 7;
    }
    return value;
}

/**
 * @brief deserialize a vector of bytes
 * @return deserialized vector
 */
std::vector<unsigned char> BCS::BCSDeserializer::deserializeBytesVector() {
    unsigned int length = deserializeUleb128AsU32();
    std::vector<unsigned char> value(buffer.begin() + index, buffer.begin() + index + length);
    index += length;
    return value;
}

/**
 * @brief deserialize an array of bytes
 * @return deserialized array
 */
unsigned char* BCS::BCSDeserializer::deserializeBytesArray() {
    unsigned int length = deserializeUleb128AsU32();
    unsigned char* value = new unsigned char[length];
    for(unsigned int i = 0; i < length; i++) {
        value[i] = buffer[index++];
    }
    return value;
}

/**
 * @brief deserialize a vector of bytes of a fixed size
 * @param size
 * @return deserialized vector
 */
std::vector<unsigned char> BCS::BCSDeserializer::deserializeFixedBytesVector(unsigned int size) {
    std::vector<unsigned char> value(buffer.begin() + index, buffer.begin() + index + size);
    index += size;
    return value;
}

/**
 * @brief deserialize an array of bytes of a fixed size
 * @param size
 * @return deserialized array
 */
unsigned char* BCS::BCSDeserializer::deserializeFixedBytesArray(unsigned int size) {
    unsigned char* value = new unsigned char[size];
    for(unsigned int i = 0; i < size; i++) {
        value[i] = buffer[index++];
    }
    return value;
}