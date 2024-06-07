#pragma once

#include "LovenseToy.h"

#include "OStim/SexToys/SexToyInterface.h"
#include "OStim/InterfaceMap.h"
#include "Util/Singleton.h"

namespace Toys {
    class ToyManager : public Util::Singleton<ToyManager>, public OStim::SexToyReloadListener {
    public:
        void setInterfaceMap(OStim::InterfaceMap* map);

        virtual void reloadToys() override;

    private:
        OStim::SexToyInterface* toyInterface = nullptr;
        std::vector<LovenseToy> toys;
    };
}