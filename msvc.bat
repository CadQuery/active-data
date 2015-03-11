@echo off

call %~dp0env.bat %1 %2 %3

echo Running Visual Studio...

if "%VCVER%" == "vc12" (
  start "%VS120COMNTOOLS%\..\IDE\devenv.exe" msvc\vc12\ActiveData.sln
) else (
  echo "Unsupported version of MS Visual Studio"
  exit 1
)

