@echo off

SET "PATH_DEB=@3RDPARTY_DLL_DEB_PATH@;@CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG@;%PATH%"
SET "PATH_REL=@3RDPARTY_DLL_PATH@;@CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE@;%PATH%"
SET "PATH=%PATH_DEB%"

SET CSF_PluginDefaults=@ACTDATA_OCAF_PLUGIN_DIR@
SET CSF_ResourcesDefaults=@ACTDATA_OCAF_PLUGIN_DIR@
SET AD_TEST_DUMP=@AD_TEST_DUMP@
SET AD_TEST_DESCR=@AD_TEST_DESCR@
SET AD_DATA=@AD_DATA@
