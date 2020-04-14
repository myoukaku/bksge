/**
 *	@file	span.hpp
 *
 *	@brief	span の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_SPAN_HPP
#define BKSGE_FND_SPAN_SPAN_HPP

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/span/detail/is_span_compatible_container.hpp>

#include <bksge/fnd/iterator/data.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/size.hpp>
//#include <bksge/fnd/iterator/wrap_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <array>
#include <cstddef>
#include <iterator>

#if BKSGE_CXX_STANDARD >= 14
#  define BKSGE_CXX11_CONSTEXPR_IF_NODEBUG constexpr
#else
#  define BKSGE_CXX11_CONSTEXPR_IF_NODEBUG
#endif

namespace bksge
{

template <typename T, std::size_t Extent>
class span
{
public:
	//  constants and types
	using element_type           = T;
	using value_type             = bksge::remove_cv_t<T>;
	using index_type             = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = T&;
	using const_reference        = T const&;
	using iterator               = pointer;//bksge::wrap_iterator<pointer>;
	using const_iterator         = const_pointer;//bksge::wrap_iterator<const_pointer>;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	BKSGE_STATIC_CONSTEXPR index_type extent = Extent;

	// [span.cons], span constructors, copy, assignment, and destructor
	BKSGE_CONSTEXPR
	span() BKSGE_NOEXCEPT
		: m_data{nullptr}
	{
		static_assert(Extent == 0,
			"Can't default construct a statically sized span with size > 0");
	}

	BKSGE_CONSTEXPR span(span const&) BKSGE_NOEXCEPT = default;
	BKSGE_CXX14_CONSTEXPR span& operator=(span const&) BKSGE_NOEXCEPT = default;

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4100);	// 引数は関数の本体部で 1 度も参照されません。
BKSGE_WARNING_DISABLE_CLANG("-Wunused-parameter");

	BKSGE_CXX11_CONSTEXPR_IF_NODEBUG
	span(pointer ptr, index_type count)
		: m_data{ptr}
	{
		//(void)count;
		BKSGE_ASSERT_MSG(Extent == count,
			"size mismatch in span's constructor (ptr, len)");
	}

	BKSGE_CXX11_CONSTEXPR_IF_NODEBUG
	span(pointer f, pointer l)
		: m_data{f}
	{
		//(void)l;
		BKSGE_ASSERT_MSG(Extent == static_cast<std::size_t>(bksge::distance(f, l)),
			"size mismatch in span's constructor (ptr, ptr)");
	}

BKSGE_WARNING_POP();

	BKSGE_CONSTEXPR
	span(element_type (&arr)[Extent]) BKSGE_NOEXCEPT
		: m_data{arr}
	{}

	BKSGE_CONSTEXPR
	span(std::array<value_type, Extent>& arr) BKSGE_NOEXCEPT
		: m_data{arr.data()}
	{}

	BKSGE_CONSTEXPR
	span(std::array<value_type, Extent> const& arr) BKSGE_NOEXCEPT
		: m_data{arr.data()}
	{}

	template <
		typename OtherElementType,
		std::size_t OtherExtent,
		typename = bksge::enable_if_t<
			(OtherExtent == Extent || OtherExtent == bksge::dynamic_extent) &&
			bksge::is_convertible<OtherElementType(*)[], element_type (*)[]>::value
		>
	>
	BKSGE_CXX11_CONSTEXPR_IF_NODEBUG
	span(span<OtherElementType, OtherExtent> const& other) BKSGE_NOEXCEPT
		: m_data{other.data()}
	{
		BKSGE_ASSERT_MSG(OtherExtent == Extent || other.size() == Extent,
			"size mismatch in span's constructor (other span)");
	}

//  ~span() noexcept = default;

	template <std::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	first() const BKSGE_NOEXCEPT
	{
		static_assert(Count <= Extent, "Count out of range in span::first()");
		return {data(), Count};
	}

	template <std::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	last() const BKSGE_NOEXCEPT
	{
		static_assert(Count <= Extent, "Count out of range in span::last()");
		return {data() + size() - Count, Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	first(index_type count) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(count <= size(), "Count out of range in span::first(count)"),
			span<element_type, bksge::dynamic_extent>{data(), count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	last(index_type count) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(count <= size(), "Count out of range in span::last(count)"),
			span<element_type, bksge::dynamic_extent>{data() + size() - count, count};
	}

	template <std::size_t Offset, std::size_t Count = bksge::dynamic_extent>
	BKSGE_CONSTEXPR auto
	subspan() const BKSGE_NOEXCEPT
	-> span<element_type, ((Count != bksge::dynamic_extent) ? Count : (Extent - Offset))>
	{
		static_assert(Offset <= Extent, "Offset out of range in span::subspan()");
		return {data() + Offset, Count == bksge::dynamic_extent ? size() - Offset : Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	subspan(index_type offset, index_type count = bksge::dynamic_extent) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(offset <= size(),
				"Offset out of range in span::subspan(offset, count)"),
			BKSGE_ASSERT_MSG(count == bksge::dynamic_extent || count  <= size(),
				"Count out of range in span::subspan(offset, count)"),
			BKSGE_ASSERT_MSG(count == bksge::dynamic_extent || offset <= size() - count,
				"count + offset out of range in span::subspan(offset, count)"),
			span<element_type, bksge::dynamic_extent>
			{
				data() + offset,
				count == bksge::dynamic_extent ? size() - offset : count
			};
	}

	BKSGE_CONSTEXPR index_type size()       const BKSGE_NOEXCEPT { return Extent; }
	BKSGE_CONSTEXPR index_type size_bytes() const BKSGE_NOEXCEPT { return Extent * sizeof(element_type); }
	BKSGE_CONSTEXPR bool empty()            const BKSGE_NOEXCEPT { return Extent == 0; }

	BKSGE_CONSTEXPR reference
	operator[](index_type idx) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(idx >= 0u && idx < size(), "span<T,N>[] index out of bounds"),
			m_data[idx];
	}

	BKSGE_CONSTEXPR reference
	front() const BKSGE_NOEXCEPT
	{
		static_assert(Extent > 0, "span<T,N>[].front() on empty span");
		return m_data[0];
	}

	BKSGE_CONSTEXPR reference
	back() const BKSGE_NOEXCEPT
	{
		static_assert(Extent > 0, "span<T,N>[].back() on empty span");
		return m_data[size()-1];
	}

	BKSGE_CONSTEXPR pointer data()                   const BKSGE_NOEXCEPT { return m_data; }

	// [span.iter], span iterator support
	BKSGE_CONSTEXPR iterator                 begin() const BKSGE_NOEXCEPT { return iterator(data()); }
	BKSGE_CONSTEXPR iterator                   end() const BKSGE_NOEXCEPT { return iterator(data() + size()); }
	BKSGE_CONSTEXPR const_iterator          cbegin() const BKSGE_NOEXCEPT { return const_iterator(data()); }
	BKSGE_CONSTEXPR const_iterator            cend() const BKSGE_NOEXCEPT { return const_iterator(data() + size()); }
	BKSGE_CXX17_CONSTEXPR reverse_iterator        rbegin() const BKSGE_NOEXCEPT { return reverse_iterator(end()); }
	BKSGE_CXX17_CONSTEXPR reverse_iterator          rend() const BKSGE_NOEXCEPT { return reverse_iterator(begin()); }
	BKSGE_CXX17_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT { return const_reverse_iterator(cend()); }
	BKSGE_CXX17_CONSTEXPR const_reverse_iterator   crend() const BKSGE_NOEXCEPT { return const_reverse_iterator(cbegin()); }

	BKSGE_CXX14_CONSTEXPR void swap(span& other) BKSGE_NOEXCEPT
	{
		pointer p = m_data;
		m_data = other.m_data;
		other.m_data = p;
	}

private:
	pointer    m_data;
};


template <typename T>
class span<T, bksge::dynamic_extent>
{
public:
	//  constants and types
	using element_type           = T;
	using value_type             = bksge::remove_cv_t<T>;
	using index_type             = std::size_t;
	using difference_type        = std::ptrdiff_t;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = T&;
	using const_reference        = T const&;
	using iterator               = pointer;//bksge::wrap_iterator<pointer>;
	using const_iterator         = const_pointer;//bksge::wrap_iterator<const_pointer>;
	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	BKSGE_STATIC_CONSTEXPR index_type extent = bksge::dynamic_extent;

	// [span.cons], span constructors, copy, assignment, and destructor
	BKSGE_CONSTEXPR
	span() BKSGE_NOEXCEPT
		: m_data{nullptr}
		, m_size{0}
	{}

	BKSGE_CONSTEXPR span(span const&) BKSGE_NOEXCEPT = default;
	BKSGE_CXX14_CONSTEXPR span& operator=(span const&) BKSGE_NOEXCEPT = default;

	BKSGE_CONSTEXPR
	span(pointer ptr, index_type count)
		: m_data{ptr}
		, m_size{count}
	{}

	BKSGE_CONSTEXPR
	span(pointer f, pointer l)
		: m_data{f}
		, m_size{static_cast<std::size_t>(bksge::distance(f, l))}
	{}

	template <std::size_t N>
	BKSGE_CONSTEXPR
	span(element_type (&arr)[N]) BKSGE_NOEXCEPT
		: m_data{arr}
		, m_size{N}
	{}

	template <std::size_t N>
	BKSGE_CONSTEXPR
	span(std::array<value_type, N>& arr) BKSGE_NOEXCEPT
		: m_data{arr.data()}
		, m_size{N}
	{}

	template <std::size_t N>
	BKSGE_CONSTEXPR
	span(std::array<value_type, N> const& arr) BKSGE_NOEXCEPT
		: m_data{arr.data()}
		, m_size{N}
	{}

	template <
		typename Container,
		typename = bksge::enable_if_t<
			span_detail::is_span_compatible_container<Container, T>::value
		>
	>
	BKSGE_CONSTEXPR
	span(Container& c)
		: m_data{bksge::data(c)}
		, m_size{static_cast<index_type>(bksge::size(c))}
	{}

	template <
		typename Container,
		typename = bksge::enable_if_t<
			span_detail::is_span_compatible_container<Container const, T>::value
		>
	>
	BKSGE_CONSTEXPR
	span(Container const& c)
		: m_data{bksge::data(c)}
		, m_size{static_cast<index_type>(bksge::size(c))}
	{}

	template <
		typename OtherElementType,
		std::size_t OtherExtent,
		typename = bksge::enable_if_t<
			bksge::is_convertible<OtherElementType(*)[], element_type (*)[]>::value
		>
	>
	BKSGE_CONSTEXPR
	span(span<OtherElementType, OtherExtent> const& other) BKSGE_NOEXCEPT
		: m_data{other.data()}
		, m_size{other.size()}
	{}

//	~span() noexcept = default;

	template <std::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	first() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(Count <= size(), "Count out of range in span::first()"),
			span<element_type, Count>{data(), Count};
	}

	template <std::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	last() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(Count <= size(), "Count out of range in span::last()"),
			span<element_type, Count>{data() + size() - Count, Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	first(index_type count) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(count <= size(), "Count out of range in span::first(count)"),
			span<element_type, bksge::dynamic_extent>{data(), count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	last (index_type count) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(count <= size(), "Count out of range in span::last(count)"),
			span<element_type, bksge::dynamic_extent>{data() + size() - count, count};
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// '+': 整数定数がオーバーフローしました。

	template <std::size_t Offset, std::size_t Count = bksge::dynamic_extent>
	BKSGE_CONSTEXPR span<T, bksge::dynamic_extent>
	subspan() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(Offset <= size(),
				"Offset out of range in span::subspan()"),
			BKSGE_ASSERT_MSG(Count == bksge::dynamic_extent || Offset + Count <= size(),
				"Count out of range in span::subspan()"),
			span<T, bksge::dynamic_extent>
			{
				data() + Offset,
				Count == bksge::dynamic_extent ? size() - Offset : Count
			};
	}

BKSGE_WARNING_POP();

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	subspan(index_type offset, index_type count = bksge::dynamic_extent) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(offset <= size(),
				"Offset out of range in span::subspan(offset, count)"),
			BKSGE_ASSERT_MSG(count == bksge::dynamic_extent || count  <= size(),
				"count out of range in span::subspan(offset, count)"),
			BKSGE_ASSERT_MSG(count == bksge::dynamic_extent || offset <= size() - count,
				"Offset + count out of range in span::subspan(offset, count)"),
			span<element_type, bksge::dynamic_extent>
			{
				data() + offset,
				((count == bksge::dynamic_extent) ? (size() - offset) : count)
			};
	}

	BKSGE_CONSTEXPR index_type size()       const BKSGE_NOEXCEPT { return m_size; }
	BKSGE_CONSTEXPR index_type size_bytes() const BKSGE_NOEXCEPT { return m_size * sizeof(element_type); }
	BKSGE_CONSTEXPR bool empty()            const BKSGE_NOEXCEPT { return m_size == 0; }

	BKSGE_CONSTEXPR reference
	operator[](index_type idx) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(idx >= 0u && idx < size(), "span<T>[] index out of bounds"),
			m_data[idx];
	}

	BKSGE_CONSTEXPR reference
	front() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(!empty(), "span<T>[].front() on empty span"),
			m_data[0];
	}

	BKSGE_CONSTEXPR reference
	back() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT_MSG(!empty(), "span<T>[].back() on empty span"),
			m_data[size()-1];
	}

	BKSGE_CONSTEXPR pointer data()                   const BKSGE_NOEXCEPT { return m_data; }

	// [span.iter], span iterator support
	BKSGE_CONSTEXPR iterator                 begin() const BKSGE_NOEXCEPT { return iterator(data()); }
	BKSGE_CONSTEXPR iterator                   end() const BKSGE_NOEXCEPT { return iterator(data() + size()); }
	BKSGE_CONSTEXPR const_iterator          cbegin() const BKSGE_NOEXCEPT { return const_iterator(data()); }
	BKSGE_CONSTEXPR const_iterator            cend() const BKSGE_NOEXCEPT { return const_iterator(data() + size()); }
	BKSGE_CXX17_CONSTEXPR reverse_iterator        rbegin() const BKSGE_NOEXCEPT { return reverse_iterator(end()); }
	BKSGE_CXX17_CONSTEXPR reverse_iterator          rend() const BKSGE_NOEXCEPT { return reverse_iterator(begin()); }
	BKSGE_CXX17_CONSTEXPR const_reverse_iterator crbegin() const BKSGE_NOEXCEPT { return const_reverse_iterator(cend()); }
	BKSGE_CXX17_CONSTEXPR const_reverse_iterator   crend() const BKSGE_NOEXCEPT { return const_reverse_iterator(cbegin()); }

	BKSGE_CXX14_CONSTEXPR void swap(span& other) BKSGE_NOEXCEPT
	{
		pointer p = m_data;
		m_data = other.m_data;
		other.m_data = p;

		index_type sz = m_size;
		m_size = other.m_size;
		other.m_size = sz;
	}

private:
	pointer    m_data;
	index_type m_size;
};

template <typename T, std::size_t Extent>
BKSGE_CXX14_CONSTEXPR void
swap(span<T, Extent>& lhs, span<T, Extent>& rhs) BKSGE_NOEXCEPT
{
	lhs.swap(rhs);
}

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

//  Deduction guides
template <typename T, std::size_t N>
span(T (&)[N])->span<T, N>;

template <typename T, std::size_t N>
span(std::array<T, N>&)->span<T, N>;

template <typename T, std::size_t N>
span(std::array<T, N> const&)->span<T const, N>;

template <typename Container>
span(Container&)->span<typename Container::value_type>;

template <typename Container>
span(Container const&)->span<typename Container::value_type const>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_SPAN_SPAN_HPP
