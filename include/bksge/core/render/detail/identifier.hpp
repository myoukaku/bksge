﻿/**
 *	@file	identifier.hpp
 *
 *	@brief	Identifier クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_IDENTIFIER_HPP
#define BKSGE_CORE_RENDER_DETAIL_IDENTIFIER_HPP

//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
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
	using ValueType = std::uint32_t;

	Identifier(void);

	ValueType value() const;

private:
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
};

bool operator==(Identifier const& lhs, Identifier const& rhs);
bool operator!=(Identifier const& lhs, Identifier const& rhs);
bool operator< (Identifier const& lhs, Identifier const& rhs);

}	// namespace render

}	// namespace bksge

#include <cstddef>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::Identifier>
{
	std::size_t operator()(bksge::render::Identifier const& arg) const
	{
		using type = bksge::render::Identifier::ValueType;
		return std::hash<type>{}(arg.value());
	}
};

}	// namespace std

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/identifier_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_IDENTIFIER_HPP