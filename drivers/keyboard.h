#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ports.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"

static char keymap[128] = {
    '\0',  '\0', '1',  '2', '3', '4', '5', '6', '7', '8',
    '9',  '0', '-', '=', '\0', '\0', 'Q', 'W', 'E', 'R',
    'T',  'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '\0',
    'A',  'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M',  ',', '.', '/', '\0', '*', '\0', ' ', '\0', '\0',
};

void init_keyboard();

#endif