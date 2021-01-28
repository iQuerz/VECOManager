curl.exe -sA "MS" https://webinstall.dev/pathman | powershell
webi pathman
@echo Setting variables...
SET thispath=%~dp0
%SystemDrive%
cd %UserProfile%
@echo Creating new install directory...
mkdir .veco
cd .veco
@echo Copying binaries...
copy "%thispath%veco.bat" "%CD%"
copy "%thispath%main.exe" "%CD%"
copy "%thispath%data.txt" "%CD%"
@echo Adding VECO to System Environment Path...
start cmd
/k setlocal enabledelayedexpansion
/k FOR %%f IN (%CD%) DO (
  set "f=%%f"
  set "f=!f:\=/!"
)
/k pathman add %f%
/c endlocal
@echo Setup Complete
@Pause