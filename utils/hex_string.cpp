#include "hex_string.h"

/** 
 * @brief Convert a vector of bytes to a hex string
 * 
 * @param buffer The vector of bytes to convert
*/
HexString HexString::fromBuffer(const std::vector<uint8_t>& buffer) {
    return HexString::fromUint8Array(buffer);
}

/** 
 * @brief Convert a vector of bytes to a hex string
 * 
 * @param arr The vector of bytes to convert
*/
HexString HexString::fromUint8Array(const std::vector<uint8_t>& arr) {
    std::string hexStr;
    for (const uint8_t& byte : arr) {
        char hexByte[3];
        sprintf(hexByte, "%02x", byte);
        hexStr += hexByte;
    }
    return HexString(hexStr);
}

HexString HexString::ensure(const std::string& hexString) {
    if (hexString.substr(0, 2) == "0x") {
        return HexString(hexString);
    }
    return HexString("0x" + hexString);
}

/**
 * Creates new HexString instance from regular string. If specified string already starts with "0x" prefix,
 * it will not add another one
*/
HexString::HexString(const std::string& hexString){
    if (hexString.substr(0, 2) == "0x") {
        this->hexString = hexString;
    } else {
        this->hexString = "0x" + hexString;
    }
}

/**
 * Creates new HexString instance from uint8 vector
 * 
 * @param arr The uint8 vector to convert
*/
HexString::HexString(const std::vector<uint8_t>& arr) {
    hexString = "0x";
    for (const uint8_t& byte : arr) {
        char hexByte[3];
        sprintf(hexByte, "%02x", byte);
        hexString += hexByte;
    }
}

/**
 * @brief Get the hex string
 * 
 * @return std::string The hex string
*/
std::string HexString::hex() const {
    return hexString;
}

/**
 * @brief Get the hex string without the "0x" prefix
 * 
 * @return std::string The hex string without the "0x" prefix
*/
std::string HexString::noPrefix() const {
    return hexString.substr(2);
}

/**
 * @brief Get the hex string without the leading zeros
 * 
 * @return std::string The hex string without the leading zeros
*/
std::string HexString::toShortString() const {
    size_t pos = 2;
    while (pos < hexString.length() && hexString[pos] == '0') {
        ++pos;
    }
    return "0x" + hexString.substr(pos);
}

/**
 * @brief Get the hex string as a vector of bytes
 * 
 * @return std::vector<uint8_t> The hex string as a vector of bytes
*/
std::vector<uint8_t> HexString::toUint8Array() const {
    std::vector<uint8_t> bytes;
    size_t pos = 2;
    while (pos < hexString.length()) {
        uint8_t byte = static_cast<uint8_t>(std::stoi(hexString.substr(pos, 2), nullptr, 16));
        bytes.push_back(byte);
        pos += 2;
    }
    return bytes;
}
