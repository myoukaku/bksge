/**
 *	@file	basic_istream_view.hpp
 *
 *	@brief	basic_istream_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_BASIC_ISTREAM_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_BASIC_ISTREAM_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/detail/stream_extractable.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <bksge/fnd/istream/basic_istream.hpp>
#include <bksge/fnd/iterator/default_sentinel.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::movable Val, typename CharT, typename Traits>
requires
	bksge::default_initializable<Val> &&
	detail::stream_extractable<Val, CharT, Traits>
#else
template <typename Val, typename CharT, typename Traits,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::movable<Val>,
		bksge::default_initializable<Val>,
		detail::stream_extractable<Val, CharT, Traits>
	>::value>
>
#endif
class basic_istream_view
	: public ranges::view_interface<basic_istream_view<Val, CharT, Traits>>
{
private:
	struct Iterator;

public:
	basic_istream_view() = default;

	BKSGE_CONSTEXPR explicit
	basic_istream_view(bksge::basic_istream<CharT, Traits>& stream)
		: m_stream(bksge::addressof(stream))
	{}

	BKSGE_CXX14_CONSTEXPR Iterator
	begin()
	{
		if (m_stream != nullptr)
		{
			*m_stream >> m_object;
		}

		return Iterator{ this };
	}

	BKSGE_CONSTEXPR bksge::default_sentinel_t
	end() const BKSGE_NOEXCEPT
	{
		return bksge::default_sentinel;
	}

private:
	bksge::basic_istream<CharT, Traits>* m_stream = nullptr;
	Val m_object = Val();

	struct Iterator
	{
	public:
		using iterator_concept = bksge::input_iterator_tag;
		using difference_type = bksge::ptrdiff_t;
		using value_type = Val;

		Iterator() = default;

		BKSGE_CONSTEXPR explicit
		Iterator(basic_istream_view* parent) BKSGE_NOEXCEPT
			: m_parent(parent)
		{}

		Iterator(Iterator const&) = delete;
		Iterator(Iterator&&) = default;
		Iterator& operator=(Iterator const&) = delete;
		Iterator& operator=(Iterator&&) = default;

		Iterator& operator++()
		{
			BKSGE_ASSERT(m_parent->m_stream != nullptr);
			*m_parent->m_stream >> m_parent->m_object;
			return *this;
		}

		void operator++(int)
		{
			++*this;
		}

		Val& operator*() const
		{
			BKSGE_ASSERT(m_parent->m_stream != nullptr);
			return m_parent->m_object;
		}

		friend bool
		operator==(Iterator const& lhs, bksge::default_sentinel_t)
		{
			return lhs.at_end();
		}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
		friend bool
		operator!=(Iterator const& lhs, bksge::default_sentinel_t rhs)
		{
			return !(lhs == rhs);
		}
#endif

	private:
		basic_istream_view* m_parent = nullptr;

		bool at_end() const
		{
			return m_parent == nullptr || !*m_parent->m_stream;
		}
	};

	friend Iterator;
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_BASIC_ISTREAM_VIEW_HPP
