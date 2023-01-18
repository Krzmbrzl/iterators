// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_DETAILS_ITERATOR_FACADE_BASE_HPP_
#define ITERATORS_DETAILS_ITERATOR_FACADE_BASE_HPP_

#include "arrow_proxy.hpp"
#include "iterators/core_traits.hpp"
#include "iterators/type_traits.hpp"

#include <iterator>
#include <type_traits>

namespace iterators::details {

template< typename Derived, typename Core, typename IteratorCategory > class iterator_facade_base;

// Output iterator
template< typename Derived, typename Core > class iterator_facade_base< Derived, Core, std::output_iterator_tag > {
public:
	using core_traits = ::iterators::core_traits< Core >;

	iterator_facade_base() = delete;

	auto operator*() const -> typename core_traits::reference {
		// TODO: Assert that Derived::reference can be used as an lvalue
		return core().dereference();
	}

private:
	auto core() const -> const Core & { return static_cast< const Derived & >(*this).m_core; }

protected:
	struct DefaultCtorTag {};
	iterator_facade_base(DefaultCtorTag) {}
};

// Input iterator
template< typename Derived, typename Core > class iterator_facade_base< Derived, Core, std::input_iterator_tag > {
public:
	static_assert(member_functions::has_equals_v< Core >,
				  "Input iterator cores must implement a suitable 'equals' function");

	// TODO: assert that the reference type is either a reference of value_type or is convertible to value_type

	using core_traits = ::iterators::core_traits< Core >;

	iterator_facade_base() = delete;

	auto operator*() const -> typename core_traits::reference {
		// TODO: Assert that Derived::reference can (only) be used as an rvalue
		return core().dereference();
	}

	auto operator->() const -> typename core_traits::pointer {
		if constexpr (std::is_reference_v< typename Derived::reference >) {
			return std::addressof(operator*());
		} else {
			// The value returned by operator*() is NOT an actual reference. In order to make
			// the "operator-> chain" work as expected without creating any dangling pointers,
			// we have to instead use a proxy type that overloads operator-> to return the
			// actual value returned by operator*().
			return arrow_proxy< typename Derived::reference >(std::move(operator*()));
		}
	}

	friend auto operator==(const Derived &lhs, const Derived &rhs) -> bool {
		return static_cast< const iterator_facade_base & >(lhs).core().equals(
			static_cast< const iterator_facade_base & >(rhs).core());
	}

	friend auto operator!=(const Derived &lhs, const Derived &rhs) -> bool { return !(lhs == rhs); }

private:
	auto core() const -> const Core & { return static_cast< const Derived & >(*this).m_core; }

protected:
	struct DefaultCtorTag {};
	iterator_facade_base(DefaultCtorTag) {}
};

// Forward iterator = input iterator + default-constructibility
template< typename Derived, typename Core >
class iterator_facade_base< Derived, Core, std::forward_iterator_tag >
	: public iterator_facade_base< Derived, Core, std::input_iterator_tag > {
public:
	using core_traits = ::iterators::core_traits< Core >;

	static_assert(std::is_default_constructible_v< Core >, "Forward iterator cores must be default-constructible");

	static_assert(std::is_reference_v< typename core_traits::reference >,
				  "Forward iterators must dereference to an actual (const) reference type");
	static_assert(std::is_convertible_v< typename core_traits::reference, typename core_traits::value_type >,
				  "Forward iterators must dereference to a reference type that is convertible to their value type");

	using base_type = iterator_facade_base< Derived, Core, std::input_iterator_tag >;

	// Access the protected "default" constructor of the base class to not require the actual default constructor (which
	// is deleted)
	iterator_facade_base() : base_type(typename base_type::DefaultCtorTag{}) {}

protected:
	iterator_facade_base(typename base_type::DefaultCtorTag) : iterator_facade_base() {}
};

// Bidirectional iterator = forward iterator + decrement-support
template< typename Derived, typename Core >
class iterator_facade_base< Derived, Core, std::bidirectional_iterator_tag >
	: public iterator_facade_base< Derived, Core, std::forward_iterator_tag > {
public:
	static_assert(member_functions::has_decrement_v< Core >,
				  "Bidirectional iterator cores must implement a suitable 'decrement' function");

	using base_type   = iterator_facade_base< Derived, Core, std::forward_iterator_tag >;
	using core_traits = ::iterators::core_traits< Core >;

	iterator_facade_base() = default;

	auto operator--() -> Derived & {
		core().decrement();
		return static_cast< Derived & >(*this);
	}

	auto operator--(int) -> Derived {
		Derived copy(static_cast< Derived & >(*this));
		operator--();
		return copy;
	}

private:
	auto core() -> Core & { return static_cast< Derived & >(*this).m_core; }

protected:
	iterator_facade_base(typename base_type::DefaultCtorTag) : iterator_facade_base() {}
};

// Random access iterator = bidirectional iterator + arithmetic operations (+/-)
//  	+ inequality comparisons + compound assignment (+=/-=)
//  	+ offset dereference
template< typename Derived, typename Core >
class iterator_facade_base< Derived, Core, std::random_access_iterator_tag >
	: public iterator_facade_base< Derived, Core, std::bidirectional_iterator_tag > {
public:
	static_assert(member_functions::has_distance_to_v< Core >,
				  "Random access iterator cores must implement a suitable 'distance_to' function");
	static_assert(member_functions::has_advance_v< Core >,
				  "Random access iterator cores must implement a suitable 'advance' function");

	using base_type   = iterator_facade_base< Derived, Core, std::bidirectional_iterator_tag >;
	using core_traits = ::iterators::core_traits< Core >;

	static_assert(std::is_convertible_v< typename core_traits::difference_type, int >,
				  "The chosen difference_type must be convertible to a signed arithmetic type");
	static_assert(std::is_convertible_v< int, typename core_traits::difference_type >,
				  "The chosen difference_type must be convertible from a signed arithmetic type");

	iterator_facade_base() = default;

	// Compound assignment
	friend auto operator+=(Derived &iterator, typename core_traits::difference_type offset) -> Derived & {
		static_cast< iterator_facade_base & >(iterator).core().advance(offset);

		return iterator;
	}

	friend auto operator-=(Derived &iterator, typename core_traits::difference_type offset) -> Derived & {
		return iterator += -offset;
	}

	// Arithmetic operators
	friend auto operator+(const Derived &iterator, typename core_traits::difference_type offset) -> Derived {
		Derived copy(iterator);
		copy += offset;
		return copy;
	}

	friend auto operator+(typename core_traits::difference_type offset, const Derived &iterator) -> Derived {
		return iterator + offset;
	}

	friend auto operator-(const Derived &iterator, typename core_traits::difference_type offset) -> Derived {
		return iterator - offset;
	}

	friend auto operator-(const Derived &lhs, const Derived &rhs) -> typename core_traits::difference_type {
		return rhs.distance_to(lhs);
	}

	// Inequality comparisons
	auto friend operator<(const Derived &lhs, const Derived &rhs) -> bool { return lhs - rhs < 0; }

	auto friend operator<=(const Derived &lhs, const Derived &rhs) -> bool { return lhs == rhs || lhs < rhs; }

	auto friend operator>(const Derived &lhs, const Derived &rhs) -> bool { return !(lhs <= rhs); }

	auto friend operator>=(const Derived &lhs, const Derived &rhs) -> bool { return lhs - rhs > 0; }

	// Offset dereference
	auto operator[](typename core_traits::difference_type offset) const -> typename core_traits::reference {
		return *(static_cast< Derived & >(*this) + offset);
	}

private:
	auto core() const -> const Core & { return static_cast< const Derived & >(*this).m_core; }

protected:
	iterator_facade_base(typename base_type::DefaultCtorTag) : iterator_facade_base() {}
};

} // namespace iterators::details

#endif // ITERATORS_DETAILS_ITERATOR_FACADE_BASE_HPP_
