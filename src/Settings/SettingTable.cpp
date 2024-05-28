#include "SettingTable.h"

#include "Util/SerializationUtil.h"

namespace Settings {
    void SettingTable::serialize(Serialization::SerializationInfo& info) {
        SerializationUtil::writeString(info.serial, domain);
        SerializationUtil::writeString(info.serial, port);
    }

    void SettingTable::deserialize(Serialization::DeserializationInfo& info) {
        domain = SerializationUtil::readString(info.serial);
        port = SerializationUtil::readString(info.serial);
    }

    void SettingTable::reset(Serialization::ResetInfo& info) {
        domain = defaultDomain;
        port = defaultPort;
    }
}