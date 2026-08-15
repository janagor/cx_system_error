#ifndef CX_SYSTEM_ERROR_DETAIL_ERROR_CODE_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERROR_CODE_HPP

#include <cx_system_error/detail/error_category.hpp>
#include <cx_system_error/detail/error_traits.hpp>
#include <cx_system_error/detail/forward.hpp>

#include <string_view>
#include <type_traits>

namespace cx {

namespace detail {

void MakeErrorCode() = delete;

}// namespace detail

class ErrorCode
{
  template<typename ErrorCodeEnum>
  using Check = std::enable_if_t<kIsErrorCodeEnumV<ErrorCodeEnum>>;

public:
  constexpr ErrorCode() noexcept : value_(0), category_(&SystemCategory()) {}

  constexpr ErrorCode(int value, const ErrorCategory &category) noexcept
    : value_(value), category_(&category)
  {}

  // Intentional implicit conversion, same as std::error_code(ErrorCodeEnum).
  // NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
  template<typename ErrorCodeEnum, typename = Check<ErrorCodeEnum>>
  // cppcheck-suppress noExplicitConstructor
  constexpr ErrorCode(ErrorCodeEnum error) noexcept : value_(0), category_(&SystemCategory())
  {
    using detail::MakeErrorCode;
    *this = MakeErrorCode(error);
  }
  // NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)

  constexpr ErrorCode(const ErrorCode &) = default;
  constexpr auto operator=(const ErrorCode &) -> ErrorCode & = default;
  constexpr ErrorCode(ErrorCode &&) noexcept = default;
  constexpr auto operator=(ErrorCode &&) noexcept -> ErrorCode & = default;
  constexpr ~ErrorCode() = default;

  constexpr void Assign(int value, const ErrorCategory &category) noexcept
  {
    value_ = value;
    category_ = &category;
  }

  constexpr void Clear() noexcept { Assign(0, SystemCategory()); }

  [[nodiscard]] constexpr auto Value() const noexcept -> int { return value_; }

  [[nodiscard]] constexpr auto Category() const noexcept -> const ErrorCategory & { return *category_; }

  [[nodiscard]] constexpr auto DefaultErrorCondition() const noexcept -> ErrorCondition;

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
