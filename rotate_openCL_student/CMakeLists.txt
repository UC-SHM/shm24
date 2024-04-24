    #Minimal OpenCL CMakeLists.txt 

    cmake_minimum_required (VERSION 3.6)

    project(rotate_ocl)

    # Handle OpenCL
    find_package(OpenCL 2.0 REQUIRED)
    include_directories(${OpenCL_INCLUDE_DIRS})
    link_directories(${OpenCL_LIBRARY})

    add_executable (rotate_ocl
    	 bmpfuncs.c
    	 hostcode.cpp
    	 rotate.cpp)
    	 
    target_include_directories (rotate_ocl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries (rotate_ocl ${OpenCL_LIBRARY} gomp )