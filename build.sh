#!/bin/zsh
clang -dynamiclib rd_route/rd_route.c weird_memory.c -o libbootstrap.dylib
clang launcher.cpp osxinj/injector.cpp osxinj/mach_inject.c -ldl -lc++ -g -o launcher
clang main.c -L. -lbootstrap -g
