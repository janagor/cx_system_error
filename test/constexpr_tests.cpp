#include <catch2/catch_test_macros.hpp>

#include <cx_system_error/system_error.hpp>

TEST_CASE("ErrorCode defaults to system success", "[ErrorCode]")
{
  constexpr cx::ErrorCode kCode{};
  STATIC_REQUIRE(!kCode);
  STATIC_REQUIRE(kCode.Value() == 0);
  STATIC_REQUIRE(kCode.Category() == cx::SystemCategory());
  STATIC_REQUIRE(kCode.Message() == "Success");
}

TEST_CASE("ErrorCondition defaults to generic success", "[ErrorCondition]")
{
  constexpr cx::ErrorCondition kCondition{};
  STATIC_REQUIRE(!kCondition);
  STATIC_REQUIRE(kCondition.Value() == 0);
  STATIC_REQUIRE(kCondition.Category() == cx::GenericCategory());
}

TEST_CASE("Errc maps through MakeErrorCode and MakeErrorCondition", "[Errc]")
{
  constexpr auto kCode = cx::MakeErrorCode(cx::Errc::kInvalidArgument);
  STATIC_REQUIRE(kCode);
  STATIC_REQUIRE(kCode.Value() == static_cast<int>(cx::Errc::kInvalidArgument));
  STATIC_REQUIRE(kCode.Category() == cx::GenericCategory());
  STATIC_REQUIRE(kCode.Message() == "Invalid argument");

  constexpr cx::ErrorCondition kCondition = cx::Errc::kPermissionDenied;
  STATIC_REQUIRE(kCondition);
  STATIC_REQUIRE(kCondition.Category() == cx::GenericCategory());
  STATIC_REQUIRE(kCondition.Message() == "Permission denied");
}

TEST_CASE("SystemCategory maps known errno values to generic conditions", "[ErrorCategory]")
{
  constexpr cx::ErrorCode kCode{ static_cast<int>(cx::Errc::kNoSuchFileOrDirectory), cx::SystemCategory() };
  constexpr auto kCondition = kCode.DefaultErrorCondition();
  STATIC_REQUIRE(kCondition.Category() == cx::GenericCategory());
  STATIC_REQUIRE(kCondition.Value() == static_cast<int>(cx::Errc::kNoSuchFileOrDirectory));
  STATIC_REQUIRE(kCode == kCondition);
}

TEST_CASE("ErrorCode comparison and Clear", "[ErrorCode]")
{
  constexpr auto kCleared = []() -> cx::ErrorCode {
    cx::ErrorCode code = cx::MakeErrorCode(cx::Errc::kTimedOut);
    code.Clear();
    return code;
  }();

  STATIC_REQUIRE(!kCleared);
  STATIC_REQUIRE(kCleared.Category() == cx::SystemCategory());
  STATIC_REQUIRE(cx::MakeErrorCode(cx::Errc::kTimedOut) != cx::MakeErrorCode(cx::Errc::kInterrupted));
}
