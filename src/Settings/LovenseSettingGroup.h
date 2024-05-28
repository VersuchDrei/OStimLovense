#pragma once

#include "OStim/Settings/SettingGroup.h"
#include "OStim/InterfaceMap.h"
#include "Util/Singleton.h"

namespace Settings {
    class LovenseSettingGroup : public OStim::SettingGroup, public Util::Singleton<LovenseSettingGroup> {
    public:
        LovenseSettingGroup();

        void setUp(OStim::InterfaceMap* map);

        virtual bool isDisposable() override;

        virtual const char* getName() override;
        virtual OStim::SettingDisplayOrder getDisplayOrder() override;

        virtual uint32_t getSettingCount() override;
        virtual OStim::Setting* getSetting(uint32_t index) override;

    private:
        std::vector<OStim::Setting*> settings;
    };
}