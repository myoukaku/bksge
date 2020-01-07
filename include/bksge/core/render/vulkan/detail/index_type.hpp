/**
 *	@file	index_type.hpp
 *
 *	@brief	IndexType クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_TYPE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_TYPE_HPP

#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class IndexType
{
public:
	explicit IndexType(bksge::TypeEnum type);

	operator ::VkIndexType() const;

private:
	::VkIndexType	m_index_type;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/index_type_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INDEX_TYPE_HPP
