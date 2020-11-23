# generated with cmake/gen_cmake_skeleton.py, DO NOT MODIFY.
set(PUBLIC_HEADERS
    cblas-wrappers.h
    compressed-matrix.h
    jama-eig.h
    jama-svd.h
    kaldi-blas.h
    kaldi-matrix-inl.h
    kaldi-matrix.h
    kaldi-vector-inl.h
    kaldi-vector.h
    matrix-common.h
    matrix-functions-inl.h
    matrix-functions.h
    matrix-lib.h
    numpy-array.h
    optimization.h
    packed-matrix.h
    sp-matrix-inl.h
    sp-matrix.h
    sparse-matrix.h
    srfft.h
    tp-matrix.h
)

add_library(kaldi-matrix
    compressed-matrix.cc
    kaldi-matrix.cc
    kaldi-vector.cc
    matrix-functions.cc
    numpy-array.cc
    optimization.cc
    packed-matrix.cc
    qr.cc
    sp-matrix.cc
    sparse-matrix.cc
    srfft.cc
    tp-matrix.cc
)

target_include_directories(kaldi-matrix PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
     $<INSTALL_INTERFACE:include/kaldi>
)

target_link_libraries(kaldi-matrix PUBLIC
    kaldi-base
)
