/**
 *	@file	pixels_inl.hpp
 *
 *	@brief	Pixels の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_INL_PIXELS_INL_HPP
#define BKSGE_RENDER_DETAIL_INL_PIXELS_INL_HPP

#include <bksge/render/detail/pixels.hpp>
#include <cstddef>
#include <cstring>
#include <vector>

namespace bksge
{

namespace render
{

BKSGE_INLINE
void Pixels::resize(std::size_t size)
{
	m_value.resize(size);
}

BKSGE_INLINE
void Pixels::copy(void const* src, std::size_t size)
{
	if (m_value.empty())
	{
		return;
	}

	std::memcpy(m_value.data(), src, size);
}

BKSGE_INLINE
std::uint8_t const* Pixels::data(void) const
{
	if (m_value.empty())
	{
		return nullptr;
	}

	return m_value.data();
}

BKSGE_INLINE
std::vector<std::uint8_t> const& Pixels::value(void) const
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

#endif // BKSGE_RENDER_DETAIL_INL_PIXELS_INL_HPP
