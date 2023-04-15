project(lab3)
file(GLOB_RECURSE lab3_SRC
     "./src/*.h"
     "./src/*.cc"
)

add_executable(lab3 ${lab3_SRC})

# find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-nana CONFIG REQUIRED)
    target_link_libraries(lab3 PRIVATE unofficial::nana::nana)
find_package(Matplot++ CONFIG REQUIRED)
    target_link_libraries(lab3 PRIVATE Matplot++::cimg std::filesystem Matplot++::matplot Matplot++::nodesoup)


target_include_directories(lab3 PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
