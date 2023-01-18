// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file at the root of the source tree or at
// <https://github.com/Krzmbrzl/iterators/blob/main/LICENSE>.

#ifndef ITERATORS_DETAILS_ARROW_PROXY_HPP_
#define ITERATORS_DETAILS_ARROW_PROXY_HPP_

#include <memory>
#include <utility>

namespace iterators::details {

template< typename Value > class arrow_proxy {
public:
	arrow_proxy(Value val) : m_val(std::move(val)) {}

	auto operator->() -> Value * { return std::addressof(m_val); }

private:
	Value m_val;
};

} // namespace iterators::details

#endif // ITERATORS_DETAILS_ARROW_PROXY_HPP_
