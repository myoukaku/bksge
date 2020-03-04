/**
 *	@file	node_fwd.hpp
 *
 *	@brief	Node クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_FWD_NODE_FWD_HPP
#define BKSGE_CORE_DRAW_FWD_NODE_FWD_HPP

#include <memory>
#include <vector>

namespace bksge
{

namespace draw
{

class Node;

using NodeWeakPtr = std::weak_ptr<Node>;
using NodeSharedPtr = std::shared_ptr<Node>;
using NodeSharedPtrList = std::vector<NodeSharedPtr>;

}	// namespace draw

using draw::Node;

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_FWD_NODE_FWD_HPP
