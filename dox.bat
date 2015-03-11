@echo off

REM ===========================================================================
REM Enable delayed expansion of variables in command interpreter
REM ===========================================================================

SETLOCAL ENABLEDELAYEDEXPANSION

REM ===========================================================================
REM Prepare environment variables. Read requested documentation type from
REM user's input
REM ===========================================================================

call env.bat

set PACK_TYPE=%1
set DOXYFILE_NAME=Doxyfile_Workbench
set DOXYFILE_NAME_SUFFIX=

REM ===========================================================================
REM Define target html pack type
REM ===========================================================================

if /I "%PACK_TYPE%" == "chm" (
  set DOXYFILE_NAME_SUFFIX=_CHM
)

REM ===========================================================================
REM Define target documentation type
REM ===========================================================================

echo.
echo ============================================================
echo Workbench documentation by !DOXYFILE_NAME!
echo Root: %DOXYDOC_ROOT%

if /I "%PACK_TYPE%" == "chm" (
  GOTO Skip
)

REM ===========================================================================
REM Remove existing documentation
REM ===========================================================================

echo ------------------------------------------------------------
echo Removing old docs from %DOXYDOC_ROOT%\overview\generated...
rd "%DOXYDOC_ROOT%/overview/generated" /S /Q

:Skip

REM ===========================================================================
REM Establish the environment and run Doxygen
REM ===========================================================================

echo ------------------------------------------------------------
echo Running Doxygen (see the log in doxygen.log)...

REM doxygen.exe -w html header.html footer.html stylesheet.css "%DOXYDOC_ROOT%/!DOXYFILE_NAME!"
REM doxygen.exe -w latex header.tex footer.tex doxygen.sty "%DOXYDOC_ROOT%/!DOXYFILE_NAME!"

doxygen.exe "%DOXYDOC_ROOT%/!DOXYFILE_NAME!" > doxygen.log 2>&1

if /I "%PACK_TYPE%" == "chm" (
  
  REM ===========================================================================
  REM Copy .chm documents
  REM ===========================================================================

  if exist "%DOXYDOC_ROOT%\overview\chm_temp_generated\overview.chm" (
    move "%DOXYDOC_ROOT%\overview\chm_temp_generated\overview.chm" "%DOXYDOC_ROOT%/overview/" 
  )

  REM ===========================================================================
  REM Remove temporary documentation
  REM ===========================================================================

  if exist "%DOXYDOC_ROOT%\overview\chm_temp_generated" (
    rd "%DOXYDOC_ROOT%\overview\chm_temp_generated" /S /Q
  )
  
) else (

  REM ===========================================================================
  REM Generate .pdf documents
  REM ===========================================================================

  if exist "%DOXYDOC_ROOT%/overview/generated/latex" (
    echo ------------------------------------------------------------
    echo Running LaTeX-PDF conversion...

    cd "%DOXYDOC_ROOT%/overview/generated/latex"
    call make.bat > log.txt 2>&1
    copy "refman.pdf" "%DOXYDOC_ROOT%/overview/ActiveData_manual.pdf"
  )
 
)

echo ============================================================
