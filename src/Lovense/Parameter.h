#pragma once

#include "ParameterType.h"

namespace Lovense {
    struct Parameter {
    public:
        std::string parameter;
        ParameterType type;

        bool operator==(const Parameter &other) const { return parameter == other.parameter; }
        bool operator<(const Parameter &other) const { return parameter < other.parameter; }
    };

    namespace Parameters {
        inline Parameter FUNCTION_ACTION{"action", ParameterType::STRING};
        inline Parameter FUNCTION_STOP_PREVIOUS{"stopPrevious", ParameterType::INT};
        inline Parameter FUNCTION_TIME_SEC{"timeSec", ParameterType::INT};
        inline Parameter PATTERN_V2_ACTIONS{"actions", ParameterType::JSON};
        inline Parameter PATTERN_V2_OFFSET_TIME{"offsetTime", ParameterType::INT};
        inline Parameter PATTERN_V2_START_TIME{"startTime", ParameterType::INT};
        inline Parameter PATTERN_V2_TYPE{"type", ParameterType::STRING};
        inline Parameter POSITION_VALUE{"value", ParameterType::STRING};
    }
}