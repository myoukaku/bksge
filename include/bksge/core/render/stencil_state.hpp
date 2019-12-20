/**
 *	@file	stencil_state.hpp
 *
 *	@brief	StencilState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_STENCIL_STATE_HPP

#include <bksge/core/render/fwd/stencil_state_fwd.hpp>
#include <bksge/core/render/comparison_function.hpp>
#include <bksge/core/render/stencil_operation.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <cstdint>
#include <ostream>
#include <ios>

namespace bksge
{

namespace render
{

/**
 *	@brief	ステンシルテストの設定
 */
class StencilState
{
public:
	StencilState(void);

	bool				enable(void) const;
	std::uint8_t		read_mask(void) const;
	std::uint8_t		write_mask(void) const;
	ComparisonFunction	func(void) const;
	StencilOperation	fail_operation(void) const;
	StencilOperation	depth_fail_operation(void) const;
	StencilOperation	pass_operation(void) const;

	void SetEnable(bool enable);
	void SetReadMask(std::uint8_t mask);
	void SetWriteMask(std::uint8_t mask);
	void SetFunc(ComparisonFunction func);
	void SetFailOperation(StencilOperation op);
	void SetDepthFailOperation(StencilOperation op);
	void SetPassOperation(StencilOperation op);

private:
	bool				m_enable;
	std::uint8_t		m_read_mask;
	std::uint8_t		m_write_mask;
	ComparisonFunction	m_func;
	StencilOperation	m_fail_operation;
	StencilOperation	m_depth_fail_operation;
	StencilOperation	m_pass_operation;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_enable);
		ar & BKSGE_SERIALIZATION_NVP(m_read_mask);
		ar & BKSGE_SERIALIZATION_NVP(m_write_mask);
		ar & BKSGE_SERIALIZATION_NVP(m_func);
		ar & BKSGE_SERIALIZATION_NVP(m_fail_operation);
		ar & BKSGE_SERIALIZATION_NVP(m_depth_fail_operation);
		ar & BKSGE_SERIALIZATION_NVP(m_pass_operation);
	}
};

bool operator==(StencilState const& lhs, StencilState const& rhs);
bool operator!=(StencilState const& lhs, StencilState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, StencilState const& rhs)
{
	bksge::ios::flags_saver ifs(os);
	return os << std::boolalpha << "{ "
		<< rhs.enable() << ", "
		<< static_cast<std::uint32_t>(rhs.read_mask()) << ", "
		<< static_cast<std::uint32_t>(rhs.write_mask()) << ", "
		<< rhs.func() << ", "
		<< rhs.fail_operation() << ", "
		<< rhs.depth_fail_operation() << ", "
		<< rhs.pass_operation() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/stencil_state_inl.hpp>
#endif

#include <cstddef>
#include <functional>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::StencilState>
{
	std::size_t operator()(bksge::render::StencilState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.read_mask(),
			arg.write_mask(),
			arg.func(),
			arg.fail_operation(),
			arg.depth_fail_operation(),
			arg.pass_operation());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_STENCIL_STATE_HPP
