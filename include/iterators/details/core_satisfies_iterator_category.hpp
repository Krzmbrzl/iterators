// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_DETAILS_CORE_SATISFIES_ITERATOR_CATEGORY_HPP_
#define ITERATORS_DETAILS_CORE_SATISFIES_ITERATOR_CATEGORY_HPP_

#include "iterators/type_traits.hpp"

#include <iterator>
#include <type_traits>

namespace iterators::details {

template< typename Core, typename IteratorCategory > struct core_satisfies_iterator_category;

template< typename Core >
struct common_requirements
	: std::integral_constant<
		  bool,
		  std::conjunction_v< std::is_copy_constructible< Core >, std::is_copy_assignable< Core >,
							  member_functions::has_increment< Core >, member_functions::has_dereference< Core > > > {};

// Input iterator
template< typename Core >
struct core_satisfies_iterator_category< Core, std::input_iterator_tag >
	: std::integral_constant<
		  bool, std::conjunction_v< common_requirements< Core >, member_functions::has_equals< Core > > > {};

// Output iterator
template< typename Core >
struct core_satisfies_iterator_category< Core, std::output_iterator_tag >
	: std::integral_constant< bool, common_requirements< Core >::value > {};

// Forward iterator
template< typename Core >
struct core_satisfies_iterator_category< Core, std::forward_iterator_tag >
	: std::integral_constant< bool,
							  std::conjunction_v< core_satisfies_iterator_category< Core, std::input_iterator_tag >,
												  core_satisfies_iterator_category< Core, std::output_iterator_tag >,
												  std::is_default_constructible< Core > > > {};

// Bidirectional iterator
template< typename Core >
struct core_satisfies_iterator_category< Core, std::bidirectional_iterator_tag >
	: std::integral_constant< bool,
							  std::conjunction_v< core_satisfies_iterator_category< Core, std::forward_iterator_tag >,
												  member_functions::has_decrement< Core > > > {};

// Random access iterator
template< typename Core >
struct core_satisfies_iterator_category< Core, std::random_access_iterator_tag >
	: std::integral_constant<
		  bool,
		  std::conjunction_v< core_satisfies_iterator_category< Core, std::bidirectional_iterator_tag >,
							  member_functions::has_distance_to< Core >, member_functions::has_advance< Core > > > {};



template< typename Core, typename IteratorCategory >
constexpr bool core_satisfies_iterator_category_v = core_satisfies_iterator_category< Core, IteratorCategory >::value;

} // namespace iterators::details

#endif // ITERATORS_DETAILS_CORE_SATISFIES_ITERATOR_CATEGORY_HPP_
