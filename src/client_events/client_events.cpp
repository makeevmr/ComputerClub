#include "include/client_events.hpp"

#include <iostream>

static void printEvent(const int& time, const int& event_id,
                       const std::string& event_body) {
    displayTime(time);
    std::cout << ' ' << event_id << ' ' << event_body << '\n';
}

void arrive(ComputerClub& computer_club, const int& time,
            const std::string& client_name) {
    if (computer_club.isClientInClub(client_name)) {
        printEvent(time, 13, "YouShallNotPass");
        return;
    }
    if (computer_club.getOpenTime() > time ||
        computer_club.getCloseTime() < time) {
        printEvent(time, 13, "NotOpenYet");
        return;
    }
    computer_club.acceptClient(client_name,
                               std::numeric_limits<std::size_t>::max());
}

void takeTable(ComputerClub& computer_club, const int& time,
               const std::string& client_name, const std::size_t& table_ind) {
    if (!computer_club.isClientInClub(client_name)) {
        printEvent(time, 13, "ClientUnknown");
        return;
    }
    if (computer_club.isTableBusy(table_ind)) {
        printEvent(time, 13, "PlaceIsBusy");
        return;
    }
    if (computer_club.isClientPlaying(client_name)) {
        computer_club.closeTable(computer_club.getClientsTable(client_name),
                                 time);
    }
    computer_club.openTable(table_ind, time, client_name);
}

void wait(ComputerClub& computer_club, const int& time,
          const std::string& client_name) {
    if (computer_club.getFreeTables() > 0) {
        printEvent(time, 13, "ICanWaitNoLonger!");
        return;
    }
    if (computer_club.getQueueSize() > computer_club.getTotalTables()) {
        printEvent(time, 11, client_name);
        leave(computer_club, time, client_name);
        return;
    }
    computer_club.addClientToQueue(client_name);
}

void leave(ComputerClub& computer_club, const int& time,
           const std::string& client_name) {
    if (!computer_club.isClientInClub(client_name)) {
        printEvent(time, 13, "ClientUnknown");
        return;
    }
    if (computer_club.isClientPlaying(client_name)) {
        std::size_t table_ind = computer_club.getClientsTable(client_name);
        computer_club.closeTable(table_ind, time);
        if ((computer_club.getQueueSize()) > 0 &&
            (time < computer_club.getCloseTime())) {
            std::string client_from_queue = computer_club.popClientFromQueue();
            printEvent(time, 12,
                       client_from_queue + std::string(" ") +
                           std::to_string(table_ind + 1));
            takeTable(computer_club, time, client_from_queue, table_ind);
        }
    }
    computer_club.removeClient(client_name);
}

void leaveAtTheEnd(ComputerClub& computer_club, const int& time,
                   const std::string& client_name) {
    printEvent(time, 11, client_name);
    leave(computer_club, time, client_name);
}
