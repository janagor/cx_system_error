#ifndef CX_SYSTEM_ERROR_DETAIL_CATEGORIES_HPP
#define CX_SYSTEM_ERROR_DETAIL_CATEGORIES_HPP

#include <cx_system_error/detail/comparisons.hpp>
#include <cx_system_error/detail/errc_message.hpp>
#include <cx_system_error/detail/error_category.hpp>
#include <cx_system_error/detail/error_code.hpp>
#include <cx_system_error/detail/error_condition.hpp>

#include <string_view>

namespace cx {

constexpr auto ErrorCategory::DefaultErrorCondition(int error_value) const noexcept -> ErrorCondition
{
  return ErrorCondition{ error_value, *this };
}

constexpr auto ErrorCategory::Equivalent(int code, const ErrorCondition &condition) const noexcept -> bool
{
  return DefaultErrorCondition(code) == condition;
}

constexpr auto ErrorCategory::Equivalent(const ErrorCode &code, int condition) const noexcept -> bool
{
  return *this == code.Category() && code.Value() == condition;
}

constexpr auto ErrorCode::DefaultErrorCondition() const noexcept -> ErrorCondition
{
  return Category().DefaultErrorCondition(Value());
}

namespace detail {

class GenericErrorCategory final : public ErrorCategory
{
public:
  constexpr GenericErrorCategory() noexcept = default;

  [[nodiscard]] constexpr auto Name() const noexcept -> const char * override { return "generic"; }

  [[nodiscard]] constexpr auto Message(int error_value) const noexcept -> std::string_view override
  {
    return ErrcMessage(error_value);
  }
};

class SystemErrorCategory final : public ErrorCategory
{
public:
  constexpr SystemErrorCategory() noexcept = default;

  [[nodiscard]] constexpr auto Name() const noexcept -> const char * override { return "system"; }

  [[nodiscard]] constexpr auto Message(int error_value) const noexcept -> std::string_view override
  {
    return ErrcMessage(error_value);
  }

  [[nodiscard]] constexpr auto DefaultErrorCondition(int error_value) const noexcept -> ErrorCondition override
  {
    if (IsGenericErrc(error_value)) { return ErrorCondition{ error_value, GenericCategory() }; }
    return ErrorCondition{ error_value, *this };
  }
};

inline constexpr GenericErrorCategory kGenericCategoryInstance{};
inline constexpr SystemErrorCategory kSystemCategoryInstance{};

}// namespace detail

[[nodiscard]] constexpr auto GenericCategory() noexcept -> const ErrorCategory &
{
  return detail::kGenericCategoryInstance;
}

[[nodiscard]] constexpr auto SystemCategory() noexcept -> const ErrorCategory &
{
  return detail::kSystemCategoryInstance;
}

}// namespace cx

#endif
