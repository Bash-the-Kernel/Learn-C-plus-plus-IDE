@echo off
echo Building C++ Learning IDE...

if not exist build mkdir build
cd build

cmake .. -G "MinGW Makefiles"
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b %errorlevel%
)

cmake --build .
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build successful!
echo Run CppLearningIDE.exe to start the application.
pause
