include(CMakeForceCompiler)

# target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR rv64)

# cross compiler
set(CMAKE_C_COMPILER riscv64-linux-gcc)
set(CMAKE_CXX_COMPILER riscv64-linux-g++)
