# generated with cmake/gen_cmake_skeleton.py, DO NOT MODIFY.
set(PUBLIC_HEADERS
    basic-filebuf.h
    common-utils.h
    const-integer-set-inl.h
    const-integer-set.h
    edit-distance-inl.h
    edit-distance.h
    hash-list-inl.h
    hash-list.h
    kaldi-cygwin-io-inl.h
    kaldi-holder-inl.h
    kaldi-holder.h
    kaldi-io-inl.h
    kaldi-io.h
    kaldi-pipebuf.h
    kaldi-semaphore.h
    kaldi-table-inl.h
    kaldi-table.h
    kaldi-thread.h
    parse-options.h
    simple-io-funcs.h
    simple-options.h
    stl-utils.h
    table-types.h
    text-utils.h
)

add_library(kaldi-util STATIC
    kaldi-holder.cc
    kaldi-io.cc
    kaldi-semaphore.cc
    kaldi-table.cc
    kaldi-thread.cc
    parse-options.cc
    simple-io-funcs.cc
    simple-options.cc
    text-utils.cc
)

target_include_directories(kaldi-util PUBLIC 
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
     $<INSTALL_INTERFACE:include/kaldi>
)

target_link_libraries(kaldi-util PUBLIC
    kaldi-matrix
    kaldi-base
)
