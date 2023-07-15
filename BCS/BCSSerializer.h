#ifndef BCSSERIALIZER_H
#define BCSSERIALIZER_H

#include <vector>
#include <cstdint>
#include <string>

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
        void serializeString(std::string& value);

        std::vector<unsigned char> getBuffer() const { return buffer; }
    private:
        std::vector<unsigned char> buffer;
    };
    

    
} // namespace BCS


#endif // BCSSERIALIZER_H