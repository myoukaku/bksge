/**
 *	@file	material_fwd.hpp
 *
 *	@brief	Material クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_FWD_MATERIAL_FWD_HPP
#define BKSGE_CORE_DRAW_FWD_MATERIAL_FWD_HPP

#include <memory>

namespace bksge
{

namespace draw
{

class Material;
using MaterialSharedPtr = std::shared_ptr<Material>;

}	// namespace draw

using draw::Material;

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_FWD_MATERIAL_FWD_HPP
