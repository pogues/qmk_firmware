#pragma once

/* shamelessly copied from oberien https://github.com/qmk/qmk_firmware/pull/8359/files# */

#include "quantum.h"

#ifndef COMPOSE_LEN
#define COMPOSE_LEN 3
#endif

bool process_compose(uint16_t keycode, keyrecord_t* record, uint16_t compose_keycode);
bool compose_mapping(uint16_t* sequence, uint8_t len);
void compose_start(void);
void compose_end(void);

/// Compares the first `len` keycode (uint16_t) of the first two arguments
/// and returns the index at which they start to differ or `len` if they are equal.
size_t compose_memcmp_index(uint16_t* seq, uint16_t* input, size_t len);
/// Compares the compose mapping input to the sequence so far.
/// Returns -1 on a full match, 0 on no match, and 1 on a partial match.
/// This is done to reduce the binary size compared to inlining it everywhere
int compose_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len);

#define ARGLEN(...) (sizeof((uint16_t[]){__VA_ARGS__})/sizeof(uint16_t))
#define ARRAYLEN(arr) (sizeof(arr)/sizeof(arr[0]))

#define COMPOSE_MAPPING(INPUT, ACTION) { \
    uint16_t input[] = INPUT; \
    _Static_assert(ARRAYLEN(input) <= COMPOSE_LEN, "Number of keys in Compose input keystroke is too long. Consider increasing COMPOSE_LEN"); \
    uint8_t input_len = ARRAYLEN(input); \
    int res = compose_compare_input(input, input_len, sequence, sequence_len); \
    if (res == -1) { \
        ACTION \
        return false; \
    } else if (res == 1) { \
        return true; \
    } \
}

#define COMPOSE_INPUT(...) \
    {__VA_ARGS__}

#define COMPOSE_ACTION(...) \
    uint16_t actions[] = {__VA_ARGS__}; \
    for (int i = 0; i < ARRAYLEN(actions); i++) { \
        register_code16(actions[i]); \
        unregister_code16(actions[i]); \
    }
