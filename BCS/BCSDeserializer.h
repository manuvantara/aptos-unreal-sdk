#ifndef BCSDESERIALIZER_H
#define BCSDESERIALIZER_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>
#include <tuple>
#include "BCSSerializer.h"
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
        bool deserializeBool();
        unsigned int deserializeUleb128AsU32();
        std::vector<unsigned char> deserializeBytesVector();
        unsigned char* deserializeBytesArray();
        std::vector<unsigned char> deserializeFixedBytesVector(unsigned int size);
        unsigned char* deserializeFixedBytesArray(unsigned int size);

        // Complex types
        // vector
        template<typename T>
        std::vector<T> deserializeVector() {
            unsigned int length = deserializeUleb128AsU32();
            std::vector<T> value;
            for(unsigned int i = 0; i < length; i++) {
                value.push_back(deserialize<T>());
            }
            return value;
        }
        
        // tuple
        template<typename... T>
        std::tuple<T...> deserializeTuple() {
            return std::make_from_tuple<std::tuple<T...>>(std::tuple<T...>{deserialize<T>()...});
        }

        // deserialize an enum
        template<typename T>
        T deserializeEnum() {
            return static_cast<T>(deserializeUleb128AsU32());
        }

        // struct
        template<typename T>
        T deserializeStruct() {
            T value;
            value.deserialize(*this);
            return value;
        }

        // Overloaded functions for convenience (and usage with generic types)
        template<typename T>
        T deserialize();
        template<typename T>
        T deserializeFixed(unsigned int size);


        void updateBuffer(std::vector<uint8_t> buffer) {
            this -> buffer = buffer;
            index = 0;
        }
    private:
        std::vector<uint8_t> buffer;
        size_t index;
    };
    
} // namespace BCS


#endif // BCSDESERIALIZER_H