# Hard-drive-command-queue-library
Library for simulating a command queue for hard drive storage  


Command Types:  
READ_LBA - Reads from logical block addresses  
WRITE_LBA - Writes to LBAs  
FLUSH -   
IDENTIFY - Returns data about the drive's capabilities, capacity, model, etc.  
SEEK - Moves the read/write head to a different location  
RETRY - Re-attempts a read/write that failed with adjusted parameters  
REALLOCATE - marks a bad sector/LBA and remaps it to an empty one  
ABORT - Cancel all current commands in queue  
