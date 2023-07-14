#ifndef BCSSERIALIZER_H
#define BCSSERIALIZER_H

#include <vector>
#include <cstdint>

namespace BCS
{
    class BCSSerializer {
    public:
        BCSSerializer();
        ~BCSSerializer();
        void serealizeU8(unsigned char value);
        void serializeU16(unsigned short value);
        void serializeU32(unsigned int value);
        void serializeU64(unsigned long long value);
        void serializeU128(__uint128_t value);

    private:
        std::vector<unsigned char> buffer;
    };
    

    
} // namespace BCS


#endif // BCSSERIALIZER_H