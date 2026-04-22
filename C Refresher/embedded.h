/*
 * embedded.h
 *
 * Professional embedded systems header file
 * Demonstrates include guards, register macros,
 * conditional debug output, and static inline functions.
 *
 * Eric Johnson — Real-Time Embedded Systems Concepts Inc.
 * Orlando, FL — April 2026
 *
 * Usage:
 *   #include "embedded.h"
 *
 *   To enable debug output:
 *   #define DEBUG  (before the include, or via -DDEBUG compiler flag)
 */

#ifndef EMBEDDED_H
#define EMBEDDED_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* ── Register manipulation macros ──────────────────────────────
 * These four macros are the foundation of bare-metal embedded C.
 * Every hardware register access uses one of these patterns.
 * The extra parentheses around every parameter and the whole
 * expression prevent operator precedence bugs when macros are
 * expanded inside larger expressions.
 * ─────────────────────────────────────────────────────────────*/
#define SET_BIT(r,b)    ((r) |=  (1U << (b)))
#define CLEAR_BIT(r,b)  ((r) &= ~(1U << (b)))
#define TOGGLE_BIT(r,b) ((r) ^=  (1U << (b)))
#define READ_BIT(r,b)   (((r) >> (b)) & 1U)

/* ── Milliseconds to RTOS ticks ─────────────────────────────────
 * Used with FreeRTOS vTaskDelay() and xQueueReceive() timeouts.
 * portTICK_PERIOD_MS is defined by FreeRTOS -- not available on
 * the host PC, only on the Pico 2 with FreeRTOS included.
 * ─────────────────────────────────────────────────────────────*/
#define MS_TO_TICKS(ms)  ((ms) / portTICK_PERIOD_MS)

/* ── Debug print macro ──────────────────────────────────────────
 * When DEBUG is defined: expands to a real printf call.
 * When DEBUG is not defined: expands to an empty do/while loop
 * that the compiler optimizes completely away -- zero overhead
 * in production firmware.
 *
 * Usage:
 *   DEBUG_PRINT("value: %d\n", x);
 *
 * In development:  prints to terminal
 * In production:   generates zero machine code
 * ─────────────────────────────────────────────────────────────*/
#ifdef DEBUG
  #define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
  #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

/* ── clamp() inline utility function ───────────────────────────
 * Clamps a value between lo and hi bounds.
 * Used for ADC scaling, PWM duty cycle limiting, sensor ranges.
 *
 * static inline: compiled directly into the call site like a
 * macro, but with full type checking like a real function.
 * No function call overhead -- important in real-time loops.
 * ─────────────────────────────────────────────────────────────*/
static inline uint32_t clamp(uint32_t val, uint32_t lo, uint32_t hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

#endif /* EMBEDDED_H */
