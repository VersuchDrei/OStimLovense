#pragma once

#include "BaseSetting.h"

namespace Settings {
    class TextSetting : public BaseSetting {
    public:
        TextSetting(BaseSettingParams params, std::string defaultText, std::function<std::string*()> valueGetter, std::function<void(std::string)> valueSetter);

        virtual const char* getDefaultText() override;
        virtual const char* getCurrentText() override;
        virtual bool setText(const char* text) override;
    private:
        std::string defaultText;
        std::function<std::string*()> valueGetter;
        std::function<void(std::string)> valueSetter;
    };
}