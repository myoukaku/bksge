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
#include <utility>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Shader::Shader(void)
	: Base()
	, m_type()
{}

BKSGE_INLINE
Shader::Shader(std::string type)
	: Base()
	, m_type(std::move(type))
{}

BKSGE_INLINE
Shader::Shader(Shader&& rhs)
	: Base(std::move(rhs))
	, m_type(std::move(rhs.m_type))
	, m_program_map(std::move(rhs.m_program_map))
	, m_parameter_map(std::move(rhs.m_parameter_map))
{}

BKSGE_INLINE
Shader& Shader::operator=(Shader&& rhs)
{
	Base::operator=(std::move(rhs));
	m_type = std::move(rhs.m_type);
	m_program_map = std::move(rhs.m_program_map);
	m_parameter_map = std::move(rhs.m_parameter_map);
	return *this;
}

BKSGE_INLINE
void Shader::SetProgram(ShaderStage stage, std::string source)
{
	m_program_map[stage] = std::move(source);
}

BKSGE_INLINE
std::string const& Shader::type(void) const
{
	return m_type;
}

BKSGE_INLINE
ShaderProgramMap const& Shader::program_map(void) const
{
	return m_program_map;
}

BKSGE_INLINE
ShaderParameterMap const& Shader::parameter_map(void) const
{
	return m_parameter_map;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_SHADER_INL_HPP
