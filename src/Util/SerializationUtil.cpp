#include "SerializationUtil.h"

namespace SerializationUtil {
    void writeString(GameAPI::GameSerializationInterface serial, std::string value) {
        serial.write<size_t>(value.size());
        for (char c : value) {
            serial.write<char>(c);
        }
    }

    std::string readString(GameAPI::GameSerializationInterface serial) {
        std::vector<char> chars;
        for (size_t size = serial.read<size_t>(); size > 0; size--) {
            chars.push_back(serial.read<char>());
        }
        return std::string(chars.begin(), chars.end());
    }
}