#include "SolacePro.h"

#include "Lovense/PatternType.h"
#include "Url/Request.h"

namespace Toys {
    uint16_t SolacePro::getUpdateInterval() {
        return 0;
        //return UPDATE_INTERVAL;
    }

    void SolacePro::update(float baseline, float peak, int16_t peakInterval) {
        if (peakInterval <= 0) {
            return;
        }

        std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastStart).count();
        if (milliseconds < 60000 && std::abs(lastPeakInterval - peakInterval) < lastPeakInterval / 10) {
            return;
        }
        
        lastStart = now;
        lastPeakInterval = peakInterval;

        std::vector<std::tuple<Lovense::Parameter, std::string>> params;
        params.push_back({Lovense::Parameters::PATTERN_V2_TYPE, Lovense::PatternTypes::SETUP.type});
        json actions = json::array();
        for (int i = 0; i < 65000; i += peakInterval) {
            json out = json::object();
            out["ts"] = i;
            out["pos"] = 0;
            actions.push_back(out);
            if (peakInterval >= 400) {
                json mid = json::object();
                mid["ts"] = i + peakInterval / 4;
                mid["pos"] = 50;
                actions.push_back(mid);
            }
            json in = json::object();
            in["ts"] = i + peakInterval / 2;
            in["pos"] = 100;
            actions.push_back(in);
            if (peakInterval >= 400) {
                json mid = json::object();
                mid["ts"] = i + peakInterval * 3 / 4;
                mid["pos"] = 50;
                actions.push_back(mid);
            }
        }
        params.push_back({Lovense::Parameters::PATTERN_V2_ACTIONS, actions.dump()});

        auto start = std::chrono::system_clock::now();
        Request::send(id, Lovense::CommandTypes::PATTERN_V2, params);
        auto end = std::chrono::system_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        params.clear();
        params.push_back({Lovense::Parameters::PATTERN_V2_TYPE, Lovense::PatternTypes::PLAY.type});
        params.push_back({Lovense::Parameters::PATTERN_V2_START_TIME, std::to_string(time)});
        params.push_back({Lovense::Parameters::PATTERN_V2_OFFSET_TIME, std::to_string(time)});
        Request::send(id, Lovense::CommandTypes::PATTERN_V2, params);

        // this is way too laggy
        /*
        // we do the thread first so that it doesn't have to wait for the url request to finish
        std::thread([this, peakInterval]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(peakInterval / 2));

            std::vector<std::tuple<Lovense::Parameter, std::string>> params;
            params.push_back({Lovense::Parameters::POSITION_VALUE, "100"});
            Request::send(id, Lovense::CommandTypes::POSITION, params);
        }).detach();

        std::vector<std::tuple<Lovense::Parameter, std::string>> params;
        params.push_back({Lovense::Parameters::POSITION_VALUE, "0"});
        Request::send(id, Lovense::CommandTypes::POSITION, params);
        */
    }

    void SolacePro::peak(float magnitude, float duration) {
        
    }

    void SolacePro::stop() {
        Request::send(id, Lovense::CommandTypes::PATTERN_V2, {{Lovense::Parameters::PATTERN_V2_TYPE, Lovense::PatternTypes::STOP.type}});
        lastStart = {};
    }
}