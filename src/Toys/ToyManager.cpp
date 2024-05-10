#include "ToyManager.h"

#include "Url/Request.h"

namespace Toys {
    void ToyManager::setInterfaceMap(OStim::InterfaceMap* map) {
        toyInterface = static_cast<OStim::SexToyInterface*>(map->queryInterface(OStim::SexToyInterface::NAME));
        toyInterface->registerReloadListener(this);
    }

    void ToyManager::reloadToys() {
        toys.clear();

        Request::RequestResult result = Request::send(LovenseToy::NO_TOY, Lovense::CommandTypes::GET_TOYS, {});
        if (result.type != Request::RequestResultType::SUCCESS) {
            return;
        }

        if (!result.result.contains("data")) {
            logger::warn("url request 'GetToys' result does not contain property 'data'");
            return;
        }

        if (!result.result["data"].is_object()) {
            logger::warn("property 'data' of url request 'GetToys' result is malformed");
            return;
        }

        if (!result.result["data"].contains("toys")) {
            logger::warn("url request 'GetToys' result does not contain property 'data.toys'");
            return;
        }

        if (!result.result["data"]["toys"].is_string()) {
            logger::warn("property 'data.toys' of url request 'GetToys' result is not a string");
            return;
        }

        // yes, they did use a json formatted as a string as value in another json, this is not a mistake
        json toys = json::parse(static_cast<std::string>(result.result["data"]["toys"]), nullptr, false);

        if (toys.is_discarded() || !toys.is_object()) {
            logger::info("property 'data.toys' of url request 'GetToys' result is malformed");
            return;
        }

        for (auto& [key, value] : toys.items()) {
            if (!value.is_object()) {
                logger::info("value of key '{}' of property 'data.toys' of url request 'GetToys' result is malformed", key);
                continue;
            }

            std::string name;
            if (value.contains("nickName") && value["nickName"].is_string() && !static_cast<std::string>(value["nickName"]).empty()) {
                name = value["nickName"];
            } else if (value.contains("name") && value["name"].is_string()) {
                name = value["name"];
            } else {
                name = key;
            }

            this->toys.push_back({key, name});
        }

        for (LovenseToy& toy : this->toys) {
            toyInterface->addToy(&toy);
        }
    }
}