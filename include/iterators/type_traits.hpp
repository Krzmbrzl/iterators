// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_DETAILS_TYPE_TRAITS_HPP_
#define ITERATORS_DETAILS_TYPE_TRAITS_HPP_

#include "is_semantically_const.hpp"

#include <iterator>
#include <type_traits>
#include <utility>

namespace iterators {

template< typename > class iterator_facade;

namespace details {

	template< typename T > struct as_const { using type = std::add_const_t< T >; };
	template< typename T > struct as_ref { using type = std::add_lvalue_reference_t< T >; };
	template< typename T > struct as_const_ref { using type = std::add_lvalue_reference_t< std::add_const_t< T > >; };

	template< typename T > using as_const_t     = typename as_const< T >::type;
	template< typename T > using as_ref_t       = typename as_ref< T >::type;
	template< typename T > using as_const_ref_t = typename as_const_ref< T >::type;

} // namespace details

namespace member_functions {

	template< typename T > using dereference_type = decltype(std::declval< details::as_const_t< T > >().dereference());
	template< typename T >
	using equals_type =
		decltype(std::declval< details::as_const_t< T > >().equals(std::declval< details::as_const_ref_t< T > >()));
	template< typename T > using increment_type = decltype(std::declval< T >().increment());
	template< typename T > using decrement_type = decltype(std::declval< T >().decrement());
	template< typename T >
	using distance_to_type = decltype(
		std::declval< details::as_const_t< T > >().distance_to(std::declval< details::as_const_ref_t< T > >()));
	template< typename T >
	using advance_type = decltype(std::declval< T >().advance(std::declval< distance_to_type< T > >()));

	template< typename T, typename = void > struct has_dereference : std::false_type {};
	template< typename T, typename = void > struct has_equals : std::false_type {};
	template< typename T, typename = void > struct has_increment : std::false_type {};
	template< typename T, typename = void > struct has_decrement : std::false_type {};
	template< typename T, typename = void > struct has_advance : std::false_type {};
	template< typename T, typename = void > struct has_distance_to : std::false_type {};

	template< typename T > struct has_dereference< T, std::void_t< dereference_type< T > > > : std::true_type {};
	template< typename T > struct has_equals< T, std::void_t< equals_type< T > > > : std::true_type {};
	template< typename T > struct has_increment< T, std::void_t< increment_type< T > > > : std::true_type {};
	template< typename T > struct has_decrement< T, std::void_t< decrement_type< T > > > : std::true_type {};
	template< typename T > struct has_advance< T, std::void_t< advance_type< T > > > : std::true_type {};
	template< typename T > struct has_distance_to< T, std::void_t< distance_to_type< T > > > : std::true_type {};

	template< typename T > constexpr bool has_dereference_v = has_dereference< T >::value;
	template< typename T > constexpr bool has_equals_v      = has_equals< T >::value;
	template< typename T > constexpr bool has_increment_v   = has_increment< T >::value;
	template< typename T > constexpr bool has_decrement_v   = has_decrement< T >::value;
	template< typename T > constexpr bool has_advance_v     = has_advance< T >::value;
	template< typename T > constexpr bool has_distance_to_v = has_distance_to< T >::value;

} // namespace member_functions

namespace iterator_category {

	template< typename CompareTag, typename MinimumTag > struct is_at_least;

	// Output iterators
	template< typename MinimumTag > struct is_at_least< std::output_iterator_tag, MinimumTag > : std::false_type {};
	template<> struct is_at_least< std::output_iterator_tag, std::output_iterator_tag > : std::true_type {};

	// Input iterators
	template< typename MinimumTag > struct is_at_least< std::input_iterator_tag, MinimumTag > : std::false_type {};
	template<> struct is_at_least< std::input_iterator_tag, std::input_iterator_tag > : std::true_type {};

	// Forward iterators
	template< typename MinimumTag > struct is_at_least< std::forward_iterator_tag, MinimumTag > : std::false_type {};
	template<> struct is_at_least< std::forward_iterator_tag, std::input_iterator_tag > : std::true_type {};
	template<> struct is_at_least< std::forward_iterator_tag, std::forward_iterator_tag > : std::true_type {};

	// Bidirectional iterators
	template< typename MinimumTag >
	struct is_at_least< std::bidirectional_iterator_tag, MinimumTag > : std::false_type {};
	template<> struct is_at_least< std::bidirectional_iterator_tag, std::input_iterator_tag > : std::true_type {};
	template<> struct is_at_least< std::bidirectional_iterator_tag, std::forward_iterator_tag > : std::true_type {};
	template<>
	struct is_at_least< std::bidirectional_iterator_tag, std::bidirectional_iterator_tag > : std::true_type {};

