@REM call .\build__clean.bat
cmake -B ./build -S .
cmake --build ./build --config Release
cd build/Release
Orbitons.exe