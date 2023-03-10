project(lab1)
file(GLOB_RECURSE lab1_SRC
     "./src/*.h"
     "./src/*.cc"
)

add_executable(lab1 ${lab1_SRC})

find_package(spdlog CONFIG REQUIRED)

find_package(Matplot++ CONFIG REQUIRED)
    target_link_libraries(lab1 PRIVATE Matplot++::cimg std::filesystem Matplot++::matplot Matplot++::nodesoup)


target_include_directories(lab1 PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
