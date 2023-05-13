project(lab5)
file(GLOB_RECURSE lab5_SRC
     "./src/*.h"
     "./src/*.cc"
)

add_executable(lab5 ${lab5_SRC})

# find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-nana CONFIG REQUIRED)
    target_link_libraries(lab5 PRIVATE unofficial::nana::nana)
find_package(Matplot++ CONFIG REQUIRED)
    target_link_libraries(lab5 PRIVATE Matplot++::cimg std::filesystem Matplot++::matplot Matplot++::nodesoup)


target_include_directories(lab5 PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
