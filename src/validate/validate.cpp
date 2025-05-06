#include "include/validate.hpp"

[[nodiscard]] bool isCorrectTime(const std::string& s) noexcept {
    const std::size_t s_size = s.size();
    if (s_size != 5 || s[2] != ':') {
        return false;
    }
    for (std::size_t i = 0; i < s_size; ++i) {
        if (i == 2) {
            continue;
        }
        if ('0' > s[i] || s[i] > '9') {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool isCorrectNumber(const std::string& s) noexcept {
    if (s.empty() || s == "0") {
        return false;
    }
    for (const char& symbol : s) {
        if ('0' > symbol || symbol > '9') {
            return false;
        }
    }
    return true;
}

[[nodiscard]] bool isCorrectName(const std::string& s) noexcept {
    if (s.empty()) {
        return false;
    }
    for (const char& symbol : s) {
        if (isalpha(symbol) == 0 && isdigit(symbol) == 0 && symbol != '_' &&
            symbol != '-') {
            return false;
        }
    }
    return true;
}
