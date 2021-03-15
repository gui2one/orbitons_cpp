@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Debug\Orbitons.exe
cmake --build ./build --config Debug
cd build/Debug
Orbitons.exe