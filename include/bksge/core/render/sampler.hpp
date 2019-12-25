/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_SAMPLER_HPP
#define BKSGE_CORE_RENDER_SAMPLER_HPP

#include <bksge/core/render/fwd/sampler_fwd.hpp>
#include <bksge/core/render/filter_mode.hpp>
#include <bksge/core/render/wrap_mode.hpp>
#include <bksge/core/render/texture.hpp>
#include <bksge/core/render/detail/identifiable.hpp>
#include <bksge/core/math/color4.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/version.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	テクスチャサンプラー
 */
class Sampler : public Identifiable
{
public:
	Sampler(void);

	explicit Sampler(Texture const& source);

	void SetSource(Texture const& source);
	void SetMinFilter(FilterMode min_filter);
	void SetMagFilter(FilterMode mag_filter);
	void SetWrapS(WrapMode wrap_s);
	void SetWrapT(WrapMode wrap_t);
	void SetWrapR(WrapMode wrap_r);
	void SetBorderColor(Color4f const& border_color);

	Texture const&	source(void)		const;
	FilterMode		min_filter(void)	const;
	FilterMode		mag_filter(void)	const;
	WrapMode		wrap_s(void)		const;
	WrapMode		wrap_t(void)		const;
	WrapMode		wrap_r(void)		const;
	Color4f const&	border_color(void)	const;

private:
	Texture			m_source;		///< テクスチャ
	FilterMode		m_min_filter;	///< 縮小フィルタの種類
	FilterMode		m_mag_filter;	///< 拡大フィルタの種類
	WrapMode		m_wrap_s;		///< テクスチャ座標sのラップモード
	WrapMode		m_wrap_t;		///< テクスチャ座標tのラップモード
	WrapMode		m_wrap_r;		///< テクスチャ座標rのラップモード
	Color4f         m_border_color; ///< 境界色

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_source);
		ar & BKSGE_SERIALIZATION_NVP(m_min_filter);
		ar & BKSGE_SERIALIZATION_NVP(m_mag_filter);
		ar & BKSGE_SERIALIZATION_NVP(m_wrap_s);
		ar & BKSGE_SERIALIZATION_NVP(m_wrap_t);
		ar & BKSGE_SERIALIZATION_NVP(m_wrap_r);
		ar & BKSGE_SERIALIZATION_NVP(m_border_color);
	}
#endif
};

bool operator==(Sampler const& lhs, Sampler const& rhs);
bool operator!=(Sampler const& lhs, Sampler const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Sampler const& rhs)
{
	return os << "{ "
		   << rhs.source() << ", "
		   << rhs.min_filter() << ", "
		   << rhs.mag_filter() << ", "
		   << rhs.wrap_s() << ", "
		   << rhs.wrap_t() << ", "
		   << rhs.wrap_r() << ", "
		   << rhs.border_color()
		   << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_SAMPLER_HPP
