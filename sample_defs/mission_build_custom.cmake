#
# Example mission_build_custom.cmake
# ----------------------------------
#
# This file will be automatically included in the top level ("mission") build scope
#
# Definitions and options specified here will be used when building local tools and
# other code that runs on the development host, but do _NOT_ apply to flight software
# (embedded) code or anything built for the target machine. 
#
# These options assume a GCC toolchain but a similar set should be applicable to clang.
#
add_compile_options(
    -std=c99                # Target the C99 standard (without gcc extensions) 
    -pedantic               # Issue all the warnings demanded by strict ISO C
    -Wall                   # Warn about most questionable operations
    -Wstrict-prototypes     # Warn about missing prototypes
    -Wwrite-strings         # Warn if not treating string literals as "const"
    -Wpointer-arith         # Warn about suspicious pointer operations
    -Wcast-align            # Warn about casts that increase alignment requirements
    -Werror                 # Treat warnings as errors (code should be clean) 
)

# The _XOPEN_SOURCE directive is required for glibc to enable conformance with the
# the X/Open standard version 6, which includes POSIX.1c as well as SUSv2/UNIX98 extensions.
add_definitions(
    -D_XOPEN_SOURCE=600
)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/config")
  # Copy all .h files from "config" to "build/inc"
  file(GLOB header_cfg_files "${CMAKE_CURRENT_LIST_DIR}/config/*.h")
  file(COPY ${header_cfg_files} DESTINATION "${CMAKE_BINARY_DIR}/inc")

  # TODO: If config/native/default_cpu1 exists, copy it as well (sub native, default, and cpu1 for appropriate variables)
  # ${ARCH_BINARY_DIR}/inc
  # ${MISSION_BINARY_DIR}/inc
  # ${CMAKE_BINARY_DIR}/inc - 'build' folder
  
endif()
