#ifndef CX_SYSTEM_ERROR_DETAIL_ERRC_MESSAGE_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERRC_MESSAGE_HPP

#include <cerrno>
#include <string_view>

namespace cx::detail {

[[nodiscard]] constexpr auto ErrcMessage(int error_value) noexcept -> std::string_view
{
  switch (error_value) {
  case 0:
    return "Success";
#ifdef EAFNOSUPPORT
  case EAFNOSUPPORT:
    return "Address family not supported";
#endif
#ifdef EADDRINUSE
  case EADDRINUSE:
    return "Address in use";
#endif
#ifdef EADDRNOTAVAIL
  case EADDRNOTAVAIL:
    return "Address not available";
#endif
#ifdef EISCONN
  case EISCONN:
    return "Already connected";
#endif
#ifdef E2BIG
  case E2BIG:
    return "Argument list too long";
#endif
#ifdef EDOM
  case EDOM:
    return "Argument out of domain";
#endif
#ifdef EFAULT
  case EFAULT:
    return "Bad address";
#endif
#ifdef EBADF
  case EBADF:
    return "Bad file descriptor";
#endif
#ifdef EBADMSG
  case EBADMSG:
    return "Bad message";
#endif
#ifdef EPIPE
  case EPIPE:
    return "Broken pipe";
#endif
#ifdef ECONNABORTED
  case ECONNABORTED:
    return "Connection aborted";
#endif
#ifdef EALREADY
  case EALREADY:
    return "Connection already in progress";
#endif
#ifdef ECONNREFUSED
  case ECONNREFUSED:
    return "Connection refused";
#endif
#ifdef ECONNRESET
  case ECONNRESET:
    return "Connection reset";
#endif
#ifdef EXDEV
  case EXDEV:
    return "Cross-device link";
#endif
#ifdef EDESTADDRREQ
  case EDESTADDRREQ:
    return "Destination address required";
#endif
#ifdef EBUSY
  case EBUSY:
    return "Device or resource busy";
#endif
#ifdef ENOTEMPTY
  case ENOTEMPTY:
    return "Directory not empty";
#endif
#ifdef ENOEXEC
  case ENOEXEC:
    return "Executable format error";
#endif
#ifdef EEXIST
  case EEXIST:
    return "File exists";
#endif
#ifdef EFBIG
  case EFBIG:
    return "File too large";
#endif
#ifdef ENAMETOOLONG
  case ENAMETOOLONG:
    return "Filename too long";
#endif
#ifdef ENOSYS
  case ENOSYS:
    return "Function not supported";
#endif
#ifdef EHOSTUNREACH
  case EHOSTUNREACH:
    return "Host unreachable";
#endif
#ifdef EIDRM
  case EIDRM:
    return "Identifier removed";
#endif
#ifdef EILSEQ
  case EILSEQ:
    return "Illegal byte sequence";
#endif
#ifdef ENOTTY
  case ENOTTY:
    return "Inappropriate I/O control operation";
#endif
#ifdef EINTR
  case EINTR:
    return "Interrupted";
#endif
#ifdef EINVAL
  case EINVAL:
    return "Invalid argument";
#endif
#ifdef ESPIPE
  case ESPIPE:
    return "Invalid seek";
#endif
#ifdef EIO
  case EIO:
    return "I/O error";
#endif
#ifdef EISDIR
  case EISDIR:
    return "Is a directory";
#endif
#ifdef EMSGSIZE
  case EMSGSIZE:
    return "Message size";
#endif
#ifdef ENETDOWN
  case ENETDOWN:
    return "Network down";
#endif
#ifdef ENETRESET
  case ENETRESET:
    return "Network reset";
#endif
#ifdef ENETUNREACH
  case ENETUNREACH:
    return "Network unreachable";
#endif
#ifdef ENOBUFS
  case ENOBUFS:
    return "No buffer space";
#endif
#ifdef ECHILD
  case ECHILD:
    return "No child process";
#endif
#ifdef ENOLINK
  case ENOLINK:
    return "No link";
#endif
#ifdef ENOLCK
  case ENOLCK:
    return "No lock available";
#endif
#ifdef ENODATA
  case ENODATA:
    return "No message available";
#endif
#ifdef ENOMSG
  case ENOMSG:
    return "No message";
#endif
#ifdef ENOPROTOOPT
  case ENOPROTOOPT:
    return "No protocol option";
#endif
#ifdef ENOSPC
  case ENOSPC:
    return "No space on device";
#endif
#ifdef ENOSR
  case ENOSR:
    return "No stream resources";
#endif
#ifdef ENXIO
  case ENXIO:
    return "No such device or address";
#endif
#ifdef ENODEV
  case ENODEV:
    return "No such device";
#endif
#ifdef ENOENT
  case ENOENT:
    return "No such file or directory";
#endif
#ifdef ESRCH
  case ESRCH:
    return "No such process";
#endif
#ifdef ENOTDIR
  case ENOTDIR:
    return "Not a directory";
#endif
#ifdef ENOTSOCK
  case ENOTSOCK:
    return "Not a socket";
#endif
#ifdef ENOSTR
  case ENOSTR:
    return "Not a stream";
#endif
#ifdef ENOTCONN
  case ENOTCONN:
    return "Not connected";
#endif
#ifdef ENOMEM
  case ENOMEM:
    return "Not enough memory";
#endif
#if defined(ENOTSUP) && (!defined(EOPNOTSUPP) || ENOTSUP != EOPNOTSUPP)
  case ENOTSUP:
    return "Not supported";
#endif
#ifdef ECANCELED
  case ECANCELED:
    return "Operation canceled";
#endif
#ifdef EINPROGRESS
  case EINPROGRESS:
    return "Operation in progress";
#endif
#ifdef EPERM
  case EPERM:
    return "Operation not permitted";
#endif
#ifdef EOPNOTSUPP
  case EOPNOTSUPP:
    return "Operation not supported";
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)
  case EWOULDBLOCK:
    return "Operation would block";
#endif
#ifdef EOWNERDEAD
  case EOWNERDEAD:
    return "Owner dead";
#endif
#ifdef EACCES
  case EACCES:
    return "Permission denied";
#endif
#ifdef EPROTO
  case EPROTO:
    return "Protocol error";
#endif
#ifdef EPROTONOSUPPORT
  case EPROTONOSUPPORT:
    return "Protocol not supported";
#endif
#ifdef EROFS
  case EROFS:
    return "Read-only file system";
#endif
#ifdef EDEADLK
  case EDEADLK:
    return "Resource deadlock would occur";
#endif
#ifdef EAGAIN
  case EAGAIN:
    return "Resource unavailable, try again";
#endif
#ifdef ERANGE
  case ERANGE:
    return "Result out of range";
#endif
#ifdef ENOTRECOVERABLE
  case ENOTRECOVERABLE:
    return "State not recoverable";
#endif
#ifdef ETIME
  case ETIME:
    return "Stream timeout";
#endif
#ifdef ETXTBSY
  case ETXTBSY:
    return "Text file busy";
#endif
#ifdef ETIMEDOUT
  case ETIMEDOUT:
    return "Timed out";
#endif
#ifdef ENFILE
  case ENFILE:
    return "Too many files open in system";
#endif
#ifdef EMFILE
  case EMFILE:
    return "Too many files open";
#endif
#ifdef EMLINK
  case EMLINK:
    return "Too many links";
#endif
#ifdef ELOOP
  case ELOOP:
    return "Too many symbolic link levels";
#endif
#ifdef EOVERFLOW
  case EOVERFLOW:
    return "Value too large";
#endif
#ifdef EPROTOTYPE
  case EPROTOTYPE:
    return "Wrong protocol type";
#endif
  default:
    return "Unknown error";
  }
}

