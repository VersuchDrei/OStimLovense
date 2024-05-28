#include "GameSerializationManager.h"

#include "Core.h"

namespace GameLogic {
    void Save(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
        logger::info("serializing data");

        if (!serial->OpenRecord(settingsRecord, 0)) {
            logger::error("Unable to open record to write cosave data.");
            return;
        }

        Serialization::SerializationInfo info{serial};
        Core::serialize(info);
    }

    void Load(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
        logger::info("deserializing data");

        std::uint32_t type;
        std::uint32_t size;
        std::uint32_t version;

        while (serial->GetNextRecordInfo(type, version, size)) {
            if (type == settingsRecord) {
                Serialization::DeserializationInfo info{serial, version};
                Core::deserialize(info);
            }
        }
    }

    void Revert(SKSE::SerializationInterface* serial) {
        std::unique_lock lock(_lock);
        logger::info("reverting data");

        Serialization::ResetInfo info{serial};
        Core::reset(info);
    }
}