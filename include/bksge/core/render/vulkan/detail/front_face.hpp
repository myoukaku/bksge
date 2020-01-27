/**
 *	@file	front_face.hpp
 *
 *	@brief	FrontFace クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FRONT_FACE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FRONT_FACE_HPP

#include <bksge/core/render/front_face.hpp>
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
class FrontFace
{
public:
	explicit FrontFace(bksge::FrontFace front_face);

	operator ::VkFrontFace() const;

private:
	::VkFrontFace	m_front_face;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/front_face_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FRONT_FACE_HPP
