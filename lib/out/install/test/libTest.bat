
@echo off
SETLOCAL

CALL "%~dp0lib\libTest.exe" %*
EXIT /B %ERRORLEVEL%
ENDLOCAL
