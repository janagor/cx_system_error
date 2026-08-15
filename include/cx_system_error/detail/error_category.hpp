#ifndef CX_SYSTEM_ERROR_DETAIL_ERROR_CATEGORY_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERROR_CATEGORY_HPP

#include <cx_system_error/detail/forward.hpp>

#include <compare>
#include <string_view>

namespace cx {

class ErrorCategory
{
public:
  constexpr ErrorCategory() noexcept = default;
  constexpr ErrorCategory(const ErrorCategory &) = delete;
  constexpr auto operator=(const ErrorCategory &) -> ErrorCategory & = delete;
  constexpr ErrorCategory(ErrorCategory &&) = delete;
  constexpr auto operator=(ErrorCategory &&) -> ErrorCategory & = delete;
  constexpr virtual ~ErrorCategory() = default;

  [[nodiscard]] constexpr virtual auto Name() const noexcept -> const char * = 0;

  // std::string in <system_error>; string_view keeps this usable in constant evaluation.
  [[nodiscard]] constexpr virtual auto Message(int error_value) const noexcept -> std::string_view = 0;

  [[nodiscard]] constexpr virtual auto DefaultErrorCondition(int error_value) const noexcept -> ErrorCondition;

  [[nodiscard]] constexpr virtual auto Equivalent(int code, const ErrorCondition &condition) const noexcept -> bool;

  [[nodiscard]] constexpr virtual auto Equivalent(const ErrorCode &code, int condition) const noexcept -> bool;

  [[nodiscard]] constexpr auto operator==(const ErrorCategory &rhs) const noexcept -> bool
  {
    return this == &rhs;
  }

  [[nodiscard]] constexpr auto operator<=>(const ErrorCategory &rhs) const noexcept -> std::strong_ordering
  {
    return std::compare_three_way{}(this, &rhs);
  }
};

[[nodiscard]] constexpr auto GenericCategory() noexcept -> const ErrorCategory &;
[[nodiscard]] constexpr auto SystemCategory() noexcept -> const ErrorCategory &;

}// namespace cx

#endif
