/**
 *	@file	scene.hpp
 *
 *	@brief	Scene クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_SCENE_HPP
#define BKSGE_CORE_DRAW_SCENE_HPP

#include <bksge/core/draw/fwd/scene_fwd.hpp>
#include <bksge/core/draw/fwd/node_fwd.hpp>
#include <bksge/core/render/fwd/renderer_fwd.hpp>
#include <memory>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class Scene
{
public:
	/**
	 *
	 */
	Scene(void);

	/**
	 *
	 */
	~Scene();

	/**
	 *
	 */
	void Add(NodeSharedPtr const& node);

	/**
	 *
	 */
	void Render(bksge::Renderer* renderer) const;

private:
	struct Impl;
	std::unique_ptr<Impl>	m_impl;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/scene_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_SCENE_HPP
