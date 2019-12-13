/**
 *	@file	identifier_inl.hpp
 *
 *	@brief	Identifier の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_IDENTIFIER_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_IDENTIFIER_INL_HPP

#include <bksge/core/render/detail/identifier.hpp>

namespace bksge
{

namespace render
{

class Identifier::Generator
{
public:
	static Generator& GetInstance()
	{
		static Generator instance;
		return instance;
	}

	ValueType Get()
	{
		return m_value++;
	}

private:
	Generator()
		: m_value(0)
	{}

	ValueType		m_value;
};

BKSGE_INLINE
Identifier::Identifier(void)
	: m_value(Generator::GetInstance().Get())
{}

BKSGE_INLINE auto
Identifier::value() const
-> ValueType
{
	return m_value;
}

BKSGE_INLINE
bool operator==(Identifier const& lhs, Identifier const& rhs)
{
	return lhs.value() == rhs.value();
}

BKSGE_INLINE
bool operator!=(Identifier const& lhs, Identifier const& rhs)
{
	return !(lhs == rhs);
}

BKSGE_INLINE
bool operator<(Identifier const& lhs, Identifier const& rhs)
{
	return lhs.value() < rhs.value();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_IDENTIFIER_INL_HPP
