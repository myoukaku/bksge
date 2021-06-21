/**
 *	@file	basic_static_string.hpp
 *
 *	@brief	basic_static_string クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_STRING_BASIC_STATIC_STRING_HPP
#define BKSGE_FND_STATIC_STRING_BASIC_STATIC_STRING_HPP

#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/static_vector/static_vector.hpp>
#include <bksge/fnd/string/char_traits.hpp>
#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>
#include <istream>
#include <ostream>

namespace bksge
{

template <typename CharT, bksge::size_t Capacity, typename Traits = bksge::char_traits<CharT>>
class basic_static_string
{
private:
	using storage_t = bksge::static_vector<CharT, Capacity>;

	storage_t	m_vec = {};

private:
	using string_view_type = bksge::basic_string_view<CharT, Traits>;

	template <typename Traits2>
	static BKSGE_CXX14_CONSTEXPR string_view_type
	to_string_view(bksge::basic_string_view<CharT, Traits2> sv) noexcept
	{
		return {sv.data(), sv.size()};
	}

	static BKSGE_CXX14_CONSTEXPR string_view_type
	to_string_view(string_view_type sv) noexcept
	{
		return sv;
	}

	template <typename T>
	using enable_if_sv = decltype(to_string_view(bksge::declval<T>()));

	BKSGE_CXX14_CONSTEXPR void append_null_char()
	{
		m_vec.push_back(CharT{});
		m_vec.pop_back();
	}

public:
	using traits_type            = Traits;
	using value_type             = typename storage_t::value_type;
	using allocator_type         = typename storage_t::allocator_type;
	using size_type              = typename storage_t::size_type;
	using difference_type        = typename storage_t::difference_type;
	using reference              = typename storage_t::reference;
	using const_reference        = typename storage_t::const_reference;
	using pointer                = typename storage_t::pointer;
	using const_pointer          = typename storage_t::const_pointer;
	using iterator               = typename storage_t::iterator;
	using const_iterator         = typename storage_t::const_iterator;
	using reverse_iterator       = typename storage_t::reverse_iterator;
	using const_reverse_iterator = typename storage_t::const_reverse_iterator;

	static size_type const npos = static_cast<size_type>(-1);
	static size_type const static_capacity = Capacity;

public:
	BKSGE_CXX14_CONSTEXPR basic_static_string() BKSGE_NOEXCEPT
	{}

	BKSGE_CXX14_CONSTEXPR basic_static_string(size_type n, CharT ch)
		: m_vec(n, ch)
	{}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string<CharT, N, Traits> const& str, size_type pos)
		: basic_static_string(str.begin() + pos, str.end())
	{}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string<CharT, N, Traits> const& str, size_type pos, size_type n)
		: basic_static_string(str.begin() + pos, bksge::min(n, str.size() - pos))
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_static_string(CharT const* s, size_type n)
		: basic_static_string(s, s + n)
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_static_string(CharT const* s)
		: basic_static_string(s, s + traits_type::length(s))
	{}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(InputIterator first, InputIterator last)
		: m_vec(first, last)
	{}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string<CharT, N, Traits> const& other)
		: basic_static_string(other.begin(), other.end())
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string const& other)
		: basic_static_string(other.begin(), other.end())
	{}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string<CharT, N, Traits>&& other)
		: basic_static_string(other.begin(), other.end())
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_static_string(basic_static_string&& other)
		: basic_static_string(other.begin(), other.end())
	{}

	BKSGE_CXX14_CONSTEXPR
	basic_static_string(std::initializer_list<CharT> il)
		: basic_static_string(il.begin(), il.end())
	{}

	template <typename T, typename = enable_if_sv<T>>
	explicit BKSGE_CXX14_CONSTEXPR
	basic_static_string(T const& t)
		: basic_static_string(to_string_view(t).data(), to_string_view(t).size())
	{}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR
	basic_static_string(T const& t, size_type pos, size_type n)
		: basic_static_string(to_string_view(t).substr(pos, n))
	{}

	//~basic_static_string();

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(basic_static_string const& str)
	{
		return this->assign(str);
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(basic_static_string<CharT, N, Traits> const& str)
	{
		return this->assign(str);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(basic_static_string&& str)
	{
		return this->assign(bksge::move(str));
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(basic_static_string<CharT, N, Traits>&& str)
	{
		return this->assign(bksge::move(str));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(CharT const* s)
	{
		return this->assign(s);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string
	operator=(CharT c)
	{
		return this->assign(size_type{1}, c);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(std::initializer_list<CharT> il)
	{
		return this->assign(il);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator=(T const& t)
	{
		return this->assign(t);
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator+=(basic_static_string<CharT, N, Traits> const& str)
	{
		return this->append(str);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator+=(CharT const* s)
	{
		return this->append(s);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator+=(CharT c)
	{
		return this->append(size_type{1}, c);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator+=(std::initializer_list<CharT> il)
	{
		return this->append(il);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	operator+=(T const& t)
	{
		return this->append(t);
	}

	BKSGE_CONSTEXPR operator string_view_type() const BKSGE_NOEXCEPT
	{
		return {data(), size()};
	}

	BKSGE_CXX14_CONSTEXPR iterator begin() BKSGE_NOEXCEPT
	{
		return m_vec.begin();
	}

	BKSGE_CONSTEXPR const_iterator begin() const BKSGE_NOEXCEPT
	{
		return m_vec.begin();
	}

	BKSGE_CXX14_CONSTEXPR iterator end() BKSGE_NOEXCEPT
	{
		return m_vec.end();
	}

	BKSGE_CONSTEXPR const_iterator end() const BKSGE_NOEXCEPT
	{
		return m_vec.end();
	}

	BKSGE_CXX14_CONSTEXPR reverse_iterator rbegin() BKSGE_NOEXCEPT
	{
		return m_vec.rbegin();
	}

	BKSGE_CONSTEXPR const_reverse_iterator rbegin() const BKSGE_NOEXCEPT
	{
		return m_vec.rbegin();
	}

	BKSGE_CXX14_CONSTEXPR reverse_iterator rend() BKSGE_NOEXCEPT
	{
		return m_vec.rend();
	}

	BKSGE_CONSTEXPR const_reverse_iterator rend() const BKSGE_NOEXCEPT
	{
		return m_vec.rend();
	}

	BKSGE_CONSTEXPR const_iterator cbegin() const BKSGE_NOEXCEPT
	{
		return m_vec.cbegin();
	}

	BKSGE_CONSTEXPR const_iterator cend() const BKSGE_NOEXCEPT
	{
		return m_vec.cend();
	}

	BKSGE_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT
	{
		return m_vec.crbegin();
	}

	BKSGE_CONSTEXPR const_reverse_iterator crend() const BKSGE_NOEXCEPT
	{
		return m_vec.crend();
	}

	BKSGE_CONSTEXPR size_type size() const BKSGE_NOEXCEPT
	{
		return m_vec.size();
	}

	BKSGE_CONSTEXPR size_type length() const BKSGE_NOEXCEPT
	{
		return m_vec.size();
	}

	static BKSGE_CONSTEXPR size_type max_size() BKSGE_NOEXCEPT
	{
		return static_capacity;
	}

	static BKSGE_CONSTEXPR size_type capacity() BKSGE_NOEXCEPT
	{
		return static_capacity;
	}

	BKSGE_CXX14_CONSTEXPR void resize(size_type n, CharT c)
	{
		m_vec.resize(n, c);
		append_null_char();
	}

	BKSGE_CXX14_CONSTEXPR void resize(size_type n)
	{
		this->resize(n, CharT{});
	}

	BKSGE_CXX14_CONSTEXPR void shrink_to_fit() BKSGE_NOEXCEPT
	{
		// do nothing
	}

	BKSGE_CXX14_CONSTEXPR void reserve(size_type) BKSGE_NOEXCEPT
	{
		// do nothing
	}

	BKSGE_CXX14_CONSTEXPR void reserve() BKSGE_NOEXCEPT
	{
		// do nothing
	}

	BKSGE_CXX14_CONSTEXPR void clear() BKSGE_NOEXCEPT
	{
		this->resize(0);
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool empty() const BKSGE_NOEXCEPT
	{
		return m_vec.empty();
	}

	BKSGE_CXX14_CONSTEXPR reference operator[](size_type pos)
	{
		return m_vec[pos];
	}

	BKSGE_CONSTEXPR const_reference operator[] (size_type pos) const BKSGE_NOEXCEPT
	{
		return m_vec[pos];
	}

	BKSGE_CXX14_CONSTEXPR reference at(size_type pos)
	{
		return m_vec.at(pos);
	}

	BKSGE_CONSTEXPR const_reference at(size_type pos) const
	{
		return m_vec.at(pos);
	}

	BKSGE_CXX14_CONSTEXPR reference front() BKSGE_NOEXCEPT
	{
		return m_vec.front();
	}

	BKSGE_CONSTEXPR const_reference front() const BKSGE_NOEXCEPT
	{
		return m_vec.front();
	}

	BKSGE_CXX14_CONSTEXPR reference back() BKSGE_NOEXCEPT
	{
		return m_vec.back();
	}

	BKSGE_CONSTEXPR const_reference back() const BKSGE_NOEXCEPT
	{
		return m_vec.back();
	}

	// append
	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(basic_static_string<CharT, N, Traits> const& str)
	{
		return this->append(str.data(), str.size());
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(basic_static_string<CharT, N, Traits> const& str, size_type pos, size_type n = npos)
	{
		auto const rlen = bksge::min(n, str.size() - pos);
		return this->append(str.data() + pos, rlen);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(CharT const* s, size_type n)
	{
		return this->append(s, s + n);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(CharT const* s)
	{
		return this->append(s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(size_type n, CharT c)
	{
		this->insert(this->end(), n, c);
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(InputIterator first, InputIterator last)
	{
		this->insert(this->end(), first, last);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(std::initializer_list<CharT> il)
	{
		return this->append(il.begin(), il.end());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(T const& t)
	{
		auto sv = to_string_view(t);
		return this->append(sv.data(), sv.size());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	append(T const& t, size_type pos, size_type n = npos)
	{
		auto sv = to_string_view(t);
		return this->append(sv.substr(pos, n));
	}

	// assign
	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(basic_static_string<CharT, N, Traits> const& str)
	{
		return this->assign(str.begin(), str.end());
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(basic_static_string<CharT, N, Traits>&& str)
	{
		return this->assign(str.begin(), str.end());
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(basic_static_string<CharT, N, Traits> const& str, size_type pos, size_type n = npos)
	{
		auto const rlen = bksge::min(n, str.size() - pos);
		return this->assign(str.data() + pos, rlen);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(CharT const* s, size_type n)
	{
		return this->assign(s, s + n);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(CharT const* s)
	{
		return this->assign(s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(size_type n, CharT c)
	{
		m_vec.assign(n, c);
		append_null_char();
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(InputIterator first, InputIterator last)
	{
		m_vec.assign(first, last);
		append_null_char();
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(std::initializer_list<CharT> il)
	{
		return this->assign(il.begin(), il.end());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(T const& t)
	{
		auto sv = to_string_view(t);
		return this->assign(sv.data(), sv.size());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	assign(T const& t, size_type pos, size_type n = npos)
	{
		auto sv = to_string_view(t);
		return this->assign(sv.substr(pos, n));
	}

	// insert
	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos1, basic_static_string<CharT, N, Traits> const& str)
	{
		return this->insert(pos1, str.data(), str.size());
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos1, basic_static_string<CharT, N, Traits> const& str,
		   size_type pos2, size_type n = npos)
	{
		auto const rlen = bksge::min(n, str.size() - pos2);
		return this->insert(pos1, str.data() + pos2, rlen);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos, CharT const* s, size_type n)
	{
		this->insert(begin() + pos, s, s + n);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos, CharT const* s)
	{
		return this->insert(pos, s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos, size_type n, CharT c)
	{
		this->insert(begin() + pos, n, c);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator p, CharT c)
	{
		return this->insert(p, size_type{1}, c);
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator p, size_type n, CharT c)
	{
		auto it = m_vec.insert(p, n, c);
		append_null_char();
		return it;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator p, InputIterator first, InputIterator last)
	{
		auto it = m_vec.insert(p, first, last);
		append_null_char();
		return it;
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator p, std::initializer_list<CharT> il)
	{
		return this->insert(p, il.begin(), il.end());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos, T const& t)
	{
		auto sv = to_string_view(t);
		return this->insert(pos, sv.data(), sv.size());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	insert(size_type pos1, T const& t, size_type pos2, size_type n = npos)
	{
		auto sv = to_string_view(t);
		return this->insert(pos1, sv.substr(pos2, n));
	}

	// erase
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	erase(size_type pos = 0, size_type n = npos)
	{
		auto const xlen = bksge::min(n, size() - pos);
		this->erase(begin() + pos, begin() + pos + xlen);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR iterator
	erase(const_iterator pos)
	{
		auto it = m_vec.erase(pos);
		append_null_char();
		return it;
	}

	BKSGE_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		auto it = m_vec.erase(first, last);
		append_null_char();
		return it;
	}

	// push_back, pop_back
	BKSGE_CXX14_CONSTEXPR void
	push_back(CharT c)
	{
		this->append(size_type{1}, c);
	}

	BKSGE_CXX14_CONSTEXPR void
	pop_back() BKSGE_NOEXCEPT
	{
		this->erase(size() - 1, 1);
	}

	// replace
	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos, size_type n, basic_static_string<CharT, N, Traits> const& str)
	{
		return this->replace(pos, n, str.data(), str.size());
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos1, size_type n1, basic_static_string<CharT, N, Traits> const& str,
			size_type pos2, size_type n2 = npos)
	{
		auto const rlen = bksge::min(n2, str.size() - pos2);
		return this->replace(pos1, n1, str.data() + pos2, rlen);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos, size_type n1, CharT const* s, size_type n2)
	{
		this->erase(pos, n1);
		this->insert(pos, s, n2);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos, size_type n1, CharT const* s)
	{
		return this->replace(pos, n1, s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos, size_type n1, size_type n2, CharT c)
	{
		this->erase(pos, n1);
		this->insert(pos, n2, c);
		return *this;
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, basic_static_string<CharT, N, Traits> const& str)
	{
		return this->replace(i1, i2, str.begin(), str.end());
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, CharT const* s, size_type n)
	{
		return this->replace(i1, i2, s, s + n);
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, CharT const* s)
	{
		return this->replace(i1, i2, s, s + traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, size_type n, CharT c)
	{
		this->erase(i1, i2);
		this->insert(i1, n, c);
		return *this;
	}

	template <BKSGE_REQUIRES_PARAM(bksge::input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, InputIterator k1, InputIterator k2)
	{
		this->erase(i1, i2);
		this->insert(i1, k1, k2);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, std::initializer_list<CharT> il)
	{
		return this->replace(i1, i2, il.begin(), il.end());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos, size_type n, T const& t)
	{
		auto sv = to_string_view(t);
		return this->replace(pos, n, sv.data(), sv.size());
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos)
	{
		auto sv = to_string_view(t);
		return this->replace(pos1, n1, sv.substr(pos2, n2));
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR basic_static_string&
	replace(const_iterator i1, const_iterator i2, T const& t)
	{
		auto sv = to_string_view(t);
		return this->replace(i1, i2, sv.data(), sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	copy(CharT* s, size_type n, size_type pos = 0) const
	{
		auto const rlen = bksge::min(n, size() - pos);
		traits_type::copy(s, data() + pos, rlen);
		return rlen;
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR void
	swap(basic_static_string<CharT, N, Traits>& s)
	{
		auto tmp = bksge::move(s);
		s = bksge::move(*this);
		*this = bksge::move(tmp);
	}

	BKSGE_CONSTEXPR CharT const* c_str() const BKSGE_NOEXCEPT
	{
		return m_vec.data();
	}

	BKSGE_CONSTEXPR CharT const* data() const BKSGE_NOEXCEPT
	{
		return m_vec.data();
	}

	BKSGE_CXX14_CONSTEXPR CharT* data() BKSGE_NOEXCEPT
	{
		return m_vec.data();
	}

//	BKSGE_CONSTEXPR allocator_type get_allocator() const BKSGE_NOEXCEPT;

	// find
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	find(basic_static_string<CharT, N, Traits> const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	find(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	find(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	find(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	find(T const& t, size_type pos = 0) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).find(to_string_view(t), pos);
	}

	// rfind
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	rfind(basic_static_string<CharT, N, Traits> const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).rfind(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).rfind(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).rfind(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	rfind(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).rfind(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	rfind(T const& t, size_type pos = npos) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).rfind(to_string_view(t), pos);
	}

	// find_first_of
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	find_first_of(basic_static_string<CharT, N, Traits> const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_of(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_of(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_of(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	find_first_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_of(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	find_first_of(T const& t, size_type pos = 0) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).find_first_of(to_string_view(t), pos);
	}

	// find_last_of
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	find_last_of(basic_static_string<CharT, N, Traits> const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_of(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_of(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_of(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	find_last_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_of(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	find_last_of(T const& t, size_type pos = npos) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).find_last_of(to_string_view(t), pos);
	}

	// find_first_not_of
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	find_first_not_of(basic_static_string<CharT, N, Traits> const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_not_of(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_not_of(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_not_of(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	find_first_not_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_first_not_of(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	find_first_not_of(T const& t, size_type pos = 0) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).find_first_not_of(to_string_view(t), pos);
	}

	// find_last_not_of
	template <bksge::size_t N>
	BKSGE_CONSTEXPR size_type
	find_last_not_of(basic_static_string<CharT, N, Traits> const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_not_of(to_string_view(str), pos);
	}

	BKSGE_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos, size_type n) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_not_of(s, pos, n);
	}

	BKSGE_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_not_of(s, pos);
	}

	BKSGE_CONSTEXPR size_type
	find_last_not_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).find_last_not_of(c, pos);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CONSTEXPR size_type
	find_last_not_of(T const& t, size_type pos = npos) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).find_last_not_of(to_string_view(t), pos);
	}

	// substr
	BKSGE_CONSTEXPR basic_static_string
	substr(size_type pos = 0, size_type n = npos) const
	{
		return basic_static_string(*this, pos, n);
	}

	// compare
	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR int
	compare(basic_static_string<CharT, N, Traits> const& str) const
	{
		return to_string_view(*this).compare(to_string_view(str));
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type n, basic_static_string<CharT, N, Traits> const& str) const
	{
		return to_string_view(*this).compare(pos, n, to_string_view(str));
	}

	template <bksge::size_t N>
	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type n1, basic_static_string<CharT, N, Traits> const& str,
		    size_type pos2, size_type n2 = npos) const
	{
		return to_string_view(*this).compare(pos1, n1, to_string_view(str), pos2, n2);
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(CharT const* s) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).compare(s);
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type n, CharT const* s) const
	{
		return to_string_view(*this).compare(pos, n, s);
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type n1, CharT const* s, size_type n2) const
	{
		return to_string_view(*this).compare(pos, n1, s, n2);
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR int
	compare(T const& t) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).compare(to_string_view(t));
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type n, T const& t) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).compare(pos, n, to_string_view(t));
	}

	template <typename T, typename = enable_if_sv<T>>
	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos1, size_type n1, T const& t,
			size_type pos2, size_type n2 = npos) const
		BKSGE_NOEXCEPT_IF((bksge::is_same<T, string_view_type>::value))
	{
		return to_string_view(*this).compare(pos1, n1, to_string_view(t), pos2, n2);
	}

	// starts_with
	template <typename Traits2>
	BKSGE_CONSTEXPR bool
	starts_with(basic_string_view<CharT, Traits2> x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).starts_with(to_string_view(x));
	}

	BKSGE_CONSTEXPR bool
	starts_with(CharT x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).starts_with(x);
	}

	BKSGE_CONSTEXPR bool
	starts_with(CharT const* x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).starts_with(x);
	}

	// ends_with
	template <typename Traits2>
	BKSGE_CONSTEXPR bool
	ends_with(basic_string_view<CharT, Traits2> x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).ends_with(to_string_view(x));
	}

	BKSGE_CONSTEXPR bool
	ends_with(CharT x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).ends_with(x);
	}

	BKSGE_CONSTEXPR bool
	ends_with(CharT const* x) const BKSGE_NOEXCEPT
	{
		return to_string_view(*this).ends_with(x);
	}
};

// operator+

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CXX14_CONSTEXPR basic_static_string<CharT, N1, Traits>
operator+(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs)
{
	basic_static_string<CharT, N1, Traits> str(lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CXX14_CONSTEXPR basic_static_string<CharT, Capacity, Traits>
operator+(basic_static_string<CharT, Capacity, Traits> const& lhs, CharT const* rhs)
{
	basic_static_string<CharT, Capacity, Traits> str(lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CXX14_CONSTEXPR basic_static_string<CharT, Capacity, Traits>
operator+(basic_static_string<CharT, Capacity, Traits> const& lhs, CharT rhs)
{
	basic_static_string<CharT, Capacity, Traits> str(lhs);
	str.push_back(rhs);
	return str;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CXX14_CONSTEXPR basic_static_string<CharT, Capacity, Traits>
operator+(CharT const* lhs, basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	basic_static_string<CharT, Capacity, Traits> str(lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CXX14_CONSTEXPR basic_static_string<CharT, Capacity, Traits>
operator+(CharT lhs, basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	using string_type = basic_static_string<CharT, Capacity, Traits>;
	using size_type = typename string_type::size_type;
	basic_static_string<CharT, Capacity, Traits> str(size_type{1}, lhs);
	str.append(rhs);
	return str;
}

// operator==

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator==(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) == 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator==(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) == 0;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR auto
operator<=>(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR auto
operator<=>(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

#else

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator==(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return rhs.compare(lhs) == 0;
}

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator!=(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator!=(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return !(lhs == rhs);
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator!=(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return !(lhs == rhs);
}

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator<(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator<(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator<(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return rhs.compare(lhs) > 0;
}

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator>(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator>(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator>(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return rhs.compare(lhs) < 0;
}

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator<=(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator<=(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator<=(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return rhs.compare(lhs) >= 0;
}

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CONSTEXPR bool operator>=(
	basic_static_string<CharT, N1, Traits> const& lhs,
	basic_static_string<CharT, N2, Traits> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator>=(
	basic_static_string<CharT, Capacity, Traits> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, bksge::size_t Capacity, typename Traits>
inline BKSGE_CONSTEXPR bool operator>=(
	CharT const* lhs,
	basic_static_string<CharT, Capacity, Traits> const& rhs)
{
	return rhs.compare(lhs) <= 0;
}

#endif // defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, bksge::size_t N1, bksge::size_t N2, typename Traits>
inline BKSGE_CXX14_CONSTEXPR void swap(
	basic_static_string<CharT, N1, Traits>& lhs,
	basic_static_string<CharT, N2, Traits>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename CharT, typename Traits1, bksge::size_t Capacity, typename Traits2>
inline std::basic_istream<CharT, Traits1>&
operator>>(std::basic_istream<CharT, Traits1>& is,
	basic_static_string<CharT, Capacity, Traits2>& str)
{
	// いったん string で受け取る
	// TODO 最適化
	bksge::basic_string<CharT> tmp;
	is >> tmp;
	str = tmp.c_str();
	return is;
}

template <typename CharT, typename Traits1, bksge::size_t Capacity, typename Traits2>
inline std::basic_ostream<CharT, Traits1>&
operator<<(std::basic_ostream<CharT, Traits1>& os,
	basic_static_string<CharT, Capacity, Traits2> const& str)
{
	return os.write(str.data(), str.size());
}

}	// namespace bksge

#endif // BKSGE_FND_STATIC_STRING_BASIC_STATIC_STRING_HPP
