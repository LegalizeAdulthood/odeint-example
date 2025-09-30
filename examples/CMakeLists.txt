find_package(Boost CONFIG REQUIRED COMPONENTS numeric_odeint)

set(ODEINT_EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/odeint/examples")

function(add_boost_example number name)
    set(target "example-${number}-${name}")
    add_boost_executable("${target}" "${ODEINT_EXAMPLES_DIR}/${name}.cpp")
    target_link_libraries("${target}" PRIVATE Boost::numeric_odeint)
    target_folder("${target}" "Examples")
endfunction()

function(add_boost_cuda_example number name)
    set(target "example-cuda-${number}-${name}")
    add_boost_executable("${target}" "${ODEINT_EXAMPLES_DIR}/thrust/${name}.cu")
    target_link_libraries("${target}" PRIVATE Boost::numeric_odeint)
    target_folder("${target}" "Examples/CUDA")
endfunction()

add_boost_example(1 lorenz)
#add_boost_example(2 chaotic_system)
add_boost_example(3 lorenz_point)
add_boost_example(4 van_der_pol_stiff)

#add_boost_cuda_example(1 lorenz_parameters)
