echo Building all
sh ./scripts/build.sh

echo Running benchmark...
./benchmark --count 5 --size 30

echo Clearing...
sh ./scripts/clear.sh