#pragma once

namespace Lovense {
    struct ActionType {
        std::string function;
        std::string pattern;
        uint8_t max;

        inline std::string parseMagnitude(float magnitude) {
            return std::to_string(static_cast<int>(std::round(magnitude * max)));
        }
    };

    namespace ActionTypes {
        inline ActionType ALL{"All", "", 20};
        inline ActionType DEPTH{"Depth", "d", 3};
        inline ActionType FINGERING{"Fingering", "f", 20};
        inline ActionType PUMP{"Pump", "p", 3};
        inline ActionType ROTATE{"Rotate", "r", 20};
        inline ActionType STOP{"Stop", "", 0};
        inline ActionType SUCTION{"Suction", "s", 20};
        inline ActionType THRUSTING{"Thrusting", "t", 20};
        inline ActionType VIBRATE{"Vibrate", "v", 20};

        inline std::vector<ActionType> DEFAULT_TYPES{VIBRATE, ROTATE, PUMP};
    }
}