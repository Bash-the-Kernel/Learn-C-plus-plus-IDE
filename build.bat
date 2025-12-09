@echo off
echo Building C++ Learning IDE...
echo.

REM Check for compilers
where g++ >nul 2>&1
if %errorlevel% equ 0 (
    echo Found: g++
    set COMPILER_FOUND=1
)

where cl >nul 2>&1
if %errorlevel% equ 0 (
    echo Found: MSVC
    set COMPILER_FOUND=1
)

if not defined COMPILER_FOUND (
    echo ERROR: No C++ compiler found!
    echo.
    echo Please install one of:
    echo   1. MinGW-w64: https://www.mingw-w64.org/
    echo   2. Visual Studio with C++ tools
    echo.
    echo After installation, add to PATH and restart terminal.
    pause
    exit /b 1
)

if not exist build mkdir build
cd build

REM Try different generators
echo Configuring with CMake...
cmake .. >nul 2>&1
if %errorlevel% equ 0 goto build

cmake .. -G "MinGW Makefiles" >nul 2>&1
if %errorlevel% equ 0 goto build

cmake .. -G "Visual Studio 17 2022" >nul 2>&1
if %errorlevel% equ 0 goto build

cmake .. -G "Visual Studio 16 2019" >nul 2>&1
if %errorlevel% equ 0 goto build

cmake .. -G "Ninja" >nul 2>&1
if %errorlevel% equ 0 goto build

echo ERROR: CMake configuration failed with all generators.
echo.
echo Try manually:
echo   cd build
echo   cmake ..
echo   cmake --build .
pause
exit /b 1

:build
echo Configuration successful!
echo Building...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Run: build\Release\CppLearningIDE.exe
echo   or: build\CppLearningIDE.exe
echo.
pause
