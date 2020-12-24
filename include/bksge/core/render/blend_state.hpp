/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_BLEND_STATE_HPP

#include <bksge/core/render/fwd/blend_state_fwd.hpp>
#include <bksge/core/render/blend_operation.hpp>
#include <bksge/core/render/blend_factor.hpp>
#include <bksge/core/render/color_write_flag.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <ios>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンドの設定
 */
class BlendState
{
public:
	BlendState(void);

	bool			enable(void) const;
	BlendOperation	color_operation(void)  const;
	BlendFactor		color_src_factor(void) const;
	BlendFactor		color_dst_factor(void) const;
	BlendOperation	alpha_operation(void)  const;
	BlendFactor		alpha_src_factor(void) const;
	BlendFactor		alpha_dst_factor(void) const;
	ColorWriteFlag	color_write_mask(void) const;

	void SetEnable(bool enable);

	void SetOperation(BlendOperation op);
	void SetColorOperation(BlendOperation op);
	void SetAlphaOperation(BlendOperation op);

	void SetFactor(BlendFactor src, BlendFactor dst);
	void SetColorSrcFactor(BlendFactor factor);
	void SetColorDstFactor(BlendFactor factor);
	void SetAlphaSrcFactor(BlendFactor factor);
	void SetAlphaDstFactor(BlendFactor factor);

	void SetColorWriteFlag(ColorWriteFlag flag);

private:
	bool			m_enable;
	BlendOperation	m_color_operation;
	BlendFactor		m_color_src_factor;
	BlendFactor		m_color_dst_factor;
	BlendOperation	m_alpha_operation;
	BlendFactor		m_alpha_src_factor;
	BlendFactor		m_alpha_dst_factor;
	ColorWriteFlag	m_color_write_mask;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_enable);
		ar & BKSGE_SERIALIZATION_NVP(m_color_operation);
		ar & BKSGE_SERIALIZATION_NVP(m_color_src_factor);
		ar & BKSGE_SERIALIZATION_NVP(m_color_dst_factor);
		ar & BKSGE_SERIALIZATION_NVP(m_alpha_operation);
		ar & BKSGE_SERIALIZATION_NVP(m_alpha_src_factor);
		ar & BKSGE_SERIALIZATION_NVP(m_alpha_dst_factor);
		ar & BKSGE_SERIALIZATION_NVP(m_color_write_mask);
	}
};

bool operator==(BlendState const& lhs, BlendState const& rhs);
bool operator!=(BlendState const& lhs, BlendState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, BlendState const& rhs)
{
	bksge::ios::flags_saver ifs(os);
	return os << std::boolalpha << "{ "
		<< rhs.enable()           << ", "
		<< rhs.color_operation()  << ", "
		<< rhs.color_src_factor() << ", "
		<< rhs.color_dst_factor() << ", "
		<< rhs.alpha_operation()  << ", "
		<< rhs.alpha_src_factor() << ", "
		<< rhs.alpha_dst_factor() << ", "
		<< rhs.color_write_mask() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/blend_state_inl.hpp>
#endif

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::BlendState>
{
	bksge::size_t operator()(bksge::render::BlendState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.color_operation(),
			arg.color_src_factor(),
			arg.color_dst_factor(),
			arg.alpha_operation(),
			arg.alpha_src_factor(),
			arg.alpha_dst_factor(),
			arg.color_write_mask());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_BLEND_STATE_HPP
