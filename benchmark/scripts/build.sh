echo Creating dirs...
mkdir data

echo Building serial...
cmake -S ../ -B build/serial -DUSE_SERIAL=ON
make -C ./build/serial

echo Building parallel...
cmake -S ../ -B build/parallel -DUSE_SERIAL=ON
make -C ./build/parallel

echo Building generator...
g++ ./generator/generator.cpp -o ./generator/generator

echo Building benchmark...
g++ ./src/benchmark.cpp -o ./benchmark

echo Done!