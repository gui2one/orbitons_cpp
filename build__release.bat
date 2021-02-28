@REM call .\build__clean.bat
@REM cmake -B ./build -S .
cmake --build ./build --config Release
cd build/Release
Orbitons.exe