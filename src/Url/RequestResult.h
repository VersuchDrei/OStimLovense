#pragma once

#include "RequestResultType.h"

namespace Request {
    struct RequestResult {
        RequestResultType type = RequestResultType::OTHER;
        json result;
    };
}