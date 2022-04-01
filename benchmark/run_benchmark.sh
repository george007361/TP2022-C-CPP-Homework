echo Building all
sh ./scripts/build.sh

echo Running benchmark...
./benchmark --count 3 --size 100

echo Clearing...
sh ./scripts/clear.sh