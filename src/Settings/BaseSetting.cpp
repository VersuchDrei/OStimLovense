#include "BaseSetting.h"

namespace Settings {
    BaseSetting::BaseSetting(BaseSettingParams params, OStim::SettingType type)
        : name{params.name},
          tooltip{params.tooltip},
          type{type} {}

    bool BaseSetting::isDisposable() {
        return false;
    }

    const char* BaseSetting::getName() {
        return name.c_str();
    }

    const char* BaseSetting::getTooltip() {
        return tooltip.c_str();
    }

    OStim::SettingType BaseSetting::getType() {
        return type;
    }

    bool BaseSetting::isEnabled() {
        return true;
    }

    
    bool BaseSetting::isActivatedByDefault() {
        return false;
    }

    bool BaseSetting::isActivated() {
        return false;
    }

    bool BaseSetting::toggle() {
        return false;
    }

    
    float BaseSetting::getDefaultValue() {
        return 0;
    }

    float BaseSetting::getCurrentValue() {
        return 0;
    }

    float BaseSetting::getValueStep() {
        return 0;
    }

    float BaseSetting::getMinValue() {
        return 0;
    }

    float BaseSetting::getMaxValue() {
        return 0;
    }

    bool BaseSetting::setValue(float value) {
        return false;
    }

    
    uint32_t BaseSetting::getDefaultIndex() {
        return 0;
    }

    uint32_t BaseSetting::getCurrentIndex() {
        return 0;
    }

    const char* BaseSetting::getCurrentOption() {
        return "";
    }

    uint32_t BaseSetting::getOptionCount() {
        return 0;
    }

    const char* BaseSetting::getOption(uint32_t index) {
        return "";
    }

    bool BaseSetting::setIndex(uint32_t index) {
        return false;
    }

    
    const char* BaseSetting::getDefaultText() {
        return "";
    }

    const char* BaseSetting::getCurrentText() {
        return "";
    }

    bool BaseSetting::setText(const char* text) {
        return false;
    }

    
    bool BaseSetting::click() {
        return false;
    }
}