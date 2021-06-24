/**
 *	@file	logic_operation.hpp
 *
 *	@brief	LogicOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_LOGIC_OPERATION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_LOGIC_OPERATION_HPP

#include <bksge/core/render/fwd/logic_operation_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class LogicOperation
{
public:
	explicit LogicOperation(bksge::LogicOperation logic_operation);

	operator ::VkLogicOp() const;

private:
	::VkLogicOp	m_logic_operation;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/logic_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_LOGIC_OPERATION_HPP
