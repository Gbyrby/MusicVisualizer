# CMakeList.txt : CMake project for CmakeTest_vspkg, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MusicVisualizer")

set(CMAKE_CXX_STANDARD 17)





# Add source to this project's executable.
add_executable (MusicVisualizer "MusicVisualizer.cpp" "MusicVisualizer.h" "App.h" "App.cpp" "Renderer.h" "Renderer.cpp" "Audio.h" "Audio.cpp" "FileSystem.h")

# this is heuristically generated, and may not be correct
find_package(imgui CONFIG REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE imgui::imgui)

# this is heuristically generated, and may not be correct
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(MusicVisualizer PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(SndFile REQUIRED)
find_package(FFTW3 REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE SndFile::sndfile FFTW3::fftw3)

find_package(GLEW REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE GLEW::GLEW)

find_package(portaudio CONFIG REQUIRED)
target_link_libraries(MusicVisualizer PRIVATE portaudio)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MusicVisualizer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
