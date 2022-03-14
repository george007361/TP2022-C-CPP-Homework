#!/usr/bin/env bash

#cpplint
sudo apt install -y pip
pip install --user cpplint

#clang-tidy
sudo apt install -y clang-tidy
cmake -B build
make -C build

#cpp-check
sudo apt install -y cppcheck

#clang-format
sudo apt install -y clang-format

# #clang-tidy
# printf "\n\n\n------Clang-tidy---------\n"
# find -name "*.c" -o -name "*.h" | egrep -v "gtest|build" | xargs clang-tidy-10 -p ./build/compile_commands.json

# #cpp-check
# printf "\n\n\n------Cppcheck---------\n"
# find -name "*.c" -o -name "*.h" | egrep -v "gtest|build"| xargs cppcheck --enable=all --suppress=checkCastIntToCharAndBack --suppress=missingInclude

# #cpplint
# printf "\n\n\n------Cpplint---------\n"
# find -name "*.c" -o -name "*.h" | egrep -v "gtest|build" | xargs python3 -m cpplint --filter=-build/include_order,-legal/copyright,-readability/casting,-build/include_subdir,-whitespace/comments

# #clang-format
# printf "\n\n\n------Clang-format---------\n"
# find -name "*.c" -o -name "*.h" | egrep -v "gtest|build|serial" | xargs clang-format-10 -dry-run -style=LLVM
