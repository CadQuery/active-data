@echo off

set VCVER=%1
set ARCH=%2

if /I "%ARCH%" == "win32" set ARCH=32
if /I "%ARCH%" == "win64" set ARCH=64

if "%VCVER%" == "" set VCVER=vc12
if "%ARCH%"  == "" set ARCH=64

set CASDEB=d
set BUILD_CONFIG=debug
if not "%3" == "" (
    if /I "%3" == "Debug" (
        set CASDEB=d
        set BUILD_CONFIG=debug
    ) else if /I "%3" == "Release" (
        set CASDEB=
        set BUILD_CONFIG=release
    ) else (
        echo Error: third argument ^(%3^) should specify build mode,
        echo one of: Debug or Release
        exit
    )
)

if exist %~dp0custom.bat call %~dp0custom.bat

set DEB=%CASDEB%

rem ===========================================================================
rem Setting Active Data environment 
rem ===========================================================================

if "%AD_ROOT%"        == "" set "AD_ROOT=%~dp0"
if "%AD_RESOURCES%"   == "" set "AD_RESOURCES=%AD_ROOT%res"
if "%AD_LIB%"         == "" set "AD_LIB=%AD_ROOT%win%ARCH%\%VCVER%\lib%DEB%"
if "%AD_INC%"         == "" set "AD_INC=%AD_ROOT%include"
if "%AD_BIN%"         == "" set "AD_BIN=%AD_ROOT%win%ARCH%\%VCVER%\bin%DEB%"
if "%AD_TEST%"        == "" set "AD_TEST=%AD_ROOT%test"
if "%AD_DATA%"        == "" set "AD_DATA=%AD_ROOT%data"
if "%AD_TEST_DUMP%"   == "" set "AD_TEST_DUMP=%AD_TEST%\dumping"
if "%AD_TEST_DESCR%"  == "" set "AD_TEST_DESCR=%AD_TEST%\descr"
if "%AD_PRODUCTS%"    == "" set "AD_PRODUCTS=%AD_ROOT%3rd-parties"

rem ===========================================================================
rem Setting OCCT environment 
rem ===========================================================================

if "%PRODUCTS_PATH%" == "" set "PRODUCTS_PATH=%AD_PRODUCTS%"
if "%CASROOT%"       == "" set "CASROOT=%AD_PRODUCTS%\occt"

set "CAS_INC=%CASROOT%\inc"
set "CAS_LIB=%CASROOT%\win%ARCH%\%VCVER%\lib%DEB%"
set "CAS_BIN=%CASROOT%\win%ARCH%\%VCVER%\bin%DEB%"

set MMGT_OPT=2
set MMGT_REENTRANT=1

rem Call OCCT env.bat -- all 3-rd party binaries will be added to PATH
call %CASROOT%\env.bat %VCVER% win%ARCH% %BUILD_CONFIG%

rem ===========================================================================
rem Setting TBB environment (concurrent collections and execution) 
rem ===========================================================================

if "%TBB_ROOT%" == "" set "TBB_ROOT=%AD_PRODUCTS%\tbb44_20150728oss"
set "TBB_INC=%TBB_ROOT%\include\tbb"
set "TBB_LIB=%TBB_ROOT%\lib\intel64\%VCVER%"
set "TBB_BIN=%TBB_ROOT%\bin\intel64\%VCVER%"

rem ===========================================================================
rem Setting environment for Doxygen
rem ===========================================================================

if "%DOXYGEN_ROOT%" == "" set "DOXYGEN_ROOT=%AD_PRODUCTS%\doxygen-1.8.5"
set "DOXYGEN_BIN=%DOXYGEN_ROOT%\bin"
set "DOXYDOC_ROOT=%AD_ROOT:\=/%doc/workbench"

rem ===========================================================================
rem Setting environment for MikTeX
rem ===========================================================================

if "%MIKTEX_ROOT%" == "" set "MIKTEX_ROOT=%AD_PRODUCTS%\miktex-2.9"
set "MIKTEX_BIN=%MIKTEX_ROOT%\miktex\bin"

rem ===========================================================================
rem Adjust PATH variable
rem ===========================================================================

set "PATH=%DOXYGEN_BIN%;%MIKTEX_BIN%;%TBB_BIN%;%AD_BIN%;%CAS_BIN%;%PATH%"

rem ===========================================================================
rem Customize OCCT environment variables
rem ===========================================================================

set "CSF_PluginDefaults=%AD_RESOURCES%"
set "CSF_ResourcesDefaults=%AD_RESOURCES%"
set "CSF_ActiveDataDrawDefaults=%AD_RESOURCES%"

echo ...
echo ARCH         = %ARCH%
echo VCVER        = %VCVER%
echo BUILD_CONFIG = %BUILD_CONFIG%
echo AD_ROOT      = %AD_ROOT%
echo AD_PRODUCTS  = %AD_PRODUCTS%
echo CASROOT      = %CASROOT%
echo TBB_ROOT     = %TBB_ROOT%
echo ...
