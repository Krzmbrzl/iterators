// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_ITERATOR_FACADE_HPP_
#define ITERATORS_ITERATOR_FACADE_HPP_

#include "core_traits.hpp"
#include "details/core_satisfies_iterator_category.hpp"
#include "details/iterator_facade_base.hpp"
#include "is_semantically_const.hpp"
#include "iterators/type_traits.hpp"

#include <type_traits>

namespace iterators {

namespace details {

	template< typename ToCore, typename FromCore >
	constexpr auto require_core_convertible_to(FromCore &&core) -> ToCore {
		static_assert(std::is_convertible_v< FromCore, ToCore >,
					  "In order for the conversion between iterator to const_iterator to work, the respective Cores "
					  "have to be convertible (from lvalues and rvalues)");
		return std::forward< FromCore >(core);
	}

} // namespace details

template< typename Core >
class iterator_facade
	: public details::iterator_facade_base< iterator_facade< Core >, Core, typename Core::target_iterator_category > {
public:
	static_assert(std::is_copy_constructible_v< Core >, "Iterator cores must be copy-constructible");
	static_assert(std::is_copy_assignable_v< Core >, "Iterator cores must be copy-assignable");
	static_assert(std::is_destructible_v< Core >, "Iterator cores must be destructable");
	static_assert(std::is_move_assignable_v< Core >, "Iterator cores must be move-constructible");
	static_assert(std::is_move_assignable_v< Core >, "Iterator cores must be move-assignable");
	static_assert(member_functions::has_dereference_v< Core >,
				  "Iterator cores must implement a suitable 'dereference' function");
	static_assert(member_functions::has_increment_v< Core >,
				  "Iterator cores must implement a suitable 'increment' function");

	using core_type   = Core;
	using core_traits = iterators::core_traits< Core >;
	using self_type   = iterator_facade< Core >;
	using base_type   = details::iterator_facade_base< iterator_facade, Core, typename Core::target_iterator_category >;

	using difference_type   = typename core_traits::difference_type;
	using value_type        = typename core_traits::value_type;
	using reference         = typename core_traits::reference;
	using pointer           = typename core_traits::pointer;
	using iterator_category = typename core_traits::iterator_category;

	static_assert(std::disjunction_v< std::is_signed< difference_type >, std::is_void< difference_type > >,
				  "An iterator's difference_type must be a signed integer type or void");


	iterator_facade(Core core) : base_type(typename base_type::DefaultCtorTag{}), m_core(std::move(core)) {}

	iterator_facade(const iterator_facade &)                                                   = default;
	iterator_facade(iterator_facade &&) noexcept(std::is_nothrow_move_constructible_v< Core >) = default;
	~iterator_facade()                                                                         = default;

	auto operator=(const iterator_facade &) -> iterator_facade & = default;
	auto operator            =(iterator_facade &&) noexcept(std::is_nothrow_move_assignable_v< Core >)
		-> iterator_facade & = default;

	// Inherit constructors from base class (default-constructor, if applicable)
	using base_type::base_type;

	auto operator++() -> iterator_facade & {
		m_core.increment();

		return *this;
	}

	auto operator++(int) -> iterator_facade {
		self_type copy(*this);
		operator++();
		return copy;
	}


	// Conversion from regular iterator to const_iterator.
	template<
		typename IteratorFacade,
		typename = std::enable_if_t<
			is_iterator_facade_v< std::remove_reference_t<
				IteratorFacade > > && !is_const_iterator_facade_v< std::remove_reference_t< IteratorFacade > > && is_const_iterator_facade_v< self_type > > >
	iterator_facade(IteratorFacade &&other)
		: base_type(typename base_type::DefaultCtorTag{}),
		  m_core(details::require_core_convertible_to< Core >(std::forward< IteratorFacade >(other).m_core)) {}

private:
	Core m_core;

	template< typename, typename, typename > friend class details::iterator_facade_base;
	template< typename > friend class iterator_facade;
};

} // namespace iterators

#endif // ITERATORS_ITERATOR_FACADE_HPP_
