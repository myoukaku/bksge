/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_INL_TEXTURE_INL_HPP

#include <bksge/core/render/texture.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <memory>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Texture::Texture(void)
	: m_format(TextureFormat::kNone)
	, m_extent(0, 0)
	, m_mipmap_count(0)
	, m_pixels(std::make_shared<Pixels>())
{}

BKSGE_INLINE
Texture::Texture(
	TextureFormat format,
	ExtentType const& extent,
	bksge::size_t mipmap_count,
	bksge::uint8_t const* src)
	: m_format(format)
	, m_extent(extent)
	, m_mipmap_count(mipmap_count)
	, m_pixels(std::make_shared<Pixels>())
{
	BKSGE_ASSERT(format != TextureFormat::kNone);
	BKSGE_ASSERT(extent.width() >= 1u);
	BKSGE_ASSERT(extent.height() >= 1u);
	BKSGE_ASSERT(mipmap_count >= 1u);

	auto const bytes = GetMipmappedSizeInBytes(format, extent.width(), extent.height(), mipmap_count);
	BKSGE_ASSERT(bytes >= 1u);

	m_pixels->resize(bytes);

	if (src)
	{
		m_pixels->copy(src, bytes);
	}
}

BKSGE_INLINE
Texture::Texture(TextureFormat format, ExtentType const& extent, bksge::size_t mipmap_count)
	: Texture(format, extent, mipmap_count, nullptr)
{}

BKSGE_INLINE
Texture::Texture(TextureFormat format, ExtentType const& extent, bksge::uint8_t const* src)
	: Texture(format, extent, 1, src)
{}

BKSGE_INLINE
Texture::Texture(TextureFormat format, ExtentType const& extent)
	: Texture(format, extent, 1, nullptr)
{}

BKSGE_INLINE
TextureFormat Texture::format(void) const
{
	return m_format;
}

BKSGE_INLINE
auto Texture::extent(void) const
-> ExtentType const&
{
	return m_extent;
}

BKSGE_INLINE
bksge::uint32_t Texture::width(void) const
{
	return extent().width();
}

BKSGE_INLINE
bksge::uint32_t Texture::height(void) const
{
	return extent().height();
}

BKSGE_INLINE
bksge::size_t Texture::mipmap_count(void) const
{
	return m_mipmap_count;
}

BKSGE_INLINE
bksge::size_t Texture::stride(void) const
{
	return GetStrideInBytes(format(), width());
}

BKSGE_INLINE
bksge::uint8_t const* Texture::data(void) const
{
	BKSGE_ASSERT(m_pixels != nullptr);
	return m_pixels->data();
}

BKSGE_INLINE
auto Texture::pixels(void) const
-> Pixels const&
{
	BKSGE_ASSERT(m_pixels != nullptr);
	return *m_pixels;
}

BKSGE_INLINE
bool operator==(Texture const& lhs, Texture const& rhs)
{
	return
		lhs.format()       == rhs.format()       &&
		lhs.extent()       == rhs.extent()       &&
		lhs.mipmap_count() == rhs.mipmap_count() &&
		lhs.pixels()       == rhs.pixels();
}

BKSGE_INLINE
bool operator!=(Texture const& lhs, Texture const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_TEXTURE_INL_HPP