	// Random access iterators
	template< typename MinimumTag >
	struct is_at_least< std::random_access_iterator_tag, MinimumTag > : std::false_type {};
	template<> struct is_at_least< std::random_access_iterator_tag, std::input_iterator_tag > : std::true_type {};
	template<> struct is_at_least< std::random_access_iterator_tag, std::forward_iterator_tag > : std::true_type {};
	template<>
	struct is_at_least< std::random_access_iterator_tag, std::bidirectional_iterator_tag > : std::true_type {};
	template<>
	struct is_at_least< std::random_access_iterator_tag, std::random_access_iterator_tag > : std::true_type {};

	template< typename CompareTag, typename MinimumTag >
	constexpr bool is_at_least_v = is_at_least< CompareTag, MinimumTag >::value;

} // namespace iterator_category

namespace operators {
	template< typename Iterator > using prefix_increment_type  = decltype(++std::declval< Iterator >());
	template< typename Iterator > using postfix_increment_type = decltype(std::declval< Iterator >()++);
	template< typename Iterator > using pretfix_decrement_type = decltype(--std::declval< Iterator >());
	template< typename Iterator > using postfix_decrement_type = decltype(std::declval< Iterator >()--);
	template< typename Iterator >
	using equality_comparison_type = decltype(std::declval< details::as_const_t< Iterator > >()
											  == std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using inequality_comparison_type = decltype(std::declval< details::as_const_t< Iterator > >()
												!= std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using less_than_comparison_type =
		decltype(std::declval< details::as_const_t< Iterator > >() < std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using less_equal_comparison_type = decltype(std::declval< details::as_const_t< Iterator > >()
												<= std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using greater_than_comparison_type =
		decltype(std::declval< details::as_const_t< Iterator > >() > std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using greater_equal_comparison_type = decltype(std::declval< details::as_const_t< Iterator > >()
												   >= std::declval< details::as_const_t< Iterator > >());

	template< typename Iterator >
	using star_dereference_type = decltype(*std::declval< details::as_const_ref_t< Iterator > >());
	template< typename Iterator >
	using arrow_dereference_type = decltype(std::declval< details::as_const_ref_t< Iterator > >().operator->());
	template< typename Iterator >
	using offset_dereference_type =
		decltype(std::declval< details::as_const_ref_t< Iterator > >()[std::declval< std::ptrdiff_t >()]);

	template< typename Iterator >
	using subtraction_with_iterator_type =
		decltype(std::declval< details::as_const_t< Iterator > >() - std::declval< details::as_const_t< Iterator > >());
	template< typename Iterator >
	using subtraction_with_arithmetic_type =
		decltype(std::declval< details::as_const_t< Iterator > >() - std::declval< std::ptrdiff_t >());
	template< typename Iterator >
	using addition_with_arithmetic_type =
		decltype(std::declval< details::as_const_t< Iterator > >() + std::declval< std::ptrdiff_t >());
	template< typename Iterator >
	using addition_to_arithmetic_type =
		decltype(std::declval< std::ptrdiff_t >() + std::declval< details::as_const_t< Iterator > >());

	template< typename Iterator >
	using add_assign_type =
		decltype(std::declval< details::as_ref_t< Iterator > >() += std::declval< std::ptrdiff_t >());
	template< typename Iterator >
	using subtract_assign_type =
		decltype(std::declval< details::as_ref_t< Iterator > >() -= std::declval< std::ptrdiff_t >());


	template< typename Iterator, typename = void > struct supports_prefix_increment : std::false_type {};
	template< typename Iterator, typename = void > struct supports_postfix_increment : std::false_type {};
	template< typename Iterator, typename = void > struct supports_prefix_decrement : std::false_type {};
	template< typename Iterator, typename = void > struct supports_postfix_decrement : std::false_type {};
	template< typename Iterator, typename = void > struct supports_equality_comparison : std::false_type {};
	template< typename Iterator, typename = void > struct supports_inequality_comparison : std::false_type {};
	template< typename Iterator, typename = void > struct supports_less_than_comparison : std::false_type {};
	template< typename Iterator, typename = void > struct supports_less_equal_comparison : std::false_type {};
	template< typename Iterator, typename = void > struct supports_greater_than_comparison : std::false_type {};
	template< typename Iterator, typename = void > struct supports_greater_equal_comparison : std::false_type {};

	template< typename Iterator, typename = void > struct supports_star_dereference : std::false_type {};
	template< typename Iterator, typename = void > struct supports_arrow_dereference : std::false_type {};
	template< typename Iterator, typename = void > struct supports_offset_dereference : std::false_type {};

	template< typename Iterator, typename = void > struct supports_subtraction_with_iterator : std::false_type {};
	template< typename Iterator, typename = void > struct supports_subtraction_with_arithmetic : std::false_type {};
	template< typename Iterator, typename = void > struct supports_addition_with_arithmetic : std::false_type {};
	template< typename Iterator, typename = void > struct supports_addition_to_arithmetic : std::false_type {};

	template< typename Iterator, typename = void > struct supports_add_assign : std::false_type {};
	template< typename Iterator, typename = void > struct supports_subtract_assign : std::false_type {};

	// Specializations for the cases where the respective operators exist
	template< typename Iterator >
	struct supports_prefix_increment< Iterator, std::void_t< prefix_increment_type< Iterator > > > : std::true_type {};
	template< typename Iterator >
	struct supports_postfix_increment< Iterator, std::void_t< postfix_increment_type< Iterator > > > : std::true_type {
	};
	template< typename Iterator >
	struct supports_prefix_decrement< Iterator, std::void_t< pretfix_decrement_type< Iterator > > > : std::true_type {};
	template< typename Iterator >
	struct supports_postfix_decrement< Iterator, std::void_t< postfix_decrement_type< Iterator > > > : std::true_type {
	};
	template< typename Iterator >
	struct supports_equality_comparison< Iterator, std::void_t< equality_comparison_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_inequality_comparison< Iterator, std::void_t< inequality_comparison_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_less_than_comparison< Iterator, std::void_t< less_than_comparison_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_less_equal_comparison< Iterator, std::void_t< less_equal_comparison_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_greater_than_comparison< Iterator, std::void_t< greater_than_comparison_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_greater_equal_comparison< Iterator, std::void_t< greater_equal_comparison_type< Iterator > > >
		: std::true_type {};

	template< typename Iterator >
	struct supports_star_dereference< Iterator, std::void_t< star_dereference_type< Iterator > > > : std::true_type {};
	template< typename Iterator >
	struct supports_arrow_dereference< Iterator, std::void_t< arrow_dereference_type< Iterator > > > : std::true_type {
	};
	template< typename Iterator >
	struct supports_offset_dereference< Iterator, std::void_t< offset_dereference_type< Iterator > > >
		: std::true_type {};

	template< typename Iterator >
	struct supports_subtraction_with_iterator< Iterator, std::void_t< subtraction_with_iterator_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_subtraction_with_arithmetic< Iterator, std::void_t< subtraction_with_arithmetic_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_addition_with_arithmetic< Iterator, std::void_t< addition_with_arithmetic_type< Iterator > > >
		: std::true_type {};
	template< typename Iterator >
	struct supports_addition_to_arithmetic< Iterator, std::void_t< addition_to_arithmetic_type< Iterator > > >
		: std::true_type {};

	template< typename Iterator >
	struct supports_add_assign< Iterator, std::void_t< add_assign_type< Iterator > > > : std::true_type {};
	template< typename Iterator >
	struct supports_subtract_assign< Iterator, std::void_t< subtract_assign_type< Iterator > > > : std::true_type {};



	template< typename Iterator >
	constexpr bool supports_prefix_increment_v = supports_prefix_increment< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_postfix_increment_v = supports_postfix_increment< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_prefix_decrement_v = supports_prefix_decrement< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_postfix_decrement_v = supports_postfix_decrement< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_equality_comparison_v = supports_equality_comparison< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_inequality_comparison_v = supports_inequality_comparison< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_less_than_comparison_v = supports_less_than_comparison< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_less_equal_comparison_v = supports_less_equal_comparison< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_greater_than_comparison_v = supports_greater_than_comparison< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_greater_equal_comparison_v = supports_greater_equal_comparison< Iterator >::value;

	template< typename Iterator >
	constexpr bool supports_star_dereference_v = supports_star_dereference< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_arrow_dereference_v = supports_arrow_dereference< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_offset_dereference_v = supports_offset_dereference< Iterator >::value;

	template< typename Iterator >
	constexpr bool supports_subtraction_with_iterator_v = supports_subtraction_with_iterator< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_subtraction_with_arithmetic_v = supports_subtraction_with_arithmetic< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_addition_with_arithmetic_v = supports_addition_with_arithmetic< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_addition_to_arithmetic_v = supports_addition_to_arithmetic< Iterator >::value;

	template< typename Iterator > constexpr bool supports_add_assign_v = supports_add_assign< Iterator >::value;
	template< typename Iterator >
	constexpr bool supports_subtract_assign_v = supports_subtract_assign< Iterator >::value;

} // namespace operators

template< typename T > struct is_iterator_facade : std::false_type {};

template< typename Core > struct is_iterator_facade< iterator_facade< Core > > : std::true_type {};

template< typename T > constexpr bool is_iterator_facade_v = is_iterator_facade< T >::value;


template< typename T, typename = void > struct is_const_iterator_facade : std::false_type {};

template< typename IteratorFacade >
struct is_const_iterator_facade<
	IteratorFacade,
	std::enable_if_t< is_iterator_facade_v< IteratorFacade > && is_semantically_const_v< IteratorFacade > > >
	: std::true_type {};

template< typename T > constexpr bool is_const_iterator_facade_v = is_const_iterator_facade< T >::value;


} // namespace iterators

#endif // ITERATORS_DETAILS_TYPE_TRAITS_HPP_
