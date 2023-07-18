#include "tests.h"

int test_prints()
{
    kprint_int(100);
    
    kprint("=============================");
    // try to replicate the bug
    kprint("initalize tests");

    kprint_at("Testing kprint_at, ", 0, 0);
    
    kprint_hex(0x111);

    return 1;
}