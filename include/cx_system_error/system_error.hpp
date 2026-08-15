#ifndef CX_SYSTEM_ERROR_SYSTEM_ERROR_HPP
#define CX_SYSTEM_ERROR_SYSTEM_ERROR_HPP

#include <cx_system_error/detail/errc_message.hpp>

#include <cerrno>
#include <compare>
#include <string_view>
#include <type_traits>

namespace cx {

class ErrorCode;
class ErrorCondition;

// Future (C++26 constexpr exceptions): class SystemError;

template<typename Type>
struct IsErrorCodeEnum : std::false_type {};

template<typename Type>
struct IsErrorConditionEnum : std::false_type {};

template<typename Type>
inline constexpr bool kIsErrorCodeEnumV = IsErrorCodeEnum<Type>::value;

template<typename Type>
inline constexpr bool kIsErrorConditionEnumV = IsErrorConditionEnum<Type>::value;

// Underlying type must stay int: values are errno constants (same as std::errc).
// NOLINTNEXTLINE(performance-enum-size)
enum class Errc {
  kAddressFamilyNotSupported = EAFNOSUPPORT,
  kAddressInUse = EADDRINUSE,
  kAddressNotAvailable = EADDRNOTAVAIL,
  kAlreadyConnected = EISCONN,
  kArgumentListTooLong = E2BIG,
  kArgumentOutOfDomain = EDOM,
  kBadAddress = EFAULT,
  kBadFileDescriptor = EBADF,
#ifdef EBADMSG
  kBadMessage = EBADMSG,
#endif
  kBrokenPipe = EPIPE,
  kConnectionAborted = ECONNABORTED,
  kConnectionAlreadyInProgress = EALREADY,
  kConnectionRefused = ECONNREFUSED,
  kConnectionReset = ECONNRESET,
  kCrossDeviceLink = EXDEV,
  kDestinationAddressRequired = EDESTADDRREQ,
  kDeviceOrResourceBusy = EBUSY,
  kDirectoryNotEmpty = ENOTEMPTY,
  kExecutableFormatError = ENOEXEC,
  kFileExists = EEXIST,
  kFileTooLarge = EFBIG,
  kFilenameTooLong = ENAMETOOLONG,
  kFunctionNotSupported = ENOSYS,
  kHostUnreachable = EHOSTUNREACH,
#ifdef EIDRM
  kIdentifierRemoved = EIDRM,
#endif
  kIllegalByteSequence = EILSEQ,
  kInappropriateIoControlOperation = ENOTTY,
  kInterrupted = EINTR,
  kInvalidArgument = EINVAL,
  kInvalidSeek = ESPIPE,
  kIoError = EIO,
  kIsADirectory = EISDIR,
  kMessageSize = EMSGSIZE,
  kNetworkDown = ENETDOWN,
  kNetworkReset = ENETRESET,
  kNetworkUnreachable = ENETUNREACH,
  kNoBufferSpace = ENOBUFS,
  kNoChildProcess = ECHILD,
#ifdef ENOLINK
  kNoLink = ENOLINK,
#endif
  kNoLockAvailable = ENOLCK,
#ifdef ENODATA
  kNoMessageAvailable = ENODATA,
#endif
  kNoMessage = ENOMSG,
  kNoProtocolOption = ENOPROTOOPT,
  kNoSpaceOnDevice = ENOSPC,
#ifdef ENOSR
  kNoStreamResources = ENOSR,
#endif
  kNoSuchDeviceOrAddress = ENXIO,
  kNoSuchDevice = ENODEV,
  kNoSuchFileOrDirectory = ENOENT,
  kNoSuchProcess = ESRCH,
  kNotADirectory = ENOTDIR,
  kNotASocket = ENOTSOCK,
#ifdef ENOSTR
  kNotAStream = ENOSTR,
#endif
  kNotConnected = ENOTCONN,
  kNotEnoughMemory = ENOMEM,
#ifdef ENOTSUP
  kNotSupported = ENOTSUP,
#endif
#ifdef ECANCELED
  kOperationCanceled = ECANCELED,
#endif
  kOperationInProgress = EINPROGRESS,
  kOperationNotPermitted = EPERM,
  kOperationNotSupported = EOPNOTSUPP,
  kOperationWouldBlock = EWOULDBLOCK,
#ifdef EOWNERDEAD
  kOwnerDead = EOWNERDEAD,
#endif
  kPermissionDenied = EACCES,
#ifdef EPROTO
  kProtocolError = EPROTO,
#endif
  kProtocolNotSupported = EPROTONOSUPPORT,
  kReadOnlyFileSystem = EROFS,
  kResourceDeadlockWouldOccur = EDEADLK,
  kResourceUnavailableTryAgain = EAGAIN,
  kResultOutOfRange = ERANGE,
#ifdef ENOTRECOVERABLE
  kStateNotRecoverable = ENOTRECOVERABLE,
#endif
#ifdef ETIME
  kStreamTimeout = ETIME,
#endif
#ifdef ETXTBSY
  kTextFileBusy = ETXTBSY,
#endif
  kTimedOut = ETIMEDOUT,
  kTooManyFilesOpenInSystem = ENFILE,
  kTooManyFilesOpen = EMFILE,
  kTooManyLinks = EMLINK,
  kTooManySymbolicLinkLevels = ELOOP,
#ifdef EOVERFLOW
  kValueTooLarge = EOVERFLOW,
#endif
  kWrongProtocolType = EPROTOTYPE
};

template<>
struct IsErrorConditionEnum<Errc> : std::true_type {};

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

namespace detail {

void MakeErrorCode() = delete;
void MakeErrorCondition() = delete;

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

[[nodiscard]] constexpr auto MakeErrorCode(Errc error) noexcept -> ErrorCode
{
  return ErrorCode{ static_cast<int>(error), GenericCategory() };
}

[[nodiscard]] constexpr auto MakeErrorCondition(Errc error) noexcept -> ErrorCondition
{
  return ErrorCondition{ static_cast<int>(error), GenericCategory() };
}

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
