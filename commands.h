#pragma once
#include <cstdint>

struct uint128_t{
    uint64_t first;
    uint64_t second;
};

enum CommandType {
    READ_LBA,
    WRITE_LBA,
    FLUSH,
    IDENTIFY,
    SEEK,
    RETRY,
    REALLOCATE,
    ABORT
};

enum Priority {
    NORMAL,
    HIGH,
    URGENT
};

enum Status {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    FAILED
};

// 16 bytes worth
class Command {
    public:
        CommandType type; // first 3 bits [2:0]
        // LBA params:
        uint32_t address; // [34:3]
        uint32_t length; // [66:35]
        uint32_t *data_buff; // [98:67]

        Priority priority = NORMAL; // 2 MSBs [127:126]
        int retry_count = 5; // Max retries remaining
        int timeout = 2000; // in ms
        volatile Status status = PENDING;

        Command(uint128_t cmd){
            type = (CommandType)(cmd.first & 0x3);
            address = (uint32_t)(cmd.first & 0x3FFF8);
            length = (uint32_t)(cmd & 0x3FFF80000);
            data_buff = (uint32_t *)(cmd.second & 0x3FFF800000000);
            priority = (Priority)(cmd.second & 0xC000000000000000);
        }
};