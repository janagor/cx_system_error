#ifndef CX_SYSTEM_ERROR_DETAIL_COMPARISONS_HPP
#define CX_SYSTEM_ERROR_DETAIL_COMPARISONS_HPP

#include <cx_system_error/detail/error_code.hpp>
#include <cx_system_error/detail/error_condition.hpp>

#include <compare>

namespace cx {

[[nodiscard]] constexpr auto operator<=>(const ErrorCode &lhs, const ErrorCode &rhs) noexcept -> std::strong_ordering
{
  if (auto cmp = lhs.Category() <=> rhs.Category(); cmp != 0) { return cmp; }
  return lhs.Value() <=> rhs.Value();
}

[[nodiscard]] constexpr auto operator==(const ErrorCode &lhs, const ErrorCode &rhs) noexcept -> bool
{
  return lhs.Category() == rhs.Category() && lhs.Value() == rhs.Value();
}

[[nodiscard]] constexpr auto operator==(const ErrorCode &lhs, const ErrorCondition &rhs) noexcept -> bool
{
  return lhs.Category().Equivalent(lhs.Value(), rhs) || rhs.Category().Equivalent(lhs, rhs.Value());
}

[[nodiscard]] constexpr auto operator==(const ErrorCondition &lhs, const ErrorCondition &rhs) noexcept -> bool
{
  return lhs.Category() == rhs.Category() && lhs.Value() == rhs.Value();
}

[[nodiscard]] constexpr auto operator<=>(const ErrorCondition &lhs, const ErrorCondition &rhs) noexcept
  -> std::strong_ordering
{
  if (auto cmp = lhs.Category() <=> rhs.Category(); cmp != 0) { return cmp; }
  return lhs.Value() <=> rhs.Value();
}

}// namespace cx

#endif
