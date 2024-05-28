#pragma once

#include "GameAPI/GameSerializationInterface.h"

namespace SerializationUtil {
    void writeString(GameAPI::GameSerializationInterface serial, std::string value);
    std::string readString(GameAPI::GameSerializationInterface serial);
}