#ifndef COMPUTER_CLUB_SRC_CLIENT_EVENTS
#define COMPUTER_CLUB_SRC_CLIENT_EVENTS

#include "../../computer_club/include/computer_club.hpp"

enum class EventID : int {
    ARRIVE = 1,
    TAKE_TABLE,
    WAIT,
    LEAVE,
    LEAVE_AT_THE_END = 11
};

void arrive(ComputerClub& computer_club, const int& time,
            const std::string& client_name);

void takeTable(ComputerClub& computer_club, const int& time,
               const std::string& client_name, const std::size_t& table_ind);

void wait(ComputerClub& computer_club, const int& time,
          const std::string& client_name);

void leave(ComputerClub& computer_club, const int& time,
           const std::string& client_name);

void leaveAtTheEnd(ComputerClub& computer_club, const int& time,
                   const std::string& client_name);

#endif  // COMPUTER_CLUB_SRC_CLIENT_EVENTS
