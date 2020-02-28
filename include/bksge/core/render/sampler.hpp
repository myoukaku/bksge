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
#include <bksge/core/render/mipmap_mode.hpp>
#include <bksge/core/render/address_mode.hpp>
#include <bksge/core/render/border_color.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	テクスチャサンプラー
 */
class Sampler
{
public:
	Sampler(void);

	void SetMinFilter(FilterMode min_filter);
	void SetMagFilter(FilterMode mag_filter);
	void SetMipFilter(MipmapMode mip_filter);
	void SetAddressModeU(AddressMode address_mode_u);
	void SetAddressModeV(AddressMode address_mode_v);
	void SetAddressModeW(AddressMode address_mode_w);
	void SetBorderColor(BorderColor border_color);
	void SetMinLod(float min_lod);
	void SetMaxLod(float max_lod);

	FilterMode		min_filter(void)	 const;
	FilterMode		mag_filter(void)	 const;
	MipmapMode		mip_filter(void)	 const;
	AddressMode		address_mode_u(void) const;
	AddressMode		address_mode_v(void) const;
	AddressMode		address_mode_w(void) const;
	BorderColor		border_color(void)	 const;
	float			min_lod(void)		 const;
	float			max_lod(void)		 const;

	bool enable_mipmap(void) const;

private:
	FilterMode		m_min_filter;		///< 縮小フィルタの種類
	FilterMode		m_mag_filter;		///< 拡大フィルタの種類
	MipmapMode		m_mip_filter;		///< ミップマップフィルタの種類
	AddressMode		m_address_mode_u;	///< テクスチャ座標uのラップモード
	AddressMode		m_address_mode_v;	///< テクスチャ座標vのラップモード
	AddressMode		m_address_mode_w;	///< テクスチャ座標wのラップモード
	BorderColor     m_border_color;		///< 境界色
	float			m_min_lod;
	float			m_max_lod;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_min_filter);
		ar & BKSGE_SERIALIZATION_NVP(m_mag_filter);
		ar & BKSGE_SERIALIZATION_NVP(m_mip_filter);
		ar & BKSGE_SERIALIZATION_NVP(m_address_mode_u);
		ar & BKSGE_SERIALIZATION_NVP(m_address_mode_v);
		ar & BKSGE_SERIALIZATION_NVP(m_address_mode_w);
		ar & BKSGE_SERIALIZATION_NVP(m_border_color);
		ar & BKSGE_SERIALIZATION_NVP(m_min_lod);
		ar & BKSGE_SERIALIZATION_NVP(m_max_lod);
	}
};

/**
 *	@brief	比較演算子
 */
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
		   << rhs.min_filter() << ", "
		   << rhs.mag_filter() << ", "
		   << rhs.mip_filter() << ", "
		   << rhs.address_mode_u() << ", "
		   << rhs.address_mode_v() << ", "
		   << rhs.address_mode_w() << ", "
		   << rhs.border_color() << ", "
		   << rhs.min_lod() << ", "
		   << rhs.max_lod()
		   << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/sampler_inl.hpp>
#endif

#include <functional>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::Sampler>
{
	bksge::size_t operator()(bksge::render::Sampler const& arg) const
	{
		return bksge::hash_combine(
			arg.min_filter(),
			arg.mag_filter(),
			arg.mip_filter(),
			arg.address_mode_u(),
			arg.address_mode_v(),
			arg.address_mode_w(),
			arg.border_color(),
			arg.min_lod(),
			arg.max_lod());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_SAMPLER_HPP
