// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>
#include "KVStore.h"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
    std::cout << "Hello world" << std::endl;
    KVStore store;

    store.put(1, 1);
    std::cout << store.get(1) << std::endl;
    std::cout << "Ending" << std::endl;
}
