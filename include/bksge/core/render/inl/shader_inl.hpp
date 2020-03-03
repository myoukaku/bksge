/**
 *	@file	shader_inl.hpp
 *
 *	@brief	Shader の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_SHADER_INL_HPP
#define BKSGE_CORE_RENDER_INL_SHADER_INL_HPP

#include <bksge/core/render/shader.hpp>
#include <bksge/core/render/detail/shader_parameter.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <initializer_list>

namespace bksge
{

namespace render
{

BKSGE_INLINE
Shader::Shader(ShaderType type, std::initializer_list<bksge::pair<ShaderStage, char const*>> il)
	: Base()
	, m_type(type)
{
	for (auto i : il)
	{
		m_shaders[i.first] = i.second;
	}
}

BKSGE_INLINE
Shader::Shader(Shader&& rhs)
	: Base(bksge::move(rhs))
	, m_type(bksge::move(rhs.m_type))
	, m_shaders(bksge::move(rhs.m_shaders))
{}

BKSGE_INLINE Shader&
Shader::operator=(Shader&& rhs)
{
	Base::operator=(bksge::move(rhs));
	m_type = bksge::move(rhs.m_type);
	m_shaders = bksge::move(rhs.m_shaders);
	return *this;
}

BKSGE_INLINE ShaderType
Shader::type(void) const
{
	return m_type;
}

BKSGE_INLINE auto
Shader::begin(void) const -> const_iterator
{
	return m_shaders.begin();
}

BKSGE_INLINE auto
Shader::end(void) const -> const_iterator
{
	return m_shaders.end();
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_SHADER_INL_HPP
