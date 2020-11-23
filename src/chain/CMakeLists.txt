# generated with cmake/gen_cmake_skeleton.py, DO NOT MODIFY.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
set(PUBLIC_HEADERS
    chain-datastruct.h
    chain-den-graph.h
    chain-denominator.h
    chain-generic-numerator.h
    chain-kernels-ansi.h
    chain-numerator.h
    chain-supervision.h
    chain-training.h
    language-model.h
)

if(CUDA_FOUND)
    cuda_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
    cuda_compile(CUDA_OBJS
        chain-kernels.cu
    )
endif()

add_library(kaldi-chain
    chain-den-graph.cc
    chain-denominator.cc
    chain-generic-numerator.cc
    chain-numerator.cc
    chain-supervision.cc
    chain-training.cc
    language-model.cc
    ${CUDA_OBJS}
)

target_include_directories(kaldi-chain PUBLIC 
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
     $<INSTALL_INTERFACE:include/kaldi>
)

target_link_libraries(kaldi-chain PUBLIC
    kaldi-cudamatrix
    kaldi-lat
    kaldi-fstext
    kaldi-hmm
    kaldi-tree
    kaldi-util
    kaldi-matrix
    kaldi-base
)

