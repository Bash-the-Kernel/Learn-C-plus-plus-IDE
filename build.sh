#!/bin/bash

echo "Building C++ Learning IDE..."

mkdir -p build
cd build

cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"
echo "Run ./CppLearningIDE to start the application."
