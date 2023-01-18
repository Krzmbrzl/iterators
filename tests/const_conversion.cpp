// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include <iterators/iterator_facade.hpp>

template< typename Category > struct MutableCore1 {
	using target_iterator_category = Category;

	[[nodiscard]] auto dereference() const -> int & { return *val; }
	[[nodiscard]] auto equals(const MutableCore1 &) const -> bool { return false; }
	void increment() {}
	void decrement() {}
	[[nodiscard]] auto distance_to(const MutableCore1 &) const -> int { return 2; }
	void advance(int) {}

private:
	int *val;

	template< typename > friend struct ConstCore1;
};

template< typename Category > struct ConstCore1 {
	using target_iterator_category = Category;

	ConstCore1() = default;

	ConstCore1(MutableCore1< Category > &other) : val(other.val) {}
	ConstCore1(MutableCore1< Category > &&other) : val(std::move(other.val)) {}

	[[nodiscard]] auto dereference() const -> const int & { return *val; }
	[[nodiscard]] auto equals(const ConstCore1 &) const -> bool { return false; }
	void increment() {}
	void decrement() {}
	[[nodiscard]] auto distance_to(const ConstCore1 &) const -> int { return 2; }
	void advance(int) {}

private:
	int *val;
};

template< typename Category > struct ConstCore2 {
	using target_iterator_category = Category;

	ConstCore2() = default;

	ConstCore2(int *ptr) : val(ptr) {}

	[[nodiscard]] auto dereference() const -> const int & { return *val; }
	[[nodiscard]] auto equals(const ConstCore2 &) const -> bool { return false; }
	void increment() {}
	void decrement() {}
	[[nodiscard]] auto distance_to(const ConstCore2 &) const -> int { return 2; }
	void advance(int) {}

private:
	int *val;
};

template< typename Category > struct MutableCore2 {
	using target_iterator_category = Category;

	[[nodiscard]] auto dereference() const -> int & { return *val; }
	[[nodiscard]] auto equals(const MutableCore2 &) const -> bool { return false; }
	void increment() {}
	void decrement() {}
	[[nodiscard]] auto distance_to(const MutableCore2 &) const -> int { return 2; }
	void advance(int) {}

	operator ConstCore2< Category >() { return ConstCore2< Category >(val); }

private:
	int *val;

	template< typename > friend struct ConstCore;
};

template< template< typename > class MutableCore, template< typename > class ConstCore > struct ConstConversionTester {
	static_assert(std::is_convertible_v< std::add_lvalue_reference_t< MutableCore< std::input_iterator_tag > >,
										 ConstCore< std::input_iterator_tag > >,
				  "Cores must be convertible in order for the iterator conversion to work");

	using OutputIterator      = iterators::iterator_facade< MutableCore< std::output_iterator_tag > >;
	using ConstOutputIterator = iterators::iterator_facade< ConstCore< std::output_iterator_tag > >;
	static_assert(std::is_convertible_v< std::add_lvalue_reference_t< OutputIterator >, ConstOutputIterator >,
				  "Output iterators should be convertible");

	using InputIterator      = iterators::iterator_facade< MutableCore< std::input_iterator_tag > >;
	using ConstInputIterator = iterators::iterator_facade< ConstCore< std::input_iterator_tag > >;
	static_assert(std::is_convertible_v< std::add_lvalue_reference_t< InputIterator >, ConstInputIterator >,
				  "Input iterators should be convertible");

	using ForwardIterator      = iterators::iterator_facade< MutableCore< std::forward_iterator_tag > >;
	using ConstForwardIterator = iterators::iterator_facade< ConstCore< std::forward_iterator_tag > >;
	static_assert(std::is_convertible_v< std::add_lvalue_reference_t< ForwardIterator >, ConstForwardIterator >,
				  "Forward iterators should be convertible");

	using BidirectionalIterator      = iterators::iterator_facade< MutableCore< std::bidirectional_iterator_tag > >;
	using ConstBidirectionalIterator = iterators::iterator_facade< ConstCore< std::bidirectional_iterator_tag > >;
	static_assert(
		std::is_convertible_v< std::add_lvalue_reference_t< BidirectionalIterator >, ConstBidirectionalIterator >,
		"Bidirectional iterators should be convertible");

	using RandomAccessIterator      = iterators::iterator_facade< MutableCore< std::random_access_iterator_tag > >;
	using ConstRandomAccessIterator = iterators::iterator_facade< ConstCore< std::random_access_iterator_tag > >;
	static_assert(
		std::is_convertible_v< std::add_lvalue_reference_t< RandomAccessIterator >, ConstRandomAccessIterator >,
		"Random access iterators should be convertible");

	void test_conversions() {
		OutputIterator mut_out(MutableCore< std::output_iterator_tag >{});
		ConstOutputIterator const_out(mut_out);
		ConstOutputIterator const_out2(std::move(mut_out));

		InputIterator mut_in(MutableCore< std::input_iterator_tag >{});
		ConstInputIterator const_in(mut_in);
		ConstInputIterator const_in2(std::move(mut_in));

		ForwardIterator mut_for(MutableCore< std::forward_iterator_tag >{});
		ConstForwardIterator const_for(mut_for);
		ConstForwardIterator const_for2(std::move(mut_for));

		BidirectionalIterator mut_bd(MutableCore< std::bidirectional_iterator_tag >{});
		ConstBidirectionalIterator const_bd(mut_bd);
		ConstBidirectionalIterator const_bd2(std::move(mut_bd));

		RandomAccessIterator mut_ra(MutableCore< std::random_access_iterator_tag >{});
		ConstRandomAccessIterator const_ra(mut_ra);
		ConstRandomAccessIterator const_ra2(std::move(mut_ra));
	}
};


int main() {
	ConstConversionTester< MutableCore1, ConstCore1 > tester1;
	ConstConversionTester< MutableCore2, ConstCore2 > tester2;

	tester1.test_conversions();
	tester2.test_conversions();
}
