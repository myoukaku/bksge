/**
 *	@file	to_wstring.hpp
 *
 *	@brief	to_wstring の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_TO_WSTRING_HPP
#define BKSGE_FND_STRING_TO_WSTRING_HPP

#include <bksge/fnd/string/wstring.hpp>
#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::to_wstring;

}	// namespace bksge

#else

#include <bksge/fnd/limits.hpp>
#include <cwchar>	// swprintf

namespace bksge
{

namespace detail
{

template <bksge::size_t N, typename T>
inline bksge::wstring to_wstring_impl(wchar_t const* fmt, T val)
{
	wchar_t buf[N]{};
	auto len = std::swprintf(buf, N, fmt, val);
	return bksge::wstring(buf, buf + len);
}

}	// namespace detail

inline wstring
to_wstring(int val)
{
	return detail::to_wstring_impl<4 * sizeof(int)>(L"%d", val);
}

inline wstring
to_wstring(long val)
{
	return detail::to_wstring_impl<4 * sizeof(long)>(L"%ld", val);
}

inline wstring
to_wstring(long long val)
{
	return detail::to_wstring_impl<4 * sizeof(long long)>(L"%lld", val);
}

inline wstring
to_wstring(unsigned val)
{
	return detail::to_wstring_impl<4 * sizeof(unsigned)>(L"%u", val);
}

inline wstring
to_wstring(unsigned long val)
{
	return detail::to_wstring_impl<4 * sizeof(unsigned long)>(L"%lu", val);
}

inline wstring
to_wstring(unsigned long long val)
{
	return detail::to_wstring_impl<4 * sizeof(unsigned long long)>(L"%llu", val);
}

inline wstring
to_wstring(float val)
{
	constexpr int n = bksge::numeric_limits<float>::max_exponent10 + 20;
	return detail::to_wstring_impl<n>(L"%f", val);
}

inline wstring
to_wstring(double val)
{
	constexpr int n = bksge::numeric_limits<double>::max_exponent10 + 20;
	return detail::to_wstring_impl<n>(L"%f", val);
}

inline wstring
to_wstring(long double val)
{
	constexpr int n = bksge::numeric_limits<long double>::max_exponent10 + 20;
	return detail::to_wstring_impl<n>(L"%Lf", val);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_STRING_TO_WSTRING_HPP
