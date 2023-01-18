// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_TESTS_TESTCORE_HPP_
#define ITERATORS_TESTS_TESTCORE_HPP_

#include <cstddef>

template< typename Category > struct TestCore {
	using target_iterator_category = Category;

	[[nodiscard]] auto dereference() const -> const int & { return val; }
	[[nodiscard]] auto equals(const TestCore &) const -> bool { return false; }
	void increment() {}
	void decrement() {}
	[[nodiscard]] auto distance_to(const TestCore &) const -> std::ptrdiff_t { return 2; }
	void advance(std::ptrdiff_t) {}

private:
	int val = 0;
};


#endif // ITERATORS_TESTS_TESTCORE_HPP_
