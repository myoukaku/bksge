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
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
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
	bksge::uint8_t		read_mask(void) const;
	bksge::uint8_t		write_mask(void) const;
	bksge::uint8_t		reference(void) const;
	ComparisonFunction	func(void) const;
	StencilOperation	fail_operation(void) const;
	StencilOperation	depth_fail_operation(void) const;
	StencilOperation	pass_operation(void) const;

	void SetEnable(bool enable);
	void SetReadMask(bksge::uint8_t mask);
	void SetWriteMask(bksge::uint8_t mask);
	void SetReference(bksge::uint8_t ref);
	void SetFunc(ComparisonFunction func);
	void SetFailOperation(StencilOperation op);
	void SetDepthFailOperation(StencilOperation op);
	void SetPassOperation(StencilOperation op);

private:
	bool				m_enable;
	bksge::uint8_t		m_read_mask;
	bksge::uint8_t		m_write_mask;
	bksge::uint8_t		m_reference;
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
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_enable);
		ar & BKSGE_SERIALIZATION_NVP(m_read_mask);
		ar & BKSGE_SERIALIZATION_NVP(m_write_mask);
		ar & BKSGE_SERIALIZATION_NVP(m_reference);
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
		<< static_cast<bksge::uint32_t>(rhs.read_mask()) << ", "
		<< static_cast<bksge::uint32_t>(rhs.write_mask()) << ", "
		<< static_cast<bksge::uint32_t>(rhs.reference()) << ", "
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

#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::StencilState>
{
	bksge::size_t operator()(bksge::render::StencilState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.read_mask(),
			arg.write_mask(),
			arg.reference(),
			arg.func(),
			arg.fail_operation(),
			arg.depth_fail_operation(),
			arg.pass_operation());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_STENCIL_STATE_HPP
