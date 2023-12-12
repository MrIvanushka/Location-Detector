RD /S /Q _BIN
RD /S /Q _LIB
RD /S /Q _BUILD

mkdir _BUILD
cd _BUILD
mkdir MSVC19_64
cd MSVC19_64

cmake -G "Visual Studio 16 2019" -A x64 ../..

pause
start Location_Detector.sln
