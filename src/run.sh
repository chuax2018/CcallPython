
echo "run shell script."

cd ../build
cmake ..
make clean
make

cd ../bin

./ccallpy

cd ../src

echo "shell script done."
