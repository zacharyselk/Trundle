@ECHO oFF
:: Runs the cmake build scripts to build Engine and Driver

set old_dir=%cd%

:: Move to scripts dir
cd /D "%~dp0"
if not exist "..\build" md ..\build
cd ..\build

:: Build everything
echo ----------------------------Building Engine--------------------------------
cmake .. -DBUILD_LIB=ON
cmake --build .
echo ---------------------------------------------------------------------------
echo.
echo ----------------------------Building Driver--------------------------------
cmake .. -DBUILD_LIB=OFF
cmake --build .
echo ---------------------------------------------------------------------------
echo.

:: Move the dll into the binary dir
echo ----------------------------Post Build Steps-------------------------------
cd ..
for /R %%i in (lib\*.dll) DO (
    echo Copying %%i to %cd%\bin
    xcopy %%i bin /Y >NUL
)
echo ---------------------------------------------------------------------------
echo.

:: Return to the original dir
cd %old_dir%
echo Finished