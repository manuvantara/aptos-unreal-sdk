#include "account_address.h"

AccountAddress::AccountAddress(const std::vector<uint8_t>& address)
    : address(address) {
    if (address.size() != LENGTH) {
        throw std::runtime_error("Expected address of length 32");
    }
}

AccountAddress AccountAddress::fromHex(const std::string& addr) {
    // getting the hex string without the "0x" prefix
    std::string address = HexString::ensure(addr).noPrefix();

    // If an address hex has an odd number of digits, pad the hex string with 0
    // e.g. '1aa' would become '01aa'.
    if (address.length() % 2 != 0) {
        address = "0" + address;
    }

    std::vector<uint8_t> addressBytes;
    addressBytes.reserve(LENGTH);

    if (address.length() > LENGTH * 2) {
        throw std::runtime_error("Hex string is too long. Address's length is 32 bytes.");
    }
    else if (address.length() == LENGTH * 2) {
        for (size_t i = 0; i < LENGTH; ++i) {
            addressBytes.push_back(std::stoi(address.substr(i * 2, 2), nullptr, 16));
        }
    }
    else {
        // Pad the address with leading zeros if necessary
        // to ensure it has exactly 64 characters (excluding the "0x" prefix)
        std::string padding(LENGTH * 2 - address.length(), '0');
        address = padding + address;

        for (size_t i = 0; i < LENGTH; ++i) {
            addressBytes.push_back(std::stoi(address.substr(i * 2, 2), nullptr, 16));
        }
    }

    return AccountAddress(addressBytes);
}

 /**
 * Checks if the string is a valid AccountAddress
 * @param addr Hex string can be with a prefix or without a prefix,
 *   e.g. '0x1aa' or '1aa'. Hex string will be left padded with 0s if too short.
 */
bool AccountAddress::isValid(const std::string& addr) {
    // At least one zero is required
    if (addr.empty() || addr == "0x") {
        return false;
    }

    std::string address = HexString::ensure(addr).noPrefix();

    // If an address hex has an odd number of digits, pad the hex string with 0
    // e.g. '1aa' would become '01aa'.
    if (address.length() % 2 != 0) {
        address = "0" + address;
    }

    return address.length() <= LENGTH * 2;
}

/**
 * @brief Get the address as a hex string
 * 
 * @return std::string The hex string
 */
std::string AccountAddress::toHexString() const {
    HexString hexString(address);
    return hexString.hex();
}

void AccountAddress::serialize(BCS::BCSSerializer& serializer) const {
    serializer.serializeFixedBytes(address);
}

AccountAddress AccountAddress::deserialize(BCS::BCSDeserializer deserializer) {
    std::vector<uint8_t> addressBytes = deserializer.deserializeFixedBytesVector(LENGTH);
    return AccountAddress(addressBytes);
}

/**
 * Standardizes an address to the format "0x" followed by 64 lowercase hexadecimal digits.
 */
std::string AccountAddress::standardizeAddress(const std::string& address) {
    // Convert the address to lowercase
    std::string lowercaseAddress = address;
    std::transform(lowercaseAddress.begin(), lowercaseAddress.end(), lowercaseAddress.begin(), ::tolower);
    
    // Remove the "0x" prefix if present
    size_t prefixLength = 0;
    if (lowercaseAddress.substr(0, 2) == "0x") {
        prefixLength = 2;
    }

    // Pad the address with leading zeros if necessary
    // to ensure it has exactly 64 characters (excluding the "0x" prefix)
    size_t addressLength = lowercaseAddress.length() - prefixLength;
    if (addressLength < LENGTH * 2) {
        std::string padding(LENGTH * 2 - addressLength, '0');
        lowercaseAddress = "0x" + padding + lowercaseAddress.substr(prefixLength);
    }

    return lowercaseAddress;
}
