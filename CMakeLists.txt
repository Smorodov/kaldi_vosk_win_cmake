# ----------------------------------------------------------------------------
# минимальная версия CMake, способная переварить этот файл
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(NAME kaldi_win_min)
project(${NAME} LANGUAGES CXX)
# Set preprocessor defines
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")
add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_LIB -DWIN32)
#set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DHAVE_OPENBLAS)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc")

include_directories(${CMAKE_SOURCE_DIR}/libstdaudio/include)

include_directories("${CMAKE_SOURCE_DIR}/deps/openfst/src/include")
include_directories("${CMAKE_SOURCE_DIR}/deps/OpenBLAS-v0.2.14-Win64-int32/include")
add_subdirectory(deps/portaudio)
add_subdirectory(deps/openfst)
add_subdirectory(src/base)
add_subdirectory(src/itf)
add_subdirectory(src/matrix)
add_subdirectory(src/util)
add_subdirectory(src/chain)
add_subdirectory(src/gmm)
add_subdirectory(src/hmm)
add_subdirectory(src/ivector)
add_subdirectory(src/tree)
add_subdirectory(src/lm)
add_subdirectory(src/nnet3)
add_subdirectory(src/nnet2)
add_subdirectory(src/cudamatrix)
add_subdirectory(src/decoder)
add_subdirectory(src/lat)
add_subdirectory(src/feat)
add_subdirectory(src/transform)
add_subdirectory(src/fstext)
add_subdirectory(src/rnnlm)
add_subdirectory(src/online2)

set(VOSK_SOURCES
    ${CMAKE_SOURCE_DIR}/vosk_src/kaldi_recognizer.cc
    ${CMAKE_SOURCE_DIR}/vosk_src/language_model.cc
    ${CMAKE_SOURCE_DIR}/vosk_src/model.cc
    ${CMAKE_SOURCE_DIR}/vosk_src/spk_model.cc
    ${CMAKE_SOURCE_DIR}/vosk_src/vosk_api.cc)

add_definitions(-DFST_NO_DYNAMIC_LINKING)
set (openblas_lib "${CMAKE_SOURCE_DIR}/deps/OpenBLAS-v0.2.14-Win64-int32/lib/")
set(LIBS
    kaldi-online2
    kaldi-decoder
    kaldi-ivector
    kaldi-gmm
    kaldi-nnet3
    kaldi-tree
    kaldi-feat
    kaldi-lat
    kaldi-lm
    kaldi-hmm
    kaldi-transform
    kaldi-cudamatrix
    kaldi-matrix
    kaldi-fstext
    kaldi-util
    kaldi-base
    fst
    fstngram
    ${openblas_lib}/libopenblas.dll.a

   # cusparse
   # cudart
   # cuda
   # curand
   # cusolver
   # cublas
)

add_library(vosk STATIC ${VOSK_SOURCES})
include_directories("${CMAKE_SOURCE_DIR}/deps/libstdaudio/include")
include_directories("${CMAKE_SOURCE_DIR}/vosk_src")
include_directories("${CMAKE_SOURCE_DIR}/src")
target_link_libraries(vosk ${LIBS})

set (sources ${CMAKE_SOURCE_DIR}/main.cpp )

add_executable(vosk_recognizer ${sources} )
target_link_libraries(vosk_recognizer vosk)
