#pragma once

#include "AutoTOML.hpp"

class Settings {
public:
    using ISetting = AutoTOML::ISetting;
    using sSetting = AutoTOML::sSetting;
    using iSetting = AutoTOML::iSetting;

    static void load() {
        try {
            const auto table = toml::parse_file("Data/SKSE/Plugins/OStimLovense.toml"s);
            for (const auto& setting : ISetting::get_settings()) {
                setting->load(table);
            }
        } catch (const toml::parse_error& e) {
            std::ostringstream ss;
            ss << "Error parsing file \'" << *e.source().path << "\':\n"
               << '\t' << e.description() << '\n'
               << "\t\t(" << e.source().begin << ')';
            logger::error("{}"sv, ss.str());
            throw std::runtime_error("failed to load settings"s);
        }
    }

    static inline sSetting domain{"Connection"s, "domain"s, "127-0-0-1.lovense.club"};
    static inline iSetting port{"Connection"s, "port"s, 30010};
};