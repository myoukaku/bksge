/**
 *	@file	span.hpp
 *
 *	@brief	span の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_SPAN_HPP
#define BKSGE_FND_SPAN_SPAN_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002) && \
	defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

namespace bksge
{

using std::span;

}	// namespace bksge

#else

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/span/detail/is_array_convertible.hpp>
#include <bksge/fnd/span/detail/span_compatible_iterator.hpp>
#include <bksge/fnd/span/detail/span_compatible_range.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/array.hpp>

namespace bksge
{

template <typename T, bksge::size_t Extent>
class span
{
private:
	template <typename U, bksge::size_t N>
	using is_compatible_array =
		bksge::conjunction<
			bksge::bool_constant<N == Extent>,
			detail::is_array_convertible<T, U>
		>;

public:
	// member types
	using element_type           = T;
	using value_type             = bksge::remove_cv_t<T>;
	using size_type              = bksge::size_t;
	using difference_type        = bksge::ptrdiff_t;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = T&;
	using const_reference        = T const&;
	using iterator               = pointer;//__gnu_cxx::__normal_iterator<pointer, span>;
	using reverse_iterator       = bksge::reverse_iterator<iterator>;

	// member constants
	BKSGE_STATIC_CONSTEXPR bksge::size_t extent = Extent;

	// constructors, copy and assignment

#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::size_t E = Extent,
		typename = bksge::enable_if_t<E == 0u>
	>
#endif
	BKSGE_CONSTEXPR span() BKSGE_NOEXCEPT
	BKSGE_REQUIRES(Extent == 0u)
		: m_ptr(nullptr)
	{}

	template <BKSGE_REQUIRES_PARAM_2(detail::span_compatible_iterator, T, It)>
	BKSGE_CXX14_CONSTEXPR explicit
	span(It first, size_type count) BKSGE_NOEXCEPT
		: m_ptr(bksge::to_address(first))
	{
		BKSGE_ASSERT(count == Extent);
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <detail::span_compatible_iterator<T> It, bksge::sized_sentinel_for<It> End>
	requires (!bksge::is_convertible<End, size_type>::value)
#else
	template <
		typename It, typename End,
		typename = bksge::enable_if_t<bksge::conjunction<
			detail::span_compatible_iterator<It, T>,
			bksge::sized_sentinel_for<End, It>,
			bksge::negation<bksge::is_convertible<End, size_type>>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR explicit
	span(It first, End last)
		BKSGE_NOEXCEPT_IF_EXPR(last - first)
		: m_ptr(bksge::to_address(first))
	{
		BKSGE_ASSERT(static_cast<size_type>(last - first) == Extent);
	}

	template <bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<N == Extent>
#endif
	>
	BKSGE_REQUIRES(N == Extent)
	BKSGE_CXX14_CONSTEXPR
	span(bksge::type_identity_t<element_type> (&arr)[N]) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr), N)
	{}

	template <typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			is_compatible_array<U, N>::value
		>
#endif
	>
	BKSGE_REQUIRES(is_compatible_array<U, N>::value)
	BKSGE_CXX14_CONSTEXPR
	span(bksge::array<U, N>& arr) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr.data()), N)
	{}

	template <typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			is_compatible_array<U const, N>::value
		>
#endif
	>
	BKSGE_REQUIRES(is_compatible_array<U const, N>::value)
	BKSGE_CXX14_CONSTEXPR
	span(bksge::array<U, N> const& arr) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr.data()), N)
	{}

	template <BKSGE_REQUIRES_PARAM_2(detail::span_compatible_range, T, Range)>
	BKSGE_CXX14_CONSTEXPR explicit
	span(Range&& r)
		BKSGE_NOEXCEPT_IF(
			BKSGE_NOEXCEPT_EXPR(ranges::data(r)) &&
			BKSGE_NOEXCEPT_EXPR(ranges::size(r)))
		: span(ranges::data(r), ranges::size(r))
	{
		BKSGE_ASSERT(ranges::size(r) == Extent);
	}

	BKSGE_CONSTEXPR span(span const&) BKSGE_NOEXCEPT = default;

	template <
		typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			N == bksge::dynamic_extent &&
			detail::is_array_convertible<T, U>::value
		>
#endif
	>
	BKSGE_REQUIRES(
		N == bksge::dynamic_extent &&
		detail::is_array_convertible<T, U>::value)
	BKSGE_CXX14_CONSTEXPR explicit
	span(span<U, N> const& s) BKSGE_NOEXCEPT
		: m_ptr(s.data())
	{
		BKSGE_ASSERT(s.size() == Extent);
	}

	template <
		typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, bksge::enable_if_t<
			N == Extent &&
			detail::is_array_convertible<T, U>::value
		>* = nullptr
#endif
	>
	BKSGE_REQUIRES(
		N == Extent &&
		detail::is_array_convertible<T, U>::value)
	BKSGE_CXX14_CONSTEXPR
	span(span<U, N> const& s) BKSGE_NOEXCEPT
		: m_ptr(s.data())
	{
		BKSGE_ASSERT(s.size() == Extent);
	}

	~span() BKSGE_NOEXCEPT = default;

	BKSGE_CXX14_CONSTEXPR span& operator=(span const&) BKSGE_NOEXCEPT = default;

	// observers

	BKSGE_CONSTEXPR size_type
	size() const BKSGE_NOEXCEPT
	{
		return Extent;
	}

	BKSGE_CONSTEXPR size_type
	size_bytes() const BKSGE_NOEXCEPT
	{
		return Extent * sizeof(element_type);
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT
	{
		return size() == 0;
	}

	// element access

	BKSGE_CONSTEXPR reference
	front() const BKSGE_NOEXCEPT
	{
		static_assert(Extent != 0, "");
		return
			BKSGE_ASSERT(!empty()),
			*this->m_ptr;
	}

	BKSGE_CONSTEXPR reference
	back() const BKSGE_NOEXCEPT
	{
		static_assert(Extent != 0, "");
		return
			BKSGE_ASSERT(!empty()),
			*(this->m_ptr + (size() - 1));
	}

	BKSGE_CONSTEXPR reference
	operator[](size_type idx) const BKSGE_NOEXCEPT
	{
		static_assert(Extent != 0, "");
		return
			BKSGE_ASSERT(idx < size()),
			*(this->m_ptr + idx);
	}

	BKSGE_CONSTEXPR pointer
	data() const BKSGE_NOEXCEPT
	{
		return this->m_ptr;
	}

	// iterator support

	BKSGE_CONSTEXPR iterator
	begin() const BKSGE_NOEXCEPT
	{
		return iterator(this->m_ptr);
	}

	BKSGE_CONSTEXPR iterator
	end() const BKSGE_NOEXCEPT
	{
		return iterator(this->m_ptr + this->size());
	}

	BKSGE_CONSTEXPR reverse_iterator
	rbegin() const BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR reverse_iterator
	rend() const BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	// subviews

	template <bksge::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	first() const BKSGE_NOEXCEPT
	{
		static_assert(Count <= Extent, "");
		using Sp = span<element_type, Count>;
		return Sp{this->data(), Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	first(size_type count) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(count <= size()),
			Sp{this->data(), count};
	}

	template <bksge::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	last() const BKSGE_NOEXCEPT
	{
		static_assert(Count <= Extent, "");
		using Sp = span<element_type, Count>;
		return Sp{this->data() + (this->size() - Count), Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	last(size_type count) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(count <= size()),
			Sp{this->data() + (this->size() - count), count};
	}

private:
	template <bksge::size_t Offset, bksge::size_t Count>
	struct subspan_impl
	{
		using type = span<element_type, Count>;

		static BKSGE_CONSTEXPR type get(pointer data)
		{
			static_assert(Count <= Extent, "");
			static_assert(Count <= (Extent - Offset), "");
			return type{data + Offset, Count};
		}
	};

	template <bksge::size_t Offset>
	struct subspan_impl<Offset, bksge::dynamic_extent>
	{
		using type = span<element_type, Extent - Offset>;

		static BKSGE_CONSTEXPR type get(pointer data)
		{
			return type{data + Offset, Extent - Offset};
		}
	};

public:
	template <bksge::size_t Offset, bksge::size_t Count = bksge::dynamic_extent>
	BKSGE_CONSTEXPR auto
	subspan() const BKSGE_NOEXCEPT
		-> typename subspan_impl<Offset, Count>::type
	{
		static_assert(Offset <= Extent, "");
		return subspan_impl<Offset, Count>::get(this->data());
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	subspan(size_type offset, size_type count = bksge::dynamic_extent) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(offset <= size()),
			(count == bksge::dynamic_extent) ?
				Sp{this->data() + offset, this->size() - offset} :
				(BKSGE_ASSERT(count <= size()),
				 BKSGE_ASSERT(offset + count <= size()),
				 Sp{this->data() + offset, count});
	}

private:
	pointer m_ptr;
};

template <typename T>
class span<T, bksge::dynamic_extent>
{
private:
	template <typename U, bksge::size_t N>
	using is_compatible_array =
		detail::is_array_convertible<T, U>;

public:
	// member types
	using element_type           = T;
	using value_type             = bksge::remove_cv_t<T>;
	using size_type              = bksge::size_t;
	using difference_type        = bksge::ptrdiff_t;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = T&;
	using const_reference        = T const&;
	using iterator               = pointer;//__gnu_cxx::__normal_iterator<pointer, span>;
	using reverse_iterator       = bksge::reverse_iterator<iterator>;

	// member constants
	BKSGE_STATIC_CONSTEXPR bksge::size_t extent = bksge::dynamic_extent;

	// constructors, copy and assignment

	BKSGE_CONSTEXPR span() BKSGE_NOEXCEPT
		: m_extent(0)
		, m_ptr(nullptr)
	{}

	template <BKSGE_REQUIRES_PARAM_2(detail::span_compatible_iterator, T, It)>
	BKSGE_CONSTEXPR
	span(It first, size_type count) BKSGE_NOEXCEPT
		: m_extent(count)
		, m_ptr(bksge::to_address(first))
	{}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <detail::span_compatible_iterator<T> It, bksge::sized_sentinel_for<It> End>
	requires (!bksge::is_convertible<End, size_type>::value)
#else
	template <
		typename It, typename End,
		typename = bksge::enable_if_t<bksge::conjunction<
			detail::span_compatible_iterator<It, T>,
			bksge::sized_sentinel_for<End, It>,
			bksge::negation<bksge::is_convertible<End, size_type>>
		>::value>
	>
#endif
	BKSGE_CONSTEXPR
	span(It first, End last)
		BKSGE_NOEXCEPT_IF_EXPR(last - first)
		: m_extent(static_cast<size_type>(last - first))
		, m_ptr(bksge::to_address(first))
	{}

	template <bksge::size_t N>
	BKSGE_CONSTEXPR
	span(bksge::type_identity_t<element_type> (&arr)[N]) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr), N)
	{}

	template <typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			is_compatible_array<U, N>::value
		>
#endif
	>
	BKSGE_REQUIRES(is_compatible_array<U, N>::value)
	BKSGE_CONSTEXPR
	span(bksge::array<U, N>& arr) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr.data()), N)
	{}

	template <typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			is_compatible_array<U const, N>::value
		>
#endif
	>
	BKSGE_REQUIRES(is_compatible_array<U const, N>::value)
	BKSGE_CONSTEXPR
	span(bksge::array<U, N> const& arr) BKSGE_NOEXCEPT
		: span(static_cast<pointer>(arr.data()), N)
	{}

	template <BKSGE_REQUIRES_PARAM_2(detail::span_compatible_range, T, Range)>
	BKSGE_CONSTEXPR
	span(Range&& r)
		BKSGE_NOEXCEPT_IF(
			BKSGE_NOEXCEPT_EXPR(ranges::data(r)) &&
			BKSGE_NOEXCEPT_EXPR(ranges::size(r)))
		: span(ranges::data(r), ranges::size(r))
	{}

	BKSGE_CONSTEXPR span(span const&) BKSGE_NOEXCEPT = default;

	template <
		typename U, bksge::size_t N
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			detail::is_array_convertible<T, U>::value
		>
#endif
	>
	BKSGE_REQUIRES(detail::is_array_convertible<T, U>::value)
	BKSGE_CONSTEXPR
	span(span<U, N> const& s) BKSGE_NOEXCEPT
		: m_extent(s.size())
		, m_ptr(s.data())
	{}

	~span() BKSGE_NOEXCEPT = default;

	BKSGE_CXX14_CONSTEXPR span& operator=(span const&) BKSGE_NOEXCEPT = default;

	// observers

	BKSGE_CONSTEXPR size_type
	size() const BKSGE_NOEXCEPT
	{
		return this->m_extent;
	}

	BKSGE_CONSTEXPR size_type
	size_bytes() const BKSGE_NOEXCEPT
	{
		return this->m_extent * sizeof(element_type);
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT
	{
		return size() == 0;
	}

	// element access

	BKSGE_CONSTEXPR reference
	front() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT(!empty()),
			*this->m_ptr;
	}

	BKSGE_CONSTEXPR reference
	back() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT(!empty()),
			*(this->m_ptr + (size() - 1));
	}

	BKSGE_CONSTEXPR reference
	operator[](size_type idx) const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT(idx < size()),
			*(this->m_ptr + idx);
	}

	BKSGE_CONSTEXPR pointer
	data() const BKSGE_NOEXCEPT
	{
		return this->m_ptr;
	}

	// iterator support

	BKSGE_CONSTEXPR iterator
	begin() const BKSGE_NOEXCEPT
	{
		return iterator(this->m_ptr);
	}

	BKSGE_CONSTEXPR iterator
	end() const BKSGE_NOEXCEPT
	{
		return iterator(this->m_ptr + this->size());
	}

	BKSGE_CONSTEXPR reverse_iterator
	rbegin() const BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR reverse_iterator
	rend() const BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	// subviews

	template <bksge::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	first() const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, Count>;
		return
			BKSGE_ASSERT(Count <= size()),
			Sp{this->data(), Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	first(size_type count) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(count <= size()),
			Sp{this->data(), count};
	}

	template <bksge::size_t Count>
	BKSGE_CONSTEXPR span<element_type, Count>
	last() const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, Count>;
		return
			BKSGE_ASSERT(Count <= size()),
			Sp{this->data() + (this->size() - Count), Count};
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	last(size_type count) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(count <= size()),
			Sp{this->data() + (this->size() - count), count};
	}

private:
	template <bksge::size_t Offset, bksge::size_t Count>
	struct subspan_impl
	{
		using type = span<element_type, Count>;

		static BKSGE_CONSTEXPR type get(pointer data, bksge::size_t size)
		{
			return
				BKSGE_ASSERT(Count <= size),
				BKSGE_ASSERT(Count <= (size - Offset)),
				type{data + Offset, Count};
		}
	};

	template <bksge::size_t Offset>
	struct subspan_impl<Offset, bksge::dynamic_extent>
	{
		using type = span<element_type, bksge::dynamic_extent>;

		static BKSGE_CONSTEXPR type get(pointer data, bksge::size_t size)
		{
			return type{data + Offset, size - Offset};
		}
	};

public:
	template <bksge::size_t Offset, bksge::size_t Count = bksge::dynamic_extent>
	BKSGE_CONSTEXPR auto
	subspan() const BKSGE_NOEXCEPT
		-> typename subspan_impl<Offset, Count>::type
	{
		return
			BKSGE_ASSERT(Offset <= size()),
			subspan_impl<Offset, Count>::get(this->data(), this->size());
	}

	BKSGE_CONSTEXPR span<element_type, bksge::dynamic_extent>
	subspan(size_type offset, size_type count = bksge::dynamic_extent) const BKSGE_NOEXCEPT
	{
		using Sp = span<element_type, bksge::dynamic_extent>;
		return
			BKSGE_ASSERT(offset <= size()),
			(count == bksge::dynamic_extent) ?
				Sp{this->data() + offset, this->size() - offset} :
				(BKSGE_ASSERT(count <= size()),
				 BKSGE_ASSERT(offset + count <= size()),
				 Sp{this->data() + offset, count});
	}

private:
	bksge::size_t	m_extent;
	pointer		m_ptr;
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

// deduction guides

template <typename T, bksge::size_t N>
span(T(&)[N]) -> span<T, N>;

template <typename T, bksge::size_t N>
span(bksge::array<T, N>&) -> span<T, N>;

template <typename T, bksge::size_t N>
span(bksge::array<T, N> const&) -> span<T const, N>;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::contiguous_iterator It, typename End>
#else
template <
	typename It, typename End,
	typename = bksge::enable_if_t<
		bksge::contiguous_iterator<It>::value
	>
>
#endif
span(It, End)
-> span<bksge::remove_reference_t<bksge::iter_reference_t<It>>>;

template <typename Range>
span(Range&&)
-> span<bksge::remove_reference_t<ranges::range_reference_t<Range&>>>;

#endif

}	// namespace bksge

#endif

#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_view.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace ranges
{

template <typename T, bksge::size_t Extent>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, bksge::span<T, Extent>);

template <typename T, bksge::size_t Extent>
BKSGE_RANGES_SPECIALIZE_ENABLE_VIEW((Extent == 0 || Extent == bksge::dynamic_extent), bksge::span<T, Extent>);

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_SPAN_SPAN_HPP
