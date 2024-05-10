#pragma once

namespace Lovense {
    enum ErrorCode {
        SUCCESS = 200,
        INVALID_COMMAND = 400,
        INVALID_PARAMETER = 404,
        INVALID_TOKEN = 501,
        MISSING_PERMISSION = 502,
        INVALID_USER_ID = 503,
        LOVENSE_APP_OFFLINE = 507
    };

    namespace ErrorCodeAPI {
        std::string getMessage(ErrorCode code) {
            switch (code) {
                case ErrorCode::SUCCESS:
                    return "Success";
                case ErrorCode::INVALID_COMMAND:
                    return "Invalid command";
                case ErrorCode::INVALID_PARAMETER:
                    return "Invalid parameter";
                case ErrorCode::INVALID_TOKEN:
                    return "Invalid token";
                case ErrorCode::MISSING_PERMISSION:
                    return "You do not have permission to use this API";
                case ErrorCode::INVALID_USER_ID:
                    return "Invalid User ID";
                case ErrorCode::LOVENSE_APP_OFFLINE:
                    return "Lovense APP is offline";
                default:
                    return "Unknown error code" + std::to_string(code);
            }
        }
    }
}