# Simple paint

Works on Windows and Linux

Requirements:
* Qt 6.6.0
* cmake 3.14

Windows:
* On Windows add QTDIR system variable with the value C:\QtDir\QtVersion\msvc2019_64.
* Then add these paths to the Path system variable: %QTDIR%\lib and %QTDIR%\bin

Build:
```cmd
mkdir build
cmake -S . -Bbuild
cmake --build build --config Release
```
