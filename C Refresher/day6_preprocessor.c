/*
 * day6_preprocessor.c
 *
 * 14-Day Embedded C Refresher Challenge — Day 6
 * Topic: Preprocessor, Macros, and Header Files
 *
 * Eric Johnson — Real-Time Embedded Systems Concepts Inc.
 * Orlando, FL — April 2026
 *
 * Build (debug output ON):
 *   gcc day6_preprocessor.c -o day6 -Wall -std=c11
 *
 * Build (debug output OFF -- simulates production firmware):
 *   gcc day6_preprocessor.c -o day6 -Wall -std=c11 -UDEBUG
 *
 * Concepts demonstrated:
 *   - Professional header file with include guards
 *   - Register manipulation macros (SET/CLEAR/TOGGLE/READ_BIT)
 *   - Conditional debug output via #ifdef DEBUG
 *   - Variadic macro with __VA_ARGS__
 *   - static inline utility function
 *   - Include guard protection (#ifndef / #define / #endif)
 */

#define DEBUG   /* comment this out to silence all debug output */

#include "embedded.h"

int main(void) {

    /* ── Test 1: Register macros ────────────────────────────── */
    printf("---Test 1: Register macros ---\n");

    uint32_t reg = 0x00000000;

    SET_BIT(reg, 0);
    printf("SET_BIT(reg, 0):    0x%08X\n", reg);

    SET_BIT(reg, 7);
    printf("SET_BIT(reg, 7):    0x%08X\n", reg);

    CLEAR_BIT(reg, 0);
    printf("CLEAR_BIT(reg, 0):  0x%08X\n", reg);

    TOGGLE_BIT(reg, 7);
    printf("TOGGLE_BIT(reg, 7): 0x%08X\n", reg);

    uint32_t bit = READ_BIT(reg, 7);
    printf("READ_BIT(reg, 7):   %u\n", bit);

    /* ── Test 2: DEBUG_PRINT macro ──────────────────────────── */
    printf("\n--- Test 2: DEBUG_PRINT ---\n");
    DEBUG_PRINT("DEBUG is ON -- reg value is: 0x%08X\n", reg);
    printf("If you can see the line above, DEBUG is defined\n");
    printf("Comment out #define DEBUG and recompile to silence it\n");

    /* ── Test 3: clamp() inline function ────────────────────── */
    printf("\n--- Test 3: clamp() ---\n");

    uint32_t val;

    val = clamp(50, 0, 100);
    printf("clamp(50,  0, 100) = %u\n", val);

    val = clamp(150, 0, 100);
    printf("clamp(150, 0, 100) = %u\n", val);

    val = clamp(0, 10, 90);
    printf("clamp(0,  10,  90) = %u\n", val);

    /* ── Test 4: Include guard ──────────────────────────────── */
    printf("\n--- Test 4: Include guard ---\n");
    printf("embedded.h is protected by #ifndef EMBEDDED_H\n");
    printf("No matter how many files include it, it compiles once\n");

    return 0;
}

/*
 * Expected output (with DEBUG defined):
 *
 * ---Test 1: Register macros ---
 * SET_BIT(reg, 0):    0x00000001
 * SET_BIT(reg, 7):    0x00000081
 * CLEAR_BIT(reg, 0):  0x00000080
 * TOGGLE_BIT(reg, 7): 0x00000000
 * READ_BIT(reg, 7):   0
 *
 * --- Test 2: DEBUG_PRINT ---
 * DEBUG is ON -- reg value is: 0x00000000
 * If you can see the line above, DEBUG is defined
 * Comment out #define DEBUG and recompile to silence it
 *
 * --- Test 3: clamp() ---
 * clamp(50,  0, 100) = 50
 * clamp(150, 0, 100) = 100
 * clamp(0,  10,  90) = 10
 *
 * --- Test 4: Include guard ---
 * embedded.h is protected by #ifndef EMBEDDED_H
 * No matter how many files include it, it compiles once
 */
