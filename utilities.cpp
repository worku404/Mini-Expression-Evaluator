#include "utilities.h"

    // Implimentation
Status make_ok() {
    return {true, "", 0};
}

Status make_error(const std::string& message, std::size_t position) {
    return {false, message, position};
}
