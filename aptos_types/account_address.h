#ifndef ACCOUNT_ADDRESS_H
#define ACCOUNT_ADDRESS_H

#include "../utils/hex_string.h"
#include "../BCS/BCSSerializer.h"
#include "../BCS/BCSDeserializer.h"

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

class AccountAddress {
public:
    static const size_t LENGTH = 32;

    explicit AccountAddress(const std::vector<uint8_t>& address);

    static AccountAddress fromHex(const std::string& addr);
    static bool isValid(const std::string& addr);
    std::string toHexString() const;

    void serialize(BCS::BCSSerializer& serializer) const;
    static AccountAddress deserialize(BCS::BCSDeserializer deserializer);

    static std::string standardizeAddress(const std::string& address);

private:
    std::vector<uint8_t> address;
};

#endif  // ACCOUNT_ADDRESS_H