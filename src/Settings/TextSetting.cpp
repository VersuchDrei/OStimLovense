#include "TextSetting.h"

namespace Settings {
    TextSetting::TextSetting(BaseSettingParams params, std::string defaultText, std::function<std::string*()> valueGetter, std::function<void(std::string)> valueSetter)
        : BaseSetting(params, OStim::SettingType::TEXT_INPUT),
          defaultText{defaultText},
          valueGetter{valueGetter},
          valueSetter{valueSetter} {}
    

    const char* TextSetting::getDefaultText() {
        return defaultText.c_str();
    }

    const char* TextSetting::getCurrentText() {
        return valueGetter()->c_str();
    }

    bool TextSetting::setText(const char* text) {
        valueSetter(std::string(text));
        return false;
    }
}