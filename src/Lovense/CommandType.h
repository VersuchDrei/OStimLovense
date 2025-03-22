#pragma once

namespace Lovense {
    struct CommandType {
    public:
        std::string command;
        uint8_t apiVer;
    };

    namespace CommandTypes {
        inline CommandType FUNCTION{"Function", 1};
        inline CommandType GET_TOYS{"GetToys", 1};
        inline CommandType PATTERN{"Pattern", 2};
        inline CommandType PATTERN_V2{"PatternV2", 1};
        inline CommandType POSITION{"Position", 1};
    }
}