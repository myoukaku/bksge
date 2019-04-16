/**
 *	@file	texture_inl.hpp
 *
 *	@brief	Texture の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_TEXTURE_INL_HPP
#define BKSGE_RENDER_INL_TEXTURE_INL_HPP

#include <bksge/render/texture.hpp>
#include <bksge/assert.hpp>
#include <memory>
#include <cstddef>
#include <cstdint>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Texture::Texture(void)
	: m_format(TextureFormat::kNone)
	, m_size(0, 0)
	, m_mipmap_count(0)
	, m_pixels(std::make_shared<Pixels>())
{}

BKSGE_INLINE
Texture::Texture(
	TextureFormat format,
	SizeType const& size,
	std::size_t mipmap_count,
	std::uint8_t const* src)
	: m_format(format)
	, m_size(size)
	, m_mipmap_count(mipmap_count)
	, m_pixels(std::make_shared<Pixels>())
{
	BKSGE_ASSERT(format != TextureFormat::kNone);
	BKSGE_ASSERT(size.width() >= 1u);
	BKSGE_ASSERT(size.height() >= 1u);
	BKSGE_ASSERT(mipmap_count >= 1u);

	auto const bytes = GetMipmappedSizeInBytes(format, size.width(), size.height(), mipmap_count);
	BKSGE_ASSERT(bytes >= 1u);

	m_pixels->resize(bytes);

	if (src)
	{
		m_pixels->copy(src, bytes);
	}
}

BKSGE_INLINE
Texture::Texture(TextureFormat format, SizeType const& size, std::size_t mipmap_count)
	: Texture(format, size, mipmap_count, nullptr)
{}

BKSGE_INLINE
Texture::Texture(TextureFormat format, SizeType const& size, std::uint8_t const* src)
	: Texture(format, size, 1, src)
{}

BKSGE_INLINE
Texture::Texture(TextureFormat format, SizeType const& size)
	: Texture(format, size, 1, nullptr)
{}

BKSGE_INLINE
TextureFormat Texture::format(void) const
{
	return m_format;
}

BKSGE_INLINE
auto Texture::size(void) const
-> SizeType const&
{
	return m_size;
}

BKSGE_INLINE
std::uint32_t Texture::width(void) const
{
	return size().width();
}

BKSGE_INLINE
std::uint32_t Texture::height(void) const
{
	return size().height();
}

BKSGE_INLINE
std::size_t Texture::mipmap_count(void) const
{
	return m_mipmap_count;
}

BKSGE_INLINE
std::size_t Texture::stride(void) const
{
	return GetStrideInBytes(format(), width());
}

BKSGE_INLINE
std::uint8_t const* Texture::data(void) const
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
		lhs.size()         == rhs.size()         &&
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

#endif // BKSGE_RENDER_INL_TEXTURE_INL_HPP
