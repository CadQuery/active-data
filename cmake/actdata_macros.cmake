# Useful macro

#-------------------------------------------------------------------------------
# Name:    ACTDATA_MAKE_PLATFORM_SHORT_NAME
# Purpose: initializes PLATFORM variable with a relevant value
#-------------------------------------------------------------------------------
macro (ACTDATA_MAKE_PLATFORM_SHORT_NAME)
  if (MSVC)
    set (PLATFORM win)
  else()
    set (PLATFORM lin)
  endif()
endmacro()

#-------------------------------------------------------------------------------
# Name:    ACTDATA_MAKE_COMPILER_SHORT_NAME
# Purpose: initializes COMPILER variable with a relevant value
#-------------------------------------------------------------------------------
macro (ACTDATA_MAKE_COMPILER_SHORT_NAME)
  if (MSVC)
    if (MSVC70)
      set (COMPILER vc7)
    elseif (MSVC80)
      set (COMPILER vc8)
    elseif (MSVC90)
      set (COMPILER vc9)
    elseif (MSVC10)
      set (COMPILER vc10)
    elseif (MSVC11)
      set (COMPILER vc11)
    elseif (MSVC12)
      set (COMPILER vc12)
    elseif (MSVC14)
      set (COMPILER vc14)
    endif()
  elseif (DEFINED CMAKE_COMPILER_IS_GNUCC)
    set (COMPILER gcc)
  elseif (DEFINED CMAKE_COMPILER_IS_GNUCXX)
    set (COMPILER gxx)
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set (COMPILER clang)
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set (COMPILER icc)
  else()
    set (COMPILER ${CMAKE_GENERATOR})
    string (REGEX REPLACE " " "" COMPILER ${COMPILER})
  endif()
endmacro()

#-------------------------------------------------------------------------------
# Name:    ACTDATA_MAKE_COMPILER_BITNESS
# Purpose: initializes COMPILER_BITNESS variable with a relevant value
#-------------------------------------------------------------------------------
macro (ACTDATA_MAKE_COMPILER_BITNESS)
  math (EXPR COMPILER_BITNESS "32 + 32*(${CMAKE_SIZEOF_VOID_P}/8)")
endmacro()

macro (ACTDATA_UNSET VARNAME)
  if (DEFINED ${VARNAME})
    unset (${VARNAME} CACHE)
  endif()
endmacro()

macro (ACTDATA_UNSET_3RDPARTY VARNAME)
  ACTDATA_UNSET ("3RDPARTY_${VARNAME}_DIR")
  ACTDATA_UNSET ("3RDPARTY_${VARNAME}_INCLUDE_DIR")
  ACTDATA_UNSET ("3RDPARTY_${VARNAME}_LIBRARY_DIR")
  ACTDATA_UNSET ("3RDPARTY_${VARNAME}_DLL_DIR")
endmacro()
