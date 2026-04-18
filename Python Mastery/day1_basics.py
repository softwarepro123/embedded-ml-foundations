"""
day1_basics.py
--------------
Day 1 of the 14-Day Python Mastery Challenge
Topic: Variables, basic types, operators, f-strings, input(),
       and intentionally triggering a traceback.

Author: Eric Johnson (github.com/softwarepro123)
        Code generated with AI assistance, hand-copied,
        and hand-debugged until output matched expectations.

Run: python day1_basics.py
"""


def main():
    # ----- Hello and basic prints -----
    print("Hello, World!")
    print("My name is Eric")
    print("I am learning Python")

    # ----- Basic types with type() verification -----
    name = "Eric"              # str
    age = 47                   # int
    rate = 85.0                # float
    is_available = True        # bool — note the capital T

    print("\n=== Types ===")
    print(f"name: {name!r:>15}  type: {type(name).__name__}")
    print(f"age:  {age:>15}  type: {type(age).__name__}")
    print(f"rate: {rate:>15}  type: {type(rate).__name__}")
    print(f"avail:{str(is_available):>15}  type: {type(is_available).__name__}")

    # ----- f-string formatting demo -----
    print("\n=== f-string Formatting ===")
    print(f"Name: {name}, Age: {age}")
    print(f"Rate: ${rate:.2f}/hr")
    print(f"Weekly (40h): ${rate * 40:,.2f}")
    print(f"Annual:       ${rate * 40 * 52:,.0f}")
    print(f"{name=}, {age=}")   # Python 3.8+ debug f-string

    # ----- Arithmetic operators -----
    print("\n=== Arithmetic ===")
    print(f"2 + 2        = {2 + 2}")
    print(f"10 / 3       = {10 / 3}       (float division)")
    print(f"10 // 3      = {10 // 3}                (integer division)")
    print(f"10 % 3       = {10 % 3}                (modulo)")
    print(f"2 ** 10      = {2 ** 10}             (power)")
    print(f"(100 // 7) * 7 + (100 % 7) = {(100 // 7) * 7 + (100 % 7)}")
    print("(the integer-division identity: (a // b) * b + (a % b) == a)")

    # ----- Comparison operators -----
    print("\n=== Comparisons (each returns a bool) ===")
    print(f"age > 40        -> {age > 40}")
    print(f"age == 47       -> {age == 47}")
    print(f"age != 47       -> {age != 47}")
    print(f"rate <= 85.0    -> {rate <= 85.0}")
    print(f"name == 'eric'  -> {name == 'eric'}    (case sensitive)")

    # ----- input() to int() math -----
    # Demonstrates: input returns str, int() converts, math on the result
    print("\n=== User Input (skipping prompt in demo mode) ===")
    demo_input = "7"   # simulate typing 7; swap with input() for interactive
    number = int(demo_input)
    print(f"Input was: {demo_input!r}")
    print(f"Converted to int: {number}")
    print(f"{number} squared is {number ** 2}")
    print(f"{number} cubed is   {number ** 3}")

    # ----- Intentional traceback demo -----
    # We CATCH the exception here so the rest of the script runs.
    # Then print the traceback so you can practice reading it.
    print("\n=== Intentional Traceback Exercise ===")
    print("Calling int('not a number') — this raises ValueError:")
    try:
        int("not a number")
    except ValueError as e:
        print(f"  Exception type: {type(e).__name__}")
        print(f"  Message:        {e}")
        print("\nLesson: read tracebacks BOTTOM-UP.")
        print("  - Last line tells you WHAT went wrong (exception + message)")
        print("  - Line above tells you the exact code that failed")
        print("  - Lines further up show the call chain that led there")


if __name__ == "__main__":
    main()
