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
        void serializeBool(bool value);
        void serializeU32AsUleb128(unsigned int value);
        void serializeBytes(std::vector<unsigned char>& value);
        void serializeBytes(unsigned char* value, unsigned int size);
        void serializeFixedBytes(std::vector<unsigned char>& value);
        void serializeFixedBytes(unsigned char* value, unsigned int size);

        std::vector<unsigned char> getBuffer() const { return buffer; }
    private:
        std::vector<unsigned char> buffer;
    };
    

    
} // namespace BCS


#endif // BCSSERIALIZER_H