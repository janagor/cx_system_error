#ifndef CX_SYSTEM_ERROR_DETAIL_ERRC_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERRC_HPP

#include <cx_system_error/detail/error_traits.hpp>

#include <cerrno>
#include <type_traits>

namespace cx {

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

template<> struct IsErrorConditionEnum<Errc> : std::true_type
{
};

}// namespace cx

#endif
