#include "LovenseToy.h"

#include "Lovense/ActionType.h"
#include "Url/Request.h"

namespace Toys {
    const char* LovenseToy::getID() {
        return id.c_str();
    }

    const char* LovenseToy::getName() {
        return name.c_str();
    }

    uint16_t LovenseToy::getUpdateInterval() {
        return 1000;
    }


    void LovenseToy::turnOn() {

    }

    void LovenseToy::turnOff() {

    }


    void LovenseToy::update(float baseline, float peak, uint16_t peakInterval) {
        std::string baseMagnitude = Lovense::ActionTypes::VIBRATE.parseMagnitude(baseline);
        std::string peakMagnitude = Lovense::ActionTypes::VIBRATE.parseMagnitude(peak);

        std::unordered_map<std::string, std::string> params;

        params["rule"] = "V:1;F:v;S:100#";

        std::string strength = peakMagnitude;
        uint16_t nextPeak = peakInterval;
        for (uint16_t step = 100; step < 1000; step += 100) {
            strength += ";";
            if (step <= nextPeak && (step + 100) > nextPeak) {
                strength += peakMagnitude;
                nextPeak += peakInterval;
            } else {
                strength += baseMagnitude;
            }
        }
        for (int i = 0; i < 20; i++) {
            strength += ";" + baseMagnitude;
        }
        params["strength"] = strength;
        
        params["timeSec"] = "3";

        Request::send(id, Lovense::CommandTypes::PATTERN, params);
    }

    void LovenseToy::peak(float magnitude, float duration) {
        std::unordered_map<std::string, std::string> params;

        std::string actionString = "";
        std::string comma = "";
        for (Lovense::ActionType& action : Lovense::ActionTypes::DEFAULT_TYPES) {
            actionString += comma + action.function + ":" + action.parseMagnitude(magnitude);
            comma = ",";
        }

        if (duration < 1.0f) {
            duration = 1.0f;
        }
        params["timeSec"] = std::to_string(duration);

        Request::send(id, Lovense::CommandTypes::FUNCTION, params);
    }

    void LovenseToy::stop() {
        Request::send(id, Lovense::CommandTypes::FUNCTION, {{"action", Lovense::ActionTypes::STOP.function},{"timeSec", "0"}});
    }
}