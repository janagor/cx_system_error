# cx_system_error

[![ci](https://github.com/janagor/cx_system_error/actions/workflows/ci.yml/badge.svg)](https://github.com/janagor/cx_system_error/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/janagor/cx_system_error/branch/main/graph/badge.svg)](https://codecov.io/gh/janagor/cx_system_error)
[![CodeQL](https://github.com/janagor/cx_system_error/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/janagor/cx_system_error/actions/workflows/codeql-analysis.yml)

## About cx_system_error

Constexpr-friendly C++23 analogue of `<system_error>`: `cx::ErrorCode`,
`cx::ErrorCondition`, `cx::ErrorCategory`, `cx::Errc`, and the generic/system
categories. `Message()` returns `std::string_view` so it can be used in constant
evaluation. The `SystemError` exception type is deferred until constexpr
exceptions are widely available.

```cpp
#include <cx_system_error/system_error.hpp>

constexpr auto code = cx::MakeErrorCode(cx::Errc::kInvalidArgument);
static_assert(code.Message() == "Invalid argument");
```

## More Details

 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [Troubleshooting](README_troubleshooting.md)
 * [Docker](README_docker.md)
