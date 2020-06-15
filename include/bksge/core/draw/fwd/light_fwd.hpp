/**
 *	@file	light_fwd.hpp
 *
 *	@brief	Light クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_FWD_LIGHT_FWD_HPP
#define BKSGE_CORE_DRAW_FWD_LIGHT_FWD_HPP

#include <memory>
#include <vector>

namespace bksge
{

namespace draw
{

class Light;
using LightSharedPtr = std::shared_ptr<Light>;
using LightSharedPtrList = std::vector<LightSharedPtr>;

}	// namespace draw

using draw::Light;

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_FWD_LIGHT_FWD_HPP
