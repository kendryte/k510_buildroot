#!/bin/bash


cmake -DCMAKE_BUILD_TYPE=Release                     \
      -DCMAKE_INSTALL_PREFIX=/app/ai/exe         \
      -DCMAKE_TOOLCHAIN_FILE=cmake/Riscv64.cmake  \
      ..

make -j && make install

popd
