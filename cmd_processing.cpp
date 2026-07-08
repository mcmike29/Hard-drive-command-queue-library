#include "commands.h"
#include <vector>
#include <algorithm>

static int URG_FLAG = 0;

// Command Queue via controller
std::vector<Command> cmd_queue;

// eventually want this to be getting streamed data
Command cmd_receiver(uint64_t curr_8_bytes){
    uint128_t curr_16_bytes = {curr_8_bytes, next_8_bytes};
    return new Command(curr_16_bytes);
}
// Command Queue push helper
int cmd_push(Command new_cmd){
    if (new_cmd.priority == URGENT){
        // insert cmd at beginning of the queue
        cmd_queue.insert(cmd_queue.begin(), new_cmd);
        // raise urgent flag so FSM sees URGENT command
        URG_FLAG = 1;
    }
    else if (new_cmd.priority == HIGH){
        // insert the current command after the last highest priority command
        auto last_high = std::find_if(cmd_queue.begin(), cmd_queue.end(), [](Command item) {
            return item.priority == HIGH;
        });
        cmd_queue.insert(last_high, new_cmd);
    }
    else{
        cmd_queue.push_back(new_cmd); // push cmd onto queue normally
    }
}
// FSM to handle current command
// - returns err code, 0 on succesful operation, -1 or err macro on failure or cmd pause
int cmd_handler(volatile Command curr_cmd){
    
}

int main(){
    return 0;
}