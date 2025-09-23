find_package(glad CONFIG REQUIRED)
find_package(wxWidgets CONFIG REQUIRED)

add_executable("chaotic-attractor" main.cpp)
target_link_libraries("chaotic-attractor" PUBLIC "dynamical-system" glad::glad wx::core wx::base)
set_target_properties("chaotic-attractor" PROPERTIES WIN32_EXECUTABLE $<PLATFORM_ID:Windows>)
target_folder("chaotic-attractor" "Tools")
