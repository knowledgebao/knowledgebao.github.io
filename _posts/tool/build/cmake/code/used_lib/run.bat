rm -r build
cmake -B build -G Ninja
cmake --build build
cd build
helloword.exe
cd ..
