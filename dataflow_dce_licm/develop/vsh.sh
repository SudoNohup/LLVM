clang -O0 -emit-llvm -c $1.c -o $1.bc
opt -mem2reg $1.bc -o $1-simp.bc
#opt -load ./dce-pass.so -dce-pass $1-simp.bc -o $1-opt.bc
#opt -load ./licm-pass.so -licm-pass $1-simp.bc -o $1-opt.bc

opt -load ./dce-pass.so -dce-pass $1-simp.bc -o $1-opt1.bc
opt -load ./licm-pass.so -licm-pass $1-opt1.bc -o $1-opt.bc

opt -licm $1-simp.bc -o $1-llvmopt.bc
llvm-dis $1-opt.bc

echo "Unoptimized (with clang)"
clang $1-simp.bc -O0 -o $1-simp
./$1-simp

echo "My LICM optimized (with clang)"
clang $1-opt.bc -O0 -o $1-opt
./$1-opt

echo "LLVM LICM optimized (with clang)"
clang $1-llvmopt.bc -O0 -o $1-llvmopt
./$1-llvmopt

echo "Unoptimized (with gcc)"
llc $1-simp.bc -o $1-simp.s
gcc $1-simp.s -O0 -o $1-simp.native
./$1-simp.native

echo "My LICM optimized (with gcc)"
llc $1-opt.bc -o $1-opt.s
gcc $1-opt.s -O0 -o $1-opt.native
./$1-opt.native

echo "LLVM LICM optimized (with gcc)"
llc $1-llvmopt.bc -o $1-llvmopt.s
gcc $1-llvmopt.s -O0 -o $1-llvmopt.native
./$1-llvmopt.native
