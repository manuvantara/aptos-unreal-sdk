#ifndef BCSSERIALIZER_H
#define BCSSERIALIZER_H

#include <vector>
#include <cstdint>
#include <string>
#include <tuple>

namespace BCS
{
    class BCSSerializer {
    public:
        BCSSerializer();
        ~BCSSerializer();
        void serializeU8(unsigned char value);
        void serializeU16(unsigned short value);
        void serializeU32(unsigned int value);
        void serializeU64(unsigned long long value);
        void serializeU128(__uint128_t value);
        void serializeString(std::string& value);
        void serializeBool(bool value);
        void serializeU32AsUleb128(unsigned int value);
        void serializeBytes(std::vector<unsigned char> value);
        void serializeBytes(unsigned char* value, unsigned int size);
        void serializeFixedBytes(std::vector<uint8_t> value);
        void serializeFixedBytes(unsigned char* value, unsigned int size);

        // Complex types
        // vector
        template<typename T>
        void serialize(std::vector<T>& value) {
            serializeU32AsUleb128(value.size());
            for(auto& element : value) {
                try {
                    this -> serialize(element);
                } catch(...) {
                    throw;
                }
            }
        }

        // tuple
        template<typename... T>
        void serialize(std::tuple<T...>& value) {
            std::apply([&](auto&&... args) { (serialize(args), ...); }, value);
        }

        // serialize an enum
        template<typename T>
        void serializeEnum(T value) {
            serializeU32AsUleb128(static_cast<unsigned int>(value));
        }

        // struct
        template<typename T>
        void serialize(T& value) {
            value.serialize(*this);
        }


        // Overloaded functions for convenience (and usage with generic types)
        // void serialize(ISerializable& value) { value.serialize(*this); }
        void serialize(unsigned char value) { serializeU8(value); }
        void serialize(unsigned short value) { serializeU16(value); }
        void serialize(unsigned int value) { serializeU32(value); }
        void serialize(unsigned long long value) { serializeU64(value); }
        void serialize(__uint128_t value) { serializeU128(value); }
        void serialize(std::string& value) { serializeString(value); }
        void serialize(bool value) { serializeBool(value); }
        void serialize(std::vector<unsigned char>& value) { serializeBytes(value); }
        void serialize(unsigned char* value, unsigned int size) { serializeBytes(value, size); }
        void serializeFixed(std::vector<unsigned char>& value) { serializeFixedBytes(value); }
        void serializeFixed(unsigned char* value, unsigned int size) { serializeFixedBytes(value, size); }

        std::vector<unsigned char> getBuffer() const { return buffer; }

        void clearBuffer() { buffer.clear(); }
    private:
        std::vector<unsigned char> buffer;
    };
    

    
} // namespace BCS


#endif // BCSSERIALIZER_H