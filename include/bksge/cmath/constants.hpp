/**
 *	@file	constants.hpp
 *
 *	@brief	数学定数
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_CONSTANTS_HPP
#define BKSGE_CMATH_CONSTANTS_HPP

#include <bksge/config.hpp>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	π
 */
template <typename T>
inline BKSGE_CONSTEXPR T pi() BKSGE_NOEXCEPT
{
	return static_cast<T>(3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651L);
}

/**
 *	@brief	π / 2
 */
template <typename T>
inline BKSGE_CONSTEXPR T half_pi() BKSGE_NOEXCEPT
{
	return static_cast<T>(1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931401741267105853399107404326L);
}

/**
 *	@brief	π / 4
 */
template <typename T>
inline BKSGE_CONSTEXPR T quarter_pi() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.78539816339744830961566084581987572104929234984377645524373614807695410157155224965700870633552926699553702163L);
}

/**
 *	@brief	3 / 4 π
 */
template <typename T>
inline BKSGE_CONSTEXPR T three_quarters_pi() BKSGE_NOEXCEPT
{
	return static_cast<T>(2.35619449019234492884698253745962716314787704953132936573120844423086230471465674897102611900658780098661106488L);
}

/**
 *	@brief	1 / 3
 */
template <typename T>
inline BKSGE_CONSTEXPR T third() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333L);
}

/**
 *	@brief	ln(10)
 */
template <typename T>
inline BKSGE_CONSTEXPR T ln_ten() BKSGE_NOEXCEPT
{
	return static_cast<T>(2.30258509299404568401799145468436420760110148862877297603332790096757260967735248023599720508959829834196778404L);
}

/**
 *	@brief	ln(2)
 */
template <typename T>
inline BKSGE_CONSTEXPR T ln_two() BKSGE_NOEXCEPT
{
	return static_cast<T>(0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542001481021L);
}

/**
 *	@brief	ネイピア数 e
 */
template <typename T>
inline BKSGE_CONSTEXPR T e() BKSGE_NOEXCEPT
{
	return static_cast<T>(2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746639193L);
}

}	// namespace cmath

using cmath::pi;
using cmath::half_pi;
using cmath::quarter_pi;
using cmath::three_quarters_pi;
using cmath::third;
using cmath::ln_ten;
using cmath::ln_two;
using cmath::e;

}	// namespace bksge

#endif // BKSGE_CMATH_CONSTANTS_HPP
