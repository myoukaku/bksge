/**
 *	@file	debug_report_callback_fwd.hpp
 *
 *	@brief	DebugReportCallback クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEBUG_REPORT_CALLBACK_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEBUG_REPORT_CALLBACK_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DebugReportCallback;
using DebugReportCallbackUniquePtr = bksge::unique_ptr<DebugReportCallback>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEBUG_REPORT_CALLBACK_FWD_HPP
