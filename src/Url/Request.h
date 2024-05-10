#pragma once

#include "RequestResult.h"

#include "Lovense/CommandType.h"

namespace Request {
    RequestResult send(std::string& toy, Lovense::CommandType& command, std::unordered_map<std::string, std::string> params);
}