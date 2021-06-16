/**
 *	@file	basic_string_view.hpp
 *
 *	@brief	basic_string_view クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP

#include <bksge/fnd/string_view/config.hpp>

#if defined(BKSGE_USE_STD_STRING_VIEW)

namespace bksge
{

using std::basic_string_view;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/string/char_traits.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/type_traits/is_standard_layout.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename CharT, typename Traits = bksge::char_traits<CharT>>
class basic_string_view
{
private:
	static_assert(!bksge::is_array<CharT>::value, "");
	static_assert(bksge::is_trivial<CharT>::value && bksge::is_standard_layout<CharT>::value, "");
	static_assert(bksge::is_same<CharT, typename Traits::char_type>::value, "");

public:
	using traits_type		        = Traits;
	using value_type		        = CharT;
	using pointer		            = value_type*;
	using const_pointer	            = value_type const*;
	using reference		            = value_type&;
	using const_reference	        = value_type const&;
	using const_iterator	        = value_type const*;
	using iterator		            = const_iterator;
	using const_reverse_iterator    = bksge::reverse_iterator<const_iterator>;
	using reverse_iterator	        = const_reverse_iterator;
	using size_type		            = bksge::size_t;
	using difference_type	        = bksge::ptrdiff_t;

	BKSGE_STATIC_CONSTEXPR size_type npos = size_type(-1);

	BKSGE_CONSTEXPR
	basic_string_view() BKSGE_NOEXCEPT
		: m_len{0}
		, m_str{nullptr}
	{}

	BKSGE_CONSTEXPR
	basic_string_view(basic_string_view const&) BKSGE_NOEXCEPT = default;

	BKSGE_CONSTEXPR
	basic_string_view(CharT const* s, size_type count) BKSGE_NOEXCEPT
		: m_len{count}
		, m_str{s}
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_string_view(CharT const* s) BKSGE_NOEXCEPT
		: m_len{traits_type::length(s)}
		, m_str{s}
	{}

	template <
		BKSGE_REQUIRES_PARAM(bksge::contiguous_iterator, It),
		BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, It, End),
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::is_same_as<bksge::iter_value_t<It>, CharT>,
			bksge::negation<bksge::is_convertible_to<End, size_type>>
		>::value>
	>
	BKSGE_CONSTEXPR
	basic_string_view(It first, End last)
		: m_len(last - first)
		, m_str(bksge::to_address(first))
	{}

	BKSGE_CXX14_CONSTEXPR basic_string_view&
	operator=(basic_string_view const&) BKSGE_NOEXCEPT = default;

	// [string.view.iterators], iterator support

	BKSGE_CONSTEXPR const_iterator
	begin() const BKSGE_NOEXCEPT
	{
		return this->m_str;
	}

	BKSGE_CONSTEXPR const_iterator
	end() const BKSGE_NOEXCEPT
	{
		return this->m_str + this->m_len;
	}

	BKSGE_CONSTEXPR const_iterator
	cbegin() const BKSGE_NOEXCEPT
	{
		return this->m_str;
	}

	BKSGE_CONSTEXPR const_iterator
	cend() const BKSGE_NOEXCEPT
	{
		return this->m_str + this->m_len;
	}

	BKSGE_CONSTEXPR const_reverse_iterator
	rbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR const_reverse_iterator
	rend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	BKSGE_CONSTEXPR const_reverse_iterator
	crbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR const_reverse_iterator
	crend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	// [string.view.capacity], capacity

	BKSGE_CONSTEXPR size_type
	size() const BKSGE_NOEXCEPT
	{
		return this->m_len;
	}

	BKSGE_CONSTEXPR size_type
	length() const BKSGE_NOEXCEPT
	{
		return m_len;
	}

	BKSGE_CONSTEXPR size_type
	max_size() const BKSGE_NOEXCEPT
	{
		return (npos - sizeof(size_type) - sizeof(void*)) / sizeof(value_type) / 4;
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT
	{
		return this->m_len == 0;
	}

	// [string.view.access], element access

	BKSGE_CONSTEXPR const_reference
	operator[](size_type pos) const BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(pos < this->m_len);
		return *(this->m_str + pos);
	}

	BKSGE_CONSTEXPR const_reference
	at(size_type pos) const
	{
		if (pos >= m_len)
		{
			bksge::throw_out_of_range("basic_string_view::at");
			//__throw_out_of_range_fmt(__N("basic_string_view::at: pos "
			//	"(which is %zu) >= this->size() "
			//	"(which is %zu)"), pos, this->size());
		}

		return *(this->m_str + pos);
	}

	BKSGE_CONSTEXPR const_reference
	front() const BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(this->m_len > 0u);
		return *this->m_str;
	}

	BKSGE_CONSTEXPR const_reference
	back() const BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(this->m_len > 0u);
		return *(this->m_str + this->m_len - 1);
	}

	BKSGE_CONSTEXPR const_pointer
	data() const BKSGE_NOEXCEPT
	{
		return this->m_str;
	}

	// remove_prefix
	BKSGE_CXX14_CONSTEXPR void
	remove_prefix(size_type n) BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(this->m_len >= n);
		this->m_str += n;
		this->m_len -= n;
	}

	// remove_suffix
	BKSGE_CXX14_CONSTEXPR void
	remove_suffix(size_type n) BKSGE_NOEXCEPT
	{
		this->m_len -= n;
	}

	// swap
	BKSGE_CXX14_CONSTEXPR void
	swap(basic_string_view& sv) BKSGE_NOEXCEPT
	{
		auto tmp = *this;
		*this = sv;
		sv = tmp;
	}

	// copy
	BKSGE_CXX14_CONSTEXPR size_type
	copy(CharT* dest, size_type count, size_type pos = 0) const
	{
		//__glibcxx_requires_string_len(dest, count);

		if (pos > size())
		{
			bksge::throw_out_of_range("basic_string_view::copy");
			//__throw_out_of_range_fmt(__N("%s: pos (which is %zu) > size "
			//	"(which is %zu)"), s, pos, size);
		}

		size_type const rlen = bksge::min(count, m_len - pos);
		traits_type::copy(dest, data() + pos, rlen);
		return rlen;
	}

	// substr
	BKSGE_CXX14_CONSTEXPR basic_string_view
	substr(size_type pos = 0, size_type count = npos) const
	{
		if (pos > size())
		{
			bksge::throw_out_of_range("basic_string_view::substr");
			//__throw_out_of_range_fmt(__N("%s: pos (which is %zu) > size "
			//	"(which is %zu)"), s, pos, size);
		}

		size_type const rlen = bksge::min(count, m_len - pos);
		return basic_string_view{m_str + pos, rlen};
	}

	// compare
	BKSGE_CXX14_CONSTEXPR int
	compare(basic_string_view sv) const BKSGE_NOEXCEPT
	{
		size_type const rlen = bksge::min(this->m_len, sv.m_len);
		int ret = traits_type::compare(this->m_str, sv.m_str, rlen);
		if (ret == 0)
		{
			ret = compare_length(this->m_len, sv.m_len);
		}
		return ret;
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type count1, basic_string_view sv) const
	{
		return this->substr(pos1, count1).compare(sv);
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type count1,
		basic_string_view sv, size_type pos2, size_type count2) const
	{
		return this->substr(pos1, count1).compare(sv.substr(pos2, count2));
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(CharT const* s) const BKSGE_NOEXCEPT
	{
		return this->compare(basic_string_view{s});
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type count1, CharT const* s) const
	{
		return this->substr(pos1, count1).compare(basic_string_view{s});
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type count1, CharT const* s, size_type count2) const
	{
		return this->substr(pos1, count1).compare(basic_string_view(s, count2));
	}

	// starts_with
	BKSGE_CXX14_CONSTEXPR bool
	starts_with(basic_string_view sv) const BKSGE_NOEXCEPT
	{
		return this->substr(0, sv.size()) == sv;
	}

	BKSGE_CXX14_CONSTEXPR bool
	starts_with(CharT c) const BKSGE_NOEXCEPT
	{
		return !this->empty() && traits_type::eq(this->front(), c);
	}

	BKSGE_CXX14_CONSTEXPR bool
	starts_with(CharT const* s) const BKSGE_NOEXCEPT
	{
		return this->starts_with(basic_string_view(s));
	}

	// ends_with
	BKSGE_CXX14_CONSTEXPR bool
	ends_with(basic_string_view sv) const BKSGE_NOEXCEPT
	{
		return this->size() >= sv.size() && this->compare(this->size() - sv.size(), npos, sv) == 0;
	}

	BKSGE_CXX14_CONSTEXPR bool
	ends_with(CharT c) const BKSGE_NOEXCEPT
	{
		return !this->empty() && traits_type::eq(this->back(), c);
	}

	BKSGE_CXX14_CONSTEXPR bool
	ends_with(CharT const* s) const BKSGE_NOEXCEPT
	{
		return this->ends_with(basic_string_view(s));
	}

	// contains
	BKSGE_CXX14_CONSTEXPR bool
	contains(basic_string_view sv) const BKSGE_NOEXCEPT
	{
		return find(sv) != npos;
	}

	BKSGE_CXX14_CONSTEXPR bool
	contains(CharT c) const BKSGE_NOEXCEPT
	{
		return find(c) != npos;
	}

	BKSGE_CXX14_CONSTEXPR bool
	contains(CharT const* s) const
	{
		return find(s) != npos;
	}

	// find
	BKSGE_CXX14_CONSTEXPR size_type
	find(basic_string_view sv, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		size_type ret = npos;
		if (pos < this->m_len)
		{
			size_type const n = this->m_len - pos;
			CharT const* p = traits_type::find(this->m_str + pos, n, c);
			if (p)
			{
				ret = p - this->m_str;
			}
		}

		return ret;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		if (n == 0)
		{
			return pos <= this->m_len ? pos : npos;
		}

		if (n <= this->m_len)
		{
			for (; pos <= this->m_len - n; ++pos)
			{
				if (traits_type::eq(this->m_str[pos], s[0]) &&
					traits_type::compare(this->m_str + pos + 1, s + 1, n - 1) == 0)
				{
					return pos;
				}
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find(s, pos, traits_type::length(s));
	}

	// rfind
	BKSGE_CXX14_CONSTEXPR size_type
	rfind(basic_string_view sv, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->rfind(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		size_type len = this->m_len;

		if (len > 0)
		{
			if (--len > pos)
			{
				len = pos;
			}

			for (++len; len-- > 0; )
			{
				if (traits_type::eq(this->m_str[len], c))
				{
					return len;
				}
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		if (n <= this->m_len)
		{
			pos = std::min(size_type(this->m_len - n), pos);
			do
			{
				if (traits_type::compare(this->m_str + pos, s, n) == 0)
				{
					return pos;
				}
			}
			while (pos-- > 0);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->rfind(s, pos, traits_type::length(s));
	}

	// find_first_of
	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(basic_string_view sv, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_of(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find(c, pos);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		for (; n && pos < this->m_len; ++pos)
		{
			CharT const* p = traits_type::find(s, n, this->m_str[pos]);
			if (p)
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_of(s, pos, traits_type::length(s));
	}

	// find_last_of
	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(basic_string_view sv, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_of(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->rfind(c, pos);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		size_type len = this->size();
		if (len && n)
		{
			if (--len > pos)
			{
				len = pos;
			}

			do
			{
				if (traits_type::find(s, n, this->m_str[len]))
				{
					return len;
				}
			}
			while (len-- != 0);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_of(s, pos, traits_type::length(s));
	}

	// find_first_not_of
	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(basic_string_view sv, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_not_of(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		for (; pos < this->m_len; ++pos)
		{
			if (!traits_type::eq(this->m_str[pos], c))
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		for (; pos < this->m_len; ++pos)
		{
			if (!traits_type::find(s, n, this->m_str[pos]))
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_not_of(s, pos, traits_type::length(s));
	}

	// find_last_not_of
	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(basic_string_view sv, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_not_of(sv.m_str, pos, sv.m_len);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		size_type len = this->m_len;
		if (len)
		{
			if (--len > pos)
			{
				len = pos;
			}

			do
			{
				if (!traits_type::eq(this->m_str[len], c))
				{
					return len;
				}
			}
			while (len--);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, n);

		size_type len = this->m_len;
		if (len)
		{
			if (--len > pos)
			{
				len = pos;
			}

			do
			{
				if (!traits_type::find(s, n, this->m_str[len]))
				{
					return len;
				}
			}
			while (len--);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_not_of(s, pos, traits_type::length(s));
	}

private:
	static BKSGE_CXX14_CONSTEXPR int
	compare_length(size_type n1, size_type n2) BKSGE_NOEXCEPT
	{
		using limits = bksge::numeric_limits<int>;
		difference_type const diff = n1 - n2;
		if (diff > limits::max())
		{
			return limits::max();
		}
		if (diff < limits::min())
		{
			return limits::min();
		}
		return static_cast<int>(diff);
	}

	bksge::size_t	m_len;
	CharT const*	m_str;
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <
	BKSGE_REQUIRES_PARAM(bksge::contiguous_iterator, It),
	BKSGE_REQUIRES_PARAM_2(bksge::sized_sentinel_for, It, End)
>
basic_string_view(It, End) -> basic_string_view<bksge::iter_value_t<It>>;

#endif

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
operator<=>(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR auto
operator<=>(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

#else

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator==(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator!=(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator<=(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, int = 1>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(
	basic_string_view<CharT, Traits> lhs,
	bksge::type_identity_t<basic_string_view<CharT, Traits>> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, int = 2>
inline BKSGE_CXX14_CONSTEXPR bool
operator>=(
	bksge::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

#endif // defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits1, typename Traits2>
inline bksge::basic_ostream<CharT, Traits1>&
operator<<(
	bksge::basic_ostream<CharT, Traits1>& os,
	basic_string_view<CharT, Traits2> sv)
{
	return os.write(sv.data(), sv.size());
}

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_STRING_VIEW)

#include <bksge/fnd/functional/config.hpp>

#if !defined(BKSGE_USE_STD_STRING_VIEW) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <typename CharT, typename Traits>
struct hash<bksge::basic_string_view<CharT, Traits>>
{
	BKSGE_CXX14_CONSTEXPR bksge::size_t
	operator()(bksge::basic_string_view<CharT, Traits> const& sv) const BKSGE_NOEXCEPT
	{
		return bksge::murmur_hash_3{}(sv.data(), sv.length());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif	// !defined(BKSGE_USE_STD_STRING_VIEW) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_view.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace ranges
{

template <typename CharT, typename Traits>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge::basic_string_view<CharT, Traits>);

template <typename CharT, typename Traits>
BKSGE_RANGES_SPECIALIZE_ENABLE_VIEW(true, bksge::basic_string_view<CharT, Traits>);

}	// namespace ranges

inline namespace literals
{
inline namespace string_view_literals
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4455);	// literal suffix identifiers that do not start with an underscore are reserved
BKSGE_WARNING_DISABLE_CLANG("-Wuser-defined-literals");
BKSGE_WARNING_DISABLE_GCC("-Wliteral-suffix");

inline BKSGE_CONSTEXPR bksge::basic_string_view<char>
operator""sv(char const* str, bksge::size_t len) BKSGE_NOEXCEPT
{
	return bksge::basic_string_view<char>{str, len};
}

inline BKSGE_CONSTEXPR bksge::basic_string_view<wchar_t>
operator""sv(wchar_t const* str, bksge::size_t len) BKSGE_NOEXCEPT
{
	return bksge::basic_string_view<wchar_t>{str, len};
}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
inline BKSGE_CONSTEXPR bksge::basic_string_view<char8_t>
operator""sv(char8_t const* str, bksge::size_t len) BKSGE_NOEXCEPT
{
	return bksge::basic_string_view<char8_t>{str, len};
}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
inline BKSGE_CONSTEXPR bksge::basic_string_view<char16_t>
operator""sv(char16_t const* str, bksge::size_t len) BKSGE_NOEXCEPT
{
	return bksge::basic_string_view<char16_t>{str, len};
}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
inline BKSGE_CONSTEXPR bksge::basic_string_view<char32_t>
operator""sv(char32_t const* str, bksge::size_t len) BKSGE_NOEXCEPT
{
	return bksge::basic_string_view<char32_t>{str, len};
}
#endif

BKSGE_WARNING_POP();

}	// namespace string_literals
}	// namespace literals

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP
