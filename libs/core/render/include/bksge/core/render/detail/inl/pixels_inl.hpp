﻿/**
 *	@file	pixels_inl.hpp
 *
 *	@brief	Pixels の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_PIXELS_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_PIXELS_INL_HPP

#include <bksge/core/render/detail/pixels.hpp>
#include <bksge/fnd/cstring/memcpy.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
void Pixels::resize(bksge::size_t size)
{
	m_value.resize(size);
}

BKSGE_INLINE
void Pixels::copy(void const* src, bksge::size_t size)
{
	if (m_value.empty())
	{
		return;
	}

	bksge::memcpy(m_value.data(), src, size);
}

BKSGE_INLINE
bksge::uint8_t const* Pixels::data(void) const
{
	if (m_value.empty())
	{
		return nullptr;
	}

	return m_value.data();
}

BKSGE_INLINE
bksge::vector<bksge::uint8_t> const& Pixels::value(void) const
{
	return m_value;
}

BKSGE_INLINE
bool operator==(Pixels const& lhs, Pixels const& rhs)
{
	return lhs.value() == rhs.value();
}

BKSGE_INLINE
bool operator!=(Pixels const& lhs, Pixels const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_PIXELS_INL_HPP
