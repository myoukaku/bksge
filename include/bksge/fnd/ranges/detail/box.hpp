/**
 *	@file	box.hpp
 *
 *	@brief	box の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_BOX_HPP
#define BKSGE_FND_RANGES_DETAIL_BOX_HPP

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/optional.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::copy_constructible T>
requires bksge::is_object<T>::value
#else
template <typename T,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::copy_constructible<T>,
		bksge::is_object<T>
	>::value>
>
#endif
struct box : bksge::optional<T>
{
	using bksge::optional<T>::optional;

	BKSGE_CONSTEXPR box()
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_default_constructible<T>::value)
		BKSGE_REQUIRES(bksge::default_initializable<T>)
		: bksge::optional<T>{bksge::in_place}
	{ }

	BKSGE_CONSTEXPR box(box const&) = default;
	BKSGE_CONSTEXPR box(box&&) = default;

	using bksge::optional<T>::operator=;

	BKSGE_CXX14_CONSTEXPR box& operator=(box const& that)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<T>::value)
		BKSGE_REQUIRES(!bksge::assignable_from<T&, T const&>)
	{
		if ((bool)that)
		{
			this->emplace(*that);
		}
		else
		{
			this->reset();
		}

		return *this;
	}

	BKSGE_CXX14_CONSTEXPR box& operator=(box&& that)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<T>::value)
		BKSGE_REQUIRES(!bksge::assignable_from<T&, T>)
	{
		if ((bool)that)
		{
			this->emplace(bksge::move(*that));
		}
		else
		{
			this->reset();
		}

		return *this;
	}
};

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_BOX_HPP
