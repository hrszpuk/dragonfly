file(GLOB_RECURSE DRAGONFLY_LIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(dragonfly_core STATIC ${DRAGONFLY_LIB_SOURCES})

target_include_directories(dragonfly_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(dragonfly_core PUBLIC cxx_std_20)

llvm_map_components_to_libnames(LLVM_LIBS
    core
    support
    irreader
    executionengine
    orcjit
    native
)

target_link_libraries(dragonfly_core PUBLIC ${LLVM_LIBS})