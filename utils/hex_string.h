#ifndef HEX_STRING_H
#define HEX_STRING_H

#include <string>
#include <vector>
#include <cstdint>

class HexString {
public:
    static HexString fromBuffer(const std::vector<uint8_t>& buffer);
    static HexString fromUint8Array(const std::vector<uint8_t>& arr);
    static HexString ensure(const std::string& hexString);
    explicit HexString(const std::string& hexString);
    explicit HexString(const std::vector<uint8_t>& arr);

    std::string hex() const;
    std::string noPrefix() const;
    std::string toShortString() const;
    std::vector<uint8_t> toUint8Array() const;

    // Add other methods and members as needed

private:
    std::string hexString;
};

#endif  // HEXSTRING_H