[[nodiscard]] constexpr auto IsGenericErrc(int error_value) noexcept -> bool
{
  switch (error_value) {
#ifdef EAFNOSUPPORT
  case EAFNOSUPPORT:
#endif
#ifdef EADDRINUSE
  case EADDRINUSE:
#endif
#ifdef EADDRNOTAVAIL
  case EADDRNOTAVAIL:
#endif
#ifdef EISCONN
  case EISCONN:
#endif
#ifdef E2BIG
  case E2BIG:
#endif
#ifdef EDOM
  case EDOM:
#endif
#ifdef EFAULT
  case EFAULT:
#endif
#ifdef EBADF
  case EBADF:
#endif
#ifdef EBADMSG
  case EBADMSG:
#endif
#ifdef EPIPE
  case EPIPE:
#endif
#ifdef ECONNABORTED
  case ECONNABORTED:
#endif
#ifdef EALREADY
  case EALREADY:
#endif
#ifdef ECONNREFUSED
  case ECONNREFUSED:
#endif
#ifdef ECONNRESET
  case ECONNRESET:
#endif
#ifdef EXDEV
  case EXDEV:
#endif
#ifdef EDESTADDRREQ
  case EDESTADDRREQ:
#endif
#ifdef EBUSY
  case EBUSY:
#endif
#ifdef ENOTEMPTY
  case ENOTEMPTY:
#endif
#ifdef ENOEXEC
  case ENOEXEC:
#endif
#ifdef EEXIST
  case EEXIST:
#endif
#ifdef EFBIG
  case EFBIG:
#endif
#ifdef ENAMETOOLONG
  case ENAMETOOLONG:
#endif
#ifdef ENOSYS
  case ENOSYS:
#endif
#ifdef EHOSTUNREACH
  case EHOSTUNREACH:
#endif
#ifdef EIDRM
  case EIDRM:
#endif
#ifdef EILSEQ
  case EILSEQ:
#endif
#ifdef ENOTTY
  case ENOTTY:
#endif
#ifdef EINTR
  case EINTR:
#endif
#ifdef EINVAL
  case EINVAL:
#endif
#ifdef ESPIPE
  case ESPIPE:
#endif
#ifdef EIO
  case EIO:
#endif
#ifdef EISDIR
  case EISDIR:
#endif
#ifdef EMSGSIZE
  case EMSGSIZE:
#endif
#ifdef ENETDOWN
  case ENETDOWN:
#endif
#ifdef ENETRESET
  case ENETRESET:
#endif
#ifdef ENETUNREACH
  case ENETUNREACH:
#endif
#ifdef ENOBUFS
  case ENOBUFS:
#endif
#ifdef ECHILD
  case ECHILD:
#endif
#ifdef ENOLINK
  case ENOLINK:
#endif
#ifdef ENOLCK
  case ENOLCK:
#endif
#ifdef ENODATA
  case ENODATA:
#endif
#ifdef ENOMSG
  case ENOMSG:
#endif
#ifdef ENOPROTOOPT
  case ENOPROTOOPT:
#endif
#ifdef ENOSPC
  case ENOSPC:
#endif
#ifdef ENOSR
  case ENOSR:
#endif
#ifdef ENXIO
  case ENXIO:
#endif
#ifdef ENODEV
  case ENODEV:
#endif
#ifdef ENOENT
  case ENOENT:
#endif
#ifdef ESRCH
  case ESRCH:
#endif
#ifdef ENOTDIR
  case ENOTDIR:
#endif
#ifdef ENOTSOCK
  case ENOTSOCK:
#endif
#ifdef ENOSTR
  case ENOSTR:
#endif
#ifdef ENOTCONN
  case ENOTCONN:
#endif
#ifdef ENOMEM
  case ENOMEM:
#endif
#if defined(ENOTSUP) && (!defined(EOPNOTSUPP) || ENOTSUP != EOPNOTSUPP)
  case ENOTSUP:
#endif
#ifdef ECANCELED
  case ECANCELED:
#endif
#ifdef EINPROGRESS
  case EINPROGRESS:
#endif
#ifdef EPERM
  case EPERM:
#endif
#ifdef EOPNOTSUPP
  case EOPNOTSUPP:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || EWOULDBLOCK != EAGAIN)
  case EWOULDBLOCK:
#endif
#ifdef EOWNERDEAD
  case EOWNERDEAD:
#endif
#ifdef EACCES
  case EACCES:
#endif
#ifdef EPROTO
  case EPROTO:
#endif
#ifdef EPROTONOSUPPORT
  case EPROTONOSUPPORT:
#endif
#ifdef EROFS
  case EROFS:
#endif
#ifdef EDEADLK
  case EDEADLK:
#endif
#ifdef EAGAIN
  case EAGAIN:
#endif
#ifdef ERANGE
  case ERANGE:
#endif
#ifdef ENOTRECOVERABLE
  case ENOTRECOVERABLE:
#endif
#ifdef ETIME
  case ETIME:
#endif
#ifdef ETXTBSY
  case ETXTBSY:
#endif
#ifdef ETIMEDOUT
  case ETIMEDOUT:
#endif
#ifdef ENFILE
  case ENFILE:
#endif
#ifdef EMFILE
  case EMFILE:
#endif
#ifdef EMLINK
  case EMLINK:
#endif
#ifdef ELOOP
  case ELOOP:
#endif
#ifdef EOVERFLOW
  case EOVERFLOW:
#endif
#ifdef EPROTOTYPE
  case EPROTOTYPE:
#endif
    return true;
  default:
    return false;
  }
}

}// namespace cx::detail

#endif
