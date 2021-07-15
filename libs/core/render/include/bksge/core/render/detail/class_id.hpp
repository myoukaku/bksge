/**
 *	@file	class_id.hpp
 *
 *	@brief	ClassId の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_CLASS_ID_HPP
#define BKSGE_CORE_RENDER_DETAIL_CLASS_ID_HPP

#include <bksge/core/render/detail/fwd/class_id_fwd.hpp>
#include <cstddef>
#include <typeinfo>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class ClassId
{
public:
	using value_type = std::size_t;

	explicit ClassId(value_type const& value);

	value_type const& value(void) const;

private:
	value_type	m_value;
};

template <typename T>
inline ClassId make_class_id(void)
{
	return ClassId(typeid(T).hash_code());
}

bool operator==(ClassId const& lhs, ClassId const& rhs);
bool operator!=(ClassId const& lhs, ClassId const& rhs);

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/class_id_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_CLASS_ID_HPP
