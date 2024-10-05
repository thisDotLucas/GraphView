cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt6_DIR C:/Qt/6.2.0/msvc2019_64/lib/cmake/Qt6/)
set(CMAKE_PREFIX_PATH C:/Qt/6.2.0/msvc2019_64) 

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(GraphView)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


add_subdirectory(GraphView)
