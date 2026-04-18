# Embedded ML Foundations

A structured, self-directed re-activation of expert-level C for embedded systems, paired with ground-up Python learning for the data and ML side of embedded ML consulting work.

This repository captures my daily progress through two parallel 14-day challenges:

- **C Refresher** — reactivating embedded C skills (pointers, registers, state machines, RTOS patterns)
- **Python Mastery** — building Python fluency from the language up through NumPy, Pandas, and automation

The combined skill set targets **embedded ML consulting**: C for the firmware side, Python for model training, data pipelines, and tooling.

---

## About the Author

**Eric Johnson** — Embedded Systems Engineer, owner of Real-Time Embedded Systems Concepts Inc., based in Orlando, FL. Targeting embedded ML consulting work.

GitHub: [github.com/softwarepro123](https://github.com/softwarepro123)

---

## Repository Structure

```
embedded-ml-foundations/
├── c-refresher/
│   ├── day1_basics.c                    — types, operators, bitwise macros
│   ├── day2_pointers.c                  — pointers, const/volatile, register access
│   ├── day3_arrays_memory.c             — memcpy/memset from scratch, ring buffer
│   └── day4_structs_unions_bitfields.c  — hardware-style struct/union/bit-field patterns
│
└── python-mastery/
    └── day1_basics.py                   — types, f-strings, operators, tracebacks
```

---

## How to Build and Run

### C files

All four C files are standalone, compile with any recent GCC, and run on any host OS. They simulate embedded patterns (hardware registers, ISRs, ring buffers) on the PC so the patterns can be exercised without real hardware.

```bash
cd c-refresher
gcc day1_basics.c -o day1_basics -Wall
./day1_basics
```

Every file compiles cleanly with `-Wall` (all warnings enabled). In professional embedded work, warnings are treated as errors — a habit worth building on day one.

### Python file

Python 3.12 or newer.

```bash
cd python-mastery
python day1_basics.py
```

---

## What Each File Demonstrates

### C Refresher

| File | Topics | Key Patterns |
|------|--------|--------------|
| `day1_basics.c` | Types, `printf` specifiers, bitwise ops | `SET_BIT` / `CLEAR_BIT` / `TOGGLE_BIT` / `READ_BIT` macros |
| `day2_pointers.c` | Pointers, arithmetic, `const`, `volatile` | Hardware register access via `volatile uint32_t *` |
| `day3_arrays_memory.c` | Arrays, memory, manual memcpy/memset | Circular ring buffer with `volatile` head/tail |
| `day4_structs_unions_bitfields.c` | Structs, unions, bit fields | UART register block, endianness via union, packed config |

### Python Mastery

| File | Topics | Key Patterns |
|------|--------|--------------|
| `day1_basics.py` | Types, f-strings, `input()`, `int()`, tracebacks | Reading tracebacks bottom-up; `type()` on every basic type |

---

## Honest Attribution

> **Code in this repository was generated with AI assistance (Claude by Anthropic) as a study aid, then hand-copied by me into my local IDE, compiled with `-Wall`, and hand-debugged until all compiler output cleared and runtime output matched expectations. Every file was built, executed, and verified on my own machine. Explanations and reasoning about each concept were worked through interactively — AI as a tutor, not as a ghostwriter.**

I think transparency matters more than the appearance of solo work — especially in 2026, when working effectively with AI tools is itself a professional skill.

---

## Reference Material

The two 14-day challenge documents that drive this repository are my own planning documents, structured around:

- **C side**: K&R C (2nd ed.), FreeRTOS kernel documentation, STM32/ARM Cortex-M register patterns
- **Python side**: *Python Crash Course* (Matthes, 3rd ed.), official Python docs, Real Python tutorials

Target hardware for the C-side final project: **Raspberry Pi Pico 2** (ARM Cortex-M33).

---

## Progress Tracker

### C Refresher (14 days)
- [x] Day 1 — Variables, types, operators, printf
- [x] Day 2 — Pointers
- [x] Day 3 — Arrays, strings, memory
- [x] Day 4 — Structs, unions, bit fields
- [ ] Day 5 — Functions, function pointers, callbacks
- [ ] Day 6 — Preprocessor, macros, header files
- [ ] Day 7 — **Synthesis:** Simulated UART driver
- [ ] Days 8–13 — Volatile, ISRs, state machines, protocols, memory, FreeRTOS
- [ ] Day 14 — **Synthesis:** Complete embedded system

### Python Mastery (14 days)
- [x] Day 1 — Hello World, types, operators, the REPL
- [ ] Day 2 — Control flow (if / while / for / for-else)
- [ ] Days 3–6 — Data structures, functions, OOP, modules & exceptions
- [ ] Day 7 — **Synthesis:** Contractor Portfolio Manager (CLI tool)
- [ ] Days 8–13 — venv/pip, NumPy, Pandas, requests, automation, pytest
- [ ] Day 14 — **Synthesis:** Job Market Tracker (data tool)

---

## License

MIT — feel free to learn from, fork, or reference.

---

*Updated daily. This repository is a live record of deliberate practice toward a working embedded ML consulting practice.*
