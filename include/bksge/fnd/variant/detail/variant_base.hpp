/**
 *	@file	variant_base.hpp
 *
 *	@brief	variant_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP

#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/valueless_t.hpp>
#include <bksge/fnd/variant/detail/variant_index_t.hpp>
#include <bksge/fnd/variant/detail/variant_npos_t.hpp>
#include <bksge/fnd/variant/detail/variant_union.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

namespace bksge
{

namespace variant_detail
{

template <trait_enum DestructibleTrait, typename... Types>
class variant_base
{
public:
	using index_t = variant_index_t<sizeof...(Types)>;

	explicit BKSGE_CONSTEXPR
	variant_base(valueless_t tag) BKSGE_NOEXCEPT
		: m_data(tag)
		, m_index(variant_npos_t<index_t>::value)
	{}

	template <std::size_t I, typename... Args>
	explicit BKSGE_CONSTEXPR
	variant_base(bksge::in_place_index_t<I>, Args&&... args)
		: m_data(bksge::in_place_index_t<I>{}, bksge::forward<Args>(args)...)
		, m_index(I)
	{}

	BKSGE_CONSTEXPR bool valueless_by_exception() const BKSGE_NOEXCEPT
	{
		return index() == variant_npos;
	}

	BKSGE_CONSTEXPR std::size_t index() const BKSGE_NOEXCEPT
	{
		return m_index == variant_npos_t<index_t>::value ? variant_npos : m_index;
	}

	static BKSGE_CONSTEXPR std::size_t size() { return sizeof...(Types); }

protected:
	BKSGE_CXX14_CONSTEXPR variant_base&        as_base() &       { return *this; }
	BKSGE_CXX14_CONSTEXPR variant_base&&       as_base() &&      { return bksge::move(*this); }
	BKSGE_CONSTEXPR       variant_base const&  as_base() const&  { return *this; }
	BKSGE_CONSTEXPR       variant_base const&& as_base() const&& { return bksge::move(*this); }

	variant_union<DestructibleTrait, 0, Types...> m_data;
	index_t m_index;

	friend struct access::base_t;
	friend struct visitation::base_t;
};

}	// namespace variant_detail

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_BASE_HPP
