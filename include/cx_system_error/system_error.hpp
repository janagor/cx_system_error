#ifndef CX_SYSTEM_ERROR_SYSTEM_ERROR_HPP
#define CX_SYSTEM_ERROR_SYSTEM_ERROR_HPP

// Public umbrella header. Prefer this, or include the finer-grained public
// headers (error_code.hpp, error_condition.hpp, ...). Implementations live in detail/.

// IWYU pragma: begin_exports
#include <cx_system_error/errc.hpp>
#include <cx_system_error/error_category.hpp>
#include <cx_system_error/error_code.hpp>
#include <cx_system_error/error_condition.hpp>
#include <cx_system_error/detail/comparisons.hpp>
#include <cx_system_error/detail/error_traits.hpp>
// IWYU pragma: end_exports

#endif
