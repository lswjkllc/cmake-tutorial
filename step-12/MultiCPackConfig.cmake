# cd debug
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# cmake --build .
# cd ../release
# cmake -DCMAKE_BUILD_TYPE=Release ..
# cmake --build .

include("release/CPackConfig.cmake")

set(
    CPACK_INSTALL_CMAKE_PROJECTS
    "debug;Tutorial;ALL;/"
    "release;Tutorial;ALL;/"
)