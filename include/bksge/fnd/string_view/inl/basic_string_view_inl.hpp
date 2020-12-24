/**
 *	@file	basic_string_view_inl.hpp
 *
 *	@brief	basic_string_view クラステンプレートの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_INL_BASIC_STRING_VIEW_INL_HPP
#define BKSGE_FND_STRING_VIEW_INL_BASIC_STRING_VIEW_INL_HPP

#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR
basic_string_view<CharT, Traits>::basic_string_view() BKSGE_NOEXCEPT
	: m_len{ 0 }
	, m_str{ nullptr }
{}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR
basic_string_view<CharT, Traits>::basic_string_view(CharT const* str)
	: m_len{ str == nullptr ? 0 : traits_type::length(str) }
	, m_str{ str }
{}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR
basic_string_view<CharT, Traits>::basic_string_view(
	CharT const* str,
	size_type len) BKSGE_NOEXCEPT
	: m_len{ len }
	, m_str{ str }
{}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::begin() const BKSGE_NOEXCEPT
-> const_iterator
{
	return m_str;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::end() const BKSGE_NOEXCEPT
-> const_iterator
{
	return m_str + size();
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::cbegin() const BKSGE_NOEXCEPT
-> const_iterator
{
	return begin();
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::cend() const BKSGE_NOEXCEPT
-> const_iterator
{
	return end();
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rbegin() const BKSGE_NOEXCEPT
-> const_reverse_iterator
{
	return const_reverse_iterator(end());
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rend() const BKSGE_NOEXCEPT
-> const_reverse_iterator
{
	return const_reverse_iterator(begin());
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::crbegin() const BKSGE_NOEXCEPT
-> const_reverse_iterator
{
	return rbegin();
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::crend() const BKSGE_NOEXCEPT
-> const_reverse_iterator
{
	return rend();
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::size() const BKSGE_NOEXCEPT
-> size_type
{
	return m_len;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::length() const BKSGE_NOEXCEPT
-> size_type
{
	return m_len;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::max_size() const BKSGE_NOEXCEPT
-> size_type
{
	return (npos - sizeof(size_type) - sizeof(void*))
		/ sizeof(value_type) / 4;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
basic_string_view<CharT, Traits>::empty() const BKSGE_NOEXCEPT
{
	return size() == 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::operator[](
	size_type pos) const BKSGE_NOEXCEPT
-> const_reference
{
	return BKSGE_ASSERT(pos < size()), m_str[pos];
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::at(size_type pos) const
-> const_reference
{
	return range_check(pos < size()), m_str[pos];
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::front() const
-> const_reference
{
	return BKSGE_ASSERT(size() > 0u), *m_str;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::back() const
-> const_reference
{
	return BKSGE_ASSERT(size() > 0u), *(m_str + size() - 1);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::data() const BKSGE_NOEXCEPT
-> const_pointer
{
	return m_str;
}

template <typename CharT, typename Traits>
inline void
basic_string_view<CharT, Traits>::remove_prefix(size_type n)
{
	BKSGE_ASSERT(size() >= n);
	m_str += n;
	m_len -= n;
}

template <typename CharT, typename Traits>
inline void
basic_string_view<CharT, Traits>::remove_suffix(size_type n)
{
	m_len -= n;
}

template <typename CharT, typename Traits>
inline void
basic_string_view<CharT, Traits>::swap(
	basic_string_view& sv) BKSGE_NOEXCEPT
{
	bksge::swap(m_len, sv.m_len);
	bksge::swap(m_str, sv.m_str);
}

template <typename CharT, typename Traits>
inline auto
basic_string_view<CharT, Traits>::copy(
	CharT* dest,
	size_type count,
	size_type pos) const
-> size_type
{
	range_check(pos <= size());

	size_type const rcount = bksge::min(count, size() - pos);

	for (auto first = data() + pos, last = first + rcount;
		first != last;)
	{
		*dest++ = *first++;
	}

	return rcount;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::substr(
	size_type pos,
	size_type count) const
-> basic_string_view
{
	return range_check(pos <= size()),
		basic_string_view {
			data() + pos, bksge::min(count, size() - pos)
		};
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	basic_string_view str) const BKSGE_NOEXCEPT
{
	return compare_impl(
		traits_type::compare(
			data(),
			str.data(),
			bksge::min(size(),
				str.size())),
		size(),
		str.size());
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	size_type pos1,
	size_type count1,
	basic_string_view str) const
{
	return substr(pos1, count1).compare(str);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	size_type pos1,
	size_type count1,
	basic_string_view str,
	size_type pos2,
	size_type count2) const
{
	return substr(pos1, count1).compare(str.substr(pos2, count2));
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	CharT const* str) const
{
	return compare(basic_string_view{ str });
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	size_type pos1,
	size_type count1,
	CharT const* str) const
{
	return substr(pos1, count1).compare(basic_string_view{ str });
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare(
	size_type pos1,
	size_type count1,
	CharT const* str,
	size_type count2) const
{
	return substr(pos1, count1).compare(basic_string_view(str, count2));
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::starts_with(
	basic_string_view sv) const BKSGE_NOEXCEPT
{
	return size() >= sv.size() && compare(0, sv.size(), sv) == 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::starts_with(
	value_type c) const BKSGE_NOEXCEPT
{
	return !empty() && Traits::eq(front(), c);
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::starts_with(
	value_type const* s) const BKSGE_NOEXCEPT
{
	return starts_with(basic_string_view(s));
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::ends_with(
	basic_string_view sv) const BKSGE_NOEXCEPT
{
	return size() >= sv.size() && compare(size() - sv.size(), npos, sv) == 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::ends_with(
	value_type c) const BKSGE_NOEXCEPT
{
	return !empty() && Traits::eq(back(), c);
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR bool
basic_string_view<CharT, Traits>::ends_with(
	value_type const* s) const BKSGE_NOEXCEPT
{
	return ends_with(basic_string_view(s));
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return find(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return find(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rfind(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return rfind_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rfind(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return rfind(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rfind(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return rfind(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::rfind(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return rfind(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_of(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_of_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_of(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_of(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_of(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_of(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_of(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return find_first_of(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_of(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_of_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_of(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_of(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_of(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_of(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_of(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return find_last_of(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_not_of(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_not_of_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_not_of(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_not_of(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_not_of(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return find_first_not_of(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_not_of(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return find_first_not_of(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_not_of(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_not_of_impl(str, pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_not_of(
	CharT c,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_not_of(basic_string_view(&c, 1), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_not_of(
	CharT const* str,
	size_type pos,
	size_type count) const BKSGE_NOEXCEPT
-> size_type
{
	return find_last_not_of(basic_string_view(str, count), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_not_of(
	CharT const* str,
	size_type pos) const
-> size_type
{
	return find_last_not_of(basic_string_view(str), pos);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR int
basic_string_view<CharT, Traits>::compare_impl(
	int r,
	size_type n1,
	size_type n2) BKSGE_NOEXCEPT
{
	return
		r == 0 ?
			n1 < n2 ? -1 :
			n1 > n2 ?  1 :
				        0 :
		r;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	if (str.size() == 0)
	{
		return pos <= size() ? pos : npos;
	}

	if (str.size() <= size())
	{
		for (; pos <= size() - str.size(); ++pos)
		{
			if (traits_type::eq(data()[pos], str[0]) &&
				traits_type::compare(
					data() + pos + 1,
					str.data() + 1,
					str.size() - 1) == 0)
			{
				return pos;
			}
		}
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::rfind_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	if (str.size() <= size())
	{
		pos = bksge::min(size() - str.size(), pos);

		do
		{
			if (traits_type::compare(
					data() + pos,
					str.data(),
					str.size()) == 0)
			{
				return pos;
			}
		}
		while (pos-- > 0);
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_of_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	for (; str.size() && pos < size(); ++pos)
	{
		if (traits_type::find(str.data(), str.size(), data()[pos]))
		{
			return pos;
		}
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_of_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	size_type i = size();

	if (i != 0 && str.size() != 0)
	{
		if (--i > pos)
		{
			i = pos;
		}

		do
		{
			if (traits_type::find(str.data(), str.size(), data()[i]))
			{
				return i;
			}
		}
		while (i-- != 0);
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_first_not_of_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	for (; pos < size(); ++pos)
	{
		if (!traits_type::find(str.data(), str.size(), data()[pos]))
		{
			return pos;
		}
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CXX14_CONSTEXPR auto
basic_string_view<CharT, Traits>::find_last_not_of_impl(
	basic_string_view str,
	size_type pos) const BKSGE_NOEXCEPT
-> size_type
{
	size_type i = size();
		
	if (i != 0)
	{
		if (--i > pos)
		{
			i = pos;
		}

		do
		{
			if (!traits_type::find(str.data(), str.size(), data()[i]))
			{
				return i;
			}
		}
		while (i-- != 0);
	}

	return npos;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
basic_string_view<CharT, Traits>::range_check(bool flag) const
{
	return flag ?
		true :
		(bksge::throw_out_of_range("basic_string_view index out of bounds"), false);
}

template <typename CharT, typename Traits1, typename Traits2>
inline bksge::basic_ostream<CharT, Traits1>&
operator<<(
	bksge::basic_ostream<CharT, Traits1>& os,
	bksge::basic_string_view<CharT, Traits2> const sv)
{
	return os.write(sv.data(), sv.size());
}

}	// namespace bksge

#endif // BKSGE_FND_STRING_VIEW_INL_BASIC_STRING_VIEW_INL_HPP
