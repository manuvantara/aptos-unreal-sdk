#include "BCSDeserializer.h"

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

// the implementation of the complex types deserialization functions

/**
 * @brief deserialize a vector of a given type
 * @return deserialized vector
 */
template<typename T>
std::vector<T> BCS::BCSDeserializer::deserialize() {
    unsigned int length = deserializeUleb128AsU32();
    std::vector<T> value;
    for(unsigned int i = 0; i < length; i++) {
        value.push_back(deserialize<T>());
    }
    return value;
}

/**
 * @brief deserialize a tuple of a given type
 * @return deserialized tuple
 */
template<typename... T>
std::tuple<T...> BCS::BCSDeserializer::deserialize() {
    return std::make_tuple(deserialize<T>()...);
}



// the implementation of the overloaded functions

template<typename T>
T BCS::BCSDeserializer::deserialize() {
    static_assert(sizeof(T) == -1, "Unsupported type for deserialization");
    // Default deserialization function, generates a compilation error
}

template<>
unsigned char BCS::BCSDeserializer::deserialize<unsigned char>() {
    return deserializeU8();
}

template<>
unsigned short BCS::BCSDeserializer::deserialize<unsigned short>() {
    return deserializeU16();
}

template<>
unsigned int BCS::BCSDeserializer::deserialize<unsigned int>() {
    return deserializeU32();
}

template<>
unsigned long long BCS::BCSDeserializer::deserialize<unsigned long long>() {
    return deserializeU64();
}

template<>
__uint128_t BCS::BCSDeserializer::deserialize<__uint128_t>() {
    return deserializeU128();
}

template<>
std::string BCS::BCSDeserializer::deserialize<std::string>() {
    return deserializeString();
}

template<>
bool BCS::BCSDeserializer::deserialize<bool>() {
    return deserializeBool();
}

template<>
std::vector<unsigned char> BCS::BCSDeserializer::deserialize<std::vector<unsigned char>>() {
    return deserializeBytesVector();
}

template<>
unsigned char* BCS::BCSDeserializer::deserialize<unsigned char*>() {
    return deserializeBytesArray();
}

template<typename T>
T BCS::BCSDeserializer::deserializeFixed(unsigned int size) {
    static_assert(sizeof(T) == -1, "Unsupported type for deserialization");
    // Default deserialization function, generates a compilation error
}

template<>
std::vector<unsigned char> BCS::BCSDeserializer::deserializeFixed<std::vector<unsigned char>>(unsigned int size) {
    return deserializeFixedBytesVector(size);
}

template<>
unsigned char* BCS::BCSDeserializer::deserializeFixed<unsigned char*>(unsigned int size) {
    return deserializeFixedBytesArray(size);
}

