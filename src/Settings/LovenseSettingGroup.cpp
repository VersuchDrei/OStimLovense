#include "LovenseSettingGroup.h"

#include "SettingTable.h"
#include "TextSetting.h"

#include "OStim/Settings/SettingInterface.h"

namespace Settings {
    LovenseSettingGroup::LovenseSettingGroup() {
        settings.push_back(new TextSetting({"IP", "The local IP of your Lovense Remote app."}, SettingTable::defaultDomain, []() { return SettingTable::getSingleton()->getDomain(); }, [](std::string domain){ SettingTable::getSingleton()->setDomain(domain);}));
        settings.push_back(new TextSetting({"SSL port", "The SSL port of your Lovense Remote app."}, SettingTable::defaultDomain, []() { return SettingTable::getSingleton()->getPort(); }, [](std::string port){ SettingTable::getSingleton()->setPort(port);}));
    }

    void LovenseSettingGroup::setUp(OStim::InterfaceMap* map) {
        OStim::SettingInterface* settingInterface = static_cast<OStim::SettingInterface*>(map->queryInterface(OStim::SettingInterface::NAME));
        settingInterface->addGroup(this);
    }


    bool LovenseSettingGroup::isDisposable() {
        return false;
    }

    const char* LovenseSettingGroup::getName() {
        return "Lovense";
    }

    OStim::SettingDisplayOrder LovenseSettingGroup::getDisplayOrder() {
        return OStim::SettingDisplayOrder::TOP_TO_BOTTOM;
    }

    uint32_t LovenseSettingGroup::getSettingCount() {
        return settings.size();
    }

    OStim::Setting* LovenseSettingGroup::getSetting(uint32_t index) {
        if (index < 0 || index >= settings.size()) {
            return nullptr;
        }

        return settings[index];
    }
}