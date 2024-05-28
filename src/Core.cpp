#include "Core.h"

#include "Settings/SettingTable.h"

namespace Core {
    void serialize(Serialization::SerializationInfo& info) {
        Settings::SettingTable::getSingleton()->serialize(info);
    }

    void deserialize(Serialization::DeserializationInfo& info) {
        Settings::SettingTable::getSingleton()->deserialize(info);
    }

    void reset(Serialization::ResetInfo& info) {
        Settings::SettingTable::getSingleton()->reset(info);
    }
}