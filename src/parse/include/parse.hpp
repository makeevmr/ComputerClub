#ifndef COMPUTER_CLUB_SRC_PARSE
#define COMPUTER_CLUB_SRC_PARSE

#include "../../validate/include/validate.hpp"
#include "../../client_events/include/client_events.hpp"

#include <fstream>

[[nodiscard]] ComputerClub parseClubInitData(std::ifstream& input_file);

void parseEvents(ComputerClub& computer_club, std::ifstream& input_file);

#endif  // COMPUTER_CLUB_SRC_PARSE
