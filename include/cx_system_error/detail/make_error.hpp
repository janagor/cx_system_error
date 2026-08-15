#ifndef CX_SYSTEM_ERROR_DETAIL_MAKE_ERROR_HPP
#define CX_SYSTEM_ERROR_DETAIL_MAKE_ERROR_HPP

#include <cx_system_error/detail/errc.hpp>
#include <cx_system_error/detail/error_category.hpp>
#include <cx_system_error/detail/error_code.hpp>
#include <cx_system_error/detail/error_condition.hpp>

namespace cx {

[[nodiscard]] constexpr auto MakeErrorCode(Errc error) noexcept -> ErrorCode
{ return ErrorCode{ static_cast<int>(error), GenericCategory() }; }

[[nodiscard]] constexpr auto MakeErrorCondition(Errc error) noexcept -> ErrorCondition
{ return ErrorCondition{ static_cast<int>(error), GenericCategory() }; }

}// namespace cx

#endif
