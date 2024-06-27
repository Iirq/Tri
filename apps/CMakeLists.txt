add_executable(TriApp tri.cpp)
target_include_directories(TriApp PUBLIC ../include)
target_compile_features(TriApp PRIVATE cxx_std_17)

target_link_libraries(TriApp PRIVATE TriLib)

