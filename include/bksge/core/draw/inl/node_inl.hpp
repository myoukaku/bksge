/**
 *	@file	node_inl.hpp
 *
 *	@brief	Nodeの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_INL_NODE_INL_HPP
#define BKSGE_CORE_DRAW_INL_NODE_INL_HPP

#include <bksge/core/draw/node.hpp>
#include <bksge/core/math/vector3.hpp>
//#include <bksge/range/algorithm_ext/erase.hpp>
#include <bksge/fnd/algorithm/find.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>

namespace bksge
{

namespace draw
{

BKSGE_INLINE
Node::Node(void)
	: m_parent()
	, m_children()
	, m_inherit_rotation(true)
	, m_inherit_scale(true)
	, m_transform()
	, m_derived_transform()
{}

BKSGE_INLINE
Node::~Node()
{
}

//BKSGE_INLINE void
//Node::AddChild(NodePtr const& node)
//{
//	if (!node)
//	{
//		return;
//	}
//
//	if (bksge::find(bksge::begin(m_children), bksge::end(m_children), node)
//		== bksge::end(m_children))
//	{
//		m_children.push_back(node);
//		node->SetParent(this);
//	}
//}

//BKSGE_INLINE
//Node* Node::GetParent(void)
//{
//	return m_parent;
//}

//BKSGE_INLINE void
//Node::SetParent(Node* parent)
//{
//	m_parent = parent;
//}

//BKSGE_INLINE
//NodeList const& Node::GetChildren(void) const
//{
//	return m_children;
//}

BKSGE_INLINE void
Node::SetPosition(PositionType const& position)
{
	m_transform.position() = position;
}

BKSGE_INLINE auto
Node::GetPosition(void) const -> PositionType const&
{
	return m_transform.position();
}

BKSGE_INLINE void
Node::SetRotation(RotationType const& rotation)
{
	m_transform.rotation() = Normalized(rotation);
}

BKSGE_INLINE auto
Node::GetRotation(void) const -> RotationType const&
{
	return m_transform.rotation();
}

BKSGE_INLINE void
Node::LookAt(PositionType const& lookat)
{
	SetRotation(RotationType::MakeLookAt(
		GetDerivedPosition(),
		lookat,
		Vector3f{ 0, 1, 0 }));
}

BKSGE_INLINE void
Node::SetScale(ScaleType const& scale)
{
	m_transform.scale() = scale;
}

BKSGE_INLINE auto
Node::GetScale(void) const -> ScaleType const&
{
	return m_transform.scale();
}

BKSGE_INLINE void
Node::SetInheritRotation(bool inherit)
{
	m_inherit_rotation = inherit;
}

BKSGE_INLINE bool
Node::GetInheritRotation(void) const
{
	return m_inherit_rotation;
}

BKSGE_INLINE void
Node::SetInheritScale(bool inherit)
{
	m_inherit_scale = inherit;
}

BKSGE_INLINE bool
Node::GetInheritScale(void) const
{
	return m_inherit_scale;
}

BKSGE_INLINE auto
Node::GetWorldMatrix(void) const -> Matrix4x4Type
{
	UpdateFromParent();
	return m_derived_transform.GetMatrix4x4();
}

BKSGE_INLINE auto
Node::GetDerivedPosition(void) const -> PositionType const&
{
	UpdateFromParent();
	return m_derived_transform.position();
}

BKSGE_INLINE auto
Node::GetDerivedRotation(void) const -> RotationType const&
{
	UpdateFromParent();
	return m_derived_transform.rotation();
}

BKSGE_INLINE auto
Node::GetDerivedScale(void) const -> ScaleType const&
{
	UpdateFromParent();
	return m_derived_transform.scale();
}

BKSGE_INLINE void
Node::UpdateFromParent(void) const
{
	//if (!m_need_update_transform)
	//{
	//	return;
	//}

	//m_need_update_transform = false;

	if (m_parent.expired())
	{
		m_derived_transform = m_transform;
	}
	else
	{
		auto const& local_scale = m_transform.scale();
		auto const& local_rotation = m_transform.rotation();
		auto const& local_position = m_transform.position();

		auto parent = m_parent.lock();

		auto const& parent_scale = parent->GetDerivedScale();
		auto const& parent_rotation = parent->GetDerivedRotation();
		auto const& parent_position = parent->GetDerivedPosition();

		auto derived_scale = m_derived_transform.scale();
		auto derived_rotation = m_derived_transform.rotation();
		auto derived_position = m_derived_transform.position();

		if (m_inherit_scale)
		{
			derived_scale = parent_scale * local_scale;
		}
		else
		{
			derived_scale = local_scale;
		}

		if (m_inherit_rotation)
		{
			derived_rotation = parent_rotation * local_rotation;
		}
		else
		{
			derived_rotation = local_rotation;
		}

		derived_position =
			(local_position * parent_scale * parent_rotation) +
			parent_position;

		m_derived_transform.scale()    = derived_scale;
		m_derived_transform.rotation() = derived_rotation;
		m_derived_transform.position() = derived_position;
	}

	//m_world_matrix = Matrix4x4f::Compose(
	//					 GetDerivedPosition(),
	//					 GetDerivedScale(),
	//					 GetDerivedRotation());
}

}	// namespace draw

}	// namespace bksge

#endif // BKSGE_CORE_DRAW_INL_NODE_INL_HPP
