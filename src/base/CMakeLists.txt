# generated with cmake/gen_cmake_skeleton.py, DO NOT MODIFY.
set(PUBLIC_HEADERS
    io-funcs-inl.h
    io-funcs.h
    kaldi-common.h
    kaldi-error.h
    kaldi-math.h
    kaldi-types.h
    kaldi-utils.h
    timer.h
)

add_library(kaldi-base STATIC
    io-funcs.cc
    kaldi-error.cc
    kaldi-math.cc
    kaldi-utils.cc
    timer.cc
)

target_include_directories(kaldi-base PUBLIC 
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
     $<INSTALL_INTERFACE:include/kaldi>
)

