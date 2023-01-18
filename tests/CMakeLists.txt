# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file at the root of the source tree or at
# <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Our tests here are all compile-time tests. However, we want to actually include the tests in the 
# actual compilation in order for them to appear in a (potentially) generated compile commands DB
# which makes editing the test files much easier (when e.g. using clang-based tools)
add_library(test_dummy_lib STATIC)
target_link_libraries(test_dummy_lib PUBLIC iterators::iterators)

function(perform_test test_name)
	get_property(REQUIRED_INCLUDE_DIRS TARGET iterators::iterators PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

	set("${test_name}_source" "${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.cpp")

	file(MD5 "${${test_name}_source}" FILE_HASH)

	if (NOT "${test_name}_file_hash" STREQUAL FILE_HASH OR NOT "${test_name}_succeeded")
		# Ensure that the test case is actually executed
		unset("${test_name}_succeeded" CACHE)
	endif()

	set("${test_name}_file_hash" "${FILE_HASH}" CACHE INTERNAL "")

	try_compile("${test_name}_succeeded" "${CMAKE_CURRENT_BINARY_DIR}"
		SOURCES "${${test_name}_source}"
		OUTPUT_VARIABLE "${test_name}_output"
		CMAKE_FLAGS "-DINCLUDE_DIRECTORIES=${REQUIRED_INCLUDE_DIRS}"
	)

	if (NOT ${test_name}_succeeded)
		message(SEND_ERROR "Test '${test_name}' failed")
		message("Compiler output was\n\n${${test_name}_output}")
	else()
		message(STATUS "Test '${test_name}' succeeded")
	endif()

	target_sources(test_dummy_lib PUBLIC "${${test_name}_source}")

endfunction()

perform_test(constructibility)
perform_test(operator_availability)
perform_test(const_conversion)
