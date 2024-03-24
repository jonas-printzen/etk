# Event ToolKit - C++

## Purpose

Focusing on simplicity and speed, this toolkit will provide classic C++ low level implementation of an event-mechanism and simple FSM.

## Design choices

This implementation will stick with low level mechanisms at the core, allowing the toolkit to be used at any level, delivering **_simple_**, **_fast_** and **_resource efficient_** performance. While the core is a straight forward single-thread solution, open-ended features facilitating more complex solutions are included as optional additions when needed. Any complex behaviors, including non-determinism and async processing must thus be implemented with these extended features and/or on a whole-system level.

ETK is a C++20 static library, with well chosen inline template constructs for flexibility. Target runtime includes AMD64 and ARM64 with RISCV64 planned. The choice between non-heap and heap memory-allocation will deliberately be delegated at compile-time using pools. The extended multi-threaded features **_may_** use C++ standard libraries with heap-only solutions where necessary to keep it simple.

_TBC_

## Validation

Aiming at 100% line-coverage and 70% or better branch-coverage is a reasonable ambition, while not absolutely guaranteed. It is up to the user of this toolkit to validate towards their own requirements. Provided as is, with no guarantees about usability or safety. Use at your own risk!