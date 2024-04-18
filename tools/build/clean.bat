@ECHO OFF

if exist "%~dp0..\..\build" (
    rmdir /s /q "%~dp0..\..\build"
)

if exist "%~dp0..\..\.clangd" (
    del "%~dp0..\..\.clangd"
)
