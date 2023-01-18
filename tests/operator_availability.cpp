// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include "TestCore.hpp"

#include <iterators/iterator_facade.hpp>
#include <iterators/type_traits.hpp>

#include <iterator>
#include <type_traits>

// Output iterators
using OutputIterator = iterators::iterator_facade< TestCore< std::output_iterator_tag > >;

static_assert(iterators::operators::supports_prefix_increment_v< OutputIterator >,
			  "Output iterators should support the prefix increment operator");
static_assert(iterators::operators::supports_postfix_increment_v< OutputIterator >,
			  "Output iterators should support the postfix increment operator");
static_assert(iterators::operators::supports_star_dereference_v< OutputIterator >,
			  "Output iterators should support the star dereference operator");
static_assert(!iterators::operators::supports_arrow_dereference_v< OutputIterator >,
			  "Output iterators should NOT support the arrow dereference operator");
static_assert(!iterators::operators::supports_equality_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the equality operator");
static_assert(!iterators::operators::supports_inequality_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the inequality operator");
static_assert(!iterators::operators::supports_prefix_decrement_v< OutputIterator >,
			  "Output iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_postfix_decrement_v< OutputIterator >,
			  "Output iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_addition_with_arithmetic_v< OutputIterator >,
			  "Output iterators should NOT support addition with arithmetic types");
static_assert(!iterators::operators::supports_addition_to_arithmetic_v< OutputIterator >,
			  "Output iterators should NOT support addition to arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_arithmetic_v< OutputIterator >,
			  "Output iterators should NOT support subtraction with arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_iterator_v< OutputIterator >,
			  "Output iterators should NOT support subtraction with another iterator");
static_assert(!iterators::operators::supports_less_than_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the less than operator");
static_assert(!iterators::operators::supports_greater_than_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the greater than operator");
static_assert(!iterators::operators::supports_less_equal_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the less-equal than operator");
static_assert(!iterators::operators::supports_greater_equal_comparison_v< OutputIterator >,
			  "Output iterators should NOT support the greater-equal than operator");
static_assert(!iterators::operators::supports_add_assign_v< OutputIterator >,
			  "Output iterators should NOT support the add-assign operator");
static_assert(!iterators::operators::supports_subtract_assign_v< OutputIterator >,
			  "Output iterators should NOT support the subtract-assign operator");
static_assert(!iterators::operators::supports_offset_dereference_v< OutputIterator >,
			  "Output iterators should NOT support the bracket (offset-dereference) operator");



// Input iterators
using InputIterator = iterators::iterator_facade< TestCore< std::input_iterator_tag > >;

static_assert(iterators::operators::supports_prefix_increment_v< InputIterator >,
			  "Input iterators should support the prefix increment operator");
static_assert(iterators::operators::supports_postfix_increment_v< InputIterator >,
			  "Input iterators should support the postfix increment operator");
static_assert(iterators::operators::supports_star_dereference_v< InputIterator >,
			  "Input iterators should support the star dereference operator");
static_assert(iterators::operators::supports_arrow_dereference_v< InputIterator >,
			  "Input iterators should support the arrow dereference operator");
static_assert(iterators::operators::supports_equality_comparison_v< InputIterator >,
			  "Input iterators should support the equality operator");
static_assert(iterators::operators::supports_inequality_comparison_v< InputIterator >,
			  "Input iterators should support the inequality operator");
static_assert(!iterators::operators::supports_prefix_decrement_v< InputIterator >,
			  "Input iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_postfix_decrement_v< InputIterator >,
			  "Input iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_addition_with_arithmetic_v< InputIterator >,
			  "Input iterators should NOT support addition with arithmetic types");
static_assert(!iterators::operators::supports_addition_to_arithmetic_v< InputIterator >,
			  "Input iterators should NOT support addition to arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_arithmetic_v< InputIterator >,
			  "Input iterators should NOT support subtraction with arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_iterator_v< InputIterator >,
			  "Input iterators should NOT support subtraction with another iterator");
static_assert(!iterators::operators::supports_less_than_comparison_v< InputIterator >,
			  "Input iterators should NOT support the less than operator");
static_assert(!iterators::operators::supports_greater_than_comparison_v< InputIterator >,
			  "Input iterators should NOT support the greater than operator");
static_assert(!iterators::operators::supports_less_equal_comparison_v< InputIterator >,
			  "Input iterators should NOT support the less-equal than operator");
static_assert(!iterators::operators::supports_greater_equal_comparison_v< InputIterator >,
			  "Input iterators should NOT support the greater-equal than operator");
static_assert(!iterators::operators::supports_add_assign_v< InputIterator >,
			  "Input iterators should NOT support the add-assign operator");
static_assert(!iterators::operators::supports_subtract_assign_v< InputIterator >,
			  "Input iterators should NOT support the subtract-assign operator");
static_assert(!iterators::operators::supports_offset_dereference_v< InputIterator >,
			  "Input iterators should NOT support the bracket (offset-dereference) operator");



// Forward iterators
using ForwardIterator = iterators::iterator_facade< TestCore< std::forward_iterator_tag > >;

static_assert(iterators::operators::supports_prefix_increment_v< ForwardIterator >,
			  "Forward iterators should support the prefix increment operator");
static_assert(iterators::operators::supports_postfix_increment_v< ForwardIterator >,
			  "Forward iterators should support the postfix increment operator");
static_assert(iterators::operators::supports_star_dereference_v< ForwardIterator >,
			  "Forward iterators should support the star dereference operator");
static_assert(iterators::operators::supports_arrow_dereference_v< ForwardIterator >,
			  "Forward iterators should support the arrow dereference operator");
static_assert(iterators::operators::supports_equality_comparison_v< ForwardIterator >,
			  "Forward iterators should support the equality operator");
static_assert(iterators::operators::supports_inequality_comparison_v< ForwardIterator >,
			  "Forward iterators should support the inequality operator");
static_assert(!iterators::operators::supports_prefix_decrement_v< ForwardIterator >,
			  "Forward iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_postfix_decrement_v< ForwardIterator >,
			  "Forward iterators should NOT support the postfix decrement operator");
static_assert(!iterators::operators::supports_addition_with_arithmetic_v< ForwardIterator >,
			  "Forward iterators should NOT support addition with arithmetic types");
static_assert(!iterators::operators::supports_addition_to_arithmetic_v< ForwardIterator >,
			  "Forward iterators should NOT support addition to arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_arithmetic_v< ForwardIterator >,
			  "Forward iterators should NOT support subtraction with arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_iterator_v< ForwardIterator >,
			  "Forward iterators should NOT support subtraction with another iterator");
static_assert(!iterators::operators::supports_less_than_comparison_v< ForwardIterator >,
			  "Forward iterators should NOT support the less than operator");
static_assert(!iterators::operators::supports_greater_than_comparison_v< ForwardIterator >,
			  "Forward iterators should NOT support the greater than operator");
static_assert(!iterators::operators::supports_less_equal_comparison_v< ForwardIterator >,
			  "Forward iterators should NOT support the less-equal than operator");
static_assert(!iterators::operators::supports_greater_equal_comparison_v< ForwardIterator >,
			  "Forward iterators should NOT support the greater-equal than operator");
static_assert(!iterators::operators::supports_add_assign_v< ForwardIterator >,
			  "Forward iterators should NOT support the add-assign operator");
static_assert(!iterators::operators::supports_subtract_assign_v< ForwardIterator >,
			  "Forward iterators should NOT support the subtract-assign operator");
static_assert(!iterators::operators::supports_offset_dereference_v< ForwardIterator >,
			  "Forward iterators should NOT support the bracket (offset-dereference) operator");



// Bidirectional iterators
using BidirectionalIterator = iterators::iterator_facade< TestCore< std::bidirectional_iterator_tag > >;

static_assert(iterators::operators::supports_prefix_increment_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the prefix increment operator");
static_assert(iterators::operators::supports_postfix_increment_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the postfix increment operator");
static_assert(iterators::operators::supports_star_dereference_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the star dereference operator");
static_assert(iterators::operators::supports_arrow_dereference_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the arrow dereference operator");
static_assert(iterators::operators::supports_equality_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the equality operator");
static_assert(iterators::operators::supports_inequality_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the inequality operator");
static_assert(iterators::operators::supports_prefix_decrement_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the postfix decrement operator");
static_assert(iterators::operators::supports_postfix_decrement_v< BidirectionalIterator >,
			  "Bidirectional iterators should support the postfix decrement operator");
static_assert(!iterators::operators::supports_addition_with_arithmetic_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support addition with arithmetic types");
static_assert(!iterators::operators::supports_addition_to_arithmetic_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support addition to arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_arithmetic_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support subtraction with arithmetic types");
static_assert(!iterators::operators::supports_subtraction_with_iterator_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support subtraction with another iterator");
static_assert(!iterators::operators::supports_less_than_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the less than operator");
static_assert(!iterators::operators::supports_greater_than_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the greater than operator");
static_assert(!iterators::operators::supports_less_equal_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the less-equal than operator");
static_assert(!iterators::operators::supports_greater_equal_comparison_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the greater-equal than operator");
static_assert(!iterators::operators::supports_add_assign_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the add-assign operator");
static_assert(!iterators::operators::supports_subtract_assign_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the subtract-assign operator");
static_assert(!iterators::operators::supports_offset_dereference_v< BidirectionalIterator >,
			  "Bidirectional iterators should NOT support the bracket (offset-dereference) operator");


// RandomAccess iterators
using RandomAccessIterator = iterators::iterator_facade< TestCore< std::random_access_iterator_tag > >;

static_assert(iterators::operators::supports_prefix_increment_v< RandomAccessIterator >,
			  "Random access iterators should support the prefix increment operator");
static_assert(iterators::operators::supports_postfix_increment_v< RandomAccessIterator >,
			  "Random access iterators should support the postfix increment operator");
static_assert(iterators::operators::supports_star_dereference_v< RandomAccessIterator >,
			  "Random access iterators should support the star dereference operator");
static_assert(iterators::operators::supports_arrow_dereference_v< RandomAccessIterator >,
			  "Random access iterators should support the arrow dereference operator");
static_assert(iterators::operators::supports_equality_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the equality operator");
static_assert(iterators::operators::supports_inequality_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the inequality operator");
static_assert(iterators::operators::supports_prefix_decrement_v< RandomAccessIterator >,
			  "Random access iterators should support the postfix decrement operator");
static_assert(iterators::operators::supports_postfix_decrement_v< RandomAccessIterator >,
			  "Random access iterators should support the postfix decrement operator");
static_assert(iterators::operators::supports_addition_with_arithmetic_v< RandomAccessIterator >,
			  "Random access iterators should support addition with arithmetic types");
static_assert(iterators::operators::supports_addition_to_arithmetic_v< RandomAccessIterator >,
			  "Random access iterators should support addition to arithmetic types");
static_assert(iterators::operators::supports_subtraction_with_arithmetic_v< RandomAccessIterator >,
			  "Random access iterators should support subtraction with arithmetic types");
static_assert(iterators::operators::supports_subtraction_with_iterator_v< RandomAccessIterator >,
			  "Random access iterators should support subtraction with another iterator");
static_assert(iterators::operators::supports_less_than_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the less than operator");
static_assert(iterators::operators::supports_greater_than_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the greater than operator");
static_assert(iterators::operators::supports_less_equal_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the less-equal than operator");
static_assert(iterators::operators::supports_greater_equal_comparison_v< RandomAccessIterator >,
			  "Random access iterators should support the greater-equal than operator");
static_assert(iterators::operators::supports_add_assign_v< RandomAccessIterator >,
			  "Random access iterators should support the add-assign operator");
static_assert(iterators::operators::supports_subtract_assign_v< RandomAccessIterator >,
			  "Random access iterators should support the subtract-assign operator");
static_assert(iterators::operators::supports_offset_dereference_v< RandomAccessIterator >,
			  "Random access iterators should support the bracket (offset-dereference) operator");
