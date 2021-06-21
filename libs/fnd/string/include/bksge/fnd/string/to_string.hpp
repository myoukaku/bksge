/**
 *	@file	to_string.hpp
 *
 *	@brief	to_string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_TO_STRING_HPP
#define BKSGE_FND_STRING_TO_STRING_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::to_string;

}	// namespace bksge

#else

#include <bksge/fnd/string/detail/to_chars_len.hpp>
#include <bksge/fnd/string/detail/to_chars_10_impl.hpp>
#include <cstdio>	// snprintf
#include <limits>

namespace bksge
{

namespace detail
{

template <bksge::size_t N, typename T>
inline bksge::string to_string_impl(char const* fmt, T val)
{
	char buf[N]{};
	auto len = std::snprintf(buf, N, fmt, val);
	return bksge::string(buf, buf + len);
}

}	// namespace detail

inline string
to_string(int val)
{
	const bool neg = val < 0;
	const unsigned uval = neg ? (unsigned)~val + 1u : val;
	const auto len = detail::to_chars_len(uval);
	string str(neg + len, '-');
	detail::to_chars_10_impl(&str[neg], len, uval);
	return str;
}

inline string
to_string(long val)
{
	const bool neg = val < 0;
	const unsigned long uval = neg ? (unsigned long)~val + 1ul : val;
	const auto len = detail::to_chars_len(uval);
	string str(neg + len, '-');
	detail::to_chars_10_impl(&str[neg], len, uval);
	return str;
}

inline string
to_string(long long val)
{
	const bool neg = val < 0;
	const unsigned long long uval = neg ? (unsigned long long)~val + 1ull : val;
	const auto len = detail::to_chars_len(uval);
	string str(neg + len, '-');
	detail::to_chars_10_impl(&str[neg], len, uval);
	return str;
}

inline string
to_string(unsigned val)
{
	string str(detail::to_chars_len(val), '\0');
	detail::to_chars_10_impl(&str[0], str.size(), val);
	return str;
}

inline string
to_string(unsigned long val)
{
	string str(detail::to_chars_len(val), '\0');
	detail::to_chars_10_impl(&str[0], str.size(), val);
	return str;
}

inline string
to_string(unsigned long long val)
{
	string str(detail::to_chars_len(val), '\0');
	detail::to_chars_10_impl(&str[0], str.size(), val);
	return str;
}

inline string
to_string(float val)
{
	constexpr int n = std::numeric_limits<float>::max_exponent10 + 20;
	return detail::to_string_impl<n>("%f", val);
}

inline string
to_string(double val)
{
	constexpr int n = std::numeric_limits<double>::max_exponent10 + 20;
	return detail::to_string_impl<n>("%f", val);
}

inline string
to_string(long double val)
{
	constexpr int n = std::numeric_limits<long double>::max_exponent10 + 20;
	return detail::to_string_impl<n>("%Lf", val);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_STRING_TO_STRING_HPP
