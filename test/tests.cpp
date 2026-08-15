#include <catch2/catch_test_macros.hpp>

#include <cx_system_error/system_error.hpp>

#include <string_view>

TEST_CASE("runtime ErrorCode message and equivalence", "[ErrorCode]")
{
  const auto code = cx::MakeErrorCode(cx::Errc::kNotEnoughMemory);
  REQUIRE(code);
  REQUIRE(code.Category().Name() == std::string_view{ "generic" });
  REQUIRE(code.Message() == "Not enough memory");

  const cx::ErrorCondition condition = cx::Errc::kNotEnoughMemory;
  REQUIRE(code == condition);

  cx::ErrorCode assigned;
  assigned.Assign(static_cast<int>(cx::Errc::kBrokenPipe), cx::SystemCategory());
  REQUIRE(assigned.DefaultErrorCondition() == cx::ErrorCondition{ cx::Errc::kBrokenPipe });
}

TEST_CASE("categories compare by identity", "[ErrorCategory]")
{
  REQUIRE(cx::GenericCategory() == cx::GenericCategory());
  REQUIRE(cx::SystemCategory() == cx::SystemCategory());
  REQUIRE(cx::GenericCategory() != cx::SystemCategory());
  REQUIRE((cx::GenericCategory() <=> cx::SystemCategory()) != 0);
}
