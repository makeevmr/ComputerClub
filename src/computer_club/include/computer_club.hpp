#ifndef COMPUTER_CLUB_SRC_COMPUTER_CLUB
#define COMPUTER_CLUB_SRC_COMPUTER_CLUB

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <limits>

class ComputerClub {
public:
    ComputerClub(const int open_time, const int close_time,
                 const uint64_t hourly_cost, const std::size_t total_tables);

    [[nodiscard]] int getOpenTime() const noexcept;

    [[nodiscard]] int getCloseTime() const noexcept;

    [[nodiscard]] std::size_t getTotalTables() const noexcept;

    [[nodiscard]] std::size_t getFreeTables() const noexcept;

    [[nodiscard]] std::size_t getQueueSize() const noexcept;

    [[nodiscard]] std::size_t getClientsTable(
        const std::string& client_name) const noexcept;

    [[nodiscard]] std::vector<std::string> getClientsList() const;

    [[nodiscard]] bool isClientInClub(
        const std::string& client_name) const noexcept;

    [[nodiscard]] bool isClientPlaying(
        const std::string& client_name) const noexcept;

    [[nodiscard]] bool isTableBusy(const std::size_t& table_ind) const noexcept;

    [[nodiscard]] std::string popClientFromQueue() noexcept;

    void acceptClient(const std::string& client_name,
                      const std::size_t& table_ind);

    void removeClient(const std::string& client_name);

    void openTable(const std::size_t& table_ind, const int& time,
                   const std::string& client_name);

    void closeTable(const std::size_t& table_ind, const int& time);

    void addClientToQueue(const std::string& client_name);

    void displayTablesInfo() const noexcept;

private:
    struct Table {
        bool is_busy_;
        int client_arrival_time_;
        int total_busy_time_;
        uint64_t revenue_;
    };

    const int open_time_;
    const int close_time_;
    const uint64_t hourly_cost_;
    std::size_t free_tables_;
    const std::size_t total_tables_;
    std::unordered_map<std::string, std::size_t> client_table_map_;
    std::queue<std::string> clients_queue_;
    std::vector<Table> tables_;

    static constexpr std::size_t kMaxSizeT =
        std::numeric_limits<std::size_t>::max();
};

void displayTime(const int& time_in_minutes) noexcept;

#endif  // COMPUTER_CLUB_SRC_COMPUTER_CLUB
