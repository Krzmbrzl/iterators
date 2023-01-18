# iterators

A C++17 header-only library allowing easy implementation of STL-conforming iterators without any additional dependencies. Think of a light-weight
version of [Boost.Iterator](https://github.com/boostorg/iterator) without the Boost dependency.

By using the provided `iterator_facade` type to create your iterators, you will expose only the minimum required interface for the chosen iterator
category, even if your type would in principle support a richer interface. This is in order to prevent downstream users from depending on parts of
your iterator's API that is not covered by the C++ standard for the given iterator category and therefore is very likely to fail, should you ever
replace your iterator implementation with another one that meets the same iterator category requirements.

## Features

- Easily implement new iterators by only implementing the iterator's _Core_ that only implements the required functions. All boilerplate for the
  actual iterator interface will be inferred by the `iterator_facade` class.
- Compile-time checks that your iterator implementation conforms to the chosen iterator category as defined by the C++ standard
- Your iterator will expose _exactly_ the required interface and _nothing more_. This prevents downstream users from accidentally depending on an
  implementation detail of your iterator.
- Automatic support for iterators returning a value on dereferencing (e.g. a wrapper type). Note: due to the C++ standard requirements this is only
  possible for input and output iterators.

## Requirements

- An ISO-C++17 compliant compiler and standard library implementation

That's it. No external dependencies.

## Example

See also the [examples](examples) directory. Using this library, you can create a new iterator implementation by implementing what we refer to as the
iterator's _Core_. This contains the iterator's state as well as functions that implement the underlying functionality of your iterator:
```cpp
#include <iterators/iterator_facade.hpp>

#include <cstddef>
#include <iostream>
#include <iterator>

struct MyCore {
	// Declare what iterator category we are aiming for
	using  target_iterator_category = std::input_iterator_tag;

	// These functions are required for all iterator cores

	MyCore(int *ptr) : m_ptr(ptr) {}
	MyCore(const MyCore &) = default;
	MyCore &operator=(const MyCore &) = default;

	int &dereference() const { return *m_ptr; }

	void increment() { m_ptr += 1; }

	// Required from forward iterators onwards
	MyCore() = default;

	// Required for all iterator categories except output iterators
	bool equals(const MyCore &other) const { return m_ptr == other.m_ptr; }

	// Required only for bidirectional and random access iterators
	void decrement() { m_ptr -= 1; }

	// Required only for random access iterators
	std::ptrdiff_t distance_to(const MyCore &other) const { return other.m_ptr - m_ptr; }

	// Required only for random access iterators
	void advance(std::ptrdiff_t amount) { m_ptr += amount; }

private:
    int * m_ptr = nullptr;
};

using MyIterator = iterators::iterator_facade< MyCore >;

int main() {
	int numbers[3] = { 1, 2, 3 };

	MyIterator iter(MyCore{numbers});

	std::cout << *iter << "\n";
	iter++;
	std::cout << *iter << "\n";
	++iter;
	std::cout << *iter << "\n";

	return 0;
}
```

## References

The following references were very helpful for implementing this library and might be useful for anyone looking into this subject:
- https://vector-of-bool.github.io/2020/06/13/cpp20-iter-facade.html
  ([source](https://github.com/vector-of-bool/vector-of-bool.github.io/blob/7597b411d95cc9e5d24158c2eaddabec87f93a59/_posts/2020-06-13-cpp20-iter-facade.md)]
- [Boost.Iterator source code](https://github.com/boostorg/iterator)
- https://quuxplusone.github.io/blog/2019/02/06/arrow-proxy/
- https://cplusplus.com/reference/iterator/
