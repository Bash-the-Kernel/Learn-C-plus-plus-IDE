# Building on Windows

## Quick Setup

### Option 1: Using Visual Studio (Recommended)

1. **Install Visual Studio 2022 Community** (free)
   - Download: https://visualstudio.microsoft.com/downloads/
   - During installation, select "Desktop development with C++"

2. **Install Qt 6**
   - Download: https://www.qt.io/download-open-source
   - Install Qt 6.x with MSVC 2022 64-bit component

3. **Build**
   ```cmd
   mkdir build
   cd build
   set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2022_64
   cmake ..
   cmake --build . --config Release
   ```

### Option 2: Using MinGW

1. **Install MinGW-w64**
   - Download: https://github.com/niXman/mingw-builds-binaries/releases
   - Extract to `C:\mingw64`
   - Add `C:\mingw64\bin` to PATH

2. **Install Qt 6**
   - Download: https://www.qt.io/download-open-source
   - Install Qt 6.x with MinGW 64-bit component

3. **Build**
   ```cmd
   mkdir build
   cd build
   set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\mingw_64
   set PATH=C:\mingw64\bin;%PATH%
   cmake .. -G "MinGW Makefiles"
   cmake --build .
   ```

## Troubleshooting

### "CMake was unable to find a build program"
- Install Visual Studio or MinGW
- Ensure compiler is in PATH

### "Qt6 not found"
- Set CMAKE_PREFIX_PATH to Qt installation
- Example: `set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2022_64`

### "Compiler not found"
- Open "x64 Native Tools Command Prompt" for Visual Studio
- Or add MinGW bin to PATH

## Quick Test

```cmd
g++ --version
cmake --version
```

Both should work before building.
