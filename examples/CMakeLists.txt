# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file at the root of the source tree or at
# <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

add_executable(example example.cpp)
add_executable(month_iterator month_iterator.cpp)
add_executable(wrapped_month_iterator wrapped_month_iterator.cpp)

target_link_libraries(example PRIVATE iterators::iterators)
target_link_libraries(month_iterator PRIVATE iterators::iterators)
target_link_libraries(wrapped_month_iterator PRIVATE iterators::iterators)
