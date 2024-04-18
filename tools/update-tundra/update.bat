@echo off


:: Getting Tundra source path
set tundra_source_path_file=%~dp0source-path

if not exist "%tundra_source_path_file%" (
    echo Tundra source path file "%tundra_source_path_file%" was not found 1>&2
    exit /b -1
)

set /p tundra_source_path=<"%tundra_source_path_file%"
if not exist "%tundra_source_path%" (
    echo Tundra source path "%tundra_source_path%" does not exist
    exit /b -1
)

echo.
echo Using Tundra source in: "%tundra_source_path%"

:: Generate, build and deploy tundra
echo.
echo Building Tundra...

call "%tundra_source_path%\tools\build\deploy.bat" || goto :error

echo. Removing existing Tundra
rm -rf "%~dp0\..\..\external\tundra" || goto :error

echo.
echo Copying Tundra
xcopy "%tundra_source_path%\build\deploy\" "%~dp0..\..\external\tundra\" /s /q > nul || goto :error

echo.
echo Updated Tundra successfully
exit /b 0

:error
echo.
echo Updating Tundra failed...
exit /b -1

:success
