/**
 *	@file	mesh_fwd.hpp
 *
 *	@brief	Mesh クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_FWD_MESH_FWD_HPP
#define BKSGE_CORE_DRAW_FWD_MESH_FWD_HPP

#include <memory>
#include <vector>

namespace bksge
{

namespace draw
{

class Mesh;
using MeshSharedPtr = std::shared_ptr<Mesh>;
using MeshSharedPtrList = std::vector<MeshSharedPtr>;

}	// namespace draw

using draw::Mesh;

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_FWD_MESH_FWD_HPP
