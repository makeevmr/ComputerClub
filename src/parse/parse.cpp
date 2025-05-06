#include "include/parse.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>

[[nodiscard]] static int getTimeInMinutes(const std::string& s) noexcept {
    if (!isCorrectTime(s)) {
        return -1;
    }
    int hours = (s[0] - '0') * 10 + (s[1] - '0');
    int minutes = (s[3] - '0') * 10 + (s[4] - '0');
    if (hours > 23 || minutes > 59) {
        return -1;
    }
    return hours * 60 + minutes;
}

static int handleTime(const std::string& time, const std::string& event) {
    int event_time = getTimeInMinutes(time);
    if (event_time == -1) {
        std::cout << event << std::endl;
        throw std::runtime_error("Invalid time format");
    }
    return event_time;
}

static void handleNumber(const std::string& num,
                         const std::string& event = "") {
    if (!isCorrectNumber(num)) {
        if (event.empty()) {
            std::cout << num << std::endl;
        } else {
            std::cout << event << std::endl;
        }
        throw std::runtime_error("Positive integer invalid format");
    }
}

static void handleName(const std::string& name, const std::string& event) {
    if (!isCorrectName(name)) {
        std::cout << event << std::endl;
        throw std::runtime_error("Invalid client name format");
    }
}

static void handleEventFormat(std::stringstream& ss, const std::string& event) {
    if (ss.eof()) {
        std::cout << event << std::endl;
        throw std::runtime_error(
            "Invalid event format. Expected <time> <event_id> <event_body>");
    }
}

static void parseClientEvent(ComputerClub& computer_club,
                             const std::string& event) {
    std::stringstream ss(event);
    std::string new_lexeme;
    ss >> new_lexeme;
    int event_time = handleTime(new_lexeme, event);
    handleEventFormat(ss, event);
    ss >> new_lexeme;
    handleNumber(new_lexeme, event);
    handleEventFormat(ss, event);
    EventID event_id{std::stoi(new_lexeme)};
    ss >> new_lexeme;
    handleName(new_lexeme, event);
    std::string client_name = new_lexeme;
    std::size_t table_ind = 0;
    if (event_id == EventID::TAKE_TABLE) {
        ss >> new_lexeme;
        handleNumber(new_lexeme, event);
        table_ind = std::stoull(new_lexeme) - 1;
        if (table_ind >= computer_club.getTotalTables()) {
            std::cout << event << std::endl;
            throw std::runtime_error("Invalid table number");
        }
    }
    if (!ss.eof()) {
        std::cout << event << std::endl;
        throw std::runtime_error(
            "Invalid event format. Expected <time> <event_id> <event_body>");
    }
    switch (event_id) {
        case EventID::ARRIVE:
            arrive(computer_club, event_time, client_name);
            break;
        case EventID::TAKE_TABLE:
            takeTable(computer_club, event_time, client_name, table_ind);
            break;
        case EventID::WAIT:
            wait(computer_club, event_time, client_name);
            break;
        case EventID::LEAVE:
            leave(computer_club, event_time, client_name);
            break;
        case EventID::LEAVE_AT_THE_END:
            leaveAtTheEnd(computer_club, event_time, client_name);
            break;
        default:
            std::cout << event << std::endl;
            throw std::runtime_error("Invalid event id");
    }
}

ComputerClub parseClubInitData(std::ifstream& input_file) {
    std::string line;
    std::getline(input_file, line);
    handleNumber(line);
    std::size_t total_tables = std::stoull(line);
    std::getline(input_file, line);
    if (std::ranges::count(line, ' ') != 1) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Opening hours invalid format");
    }
    std::size_t space_ind = line.find(' ');
    std::string open_time_str = line.substr(0, space_ind);
    std::string close_time_str = line.substr(space_ind + 1);
    int open_time = handleTime(open_time_str, line);
    int close_time = handleTime(close_time_str, line);
    if (open_time >= close_time) {
        std::cout << line << std::endl;
        throw std::invalid_argument("Opening hours invalid format");
    }
    std::getline(input_file, line);
    handleNumber(line);
    uint64_t hourly_cost = std::stoull(line);
    return ComputerClub(open_time, close_time, hourly_cost, total_tables);
}

void parseEvents(ComputerClub& computer_club, std::ifstream& input_file) {
    displayTime(computer_club.getOpenTime());
    std::cout << '\n';
    std::string line;
    while (input_file.peek() != EOF) {
        std::getline(input_file, line);
        std::cout << line << '\n';
        parseClientEvent(computer_club, line);
    }
    int close_time = computer_club.getCloseTime();
    std::string time = {
        static_cast<char>(close_time / 60 / 10 + '0'),
        static_cast<char>(close_time / 60 % 10 + '0'),
        ':',
        static_cast<char>(close_time % 60 / 10 + '0'),
        static_cast<char>(close_time % 60 % 10 + '0'),
    };
    std::vector<std::string> sorted_clients_list =
        computer_club.getClientsList();
    for (const auto& client_name : sorted_clients_list) {
        parseClientEvent(computer_club, time + " 11 " + client_name);
    }
    displayTime(computer_club.getCloseTime());
    std::cout << '\n';
    computer_club.displayTablesInfo();
}
