/**
 *	@file	render_texture.hpp
 *
 *	@brief	RenderTexture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_RENDER_TEXTURE_HPP
#define BKSGE_CORE_RENDER_RENDER_TEXTURE_HPP

#include <bksge/core/render/fwd/render_texture_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/core/math/extent2.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

class RenderTexture : public Identifiable
{
public:
	using ExtentType = Extent2<std::uint32_t>;

	RenderTexture(TextureFormat format, ExtentType const& extent);

	/**
	 *	@brief	フォーマットを取得します
	 */
	TextureFormat format(void) const;

	/**
	 *	@brief	幅と高さを取得します
	 */
	ExtentType const& extent(void) const;

private:
	TextureFormat	m_format;	///< フォーマット
	ExtentType		m_extent;	///< 幅と高さ
};

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/render_texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_RENDER_TEXTURE_HPP
