# CMakeList.txt: iq_convert_sample에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

project ("iq_convert_sample" CXX)

set(CMAKE_CXX_STANDARD 20 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (iq_convert_sample main.cpp)
target_link_libraries(iq_convert_sample tbb)

add_custom_command(TARGET iq_convert_sample POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "${CMAKE_SOURCE_DIR}/sample_16t.iq"
     "${CMAKE_BINARY_DIR}" )

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
