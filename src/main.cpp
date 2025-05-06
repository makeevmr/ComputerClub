#include "parse/include/parse.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "USAGE: <EXECUTABLE> <INPUT_FILE>\n";
        return EXIT_FAILURE;
    }
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        throw std::runtime_error(std::string("Couldn't open file: ") +
                                 std::string(argv[1]));
    }
    ComputerClub computer_club = parseClubInitData(input_file);
    parseEvents(computer_club, input_file);
    input_file.close();
    return EXIT_SUCCESS;
}