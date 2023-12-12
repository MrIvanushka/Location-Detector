RD /S /Q _BIN
RD /S /Q _LIB
RD /S /Q _BUILD

mkdir _BUILD
cd _BUILD
mkdir MSVC22_64
cd MSVC22_64

cmake -G "Visual Studio 17 2022" -A x64 ../..

pause
start Location_Detector.sln
