# SimpleTest Changelog

Versions follow [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

The public API consists of all entities directly within the `stest` namespace and public members thereof, plus documented macros.  
In particular, members of the `stest::detail` namespace and entities named beginning with an underscore are not part of the public API (they are internal implementation details).

TODO: update when making changes.

## 1.1.0 - 2022/04/20

 - Added `constexpr` support to `test_assert()`.
 - Added `noexcept` in some places where it should be.

## 1.0.0 - 2022/04/10

Initial stable implementation, proper CMake setup, and decent documentation.
