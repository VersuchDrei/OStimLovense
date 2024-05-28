#pragma once

namespace GameLogic {
    inline const auto settingsRecord = _byteswap_ulong('STNG');

    inline std::mutex _lock;

    void Save(SKSE::SerializationInterface* a_intfc);
    void Load(SKSE::SerializationInterface* a_intfc);
    void Revert(SKSE::SerializationInterface* a_intfc);
}