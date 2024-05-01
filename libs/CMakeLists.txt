find_package(Boost CONFIG REQUIRED COMPONENTS numeric_odeint)

add_library("dynamical-system"
    "include/dynamical-system/dynamical-system.h"
    "dynamical-system.cpp"
)
target_include_directories("dynamical-system" PUBLIC include)
target_link_libraries("dynamical-system" PRIVATE Boost::numeric_odeint)
target_folder("dynamical-system" "Libraries")
