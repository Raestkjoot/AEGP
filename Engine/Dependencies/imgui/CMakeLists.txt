project(imgui VERSION 1.91.4)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

set(imgui_folder "${CMAKE_CURRENT_LIST_DIR}")

file(GLOB imgui_core "*.cpp" "*.h")
set(imgui_extra
    "${imgui_folder}/backends/imgui_impl_opengl3.h" # OpenGL
    "${imgui_folder}/backends/imgui_impl_opengl3.cpp" # OpenGL
	"${imgui_folder}/backends/imgui_impl_glfw.h" # GLFW
	"${imgui_folder}/backends/imgui_impl_glfw.cpp" # GLFW

	"${imgui_folder}/misc/debuggers/imgui.natvis" # Visual Studio Debugging
	"${imgui_folder}/misc/debuggers/imgui.natstepfilter"

	"${imgui_folder}/misc/cpp/imgui_stdlib.cpp" # std::string
)

add_library(${PROJECT_NAME} STATIC
    ${imgui_core}
    ${imgui_extra}
)

target_link_libraries(${PROJECT_NAME}
    glfw ${GLFW_LIBRARIES}
    glad
    glm
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_CURRENT_LIST_DIR}/backends")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_CURRENT_LIST_DIR}/misc")
