/**
 *	@file	texture.hpp
 *
 *	@brief	Texture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_TEXTURE_HPP
#define BKSGE_CORE_RENDER_TEXTURE_HPP

#include <bksge/core/render/fwd/texture_fwd.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/render/detail/pixels.hpp>
#include <bksge/core/render/texture_format.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <memory>
#include <ostream>
#include <vector>

namespace bksge
{

namespace render
{

class Texture : public Identifiable
{
public:
	using ExtentType = Extent2<bksge::uint32_t>;

	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	各メンバは以下のように初期化され、画像用のメモリを確保することはありません。
	 *	format			TextureFormat::kNone
	 *	width			0
	 *	height			0
	 *	mipmap_count	0
	 *	data			nullptr
	 */
	Texture(void);

	/**
	 *	@brief	コンストラクタ
	 *
	 *	format,extent,mipmap_countの情報を元に必要なメモリを確保し、
	 *	dataがnullptrでなければdataの指す先からコピーします。
	 *	dataの指す先のサイズやフォーマットが正しいかどうかは、呼び出す側が保証する必要があります。
	 *	dataがnullptrのときは確保したメモリ領域を初期化しません。必要に応じてFill関数などを使用してください。
	 */
	Texture(TextureFormat format, ExtentType const& extent, bksge::size_t mipmap_count, bksge::uint8_t const* data);

	/**
	 *	@brief	コンストラクタ
	 *
	 *	Texture(format, extent, mipmap_count, nullptr)	と同じです
	 */
	Texture(TextureFormat format, ExtentType const& extent, bksge::size_t mipmap_count);

	/**
	 *	@brief	コンストラクタ
	 *
	 *	Texture(format, extent, 1, data)	と同じです
	 */
	Texture(TextureFormat format, ExtentType const& extent, bksge::uint8_t const* data);

	/**
	 *	@brief	コンストラクタ
	 *
	 *	Texture(format, extent, 1, nullptr)	と同じです
	 */
	Texture(TextureFormat format, ExtentType const& extent);

	/**
	 *	@brief	フォーマットを取得します
	 */
	TextureFormat format(void) const;

	/**
	 *	@brief	幅と高さを取得します
	 */
	ExtentType const& extent(void) const;

	/**
	 *	@brief	横幅を取得します
	 */
	bksge::uint32_t width(void) const;

	/**
	 *	@brief	高さを取得します
	 */
	bksge::uint32_t height(void) const;

	/**
	 *	@brief	ミップマップの数を取得します
	 */
	bksge::size_t mipmap_count(void) const;

	/**
	 *	@brief	画像データのバイト数を取得します
	 */
//	bksge::size_t bytes(void) const;

	/**
	 *	@brief	画像データの１行のバイト数を取得します
	 */
	bksge::size_t stride(void) const;

	/**
	 *	@brief	画像データへのポインタを取得します
	 */
	bksge::uint8_t const* data(void) const;

	/**
	 *	@brief
	 */
	Pixels const& pixels(void) const;

private:
	TextureFormat			m_format;       ///< フォーマット
	ExtentType				m_extent;       ///< 幅と高さ
	bksge::size_t			m_mipmap_count; ///< ミップマップの数。オリジナル画像を含みます。
	std::shared_ptr<Pixels>	m_pixels;       ///< 画像データ

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_format);
		ar & BKSGE_SERIALIZATION_NVP(m_extent);
		ar & BKSGE_SERIALIZATION_NVP(m_mipmap_count);
		ar & BKSGE_SERIALIZATION_NVP(m_pixels);
	}
#endif
};

/**
 *	@brief	比較演算子
 */
bool operator==(Texture const& lhs, Texture const& rhs);
bool operator!=(Texture const& lhs, Texture const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Texture const& rhs)
{
	os	<< "{ "
		<< rhs.format() << ", "
		<< rhs.extent() << ", "
		<< rhs.mipmap_count() << ", "
		<< rhs.pixels()
		<< " }";

	return os;
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_TEXTURE_HPP
