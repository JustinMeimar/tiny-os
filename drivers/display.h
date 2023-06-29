#include "ports.h"
#define MAX_COLS 80
#define MAX_ROWS 25
#define VIDEO_MEM 0xb8000

void kprint_at(const char* msg, uint8_t row, uint8_t col);
void kprint(const char* msg);

void set_cursor_index(uint16_t index);
uint16_t get_cursor_index();

uint16_t get_cursor_index_from_coords(uint8_t row, uint8_t col);

uint8_t get_row_from_cursor_index(uint16_t index);
uint8_t get_col_from_cursor_index(uint16_t index);