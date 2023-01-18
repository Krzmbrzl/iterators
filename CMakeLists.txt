# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file at the root of the source tree or at
# <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

cmake_minimum_required(VERSION 3.10)

project(iterators
	VERSION 1.0.0
	DESCRIPTION "A library allowing easy implementation of STL-style iterators"
	LANGUAGES CXX
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(iterators_lib INTERFACE)

target_include_directories(iterators_lib INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_compile_features(iterators_lib INTERFACE cxx_std_17)

add_library(iterators::iterators ALIAS iterators_lib)

if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	add_subdirectory(examples)
	add_subdirectory(tests)
endif()
