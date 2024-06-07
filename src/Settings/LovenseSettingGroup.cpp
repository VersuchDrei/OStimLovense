#include "LovenseSettingGroup.h"

#include "SettingTable.h"
#include "TextSetting.h"

namespace Settings {
    LovenseSettingGroup::LovenseSettingGroup() {
        settings.push_back(new TextSetting({"IP", "The local IP of your Lovense Remote app."}, SettingTable::defaultDomain, []() { return SettingTable::getSingleton()->getDomain(); }, [](std::string domain){ SettingTable::getSingleton()->setDomain(domain);}));
        settings.push_back(new TextSetting({"SSL port", "The SSL port of your Lovense Remote app."}, SettingTable::defaultDomain, []() { return SettingTable::getSingleton()->getPort(); }, [](std::string port){ SettingTable::getSingleton()->setPort(port);}));
    }

    void LovenseSettingGroup::setUp(OStim::InterfaceMap* map) {
        settingInterface = static_cast<OStim::SettingInterface*>(map->queryInterface(OStim::SettingInterface::NAME));
        if (!settingInterface) {
            return;
        }
        settingInterface->addGroup(this);
        settingInterface->registerExportImportListener(this);
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


    void LovenseSettingGroup::exportSettings(OStim::SettingExportImportScale scale) {
        if (!settingInterface) {
            return;
        }

        SettingTable* table = SettingTable::getSingleton();
        settingInterface->exportStringSimple(ADDON, SETTING_DOMAIN, table->getDomain()->c_str());
        settingInterface->exportStringSimple(ADDON, SETTING_PORT, table->getPort()->c_str());
    }

    void LovenseSettingGroup::importSettings(OStim::SettingExportImportScale scale) {
        if (!settingInterface) {
            return;
        }

        SettingTable* table = SettingTable::getSingleton();
        table->setDomain(settingInterface->importStringSimple(ADDON, SETTING_DOMAIN, table->getDomain()->c_str()));
        table->setPort(settingInterface->importStringSimple(ADDON, SETTING_PORT, table->getPort()->c_str()));
    }
}