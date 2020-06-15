/**
 *	@file	node.hpp
 *
 *	@brief	Node クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_DRAW_NODE_HPP
#define BKSGE_CORE_DRAW_NODE_HPP

#include <bksge/core/draw/fwd/node_fwd.hpp>
#include <bksge/core/math/transform3.hpp>
//#include <bksge/fnd/serialization/access.hpp>
//#include <bksge/fnd/serialization/nvp.hpp>
//#include <bksge/fnd/serialization/vector.hpp>
//#include <bksge/fnd/serialization/shared_ptr.hpp>

namespace bksge
{

namespace draw
{

/**
 *	@brief
 */
class Node
{
public:
	using TransformType = Transform3<float>;
	using PositionType  = TransformType::PositionType;
	using RotationType  = TransformType::RotationType;
	using ScaleType     = TransformType::ScaleType;
	using Matrix4x4Type	= TransformType::Matrix4x4Type;

	/**
	 *	@brief
	 */
	Node(void);

	/**
	 *	@brief
	 */
	virtual ~Node();

	/**
	 *	@brief	子ノードを追加します
	 *
	 *	@param	node	追加する子ノード
	 *
	 *	nodeが既に他のノードの子供だった時は、
	 *	自動的にそのノードから切り離してから追加します
	 */
//	void AddChild(NodePtr const& node);

	/**
	 *	@brief
	 */
//	Node* GetParent(void);

	/**
	 *	@brief	子ノードのリストを取得します
	 */
//	NodeList const& GetChildren(void) const;

	/**
	 *	@brief	親からの相対位置を設定します
	 */
	void SetPosition(PositionType const& position);

	/**
	 *	@brief	親からの相対位置を取得します
	 */
	PositionType const& GetPosition(void) const;

	/**
	 *	@brief	親からの相対回転を設定します
	 */
	void SetRotation(RotationType const& rotation);

	/**
	 *	@brief	親からの相対回転を取得します
	 */
	RotationType const& GetRotation(void) const;

	/**
	 *	@brief	現在位置と注視点から姿勢を設定します
	 */
	void LookAt(PositionType const& lookat);

	/**
	 *	@brief	親からの相対拡縮を設定します
	 */
	void SetScale(ScaleType const& scale);

	/**
	 *	@brief	親からの相対拡縮を取得します
	 */
	ScaleType const& GetScale(void) const;

	/**
	 *	@brief	親の回転を継承するかどうかを設定します
	 */
	void SetInheritRotation(bool inherit);

	/**
	 *	@brief	親の回転を継承するかどうかを取得します
	 */
	bool GetInheritRotation(void) const;

	/**
	 *	@brief	親の拡縮を継承するかどうかを設定します
	 */
	void SetInheritScale(bool inherit);

	/**
	 *	@brief	親の拡縮を継承するかどうかを取得します
	 */
	bool GetInheritScale(void) const;

	/**
	 *	@brief	このノードのワールド変換行列を取得します
	 */
	Matrix4x4Type GetWorldMatrix(void) const;

	/**
	 *	@brief
	 */
	PositionType const& GetDerivedPosition(void) const;

	/**
	 *	@brief
	 */
	RotationType const& GetDerivedRotation(void) const;

	/**
	 *	@brief
	 */
	ScaleType const& GetDerivedScale(void) const;

	//template <typename F>
	//void Traverse(F f) const
	//{
	//	f(this);

	//	for (auto&& child : m_children)
	//	{
	//		child->Traverse(f);
	//	}
	//}

private:
	void UpdateFromParent(void) const;
	void SetParent(Node* parent);

	NodeWeakPtr				m_parent;
	NodeSharedPtrList		m_children;
	bool					m_inherit_rotation;
	bool					m_inherit_scale;
	TransformType			m_transform;
	mutable TransformType	m_derived_transform;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_parent);
		ar & BKSGE_SERIALIZATION_NVP(m_children);
		ar & BKSGE_SERIALIZATION_NVP(m_inherit_rotation);
		ar & BKSGE_SERIALIZATION_NVP(m_inherit_scale);
		ar & BKSGE_SERIALIZATION_NVP(m_transform);
		ar & BKSGE_SERIALIZATION_NVP(m_derived_transform);
	}
#endif
};

}	// namespace draw

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/draw/inl/node_inl.hpp>
#endif

#endif // BKSGE_CORE_DRAW_NODE_HPP
