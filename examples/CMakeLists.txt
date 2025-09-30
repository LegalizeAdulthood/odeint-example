include(CheckLanguage)
check_language(CUDA)

find_package(Boost CONFIG REQUIRED COMPONENTS numeric_odeint)

set(ODEINT_EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/odeint/examples")

function(add_odeint_example target source folder)
    add_executable("${target}" "${source}")
    target_link_libraries("${target}" PRIVATE Boost::numeric_odeint)
    target_folder("${target}" "${folder}")
endfunction()

function(add_boost_example number name)
    set(target "example-${number}-${name}")
    add_odeint_example("${target}" "${ODEINT_EXAMPLES_DIR}/${name}.cpp" "Examples")
endfunction()

function(add_boost_cuda_example number name)
    set(target "example-cuda-${number}-${name}")
    add_odeint_example("${target}" "${ODEINT_EXAMPLES_DIR}/thrust/${name}.cu" "Examples/CUDA")
endfunction()

add_boost_example(1 lorenz)
add_boost_example(3 lorenz_point)
add_boost_example(4 van_der_pol_stiff)

# Corrected version of boost example
add_odeint_example("example-2-chaotic_system" "chaotic_system.cpp" "Examples")
target_include_directories("example-2-chaotic_system" PRIVATE . "${ODEINT_EXAMPLES_DIR}")

if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    #add_boost_cuda_example(1 lorenz_parameters)
endif()
