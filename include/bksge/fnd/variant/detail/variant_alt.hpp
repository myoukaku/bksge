/**
 *	@file	variant_alt.hpp
 *
 *	@brief	variant_alt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_ALT_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_ALT_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <std::size_t Index, typename T>
struct variant_alt
{
	using value_type = T;

	template <typename... Args>
	explicit BKSGE_CONSTEXPR
	variant_alt(bksge::in_place_t, Args&&... args)
		: m_value(bksge::forward<Args>(args)...) {}

	value_type m_value;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_ALT_HPP
