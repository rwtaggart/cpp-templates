C++ generics and template
---
Quick reference for how to implement generic containers using C++ templates.

This contains some examples about how to use templates and template specializations in C++. This is based on the C++11 standard.

This project is intended to provide quick references for less common things I try to do.

### Compile
```
$ g++ -std=c++11 *.C -o test_generics
```

### Run
```
$ ./test_generics
```
### Tests
TODO:  Add unit test stuff?
 - Google Test (gtest)
 - Custom test

## References

C++ Types
https://en.cppreference.com/w/cpp/language/type

User-defined types (i.e. classes)
https://en.cppreference.com/w/cpp/language/classes

Templates
https://en.cppreference.com/w/cpp/language/templates

typename
https://en.cppreference.com/w/cpp/keyword/typename

typename vs. class specifier
https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates


### Things to add
```
./generics
./generic_types.h
./interface_types.h
./generic_interface_types.h
```

Add variadaic templates example ... ?


### Other examples
- TODO: Add threads example
- TODO: Add macros example
- TODO: Add common compiler options
