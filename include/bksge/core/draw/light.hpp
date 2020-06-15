/**
 *	@file	light.hpp
 *
 *	@brief	Light クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_LIGHT_HPP
#define BKSGE_CORE_DRAW_LIGHT_HPP

#include <bksge/core/draw/fwd/light_fwd.hpp>
#include <bksge/core/draw/node.hpp>
#include <bksge/core/math/color3.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief	ライトの基底となるクラス
 */
class Light : public Node
{
public:
	using ColorType = Color3f;
	using IntensityType = float;

	/**
	 *	@brief
	 */
	Light(void);

	/**
	 *	@brief
	 */
	virtual ~Light() override;

	/**
	 *	@brief	ライトの色を設定
	 */
	void SetColor(ColorType const& color);

	/**
	 *	@brief	ライトの色を取得
	 */
	ColorType const& GetColor(void) const;

	/**
	 *	@brief	ライトの強度を設定
	 */
	void SetIntensity(IntensityType intensity);

	/**
	 *	@brief	ライトの強度を取得
	 */
	IntensityType GetIntensity(void) const;

private:
	ColorType		m_color;		///< ライトの色
	IntensityType	m_intensity;	///< ライトの強度

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_BASE_OBJECT_NVP(Node);
		ar & BKSGE_SERIALIZATION_NVP(m_color);
		ar & BKSGE_SERIALIZATION_NVP(m_intensity);
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/light_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_LIGHT_HPP
