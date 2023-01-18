// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include <iterators/details/core_satisfies_iterator_category.hpp>
#include <iterators/iterator_facade.hpp>

#include <iostream>
#include <iterator>

enum class Month { January, February, March, April, May, June, July, August, September, October, November, December };

class MonthEnumCore {
public:
	using target_iterator_category = std::input_iterator_tag;

	MonthEnumCore() = default;
	MonthEnumCore(Month month) : m_currentMonth(month) {}
	MonthEnumCore(const MonthEnumCore &) = default;
	auto operator=(const MonthEnumCore &) -> MonthEnumCore & = default;

	auto dereference() const -> Month { return m_currentMonth; }

	void increment() {
		m_currentMonth = static_cast< Month >(static_cast< std::underlying_type_t< Month > >(m_currentMonth) + 1);
	}

	void decrement() {
		m_currentMonth = static_cast< Month >(static_cast< std::underlying_type_t< Month > >(m_currentMonth) - 1);
	}

	auto equals(const MonthEnumCore &other) const -> bool { return m_currentMonth == other.m_currentMonth; }

private:
	Month m_currentMonth = Month::January;
};

using MonthIterator = iterators::iterator_facade< MonthEnumCore >;

auto main() -> int {
	MonthIterator end(Month::December);
	end++;
	MonthIterator start(Month::January);

	for (auto iter = start; iter != end; ++iter) {
		std::cout << static_cast< int >(*iter) << "\n";
	}
}
