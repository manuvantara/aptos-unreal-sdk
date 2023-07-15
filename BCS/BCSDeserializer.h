#ifndef BCSDESERIALIZER_H
#define BCSDESERIALIZER_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>

namespace BCS
{
    class BCSDeserializer {
    public:
        BCSDeserializer(std::vector<uint8_t> buffer);
        ~BCSDeserializer();
        unsigned char deserializeU8();
        unsigned short deserializeU16();
        unsigned int deserializeU32();
        unsigned long long deserializeU64();
        __uint128_t deserializeU128();
        std::string deserializeString();

    private:
        std::vector<uint8_t> buffer;
        size_t index;
    };
    
} // namespace BCS


#endif // BCSDESERIALIZER_H