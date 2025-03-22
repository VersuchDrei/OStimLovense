#pragma once

namespace Lovense {
    struct PatternType {
        std::string type;
    };

    namespace PatternTypes {
        inline PatternType PLAY{"Play"};
        inline PatternType SETUP{"Setup"};
        inline PatternType STOP{"Stop"};
        inline PatternType SYNC_TIME{"SyncTime"};
    }
}