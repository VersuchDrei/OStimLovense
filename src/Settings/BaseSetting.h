#pragma once

#include "BaseSettingParams.h"

#include "OStim/Settings/Setting.h"

namespace Settings {
    class BaseSetting : public OStim::Setting {
    public:
        BaseSetting(BaseSettingParams params, OStim::SettingType type);

        virtual bool isDisposable() override;

        virtual const char* getName() override;
        virtual const char* getTooltip() override;
        virtual OStim::SettingType getType() override;
        virtual bool isEnabled() override;

        // toggle options
        virtual bool isActivatedByDefault() override;
        virtual bool isActivated() override;
        virtual bool toggle() override;

        // slider options
        virtual float getDefaultValue() override;
        virtual float getCurrentValue() override;
        virtual float getValueStep() override;
        virtual float getMinValue() override;
        virtual float getMaxValue() override;
        virtual bool setValue(float value) override;

        // drop down options
        virtual uint32_t getDefaultIndex() override;
        virtual uint32_t getCurrentIndex() override;
        virtual const char* getCurrentOption() override;
        virtual uint32_t getOptionCount() override;
        virtual const char* getOption(uint32_t index) override;
        virtual bool setIndex(uint32_t index) override;

        // text input options
        virtual const char* getDefaultText() override;
        virtual const char* getCurrentText() override;
        virtual bool setText(const char* text) override;

        // button options
        virtual bool click() override;

    private:
        std::string name;
        std::string tooltip;
        OStim::SettingType type;
    };
}