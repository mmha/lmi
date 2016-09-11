add_library(lmi INTERFACE)

if(UNIX OR MINGW)
    target_compile_options(lmi INTERFACE -Wall -Wextra -Wpedantic -fdiagnostics-color=always)
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(lmi INTERFACE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic)
endif()

set_property(TARGET lmi PROPERTY INTERFACE_lmi_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET lmi PROPERTY INTERFACE_lmi_MINOR_VERSION ${PROJECT_VERSION_MINOR})

target_include_directories(lmi INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS lmi EXPORT lmiTargets
        INCLUDES DESTINATION include
)
install(DIRECTORY lmi
        DESTINATION include
        COMPONENT devel
)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/lmi/lmiConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT lmiTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/lmi/lmiTargets.cmake"
       NAMESPACE lmi::
)
configure_file(lmiConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/lmi/lmiConfig.cmake"
        COPYONLY
)

set(ConfigPackageLocation lib/cmake/lmi)
install(EXPORT lmiTargets
        FILE lmiTargets.cmake
        NAMESPACE lmi::
        DESTINATION ${ConfigPackageLocation}
)
install(FILES lmiConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/lmi/lmiConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation}
        COMPONENT devel
)