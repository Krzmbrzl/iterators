# iterators

A C++17 header-only library allowing easy implementation of STL-conforming iterators without any additional dependencies. Think
of a light-weight version of [Boost.Iterator](https://github.com/boostorg/iterator) without the Boost dependency.

By using the provided `iterator_facade` type to create your iterators, you will expose only the minimum required interface for the chosen iterator
category, even if your type would in principle support a richer interface. This is in order to prevent downstream users from depending on parts of
your iterator's API that is not covered by the C++ standard for the given iterator category and therefore is very likely to fail, should you ever
replace your iterator implementation with another one that meets the same iterator category requirements.

**Note**: The only exception from the above is move-constructibility and move-assignability. All iterators created via this library will support these
operations, even though the standard only requires copy-constructibility and copy-assignability.

## References

The following references were very helpful for implementing this library and might be useful for anyone looking into this subject:
- https://vector-of-bool.github.io/2020/06/13/cpp20-iter-facade.html
  ([source](https://github.com/vector-of-bool/vector-of-bool.github.io/blob/7597b411d95cc9e5d24158c2eaddabec87f93a59/_posts/2020-06-13-cpp20-iter-facade.md)]
- [Boost.Iterator source code](https://github.com/boostorg/iterator)
- https://quuxplusone.github.io/blog/2019/02/06/arrow-proxy/
