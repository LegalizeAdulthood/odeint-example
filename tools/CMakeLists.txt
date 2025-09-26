find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(wxWidgets CONFIG REQUIRED)

add_executable("chaotic-attractor" main.cpp)
target_link_libraries("chaotic-attractor" PUBLIC "dynamical-system" OpenGL::GL glm::glm-header-only glad::glad wx::wxgl wx::core wx::base)
set_target_properties("chaotic-attractor" PROPERTIES WIN32_EXECUTABLE $<PLATFORM_ID:Windows>)
target_folder("chaotic-attractor" "Tools")
