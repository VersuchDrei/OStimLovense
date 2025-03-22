#pragma once

#include "OStim/SexToys/SexToy.h"

namespace Toys {
    class LovenseToy : public OStim::SexToy {
    public:
        static inline std::string NO_TOY = "";

        inline LovenseToy(std::string id, std::string name) : id{id}, name{name} {}
        virtual ~LovenseToy();

        virtual const char* getID();
        virtual const char* getName();
        virtual uint16_t getUpdateInterval();

        virtual void turnOn();
        virtual void turnOff();

        virtual void update(float baseline, float peak, int16_t peakInterval);
        virtual void peak(float magnitude, float duration);
        virtual void stop();

    protected:
        std::string id;

    private:
        std::string name;
    };

    inline LovenseToy::~LovenseToy(){}
}