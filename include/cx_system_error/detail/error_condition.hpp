#ifndef CX_SYSTEM_ERROR_DETAIL_ERROR_CONDITION_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERROR_CONDITION_HPP

#include <cx_system_error/detail/error_category.hpp>
#include <cx_system_error/detail/error_traits.hpp>
#include <cx_system_error/detail/forward.hpp>

#include <string_view>
#include <type_traits>

namespace cx {

namespace detail {

void MakeErrorCondition() = delete;

}// namespace detail

class ErrorCondition
{
  template<typename ErrorConditionEnum>
  using Check = std::enable_if_t<kIsErrorConditionEnumV<ErrorConditionEnum>>;

public:
  constexpr ErrorCondition() noexcept : value_(0), category_(&GenericCategory()) {}

  constexpr ErrorCondition(int value, const ErrorCategory &category) noexcept
    : value_(value), category_(&category)
  {}

  // Intentional implicit conversion, same as std::error_condition(ErrorConditionEnum).
  // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
  template<typename ErrorConditionEnum, typename = Check<ErrorConditionEnum>>
  // cppcheck-suppress noExplicitConstructor
  constexpr ErrorCondition(ErrorConditionEnum error) noexcept : value_(0), category_(&GenericCategory())
  {
    using detail::MakeErrorCondition;
    *this = MakeErrorCondition(error);
  }
  // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)

  constexpr ErrorCondition(const ErrorCondition &) = default;
  constexpr auto operator=(const ErrorCondition &) -> ErrorCondition & = default;
  constexpr ErrorCondition(ErrorCondition &&) noexcept = default;
  constexpr auto operator=(ErrorCondition &&) noexcept -> ErrorCondition & = default;
  constexpr ~ErrorCondition() = default;

  constexpr void Assign(int value, const ErrorCategory &category) noexcept
  {
    value_ = value;
    category_ = &category;
  }

  constexpr void Clear() noexcept { Assign(0, GenericCategory()); }

  [[nodiscard]] constexpr auto Value() const noexcept -> int { return value_; }

  [[nodiscard]] constexpr auto Category() const noexcept -> const ErrorCategory & { return *category_; }

  [[nodiscard]] constexpr auto Message() const noexcept -> std::string_view
  {
    return Category().Message(Value());
  }

  [[nodiscard]] constexpr explicit operator bool() const noexcept { return value_ != 0; }

private:
  int value_;
  const ErrorCategory *category_;
};

}// namespace cx

#endif
