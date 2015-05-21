clang -c -g -emit-llvm loop.c
opt -load ./assignment1.so -assignment1 loop.bc > /dev/null
