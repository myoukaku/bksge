/**
 *	@file	shader_program_map_inl.hpp
 *
 *	@brief	ShaderProgramMap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_INL_SHADER_PROGRAM_MAP_INL_HPP
#define BKSGE_RENDER_DETAIL_INL_SHADER_PROGRAM_MAP_INL_HPP

#include <bksge/render/detail/shader_program_map.hpp>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
ShaderProgramMap::ShaderProgramMap(ShaderProgramMap&& rhs)
	: m_value(std::move(rhs.m_value))
{
}

BKSGE_INLINE
ShaderProgramMap& ShaderProgramMap::operator=(ShaderProgramMap&& rhs)
{
	m_value = std::move(rhs.m_value);
	return *this;
}

BKSGE_INLINE
auto ShaderProgramMap::operator[](key_type const& key) -> mapped_type&
{
	return m_value[key];
}

BKSGE_INLINE
auto ShaderProgramMap::begin(void) const -> const_iterator
{
	return m_value.begin();
}

BKSGE_INLINE
auto ShaderProgramMap::end(void) const -> const_iterator
{
	return m_value.end();
}

BKSGE_INLINE
bool operator==(ShaderProgramMap const& lhs, ShaderProgramMap const& rhs)
{
	return lhs.m_value == rhs.m_value;
}

BKSGE_INLINE
bool operator!=(ShaderProgramMap const& lhs, ShaderProgramMap const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_DETAIL_INL_SHADER_PROGRAM_MAP_INL_HPP
