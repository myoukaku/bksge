/**
 *	@file	identifier.hpp
 *
 *	@brief	Identifier クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_IDENTIFIER_HPP
#define BKSGE_RENDER_DETAIL_IDENTIFIER_HPP

//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/nvp.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class Identifier
{
public:
	Identifier(void);

private:
	using ValueType = std::uint32_t;

	ValueType m_value;

	class Generator;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif

private:
	friend bool operator==(Identifier const& lhs, Identifier const& rhs);
	friend bool operator< (Identifier const& lhs, Identifier const& rhs);
};

bool operator!=(Identifier const& lhs, Identifier const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/identifier_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_IDENTIFIER_HPP
