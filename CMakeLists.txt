project(libtorch-example)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# libtorch
set(Torch_DIR C:/Users/admin/anaconda3/Lib/site-packages/torch/share/cmake/Torch)
set(NVTOOLEXT_HOME "${CMAKE_CURRENT_LIST_DIR}/thirdparty/NvToolsExt+cu116")
unset(ENV{NVTOOLSEXT_PATH})
find_package(Torch QUIET)
if(TORCH_FOUND)
  # kineto has exported some fmtlib symbols, which makes some conflicts.
  LIST(FILTER TORCH_LIBRARIES EXCLUDE REGEX "kineto")
endif()

# Specify the path to the LibTorch library
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find the LibTorch package
find_package(Torch REQUIRED)

# Include directories
include_directories(include ${TORCH_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(libtorch-example ${SOURCES})

# Link the LibTorch library
target_link_libraries(libtorch-example "${TORCH_LIBRARIES}")
target_link_options(libtorch-example PUBLIC "/DELAYLOAD:torch_cuda.dll")
target_link_options(libtorch-example PUBLIC "/DELAYLOAD:torch_cpu.dll")
target_link_options(libtorch-example PUBLIC "/DELAYLOAD:c10.dll")
target_link_options(libtorch-example PUBLIC "/DELAYLOAD:c10_cuda.dll")
# NO_EXPORT 
target_compile_definitions(libtorch-example PUBLIC NO_EXPORT)