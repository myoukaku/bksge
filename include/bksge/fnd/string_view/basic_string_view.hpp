/**
 *	@file	basic_string_view.hpp
 *
 *	@brief	basic_string_view クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP
#define BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP

#include <bksge/fnd/config.hpp>

#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<string_view>)
#include <string_view>
#endif

#if defined(__cpp_lib_string_view) && (__cpp_lib_string_view >= 201606)

namespace bksge
{

using std::basic_string_view;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <cstddef>
#include <iosfwd>	// basic_ostream
#include <string>	// char_traits

namespace bksge
{

template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string_view
{
public:
	using traits_type            = Traits;
	using value_type             = CharT;
	using const_pointer          = CharT const*;
	using pointer                = CharT*;
	using const_reference        = CharT const&;
	using reference              = CharT&;
	using const_iterator         = CharT const*;
	using iterator               = const_iterator;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator       = const_reverse_iterator;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;

	BKSGE_STATIC_CONSTEXPR size_type npos = size_type(-1);

    static_assert(bksge::is_trivial<value_type>::value,
		"Character type of basic_string_view must be trivial");
    static_assert((bksge::is_same<CharT, typename traits_type::char_type>::value),
		"traits_type::char_type must be the same type as CharT");

	BKSGE_CONSTEXPR basic_string_view() BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR basic_string_view(basic_string_view const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR basic_string_view(CharT const* str);
	BKSGE_CONSTEXPR basic_string_view(CharT const* str, size_type len) BKSGE_NOEXCEPT;

	basic_string_view& operator=(basic_string_view const&) BKSGE_NOEXCEPT = default;

	BKSGE_CONSTEXPR const_iterator         begin()   const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_iterator         end()     const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_iterator         cbegin()  const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_iterator         cend()    const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_reverse_iterator rbegin()  const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_reverse_iterator rend()    const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_reverse_iterator crend()   const BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR size_type size()     const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type length()   const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type max_size() const BKSGE_NOEXCEPT;
	BKSGE_NODISCARD BKSGE_CONSTEXPR bool empty() const BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR const_reference operator[](size_type pos) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR const_reference at(size_type pos)         const;
	BKSGE_CONSTEXPR const_reference front()                   const;
	BKSGE_CONSTEXPR const_reference back()                    const;
	BKSGE_CONSTEXPR const_pointer   data()                    const BKSGE_NOEXCEPT;

	void remove_prefix(size_type n);
	void remove_suffix(size_type n);

	void swap(basic_string_view& sv) BKSGE_NOEXCEPT;

	size_type copy(CharT* dest, size_type count, size_type pos = 0) const;

	BKSGE_CONSTEXPR basic_string_view substr(size_type pos = 0, size_type count = npos) const;

	BKSGE_CONSTEXPR int compare(basic_string_view str) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR int compare(size_type pos1, size_type count1, basic_string_view str) const;
	BKSGE_CONSTEXPR int compare(size_type pos1, size_type count1, basic_string_view str, size_type pos2, size_type count2) const;
	BKSGE_CONSTEXPR int compare(CharT const* str) const;
	BKSGE_CONSTEXPR int compare(size_type pos1, size_type count1, CharT const* str) const;
	BKSGE_CONSTEXPR int compare(size_type pos1, size_type count1, CharT const* str, size_type count2) const;

	BKSGE_CXX14_CONSTEXPR bool starts_with(basic_string_view sv) const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR bool starts_with(value_type c)         const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR bool starts_with(value_type const* s)  const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR bool ends_with(basic_string_view sv) const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR bool ends_with(value_type c)         const BKSGE_NOEXCEPT;
	BKSGE_CXX14_CONSTEXPR bool ends_with(value_type const* s)  const BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR size_type find(basic_string_view str, size_type pos = 0)         const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find(CharT c, size_type pos = 0)                       const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find(CharT const* str, size_type pos = 0)              const;

	BKSGE_CONSTEXPR size_type rfind(basic_string_view str, size_type pos = npos)      const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type rfind(CharT c, size_type pos = npos)                    const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type rfind(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type rfind(CharT const* str, size_type pos = npos)           const;

	BKSGE_CONSTEXPR size_type find_first_of(basic_string_view str, size_type pos = 0)         const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_of(CharT c, size_type pos = 0)                       const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_of(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_of(CharT const* str, size_type pos = 0)              const;

	BKSGE_CONSTEXPR size_type find_last_of(basic_string_view str, size_type pos = npos)      const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_of(CharT c, size_type pos = npos)                    const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_of(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_of(CharT const* str, size_type pos = npos)           const;

	BKSGE_CONSTEXPR size_type find_first_not_of(basic_string_view str, size_type pos = 0)         const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_not_of(CharT c, size_type pos = 0)                       const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_not_of(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_first_not_of(CharT const* str, size_type pos = 0)              const;

	BKSGE_CONSTEXPR size_type find_last_not_of(basic_string_view str, size_type pos = npos)      const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_not_of(CharT c, size_type pos = npos)                    const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_not_of(CharT const* str, size_type pos, size_type count) const BKSGE_NOEXCEPT;
	BKSGE_CONSTEXPR size_type find_last_not_of(CharT const* str, size_type pos = npos)           const;

private:
	static BKSGE_CONSTEXPR int
	compare_impl(int r, size_type n1, size_type n2) BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	find_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	rfind_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of_impl(basic_string_view str, size_type pos) const BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR bool
	range_check(bool flag) const;

	size_type    m_len;
	CharT const* m_str;
};

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator!=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator< (
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator> (
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator<=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits>
inline BKSGE_CONSTEXPR bool
operator>=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(
	std::basic_ostream<CharT, Traits>& os,
	bksge::basic_string_view<CharT, Traits> const sv);

}	// namespace bksge

#include <bksge/fnd/string_view/inl/basic_string_view_inl.hpp>

#endif

#endif // BKSGE_FND_STRING_VIEW_BASIC_STRING_VIEW_HPP
