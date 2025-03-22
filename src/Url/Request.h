#pragma once

#include "RequestResult.h"

#include "Lovense/CommandType.h"
#include "Lovense/Parameter.h"

namespace Request {
    RequestResult send(std::string& toy, Lovense::CommandType& command, std::vector<std::tuple<Lovense::Parameter, std::string>> params);
}