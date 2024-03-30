# Event ToolKit - C++

## Purpose

Focusing on simplicity and speed, this toolkit will provide classic C++ low level implementation of an event-mechanism and simple FSM.

## Design choices

This implementation will stick with low level mechanisms at the core, allowing the toolkit to be used at any level, delivering **_simple_**, **_fast_** and **_resource efficient_** performance. While the core is a straight forward single-thread solution, open-ended features facilitating more complex solutions are included as optional additions when needed. Any complex behaviors, including non-determinism and async processing must thus be implemented with these extended features and/or on a whole-system level.

ETK is a C++20 static library, with well chosen inline template constructs for flexibility. Target runtime includes AMD64 and ARM64 with RISCV64 planned. The choice between non-heap and heap memory-allocation will deliberately be delegated at compile-time using pools. The extended multi-threaded features **_may_** use C++ standard libraries with heap-only solutions where necessary to keep it simple.

_TBC_

## Validation

Aiming at 100% line-coverage and 70% or better branch-coverage is a reasonable ambition, while not absolutely guaranteed. It is up to the user of this toolkit to validate towards their own requirements. Provided as is, with no guarantees about usability or safety. Use at your own risk!

## Building

This toolkit adopts Conan 2 for building. At this time we use cmake, since this is the primary and most matured solution.

Provided you have conan installed, you can prepare for building using the following commands.

``` bash
$> conan profile detect
...
$> conan install . --build=missing [-s build_type=Debug]
.... will take some time
```

The first command will setup a profile for building on the machine you are running on. The second command will fetch, and if needed build, all dependencies declared in the projects `conanfile.py`.

Then, to actually build this project, run the following.

``` bash
$> conan build . [-s build_type=Debug]
```

This will build the project and you can find the result in ./build/[Debug|Release]/etk/. 

I you wan't the coverage to be generated, you have to do both install and build using the optional Debug build_type. 

View the coverage in a browser at file:///.../etk/cov/index.html.

The unit-tests will run in either case.

There is also a Doxyfile to generate documentation. Just run ...

``` bash
$> doxygen
```

... and view the documentation in a browser @ file:///.../etk/dox/index.html.