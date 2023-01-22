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
    call build.bat inc
    goto end
) else if [%1] == [all] (
    call build.bat delete
    call build.bat cmake
    call build.bat inc
    goto end
) else (
    set target=%1
)

if %target%==delete goto tgt_delete
if %target%==clean goto tgt_clean
if %target%==cmake goto tgt_cmake
if %target%==inc goto tgt_inc
if %target%==gtest goto tgt_gtest
echo invalid target %target%
goto end


:tgt_delete
if exist .\build del /F /S /Q .\build\*
goto end

:tgt_cmake
if not exist .\build mkdir build
cd build
cmake -G Ninja ../search_engine
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

:tgt_clean
if not exist .\build goto tgt_clean_fail
cd build
ninja clean -j 10
cd ..
goto end
:tgt_clean_fail
set errorlevel=1
goto end

:tgt_gtest
if not exist .\build goto tgt_gtest_fail
cd build
ninja gtest_main -j 10
cd ..
goto end
:tgt_gtest_fail
set errorlevel=1
goto end

:end
rem cd %save_cwd%
exit /b %errorlevel%
