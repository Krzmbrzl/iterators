// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include "TestCore.hpp"

#include <iterators/iterator_facade.hpp>

#include <iterator>
#include <type_traits>

using OutputIterator = iterators::iterator_facade< TestCore< std::output_iterator_tag > >;

static_assert(!std::is_default_constructible_v< OutputIterator >,
			  "Output iterators should NOT be default-constructible");
static_assert(std::is_copy_constructible_v< OutputIterator >, "Iterators must be copy-constructible");
static_assert(std::is_copy_assignable_v< OutputIterator >, "Iterators must be copy-assignable");


using InputIterator = iterators::iterator_facade< TestCore< std::input_iterator_tag > >;
static_assert(!std::is_default_constructible_v< InputIterator >, "Input iterators should NOT be default-constructible");
static_assert(std::is_copy_constructible_v< InputIterator >, "Iterators must be copy-constructible");
static_assert(std::is_copy_assignable_v< InputIterator >, "Iterators must be copy-assignable");


using ForwardIterator = iterators::iterator_facade< TestCore< std::forward_iterator_tag > >;
static_assert(std::is_default_constructible_v< ForwardIterator >, "Forward iterators should be default-constructible");
static_assert(std::is_copy_constructible_v< ForwardIterator >, "Iterators must be copy-constructible");
static_assert(std::is_copy_assignable_v< ForwardIterator >, "Iterators must be copy-assignable");


using BidirectionalIterator = iterators::iterator_facade< TestCore< std::bidirectional_iterator_tag > >;
static_assert(std::is_default_constructible_v< BidirectionalIterator >,
			  "Bidirectional iterators should be default-constructible");
static_assert(std::is_copy_constructible_v< BidirectionalIterator >, "Iterators must be copy-constructible");
static_assert(std::is_copy_assignable_v< BidirectionalIterator >, "Iterators must be copy-assignable");


using RandomAccessIterator = iterators::iterator_facade< TestCore< std::random_access_iterator_tag > >;
static_assert(std::is_default_constructible_v< RandomAccessIterator >,
			  "Random access iterators should be default-constructible");
static_assert(std::is_copy_constructible_v< RandomAccessIterator >, "Iterators must be copy-constructible");
static_assert(std::is_copy_assignable_v< RandomAccessIterator >, "Iterators must be copy-assignable");
