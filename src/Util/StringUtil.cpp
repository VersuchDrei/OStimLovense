#include "StringUtil.h"

namespace StringUtil {
    bool isNumber(std::string& text) {
        return !text.empty() && std::find_if(text.begin(), text.end(), [](unsigned char c) { return !std::isdigit(c); }) == text.end();
    }
}