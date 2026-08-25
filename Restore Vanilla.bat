@echo off
setlocal
cd /d "%~dp0"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0LuvvyOdyssey\RestoreVanilla.ps1"
pause
endlocal
