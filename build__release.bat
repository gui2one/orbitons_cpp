@REM call .\build__clean.bat
@REM cmake -B ./build -S .
del .\build\Release\Orbitons.exe
cmake --build ./build --config Release
cd build/Release
Orbitons.exe