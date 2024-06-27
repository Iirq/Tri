# Testing library

# Tests need to be added as executables first
add_executable(TriTests)
target_include_directories(TriTests PUBLIC ../include)
target_sources(TriTests
    PRIVATE
            "IntersectionsTests.cpp"
            "Orts3dTests.cpp"
            "TasksExecutorTests.cpp"
            "TestEngine.cpp"
            "TriangleTests.cpp"
            "TriTests.cpp"
            "Vector3dTests.cpp"
    PUBLIC
            "TestEngine.h"
)

target_compile_features(TriTests PUBLIC cxx_std_17)

target_link_libraries(TriTests PRIVATE TriLib)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME TriLibTests COMMAND TriTests) # Command can be a target
