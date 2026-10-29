cmake_minimum_required(VERSION 3.16)
project(KMeansLibrary VERSION 1.0 LANGUAGES CXX)

# Make CMake's actual include paths, compiler, and language flags available to
# editor integrations such as VS Code C/C++ IntelliSense.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

option(KMEANS_BUILD_EXAMPLES "Build the K-means examples" ON)

add_library(kmeans_lib
    src/Centroid_initialization.cpp
    src/Centroid_Update.cpp
    src/Cluster_evaluation.cpp
    src/ClusterAssignment.cpp
    src/ConvergenceDetector.cpp
    src/DataLoader.cpp
    src/DataPreprocessor.cpp
    src/Distance_calculation.cpp
    src/EmptyCluster.cpp
    src/feature_scaler.cpp
)
add_library(KMeansLibrary::kmeans_lib ALIAS kmeans_lib)
set_target_properties(kmeans_lib PROPERTIES
    EXPORT_NAME kmeans_lib
    CXX_EXTENSIONS OFF
)
target_compile_features(kmeans_lib PUBLIC cxx_std_20)
target_include_directories(kmeans_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(KMEANS_BUILD_EXAMPLES)
    add_executable(example_kmeans examples/example_kmeans.cpp)
    target_include_directories(example_kmeans PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/examples)
    target_link_libraries(example_kmeans PRIVATE KMeansLibrary::kmeans_lib)

    add_executable(example_csv_clustering examples/example_csv_clustering.cpp)
    target_include_directories(example_csv_clustering PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/examples)
    target_link_libraries(example_csv_clustering PRIVATE KMeansLibrary::kmeans_lib)
endif()

if(BUILD_TESTING)
    function(add_kmeans_test test_name test_source)
        add_executable(${test_name} "tests/${test_source}")
        target_link_libraries(${test_name} PRIVATE KMeansLibrary::kmeans_lib)
        # Keep assert()-based checks active even when the whole project is
        # configured as Release (which normally defines NDEBUG).
        if(MSVC)
            target_compile_options(${test_name} PRIVATE /UNDEBUG)
        else()
            target_compile_options(${test_name} PRIVATE -UNDEBUG)
        endif()
        add_test(NAME ${test_name} COMMAND ${test_name})
    endfunction()

    add_kmeans_test(test_centroid_initialization test_centroid_initialization.cpp)
    add_kmeans_test(test_centroid_update test_centroid_update.cpp)
    add_kmeans_test(test_cluster_assignment test_cluster_assignment.cpp)
    add_kmeans_test(test_cluster_evaluator test_cluster_evaluator.cpp)
    add_kmeans_test(test_convergence test_convergence.cpp)
    add_kmeans_test(test_data_loader test_data_loader.cpp)
    add_kmeans_test(test_data_preprocessor test_data_preprocessor.cpp)
    add_kmeans_test(test_distance_calculation test_distance_calculation.cpp)
    add_kmeans_test(test_empty_cluster test_empty_cluster.cpp)
    add_kmeans_test(test_feature_scaler test_feature_scaler.cpp)
endif()

install(TARGETS kmeans_lib
    EXPORT KMeansLibraryTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/k_means DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT KMeansLibraryTargets
    FILE KMeansLibraryTargets.cmake
    NAMESPACE KMeansLibrary::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KMeansLibrary
)

configure_package_config_file(
    cmake/KMeansLibraryConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/KMeansLibraryConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KMeansLibrary
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/KMeansLibraryConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/KMeansLibraryConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/KMeansLibraryConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/KMeansLibrary
)
