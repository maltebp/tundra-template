@ECHO OFF

IF NOT "%~1"=="release" IF NOT "%~1"=="debug" (
    echo Invalid configuration - must be debug/release 1>&2
    exit /b
)

set build_dir=%~dp0..\..\build

if not exist "%build_dir%" (
    echo "%build_dir%" folder does not exist - did you generate first?
    exit /b -1
)

pushd %~dp0 || exit /b

set CMAKE=%~dp0..\..\external\tundra\external\cmake\bin\cmake
%cmake% --build "%build_dir%" --config %~1 || goto done

:done
popd