/**
 *	@file	depth_state.hpp
 *
 *	@brief	DepthState の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DEPTH_STATE_HPP
#define BKSGE_CORE_RENDER_DEPTH_STATE_HPP

#include <bksge/core/render/fwd/depth_state_fwd.hpp>
#include <bksge/core/render/comparison_function.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <ios>

namespace bksge
{

namespace render
{

/**
 *	@brief	デプステストの設定
 */
class DepthState
{
public:
	DepthState(void);

	bool				enable(void) const;
	bool				write(void) const;
	ComparisonFunction	func(void) const;

	void SetEnable(bool enable);
	void SetWrite(bool write);
	void SetFunc(ComparisonFunction func);

private:
	bool				m_enable;
	bool				m_write;
	ComparisonFunction	m_func;

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_enable);
		ar & BKSGE_SERIALIZATION_NVP(m_write);
		ar & BKSGE_SERIALIZATION_NVP(m_func);
	}
};

bool operator==(DepthState const& lhs, DepthState const& rhs);
bool operator!=(DepthState const& lhs, DepthState const& rhs);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, DepthState const& rhs)
{
	bksge::ios::flags_saver ifs(os);
	return os << std::boolalpha << "{ "
		<< rhs.enable() << ", "
		<< rhs.write() << ", "
		<< rhs.func() << " }";
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/depth_state_inl.hpp>
#endif

#include <functional>
#include <cstddef>
#include <bksge/fnd/functional/hash_combine.hpp>

namespace std
{

template<>
struct hash<bksge::render::DepthState>
{
	std::size_t operator()(bksge::render::DepthState const& arg) const
	{
		return bksge::hash_combine(
			arg.enable(),
			arg.write(),
			arg.func());
	}
};

}	// namespace std

#endif // BKSGE_CORE_RENDER_DEPTH_STATE_HPP
