find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(lmi_test testmain.cpp)
target_include_directories(lmi_test SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(lmi_test PRIVATE ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES} Threads::Threads lmi)

gtest_add_tests(lmi_test "" testmain.cpp)
add_clang_tidy_check(lmi_test)