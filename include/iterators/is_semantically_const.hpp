// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_IS_SEMANTICALLY_CONST_HPP_
#define ITERATORS_IS_SEMANTICALLY_CONST_HPP_

#include <type_traits>

namespace iterators {

template< typename > class iterator_facade;

namespace details {
	template< typename T > using get_function_type   = decltype(std::declval< T >().get());
	template< typename T > using value_function_type = decltype(std::declval< T >().value());

	template< typename T, typename = void > struct has_get_function : std::false_type {};
	template< typename T > struct has_get_function< T, std::void_t< get_function_type< T > > > : std::true_type {};

	template< typename T, typename = void > struct has_value_function : std::false_type {};
	template< typename T > struct has_value_function< T, std::void_t< value_function_type< T > > > : std::true_type {};

} // namespace details

template< typename T, typename = void > struct is_semantically_const : std::is_const< T > {
	static_assert(!std::is_reference_v< T >);
	static_assert(!std::is_pointer_v< T >);
};

// Specialization for references
template< typename T >
struct is_semantically_const< T, std::enable_if_t< std::is_reference_v< T > > >
	: is_semantically_const< std::remove_reference_t< T > > {};

// Specialization for pointers
template< typename T >
struct is_semantically_const< T, std::enable_if_t< std::is_pointer_v< T > > >
	: is_semantically_const< std::remove_pointer_t< T > > {};

// Specialization for types with a get() member function
template< typename T >
struct is_semantically_const< T, std::enable_if_t< details::has_get_function< T >::value > >
	: is_semantically_const< details::get_function_type< T > > {};

// Specialization for types with a value() member function
template< typename T >
struct is_semantically_const< T, std::enable_if_t< details::has_value_function< T >::value > >
	: is_semantically_const< details::value_function_type< T > > {};

// Specialization for iterator_facade
template< typename Core >
struct is_semantically_const< iterator_facade< Core > >
	: is_semantically_const< typename iterator_facade< Core >::reference > {};


template< typename T > constexpr bool is_semantically_const_v = is_semantically_const< T >::value;

} // namespace iterators

#endif // ITERATORS_IS_SEMANTICALLY_CONST_HPP_
