/**
 *	@file	pixels.hpp
 *
 *	@brief	Pixels の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_PIXELS_HPP
#define BKSGE_RENDER_DETAIL_PIXELS_HPP

//#include <bksge/serialization/access.hpp>
//#include <bksge/serialization/vector.hpp>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>

namespace bksge
{

namespace render
{

class Pixels
{
public:
	void resize(std::size_t size);

	void copy(void const* src, std::size_t size);

	std::uint8_t const* data(void) const;

	std::vector<std::uint8_t> const& value(void) const;

private:
	std::vector<std::uint8_t>	m_value;

private:
#if 0
	/**
	 *	@brief	シリアライズ
	 */
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, unsigned int /*version*/)
	{
		ar & BKSGE_SERIALIZATION_NVP(m_value);
	}
#endif
};

bool operator==(Pixels const& lhs, Pixels const& rhs);
bool operator!=(Pixels const& lhs, Pixels const& rhs);

template <typename CharT, typename Traits> inline
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, Pixels const& rhs)
{
	os << "{ ";

	for (auto& x : rhs.value())
	{
		os << x << ", ";
	}

	os << " }";
	return os;
}

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/pixels_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_PIXELS_HPP
