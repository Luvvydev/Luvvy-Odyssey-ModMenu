@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0LuvvyOdyssey\InstallAndLaunch.ps1"
if errorlevel 1 pause
endlocal
