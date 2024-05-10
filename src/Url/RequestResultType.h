#pragma once

namespace Request {
    enum RequestResultType {
        SUCCESS,
        CURL_ERROR,
        LOVENSE_ERROR,
        OTHER
    };
}