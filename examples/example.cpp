// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include <iterators/iterator_facade.hpp>

#include <cstddef>
#include <iostream>
#include <iterator>

struct MyCore {
	// Declare what iterator category we are aiming for
	using target_iterator_category = std::input_iterator_tag;

	MyCore(int *ptr) : m_ptr(ptr) {}
	MyCore(const MyCore &) = default;
	MyCore(MyCore &&)      = default;
	~MyCore()              = default;
	auto operator=(const MyCore &) -> MyCore & = default;
	auto operator=(MyCore &&) -> MyCore & = default;

	// Required from forward iterators onwards
	MyCore() = default;

	[[nodiscard]] auto dereference() const -> int & { return *m_ptr; }

	void increment() { m_ptr += 1; }

	// Required for all iterator categories except output iterators
	[[nodiscard]] auto equals(const MyCore &other) const -> bool { return m_ptr == other.m_ptr; }

	// Required only for bidirectional and random access iterators
	void decrement() { m_ptr -= 1; }

	// Required only for random access iterators
	[[nodiscard]] auto distance_to(const MyCore &other) const -> std::ptrdiff_t { return other.m_ptr - m_ptr; }

	// Required only for random access iterators
	void advance(std::ptrdiff_t amount) { m_ptr += amount; }

private:
	int *m_ptr = nullptr;
};

using MyIterator = iterators::iterator_facade< MyCore >;

auto main() -> int {
	int numbers[3] = { 1, 2, 3 };

	MyIterator iter(MyCore{ numbers });

	std::cout << *iter << "\n";
	iter++;
	std::cout << *iter << "\n";
	++iter;
	std::cout << *iter << "\n";
}
