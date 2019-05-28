/**
 *	@file	shader_inl.hpp
 *
 *	@brief	Shader の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_SHADER_INL_HPP
#define BKSGE_RENDER_INL_SHADER_INL_HPP

#include <bksge/render/shader.hpp>
#include <bksge/render/detail/shader_parameter.hpp>
#include <initializer_list>
#include <string>
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Shader::Shader(std::initializer_list<std::pair<ShaderStage, char const*>> il)
	: Base()
{
	for (auto i : il)
	{
		m_program_map[i.first] = i.second;
	}
}

BKSGE_INLINE
Shader::Shader(Shader&& rhs)
	: Base(std::move(rhs))
	, m_program_map(std::move(rhs.m_program_map))
{}

BKSGE_INLINE
Shader& Shader::operator=(Shader&& rhs)
{
	Base::operator=(std::move(rhs));
	m_program_map = std::move(rhs.m_program_map);
	return *this;
}

BKSGE_INLINE
ShaderProgramMap const& Shader::program_map(void) const
{
	return m_program_map;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SHADER_INL_HPP
