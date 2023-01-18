# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file at the root of the source tree or at
# <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

add_executable(example example.cpp)

target_link_libraries(example PRIVATE iterators::iterators)
