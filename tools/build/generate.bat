@ECHO OFF

set build_dir=%~dp0..\..\build

if not exist "%build_dir%" (
    mkdir "%build_dir%"
)

pushd "%build_dir%"
set CMAKE=%~dp0..\..\external\tundra\external\cmake\bin\cmake
%cmake% -G "Ninja Multi-Config" ..\tools\build\ -Wno-dev
popd