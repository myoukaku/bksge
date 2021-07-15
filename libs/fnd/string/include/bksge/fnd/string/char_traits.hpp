/**
 *	@file	char_traits.hpp
 *
 *	@brief	char_traits クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_CHAR_TRAITS_HPP
#define BKSGE_FND_STRING_CHAR_TRAITS_HPP

#include <bksge/fnd/algorithm/copy_backward.hpp>
#include <bksge/fnd/algorithm/copy_n.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <ios>
#include <cwchar>
#include <cstdio>
#include <cstddef>

namespace bksge
{

namespace detail
{

template <typename CharT>
struct char_traits_types
{
	using int_type   = unsigned long;
	using pos_type   = std::streampos;
};

template <>
struct char_traits_types<char>
{
	using int_type   = int;
	using pos_type   = std::streampos;
};

template <>
struct char_traits_types<wchar_t>
{
	using int_type   = std::wint_t;
	using pos_type   = std::wstreampos;
};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct char_traits_types<char8_t>
{
	using int_type   = unsigned int;
	using pos_type   = std::u8streampos;
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
template <>
struct char_traits_types<char16_t>
{
	using int_type   = bksge::uint_least16_t;
	using pos_type   = std::u16streampos;
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
template <>
struct char_traits_types<char32_t>
{
	using int_type   = bksge::uint_least32_t;
	using pos_type   = std::u32streampos;
};
#endif

template <typename CharT, typename Derived>
struct char_traits_base
{
	using char_type  = CharT;
	using int_type   = typename char_traits_types<CharT>::int_type;
	using pos_type   = typename char_traits_types<CharT>::pos_type;
	using off_type   = std::streamoff;
	using state_type = std::mbstate_t;
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	using comparison_category = bksge::strong_ordering;
#endif

	static BKSGE_CXX14_CONSTEXPR void
	assign(char_type& c1, char_type const& c2)
		BKSGE_NOEXCEPT_IF_EXPR(c1 = c2)
	{
		c1 = c2;
	}

	static BKSGE_CONSTEXPR bool
	eq(char_type const& c1, char_type const& c2)
		BKSGE_NOEXCEPT_IF_EXPR(c1 == c2)
	{
		return c1 == c2;
	}

	static BKSGE_CONSTEXPR bool
	lt(char_type const& c1, char_type const& c2)
		BKSGE_NOEXCEPT_IF_EXPR(c1 < c2)
	{
		return c1 < c2;
	}

	static BKSGE_CXX14_CONSTEXPR int
	compare(char_type const* s1, char_type const* s2, std::size_t n)
	{
		for (std::size_t i = 0; i < n; ++i)
		{
			if (Derived::lt(s1[i], s2[i]))
			{
				return -1;
			}
			else if (Derived::lt(s2[i], s1[i]))
			{
				return 1;
			}
		}

		return 0;
	}

	static BKSGE_CXX14_CONSTEXPR std::size_t
	length(char_type const* s)
	{
		std::size_t i = 0;
		while (!Derived::eq(s[i], char_type()))
		{
			++i;
		}

		return i;
	}

	static BKSGE_CXX14_CONSTEXPR char_type const*
	find(char_type const* s, std::size_t n, char_type const& a)
	{
		for (std::size_t i = 0; i < n; ++i)
		{
			if (Derived::eq(s[i], a))
			{
				return s + i;
			}
		}

		return 0;
	}

	static BKSGE_CXX14_CONSTEXPR char_type*
	move(char_type* s1, char_type const* s2, std::size_t n)
	{
		if (n == 0)
		{
			return s1;
		}

		if (s2 < s1 && s1 < s2 + n)
		{
			bksge::copy_backward(s2, s2 + n, s1 + n);
		}
		else
		{
			bksge::copy_n(s2, n, s1);
		}

		return s1;
	}

	static BKSGE_CXX14_CONSTEXPR char_type*
	copy(char_type* s1, char_type const* s2, std::size_t n)
	{
		bksge::copy_n(s2, n, s1);
		return s1;
	}

	static BKSGE_CXX14_CONSTEXPR char_type*
	assign(char_type* s, std::size_t n, char_type a)
	{
		for (std::size_t i = 0; i < n; ++i)
		{
			Derived::assign(s[i], a);
		}

		return s;
	}

	static BKSGE_CONSTEXPR char_type
	to_char_type(int_type const& c)
		BKSGE_NOEXCEPT_IF_EXPR(static_cast<char_type>(c))
	{
		return static_cast<char_type>(c);
	}

	static BKSGE_CONSTEXPR int_type
	to_int_type(char_type const& c)
		BKSGE_NOEXCEPT_IF_EXPR(static_cast<int_type>(c))
	{
		return static_cast<int_type>(c);
	}

	static BKSGE_CONSTEXPR bool
	eq_int_type(int_type const& c1, int_type const& c2)
		BKSGE_NOEXCEPT_IF_EXPR(c1 == c2)
	{
		return c1 == c2;
	}

	static BKSGE_CONSTEXPR int_type eof()
		BKSGE_NOEXCEPT_IF_EXPR(static_cast<int_type>(-1))
	{
		return static_cast<int_type>(-1);
	}

	static BKSGE_CONSTEXPR int_type not_eof(int_type const& c)
	{
		return !Derived::eq_int_type(c, Derived::eof()) ? c : Derived::to_int_type(char_type());
	}
};

}	// namespace detail

template <typename CharT>
struct char_traits : public detail::char_traits_base<CharT, char_traits<CharT>>
{};

template <>
struct char_traits<char> : public detail::char_traits_base<char, char_traits<char>>
{
	static BKSGE_CONSTEXPR bool
	eq(char_type const& c1, char_type const& c2) BKSGE_NOEXCEPT
	{
		return
			static_cast<unsigned char>(c1) ==
			static_cast<unsigned char>(c2);
	}

	static BKSGE_CONSTEXPR bool
	lt(char_type const& c1, char_type const& c2) BKSGE_NOEXCEPT
	{
		return
			static_cast<unsigned char>(c1) <
			static_cast<unsigned char>(c2);
	}

	// To keep both the byte 0xff and the eof symbol 0xffffffff
	// from ending up as 0xffffffff.
	static BKSGE_CONSTEXPR int_type
	to_int_type(char_type const& c) BKSGE_NOEXCEPT
	{
		return static_cast<int_type>(static_cast<unsigned char>(c));
	}

	static BKSGE_CONSTEXPR int_type
	eof() BKSGE_NOEXCEPT
	{
		return static_cast<int_type>(EOF);
	}
};

template <>
struct char_traits<wchar_t> : public detail::char_traits_base<wchar_t, char_traits<wchar_t>>
{
	static BKSGE_CONSTEXPR int_type
	eof() BKSGE_NOEXCEPT
	{
		return static_cast<int_type>(WEOF);
	}
};

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <>
struct char_traits<char8_t> : public detail::char_traits_base<char8_t, char_traits<char8_t>>
{
};
#endif	// defined(BKSGE_HAS_CXX20_CHAR8_T)

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
template <>
struct char_traits<char16_t> : public detail::char_traits_base<char16_t, char_traits<char16_t>>
{
	static constexpr int_type
	to_int_type(char_type const& c) BKSGE_NOEXCEPT
	{
		return c == static_cast<char_type>(-1) ? int_type(0xfffd) : int_type(c);
	}
};
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
template <>
struct char_traits<char32_t> : public detail::char_traits_base<char32_t, char_traits<char32_t>>
{
};
#endif

namespace detail
{

template <typename Traits>
struct char_traits_cmp_cat
{
	using type = typename Traits::comparison_category;
	static_assert(!bksge::is_void<bksge::common_comparison_category_t<type>>::value, "");
};

template <typename Traits>
using char_traits_cmp_cat_t = typename char_traits_cmp_cat<Traits>::type;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_CHAR_TRAITS_HPP
