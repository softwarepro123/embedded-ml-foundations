/*
 * day5_functions_pointers.c
 *
 * 14-Day Embedded C Refresher Challenge — Day 5
 * Topic: Functions, Function Pointers, Callbacks, and the HAL Pattern
 *
 * Eric Johnson — Real-Time Embedded Systems Concepts Inc.
 * Orlando, FL — April 2026
 *
 * Build:
 *   gcc day5_functions_pointers.c -o day5 -Wall -std=c11
 *
 * Concepts demonstrated:
 *   - Function pointer declaration and typedef
 *   - Callback pattern — passing functions as arguments
 *   - ISR vector table — array of function pointers
 *   - NULL guard before calling a function pointer
 *   - HAL driver struct — bundled function pointers as a driver interface
 *
 * Note: All three patterns run on the host PC with no hardware required.
 * The ISR vector table and HAL driver struct mirror exactly how the
 * Raspberry Pi Pico 2 C SDK and FreeRTOS driver layers are structured.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ═══════════════════════════════════════════════════════════════
 * PART 1 — Basic Callback Pattern
 *
 * A callback is a function passed as an argument to another function.
 * The receiving function calls it at the appropriate time.
 * This is how drivers notify application code of events.
 * ═══════════════════════════════════════════════════════════════ */

/* typedef: name the function pointer type for readability */
typedef void (*callback_fn_t)(void);

/*
 * run_after_delay() -- accepts a callback as a parameter
 * Simulates a delay then calls whatever function was passed in.
 * The caller decides what happens -- not this function.
 */
void run_after_delay(callback_fn_t cb) {
    printf("Simulating delay...\n");
    cb();   /* call the function through the pointer */
}

/* two different callbacks -- same signature, different behavior */
void on_complete(void) {
    printf("Transfer complete!\n");
}

void on_timeout(void) {
    printf("Operation timed out!\n");
}

/* ═══════════════════════════════════════════════════════════════
 * PART 2 — ISR Vector Table
 *
 * An array of function pointers -- one slot per interrupt number.
 * When hardware fires interrupt N, the dispatcher calls isr_table[N].
 * This mirrors the ARM Cortex-M vector table on the Pico 2.
 * ═══════════════════════════════════════════════════════════════ */

/* typedef: an ISR handler takes nothing and returns nothing */
typedef void (*irq_handler_t)(void);

/* vector table -- 8 interrupt slots, initialized to NULL */
static irq_handler_t isr_table[8] = {0};

/*
 * register_isr() -- store a handler at a specific IRQ slot
 * Called at startup to connect hardware interrupts to C functions.
 */
void register_isr(uint8_t irq_num, irq_handler_t handler) {
    isr_table[irq_num] = handler;
}

/*
 * dispatch_isr() -- called when hardware interrupt fires
 * NULL guard is critical -- calling a NULL function pointer
 * causes a hard fault on ARM Cortex-M hardware.
 */
void dispatch_isr(uint8_t irq_num) {
    if (isr_table[irq_num] != NULL) {
        isr_table[irq_num]();   /* call the registered handler */
    }
}

/* ISR handlers -- short and fast, exactly as required in real firmware */
void uart_isr(void) {
    printf("UART interrupt handled\n");
}

void timer_isr(void) {
    printf("Timer interrupt handled\n");
}

/* ═══════════════════════════════════════════════════════════════
 * PART 3 — HAL Driver Struct Pattern
 *
 * Function pointers bundled into a struct form a driver interface.
 * The application calls through the struct -- it never needs to know
 * which physical UART it is talking to.
 * Swap the struct and the entire driver changes -- zero application
 * code changes required. This is the Hardware Abstraction Layer.
 * ═══════════════════════════════════════════════════════════════ */

/* the driver interface -- a struct of function pointers */
typedef struct {
    void    (*init)(void);
    void    (*send)(uint8_t byte);
    uint8_t (*receive)(void);
    void    (*deinit)(void);
} UartDriver_t;

/* ── UART A implementation ── */
void uartA_init(void)             { printf("UART A init\n"); }
void uartA_send(uint8_t byte)     { printf("UART A sending: 0x%02X\n", byte); }
uint8_t uartA_receive(void)       { printf("UART A receive\n"); return 0x42; }
void uartA_deinit(void)           { printf("UART A deinit\n"); }

/* ── UART B implementation ── */
void uartB_init(void)             { printf("UART B init\n"); }
void uartB_send(uint8_t byte)     { printf("UART B sending: 0x%02X\n", byte); }
uint8_t uartB_receive(void)       { printf("UART B receive\n"); return 0x99; }
void uartB_deinit(void)           { printf("UART B deinit\n"); }

/* ═══════════════════════════════════════════════════════════════
 * MAIN
 * ═══════════════════════════════════════════════════════════════ */

int main(void) {

    /* ── Part 1: Callbacks ── */
    printf("--- Part 1: Callbacks ---\n");
    run_after_delay(on_complete);
    run_after_delay(on_timeout);

    /* ── Part 2: ISR vector table ── */
    printf("\n--- Part 2: ISR vector table ---\n");
    register_isr(0, uart_isr);
    register_isr(1, timer_isr);
    dispatch_isr(0);   /* fires uart_isr */
    dispatch_isr(1);   /* fires timer_isr */

    /* ── Part 3: HAL driver struct ── */
    printf("\n--- Part 3: HAL driver struct ---\n");

    /* build driver A -- wire up all function pointers */
    UartDriver_t driverA = {
        .init    = uartA_init,
        .send    = uartA_send,
        .receive = uartA_receive,
        .deinit  = uartA_deinit
    };

    /* build driver B -- different implementation, same interface */
    UartDriver_t driverB = {
        .init    = uartB_init,
        .send    = uartB_send,
        .receive = uartB_receive,
        .deinit  = uartB_deinit
    };

    /* use driver A -- application never calls uartA_* directly */
    driverA.init();
    driverA.send(0xAB);
    uint8_t val = driverA.receive();
    printf("Received: 0x%02X\n", val);
    driverA.deinit();

    /* swap to driver B -- identical calls, completely different hardware */
    printf("\n");
    driverB.init();
    driverB.send(0xCD);
    val = driverB.receive();
    printf("Received: 0x%02X\n", val);
    driverB.deinit();

    return 0;
}

/*
 * Expected output:
 *
 * --- Part 1: Callbacks ---
 * Simulating delay...
 * Transfer complete!
 * Simulating delay...
 * Operation timed out!
 *
 * --- Part 2: ISR vector table ---
 * UART interrupt handled
 * Timer interrupt handled
 *
 * --- Part 3: HAL driver struct ---
 * UART A init
 * UART A sending: 0xAB
 * UART A receive
 * Received: 0x42
 * UART A deinit
 *
 * UART B init
 * UART B sending: 0xCD
 * UART B receive
 * Received: 0x99
 * UART B deinit
 */


