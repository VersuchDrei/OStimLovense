#pragma once

#include "Serialization/DeserializationInfo.h"
#include "Serialization/ResetInfo.h"
#include "Serialization/SerializationInfo.h"

namespace Core {
    void serialize(Serialization::SerializationInfo& info);
    void deserialize(Serialization::DeserializationInfo& info);
    void reset(Serialization::ResetInfo& info);
}