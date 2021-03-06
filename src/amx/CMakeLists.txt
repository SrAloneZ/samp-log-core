include(AMXConfig)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(
  -DAMX_ALIGN
  -DAMX_CLEANUP
  -DAMX_EXEC
  -DAMX_FLAGS
  -DAMX_GETADDR
  -DAMX_INIT
  -DAMX_REGISTER
  -DAMX_SETCALLBACK
  -DAMX_SETDEBUGHOOK
  -DAMX_XXXNATIVES
  -DAMX_XXXPUBLICS
  -DAMX_XXXUSERDATA
  -DAMX_XXXSTRING
  -DAMX_ANSIONLY
  -DAMX_NODYNALOAD
)

add_library(amx STATIC
  amx.c
  amx.h
  amxaux.c
  amxaux.h
  amxdbg.c
  amxdbg.h
  getch.h
  osdefs.h
  sclinux.h
  amx2.h
  amxplugin2.cpp
)

if(UNIX)
	target_compile_options(amx PUBLIC "-Wno-unused-result")
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
