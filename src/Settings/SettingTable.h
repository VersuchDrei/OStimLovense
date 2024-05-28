#pragma once

#include "Serialization/DeserializationInfo.h"
#include "Serialization/ResetInfo.h"
#include "Serialization/SerializationInfo.h"
#include "Util/Singleton.h"

namespace Settings {
    class SettingTable : public Util::Singleton<SettingTable> {
    public:
        inline static std::string defaultDomain = "127-0-0-1.lovense.club";
        inline static std::string defaultPort = "30010";

        inline std::string* getDomain() { return &domain; }
        inline void setDomain(std::string domain) { this->domain = domain; }
        inline std::string* getPort() { return &port; }
        inline void setPort(std::string port) { this->port = port; }

        void serialize(Serialization::SerializationInfo& info);
        void deserialize(Serialization::DeserializationInfo& info);
        void reset(Serialization::ResetInfo& info);
    private:
        std::string domain = defaultDomain;
        std::string port = defaultPort;
    };
}