echo Building all
sh ./scripts/build.sh

echo Running benchmark...
./benchmark --count 8 --size 200

echo Clearing...
sh ./scripts/clear.sh