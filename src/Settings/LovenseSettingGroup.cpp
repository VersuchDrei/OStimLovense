#include "LovenseSettingGroup.h"

#include "SettingTable.h"
#include "TextSetting.h"

namespace Settings {
    LovenseSettingGroup::LovenseSettingGroup() {
        if (REL::Module::IsVR()) {
            loadVRConfig();
        }
        settings.push_back(new TextSetting({"IP", "The local IP of your Lovense Remote app."}, SettingTable::defaultDomain, []() { return SettingTable::getSingleton()->getDomain(); }, [](std::string domain){ SettingTable::getSingleton()->setDomain(domain);}));
        settings.push_back(new TextSetting({"SSL port", "The SSL port of your Lovense Remote app."}, SettingTable::defaultPort, []() { return SettingTable::getSingleton()->getPort(); }, [](std::string port){ SettingTable::getSingleton()->setPort(port);}));
    }

    void LovenseSettingGroup::setUp(OStim::InterfaceMap* map) {
        settingInterface = static_cast<OStim::SettingInterface*>(map->queryInterface(OStim::SettingInterface::NAME));
        if (!settingInterface) {
            return;
        }
        settingInterface->addGroup(this);
        settingInterface->registerExportImportListener(this);
    }


    bool LovenseSettingGroup::isDisposable() {
        return false;
    }

    const char* LovenseSettingGroup::getName() {
        return "Lovense";
    }

    OStim::SettingDisplayOrder LovenseSettingGroup::getDisplayOrder() {
        return OStim::SettingDisplayOrder::TOP_TO_BOTTOM;
    }

    uint32_t LovenseSettingGroup::getSettingCount() {
        return settings.size();
    }

    OStim::Setting* LovenseSettingGroup::getSetting(uint32_t index) {
        if (index < 0 || index >= settings.size()) {
            return nullptr;
        }

        return settings[index];
    }


    void LovenseSettingGroup::exportSettings(OStim::SettingExportImportScale scale) {
        if (!settingInterface) {
            return;
        }

        SettingTable* table = SettingTable::getSingleton();
        settingInterface->exportStringSimple(ADDON, SETTING_DOMAIN, table->getDomain()->c_str());
        settingInterface->exportStringSimple(ADDON, SETTING_PORT, table->getPort()->c_str());
    }

    void LovenseSettingGroup::importSettings(OStim::SettingExportImportScale scale) {
        if (!settingInterface) {
            return;
        }

        SettingTable* table = SettingTable::getSingleton();
        table->setDomain(settingInterface->importStringSimple(ADDON, SETTING_DOMAIN, table->getDomain()->c_str()));
        table->setPort(settingInterface->importStringSimple(ADDON, SETTING_PORT, table->getPort()->c_str()));
    }

    //VR STUFF
    void skipComments(std::string& str) {
        auto pos = str.find("#");
        if (pos != std::string::npos) {
            str.erase(pos);
        }
    }

    void trim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(static_cast<unsigned char>(c)); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(static_cast<unsigned char>(c)); }).base(), s.end());
    }

    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.emplace_back(token);
        }
        return tokens;
    }

    std::string GetConfigSettingsValue(std::string line, std::string& variable) {
        if (!line.empty() && line.back() == '=') {
            line.push_back(' ');
        }
        std::string valuestr = "";
        std::vector<std::string> splittedLine = split(line, '=');
        variable = "";
        if (splittedLine.size() > 1) {
            variable = splittedLine[0];
            trim(variable);

            valuestr = splittedLine[1];
            trim(valuestr);
        } else {
            variable = line;
            trim(variable);
            valuestr = "0";
        }

        return valuestr;
    }

    void saveNewVRConfig() 
    {
        std::string filepath = "Data\\SKSE\\Plugins\\OStimLovenseVR.ini";

        std::ofstream output(filepath, std::fstream::out);
        if (!output.is_open()) {
            logger::error("...Failure while saving OStimLovenseVR.ini file.");
            return;
        }

        output << std::fixed;
        output << "################################################################################################\n";
        output << "# This is the config file for OStim Lovense Addon VR settings ini .\n";
        output << "#\n";
        output << "#\n";
        output << "# # ->This is the comment character.\n";
        output << "#\n";
        output << "################################################################################################\n";
        output << "[Settings]\n";
        output << "\n";
        output << "Domain = 127-0-0-1.lovense.club          #Enter the domain without https://\n";
        output << "\n";
        output << "Port = 30010                #Enter the port\n";
        output << "\n";
        output << "\n";

        output.close();
    }

    void LovenseSettingGroup::loadVRConfig() 
    {
        std::string filepath = "Data\\SKSE\\Plugins\\OStimLovenseVR.ini";

        std::ifstream file(filepath);

        if (!file.is_open()) {
            transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);
            file.open(filepath);
        }

        if (file.is_open()) {
            std::string line;
            std::string currentSetting;
            while (std::getline(file, line)) {
                // trim(line);
                skipComments(line);
                trim(line);
                if (line.length() > 0) {
                    if (line.substr(0, 1) == "[") {
                        // newsetting
                        currentSetting = line;
                    } else {
                        if (currentSetting == "[Settings]") {
                            std::string variableName;
                            std::string variableValue = GetConfigSettingsValue(line, variableName);

                            if (variableName == "Domain") {
                                SettingTable::defaultDomain = variableValue;
                            } else if (variableName == "Port") {
                                SettingTable::defaultPort = variableValue;
                            } 
                        }
                    }
                }
            }
        } else  // Regenerate new file
        {
            saveNewVRConfig();
        }
    }
}