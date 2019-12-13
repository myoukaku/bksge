/**
 *	@file	class_id_inl.hpp
 *
 *	@brief	ClassId の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_CLASS_ID_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_CLASS_ID_INL_HPP

#include <bksge/core/render/detail/class_id.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ClassId::ClassId(value_type const& value)
	: m_value(value)
{}

BKSGE_INLINE
auto ClassId::value(void) const
-> value_type const&
{
	return m_value;
}

BKSGE_INLINE
bool operator==(ClassId const& lhs, ClassId const& rhs)
{
	return lhs.value() == rhs.value();
}

BKSGE_INLINE
bool operator!=(ClassId const& lhs, ClassId const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_CLASS_ID_INL_HPP
