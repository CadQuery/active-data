if (ActiveData_USE_TBB)
  if (WIN32)
    ACTDATA_THIRDPARTY_PRODUCT("tbb" "include" "tbb" "tbb" "")
  else()
    ACTDATA_THIRDPARTY_PRODUCT("tbb" "include" "tbb" "libtbb" "lib/intel64/gcc4.8")
  endif()
else()
  ACTDATA_UNSET_3RDPARTY("tbb")
endif()
