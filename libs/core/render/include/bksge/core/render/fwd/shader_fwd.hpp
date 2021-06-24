/**
 *	@file	shader_fwd.hpp
 *
 *	@brief	Shader の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FWD_SHADER_FWD_HPP
#define BKSGE_CORE_RENDER_FWD_SHADER_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

class Shader;
using ShaderPtr = bksge::shared_ptr<Shader>;

}	// namespace render

using render::Shader;
using render::ShaderPtr;

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_FWD_SHADER_FWD_HPP
