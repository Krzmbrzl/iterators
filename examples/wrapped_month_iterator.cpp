// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#include <iterators/iterator_facade.hpp>

#include <iostream>
#include <iterator>
#include <string>

enum class Month { January, February, March, April, May, June, July, August, September, October, November, December };

class MonthWrapper {
public:
	MonthWrapper(Month month) : m_month(month) {}

	[[nodiscard]] auto getMonth() const -> Month { return m_month; }

	operator std::string() const {
		switch (m_month) {
			case Month::January:
				return "January";
			case Month::February:
				return "February";
			case Month::March:
				return "March";
			case Month::April:
				return "April";
			case Month::May:
				return "May";
			case Month::June:
				return "June";
			case Month::July:
				return "July";
			case Month::August:
				return "August";
			case Month::September:
				return "September";
			case Month::October:
				return "October";
			case Month::November:
				return "November";
			case Month::December:
				return "December";
		}

		return "Unknown";
	}

private:
	Month m_month;
};

class MonthEnumCore {
public:
	using target_iterator_category = std::input_iterator_tag;

	MonthEnumCore() = default;
	MonthEnumCore(Month month) : m_currentMonth(month) {}
	MonthEnumCore(const MonthEnumCore &) = default;
	MonthEnumCore(MonthEnumCore &&)      = default;
	auto operator=(const MonthEnumCore &) -> MonthEnumCore & = default;
	auto operator=(MonthEnumCore &&) -> MonthEnumCore & = default;
	~MonthEnumCore()                                    = default;

	// Notice that this function no returns a newly constructed wrapper type
	[[nodiscard]] auto dereference() const -> MonthWrapper { return { m_currentMonth }; }

	void increment() {
		m_currentMonth = static_cast< Month >(static_cast< std::underlying_type_t< Month > >(m_currentMonth) + 1);
	}

	void decrement() {
		m_currentMonth = static_cast< Month >(static_cast< std::underlying_type_t< Month > >(m_currentMonth) - 1);
	}

	[[nodiscard]] auto equals(const MonthEnumCore &other) const -> bool {
		return m_currentMonth == other.m_currentMonth;
	}

private:
	Month m_currentMonth = Month::January;
};

using MonthIterator = iterators::iterator_facade< MonthEnumCore >;

auto main() -> int {
	MonthIterator end(static_cast< Month >(static_cast< int >(Month::December) + 1));
	MonthIterator start(Month::January);

	for (auto iter = start; iter != end; ++iter) {
		std::cout << "Month " << static_cast< int >(iter->getMonth()) << " has name '"
				  << static_cast< std::string >(*iter) << "'\n";
	}
}
