#pragma once

#include "../PluginInterface.h"
#include "SettingPage.h"

namespace OStim {
    class SettingInterface : public PluginInterface {
    public:
        inline static const char* NAME = "Settings";

        // --- API version 1 ---

        /**
         * adds a setting group to the addon page in the configuration menu
         */
        virtual void addGroup(SettingGroup* group) = 0;

        /**
         * adds a new page to the configuration menu
         */
        virtual void addPage(SettingPage* page) = 0;
    };
}