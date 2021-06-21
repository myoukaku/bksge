/**
 *	@file	getline.hpp
 *
 *	@brief	getline の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_GETLINE_HPP
#define BKSGE_FND_STRING_GETLINE_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::getline;

}	// namespace bksge

#else

#include <istream>

namespace bksge
{

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline std::basic_istream<CharT, Traits1>&
getline(
	std::basic_istream<CharT, Traits1>& is,
	bksge::basic_string<CharT, Traits2, Allocator>& str, CharT delim)
{
	using istream_type = std::basic_istream<CharT, Traits1>;
	using string_type  = bksge::basic_string<CharT, Traits2, Allocator>;
	using ios_base     = typename istream_type::ios_base;
	using int_type     = typename istream_type::int_type;
	using size_type    = typename string_type::size_type;

	size_type extracted = 0;
	size_type const n = str.max_size();
	typename ios_base::iostate err = ios_base::goodbit;
	typename istream_type::sentry cerb(is, true);

	if (cerb)
	{
		try
		{
			str.erase();
			int_type const idelim = Traits2::to_int_type(delim);
			int_type const eof = Traits2::eof();
			int_type c = is.rdbuf()->sgetc();

			while (extracted < n &&
				!Traits2::eq_int_type(c, eof) &&
				!Traits2::eq_int_type(c, idelim))
			{
				str += Traits2::to_char_type(c);
				++extracted;
				c = is.rdbuf()->snextc();
			}

			if (Traits2::eq_int_type(c, eof))
			{
				err |= ios_base::eofbit;
			}
			else if (Traits2::eq_int_type(c, idelim))
			{
				++extracted;
				is.rdbuf()->sbumpc();
			}
			else
			{
				err |= ios_base::failbit;
			}
		}
		/*catch(__cxxabiv1::__forced_unwind&)
		{
			is._M_setstate(ios_base::badbit);
			__throw_exception_again;
		}*/
		catch(...)
		{
			//is._M_setstate(ios_base::badbit);
			is.setstate(ios_base::badbit);
			if (is.exceptions() & ios_base::badbit)
			{
				throw;//__throw_exception_again;
			}
		}
	}

	if (!extracted)
	{
		err |= ios_base::failbit;
	}

	if (err)
	{
		is.setstate(err);
	}

	return is;

}

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline std::basic_istream<CharT, Traits1>&
getline(
	std::basic_istream<CharT, Traits1>& is,
	bksge::basic_string<CharT, Traits2, Allocator>& str)
{
	return bksge::getline(is, str, is.widen('\n'));
}

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline std::basic_istream<CharT, Traits1>&
getline(
	std::basic_istream<CharT, Traits1>&& is,
	bksge::basic_string<CharT, Traits2, Allocator>& str, CharT delim)
{
	return bksge::getline(is, str, delim);
}

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline std::basic_istream<CharT, Traits1>&
getline(
	std::basic_istream<CharT, Traits1>&& is,
	bksge::basic_string<CharT, Traits2, Allocator>& str)
{
	return bksge::getline(is, str);
}

//template <>
//std::basic_istream<char>&
//getline(std::basic_istream<char>& in, bksge::basic_string<char>& str, char delim);
//
//template <>
//std::basic_istream<wchar_t>&
//getline(std::basic_istream<wchar_t>& in, bksge::basic_string<wchar_t>& str, wchar_t delim);

}	// namespace bksge

#endif

#endif // BKSGE_FND_STRING_GETLINE_HPP
