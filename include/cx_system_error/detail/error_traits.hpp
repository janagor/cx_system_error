#ifndef CX_SYSTEM_ERROR_DETAIL_ERROR_TRAITS_HPP
#define CX_SYSTEM_ERROR_DETAIL_ERROR_TRAITS_HPP

#include <type_traits>

namespace cx {

template<typename Type> struct IsErrorCodeEnum : std::false_type
{
};

template<typename Type> struct IsErrorConditionEnum : std::false_type
{
};

template<typename Type> inline constexpr bool kIsErrorCodeEnumV = IsErrorCodeEnum<Type>::value;

template<typename Type> inline constexpr bool kIsErrorConditionEnumV = IsErrorConditionEnum<Type>::value;

}// namespace cx

#endif
