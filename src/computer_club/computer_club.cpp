#include "include/computer_club.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>

ComputerClub::ComputerClub(const int open_time, const int close_time,
                           const uint64_t hourly_cost,
                           const std::size_t total_tables)
    : open_time_(open_time),
      close_time_(close_time),
      hourly_cost_(hourly_cost),
      free_tables_(total_tables),
      total_tables_(total_tables),
      client_table_map_(),
      clients_queue_(),
      tables_(total_tables_) {}

[[nodiscard]] int ComputerClub::getOpenTime() const noexcept {
    return open_time_;
}

[[nodiscard]] int ComputerClub::getCloseTime() const noexcept {
    return close_time_;
}

[[nodiscard]] std::size_t ComputerClub::getTotalTables() const noexcept {
    return total_tables_;
}

[[nodiscard]] std::size_t ComputerClub::getFreeTables() const noexcept {
    return free_tables_;
}

[[nodiscard]] std::size_t ComputerClub::getQueueSize() const noexcept {
    return clients_queue_.size();
}

[[nodiscard]] std::size_t ComputerClub::getClientsTable(
    const std::string& client_name) const noexcept {
    return client_table_map_.at(client_name);
}

[[nodiscard]] std::vector<std::string> ComputerClub::getClientsList() const {
    std::vector<std::string> sorted_clients_list;
    sorted_clients_list.reserve(client_table_map_.size());
    for (const auto& [client_name, _] : client_table_map_) {
        sorted_clients_list.push_back(client_name);
    }
    std::sort(sorted_clients_list.begin(), sorted_clients_list.end());
    return sorted_clients_list;
}

[[nodiscard]] bool ComputerClub::isClientInClub(
    const std::string& client_name) const noexcept {
    return client_table_map_.contains(client_name);
}

[[nodiscard]] bool ComputerClub::isClientPlaying(
    const std::string& client_name) const noexcept {
    return client_table_map_.at(client_name) != kMaxSizeT;
}

[[nodiscard]] bool ComputerClub::isTableBusy(
    const std::size_t& table_ind) const noexcept {
    return tables_[table_ind].is_busy_;
}

[[nodiscard]] std::string ComputerClub::popClientFromQueue() noexcept {
    std::string queue_client_name = std::move(clients_queue_.front());
    clients_queue_.pop();
    return queue_client_name;
}

void ComputerClub::acceptClient(const std::string& client_name,
                                const std::size_t& table_ind) {
    client_table_map_[client_name] = table_ind;
}

void ComputerClub::removeClient(const std::string& client_name) {
    client_table_map_.erase(client_name);
}

void ComputerClub::openTable(const std::size_t& table_ind, const int& time,
                             const std::string& client_name) {
    Table& opened_table = tables_[table_ind];
    opened_table.is_busy_ = true;
    --free_tables_;
    opened_table.client_arrival_time_ = time;
    acceptClient(client_name, table_ind);
}

void ComputerClub::closeTable(const std::size_t& table_ind, const int& time) {
    Table& closed_table = tables_[table_ind];
    int play_time = time - closed_table.client_arrival_time_;
    uint64_t play_hours = static_cast<uint64_t>(play_time / 60);
    if (play_time % 60 != 0) {
        ++play_hours;
    }
    closed_table.revenue_ += play_hours * hourly_cost_;
    closed_table.total_busy_time_ += play_time;
    closed_table.is_busy_ = false;
    ++free_tables_;
}

void ComputerClub::addClientToQueue(const std::string& client_name) {
    clients_queue_.push(client_name);
}

void ComputerClub::displayTablesInfo() const noexcept {
    std::size_t tables_size = tables_.size();
    for (size_t i = 0; i < tables_size; ++i) {
        std::cout << i + 1 << ' ' << tables_[i].revenue_ << ' ';
        displayTime(tables_[i].total_busy_time_);
        std::cout << '\n';
    }
}

void displayTime(const int& time_in_minutes) noexcept {
    std::cout << std::setfill('0') << std::setw(2) << time_in_minutes / 60
              << ':' << std::setw(2) << time_in_minutes % 60;
}
