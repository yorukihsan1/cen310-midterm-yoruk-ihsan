# tests/CMakeLists.txt

# Download and include GoogleTest
include(FetchContent)

# ONLINE 
# ----------------------------------------------------------------------------------
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# ----------------------------------------------------------------------------------

# Utility tests
if(ENABLE_UTILITY)
	add_subdirectory(utility)
endif()

# Calculator tests
if(ENABLE_CALCULATOR)
	add_subdirectory(calculator)
endif()

