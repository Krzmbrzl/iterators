// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_ITERATOR_CORE_TRAITS_HPP_
#define ITERATORS_ITERATOR_CORE_TRAITS_HPP_

#include "details/arrow_proxy.hpp"
#include "iterators/type_traits.hpp"

#include <type_traits>

namespace iterators {

namespace details {

	template< typename, typename = void > struct infer_difference_type { using type = void; };

	template< typename Core >
	struct infer_difference_type< Core, std::void_t< member_functions::distance_to_type< Core > > > {
		using type = member_functions::distance_to_type< Core >;

		static_assert(std::is_signed_v< type >,
					  "If implemented, an iterator's 'distance_to' must returned a signed integer type");
	};

	template< typename Core, typename = void > struct infer_value_type {
		using type = std::decay_t< member_functions::dereference_type< Core > >;
	};

	template< typename Core > struct infer_value_type< Core, typename Core::value_type > {
		using type = typename Core::value_type;
	};

	template< typename Core, typename = void > struct infer_pointer_type {
		using type = arrow_proxy< member_functions::dereference_type< Core > >;
	};

	template< typename Core >
	struct infer_pointer_type< Core,
							   std::enable_if_t< std::is_reference_v< member_functions::dereference_type< Core > > > > {
		using type = std::add_pointer_t< member_functions::dereference_type< Core > >;
	};


} // namespace details

template< typename Core > struct core_traits {
	using difference_type   = typename details::infer_difference_type< Core >::type;
	using value_type        = typename details::infer_value_type< Core >::type;
	using pointer           = typename details::infer_pointer_type< Core >::type;
	using reference         = member_functions::dereference_type< Core >;
	using iterator_category = typename Core::target_iterator_category;
};

} // namespace iterators

#endif // ITERATORS_ITERATOR_CORE_TRAITS_HPP_
