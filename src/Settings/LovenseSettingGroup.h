#pragma once

#include "OStim/Settings/SettingExportImportListener.h"
#include "OStim/Settings/SettingGroup.h"
#include "OStim/Settings/SettingInterface.h"
#include "OStim/InterfaceMap.h"
#include "Util/Singleton.h"

namespace Settings {
    class LovenseSettingGroup : public Util::Singleton<LovenseSettingGroup>, public OStim::SettingGroup, public OStim::SettingExportImportListener {
    public:
        inline static const char* ADDON = "Lovense";
        inline static const char* SETTING_DOMAIN = "domain";
        inline static const char* SETTING_PORT = "port";

        LovenseSettingGroup();

        void setUp(OStim::InterfaceMap* map);

        virtual bool isDisposable() override;

        virtual const char* getName() override;
        virtual OStim::SettingDisplayOrder getDisplayOrder() override;

        virtual uint32_t getSettingCount() override;
        virtual OStim::Setting* getSetting(uint32_t index) override;


        virtual void exportSettings(OStim::SettingExportImportScale scale) override;
        virtual void importSettings(OStim::SettingExportImportScale scale) override;

        void loadVRConfig(); 
    private:
        std::vector<OStim::Setting*> settings;
        OStim::SettingInterface* settingInterface = nullptr;
    };
}