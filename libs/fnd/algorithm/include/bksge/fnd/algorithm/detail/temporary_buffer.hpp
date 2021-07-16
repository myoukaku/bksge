/**
 *	@file	temporary_buffer.hpp
 *
 *	@brief	temporary_buffer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_TEMPORARY_BUFFER_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_TEMPORARY_BUFFER_HPP

#include <bksge/fnd/memory/destroy.hpp>
#include <bksge/fnd/memory/construct_at.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/type_traits/is_trivially_constructible.hpp>
#include <cstdlib>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename ForwardIterator, typename T>
class temporary_buffer
{
	// concept requirements
	//__glibcxx_class_requires(ForwardIterator, _ForwardIteratorConcept)

public:
	using value_type = T;
	using pointer    = value_type*;
	using iterator   = pointer;
	using size_type  = std::ptrdiff_t;

protected:
	size_type  m_original_len;
	size_type  m_len;
	pointer    m_buffer;

public:
	/// As per Table mumble.
	size_type size() const
	{
		return m_len;
	}

	/// Returns the size requested by the constructor; may be >size().
	size_type requested_size() const
	{
		return m_original_len;
	}

	/// As per Table mumble.
	iterator begin()
	{
		return m_buffer;
	}

	/// As per Table mumble.
	iterator end()
	{
		return m_buffer + m_len;
	}

	/**
	 * Constructs a temporary buffer of a size somewhere between
	 * zero and the given length.
	 */
	temporary_buffer(ForwardIterator seed, size_type original_len);

	~temporary_buffer()
	{
		bksge::destroy(m_buffer, m_buffer + m_len);
		std::free(m_buffer);
	}

private:
	// Disable copy constructor and assignment operator.
	temporary_buffer(const temporary_buffer&);

	void operator=(const temporary_buffer&);
};

template <bool>
struct uninitialized_construct_buf_dispatch
{
	template <typename Pointer, typename ForwardIterator>
	static void ucr(Pointer first, Pointer last, ForwardIterator seed)
	{
		if (first == last)
		{
			return;
		}

		Pointer cur = first;

		try
		{
			bksge::construct_at(bksge::addressof(*first), std::move(*seed));
			Pointer prev = cur;
			++cur;

			for (; cur != last; ++cur, ++prev)
			{
				bksge::construct_at(bksge::addressof(*cur), std::move(*prev));
			}

			*seed = std::move(*prev);
		}
		catch(...)
		{
			bksge::destroy(first, cur);
			throw;
		}
	}
};

template <>
struct uninitialized_construct_buf_dispatch<true>
{
	template <typename Pointer, typename ForwardIterator>
	static void ucr(Pointer, Pointer, ForwardIterator) {}
};

// Constructs objects in the range [first, last).
// Note that while these new objects will take valid values,
// their exact value is not defined. In particular they may
// be 'moved from'.
//
// While *seed may be altered during this algorithm, it will have
// the same value when the algorithm finishes, unless one of the
// constructions throws.
//
// Requirements: Pointer::value_type(T&&) is valid.
template <typename Pointer, typename ForwardIterator>
inline void
uninitialized_construct_buf(Pointer first, Pointer last, ForwardIterator seed)
{
	using value_t = bksge::iter_value_t<Pointer>;
	detail::uninitialized_construct_buf_dispatch<
		bksge::is_trivially_constructible<value_t>::value
	>::ucr(first, last, seed);
}

template <typename ForwardIterator, typename T>
temporary_buffer<ForwardIterator, T>::temporary_buffer(
	ForwardIterator seed, size_type original_len)
	: m_original_len(original_len)
	, m_len(0)
	, m_buffer(0)
{
	auto size = sizeof(value_type) * m_original_len;
	auto p = reinterpret_cast<value_type*>(std::malloc(size));

	if (p)
	{
		try
		{
			detail::uninitialized_construct_buf(p, p + m_original_len, seed);
			m_buffer = p;
			m_len = m_original_len;
		}
		catch(...)
		{
			std::free(p);
			throw;
		}
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_TEMPORARY_BUFFER_HPP
