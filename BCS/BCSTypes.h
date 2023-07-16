#include "BCSDeserializer.h"
#include "BCSSerializer.h"

namespace BCS
{
    // Serializable interface
    class ISerializable {
    public:
        virtual void serialize(BCSSerializer& serializer) = 0;
        virtual void deserialize(BCSDeserializer& deserializer) = 0;
    };
} // namespace BCS
