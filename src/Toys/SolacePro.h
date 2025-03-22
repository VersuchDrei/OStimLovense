#pragma once

#include "LovenseToy.h"

namespace Toys {
    class SolacePro : public LovenseToy {
    public:
        static const uint32_t UPDATE_INTERVAL = 30000;

        inline SolacePro(std::string id, std::string name) : LovenseToy(id, name) {}

        virtual uint16_t getUpdateInterval();

        virtual void update(float baseline, float peak, int16_t peakInterval);
        virtual void peak(float magnitude, float duration);
        virtual void stop();

    private:
        std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> lastStart;
        int16_t lastPeakInterval = 0;
    };
}