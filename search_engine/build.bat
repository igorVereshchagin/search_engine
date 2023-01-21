@echo off

rem set save_cwd=%~dp0

call cmake_path.bat
if not %errorlevel%==0 (
    echo cmake path failed!
    goto end
)

call ninja_path.bat
if not %errorlevel%==0 (
    echo ninja path failed!
    goto end
)

call mingw_path.bat
if not %errorlevel%==0 (
    echo mingw path failed!
    goto end
)

if [%1] == [] (
    call build.bat clean
    call build.bat cmake
    call build.bat inc
    goto end
) else (
    set target=%1
)

echo %target%

if %target%==clean goto tgt_clean
if %target%==cmake goto tgt_cmake
if %target%==inc goto tgt_inc
goto end


:tgt_clean
if exist .\build del /F /S /Q .\build\*
goto end

:tgt_cmake
if not exist .\build mkdir build
cd build
cmake -G Ninja ../
if not %errorlevel%==0 goto end
cd ..
goto end

:tgt_inc
if not exist .\build goto tgt_inc_fail
cd build
ninja -j 10
cd ..
goto end
:tgt_inc_fail
set errorlevel=1
goto end

:end
rem cd %save_cwd%
exit /b %errorlevel%
