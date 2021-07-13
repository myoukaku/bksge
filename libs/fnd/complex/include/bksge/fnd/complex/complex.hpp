/**
 *	@file	complex.hpp
 *
 *	@brief	complex の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPLEX_COMPLEX_HPP
#define BKSGE_FND_COMPLEX_COMPLEX_HPP

#include <bksge/fnd/complex/config.hpp>

#if defined(BKSGE_USE_STD_COMPLEX)

#include <complex>

namespace bksge
{

using std::complex;
using std::real;
using std::imag;
using std::abs;
using std::arg;
using std::norm;
using std::conj;
using std::proj;
using std::polar;
using std::exp;
using std::log;
using std::log10;
using std::pow;
using std::sqrt;
using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;
using std::sinh;
using std::cosh;
using std::tanh;
using std::asinh;
using std::acosh;
using std::atanh;

}	// namespace bksge

#else

#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/asinh.hpp>
#include <bksge/fnd/cmath/atan2.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/cosh.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/hypot.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/ldexp.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/log1p.hpp>
#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/sinh.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <ios>	// ios_base
#include <istream>
#include <limits>
#include <sstream>
#include <ostream>

namespace bksge
{

 // Forward declarations.
template <typename T> class complex;
template <> class complex<float>;
template <> class complex<double>;
template <> class complex<long double>;

template <typename T> T abs(complex<T> const&);
template <typename T> T arg(complex<T> const&);
template <typename T> BKSGE_CXX14_CONSTEXPR T norm(complex<T> const&);

template <typename T> BKSGE_CXX14_CONSTEXPR complex<T> conj(complex<T> const&);
template <typename T> complex<T> polar(T const&, T const& = 0);

template <typename T> complex<T> exp(complex<T> const&);
template <typename T> complex<T> log(complex<T> const&);
template <typename T> complex<T> log10(complex<T> const&);
template <typename T> complex<T> pow(complex<T> const&, int);
template <typename T> complex<T> pow(complex<T> const&, T const&);
template <typename T> complex<T> pow(complex<T> const&, complex<T> const&);
template <typename T> complex<T> pow(T const&, complex<T> const&);
template <typename T> complex<T> sqrt(complex<T> const&);

template <typename T> complex<T> sin(complex<T> const&);
template <typename T> complex<T> cos(complex<T> const&);
template <typename T> complex<T> tan(complex<T> const&);

template <typename T> complex<T> asin(complex<T> const&);
template <typename T> complex<T> acos(complex<T> const&);
template <typename T> complex<T> atan(complex<T> const&);

template <typename T> complex<T> sinh(complex<T> const&);
template <typename T> complex<T> cosh(complex<T> const&);
template <typename T> complex<T> tanh(complex<T> const&);

template <typename T> complex<T> asinh(complex<T> const&);
template <typename T> complex<T> acosh(complex<T> const&);
template <typename T> complex<T> atanh(complex<T> const&);

template <typename T>
class complex
{
public:
	typedef T value_type;

	BKSGE_CONSTEXPR complex(T const& re = T(), T const& im = T())
		: m_real(re)
		, m_imag(im)
	{}

	// Let the compiler synthesize the copy constructor
	BKSGE_CONSTEXPR complex(complex const&) = default;

	template <typename U>
	BKSGE_CONSTEXPR complex(complex<U> const& other)
		: m_real(static_cast<T>(other.real()))
		, m_imag(static_cast<T>(other.imag()))
	{}

	BKSGE_CONSTEXPR T real() const { return m_real; }

	BKSGE_CONSTEXPR T imag() const { return m_imag; }

	BKSGE_CXX14_CONSTEXPR void real(T val) { m_real = val; }

	BKSGE_CXX14_CONSTEXPR void imag(T val) { m_imag = val; }

	BKSGE_CXX14_CONSTEXPR complex<T>& operator=(T const& re)
	{
		m_real = re;
		m_imag = T();
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex<T>& operator+=(T const& re)
	{
		m_real += re;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex<T>& operator-=(T const& re)
	{
		m_real -= re;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex<T>& operator*=(T const& re)
	{
		m_real *= re;
		m_imag *= re;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex<T>& operator/=(T const& re)
	{
		m_real /= re;
		m_imag /= re;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename U>
	BKSGE_CXX14_CONSTEXPR complex<T>& operator=(complex<U> const& other)
	{
		m_real = static_cast<T>(other.real());
		m_imag = static_cast<T>(other.imag());
		return *this;
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR complex<T>& operator+=(complex<U> const& other)
	{
		m_real += static_cast<T>(other.real());
		m_imag += static_cast<T>(other.imag());
		return *this;
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR complex<T>& operator-=(complex<U> const& other)
	{
		m_real -= static_cast<T>(other.real());
		m_imag -= static_cast<T>(other.imag());
		return *this;
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR complex<T>& operator*=(complex<U> const& other)
	{
		T const r = static_cast<T>(m_real * other.real() - m_imag * other.imag());
		m_imag    = static_cast<T>(m_real * other.imag() + m_imag * other.real());
		m_real    = r;
		return *this;
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR complex<T>& operator/=(complex<U> const& other)
	{
		T const r = m_real * other.real() + m_imag * other.imag();
		T const n = bksge::norm(other);
		m_imag = (m_imag * other.real() - m_real * other.imag()) / n;
		m_real = r / n;
		return *this;
	}

private:
	T m_real;
	T m_imag;
};

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator+(complex<T> const& lhs, complex<T> const& rhs)
{
	complex<T> r = lhs;
	r += rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator+(complex<T> const& lhs, T const& rhs)
{
	complex<T> r = lhs;
	r += rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator+(T const& lhs, complex<T> const& rhs)
{
	complex<T> r = rhs;
	r += lhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator-(complex<T> const& lhs, complex<T> const& rhs)
{
	complex<T> r = lhs;
	r -= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator-(complex<T> const& lhs, T const& rhs)
{
	complex<T> r = lhs;
	r -= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator-(T const& lhs, complex<T> const& rhs)
{
	complex<T> r = -rhs;
	r += lhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator*(complex<T> const& lhs, complex<T> const& rhs)
{
	complex<T> r = lhs;
	r *= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator*(complex<T> const& lhs, T const& rhs)
{
	complex<T> r = lhs;
	r *= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator*(T const& lhs, complex<T> const& rhs)
{
	complex<T> r = rhs;
	r *= lhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator/(complex<T> const& lhs, complex<T> const& rhs)
{
	complex<T> r = lhs;
	r /= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator/(complex<T> const& lhs, T const& rhs)
{
	complex<T> r = lhs;
	r /= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator/(T const& lhs, complex<T> const& rhs)
{
	complex<T> r = lhs;
	r /= rhs;
	return r;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator+(complex<T> const& x)
{
	return x;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
operator-(complex<T> const& x)
{
	return complex<T>(-x.real(), -x.imag());
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(complex<T> const& lhs, complex<T> const& rhs)
{
	return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(complex<T> const& lhs, T const& rhs)
{
	return lhs.real() == rhs && lhs.imag() == T();
}

#if !defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(T const& lhs, complex<T> const& rhs)
{
	return lhs == rhs.real() && T() == rhs.imag();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(complex<T> const& lhs, complex<T> const& rhs)
{
	return lhs.real() != rhs.real() || lhs.imag() != rhs.imag();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(complex<T> const& lhs, T const& rhs)
{
	return lhs.real() != rhs || lhs.imag() != T();
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(T const& lhs, complex<T> const& rhs)
{
	return lhs != rhs.real() || T() != rhs.imag();
}

#endif

template <typename T, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, complex<T>& x)
{
	bool fail = true;
	CharT ch;
	if (is >> ch)
	{
		if (Traits::eq(ch, is.widen('(')))
		{
			T u;
			if (is >> u >> ch)
			{
				CharT const rparen = is.widen(')');
				if (Traits::eq(ch, rparen))
				{
					x = u;
					fail = false;
				}
				else if (Traits::eq(ch, is.widen(',')))
				{
					T v;
					if (is >> v >> ch)
					{
						if (Traits::eq(ch, rparen))
						{
							x = complex<T>(u, v);
							fail = false;
						}
						else
						{
							is.putback(ch);
						}
					}
				}
				else
				{
					is.putback(ch);
				}
			}
		}
		else
		{
			is.putback(ch);
			T u;
			if (is >> u)
			{
				x = u;
				fail = false;
			}
		}
	}

	if (fail)
	{
		is.setstate(std::ios_base::failbit);
	}

	return is;
}

///  Insertion operator for complex values.
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, complex<T> const& x)
{
	std::basic_ostringstream<CharT, Traits> ss;
	ss.flags(os.flags());
	ss.imbue(os.getloc());
	ss.precision(os.precision());
	ss << '(' << x.real() << ',' << x.imag() << ')';
	return os << ss.str();
}

namespace detail
{

template <typename T>
struct complex_base
{
	T m_value[2];

	BKSGE_CONSTEXPR T GetReal() const { return m_value[0]; }
	BKSGE_CONSTEXPR T GetImag() const { return m_value[1]; }
	BKSGE_CXX14_CONSTEXPR void SetReal(T v) { m_value[0] = v; }
	BKSGE_CXX14_CONSTEXPR void SetImag(T v) { m_value[1] = v; }

	BKSGE_CXX14_CONSTEXPR void Assign(T const& rhs)
	{
		m_value[0] = rhs;
		m_value[1] = 0;
	}
	BKSGE_CXX14_CONSTEXPR void Add(T const& rhs)
	{
		m_value[0] += rhs;
	}
	BKSGE_CXX14_CONSTEXPR void Sub(T const& rhs)
	{
		m_value[0] -= rhs;
	}
	BKSGE_CXX14_CONSTEXPR void Mul(T const& rhs)
	{
		m_value[0] *= rhs;
		m_value[1] *= rhs;
	}
	BKSGE_CXX14_CONSTEXPR void Div(T const& rhs)
	{
		m_value[0] /= rhs;
		m_value[1] /= rhs;
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR void Assign(complex<U> const& rhs)
	{
		m_value[0] = static_cast<T>(rhs.real());
		m_value[1] = static_cast<T>(rhs.imag());
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR void Add(complex<U> const& rhs)
	{
		m_value[0] += static_cast<T>(rhs.real());
		m_value[1] += static_cast<T>(rhs.imag());
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR void Sub(complex<U> const& rhs)
	{
		m_value[0] -= static_cast<T>(rhs.real());
		m_value[1] -= static_cast<T>(rhs.imag());
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR void Mul(complex<U> const& rhs)
	{
		auto const re = static_cast<T>(rhs.real());
		auto const im = static_cast<T>(rhs.imag());

		T const tmp = m_value[0] * re - m_value[1] * im;
		m_value[1]  = m_value[0] * im + m_value[1] * re;
		m_value[0]  = tmp;
	}

	template <typename U>
    BKSGE_CXX14_CONSTEXPR void Div(complex<U> const& rhs)
	{
        auto const re = static_cast<T>(rhs.real());
        auto const im = static_cast<T>(rhs.imag());

        if (bksge::isnan(re) || bksge::isnan(im))
		{
			// set NaN result
            m_value[0] = std::numeric_limits<T>::quiet_NaN();
            m_value[1] = std::numeric_limits<T>::quiet_NaN();
        }
		else if (bksge::abs(im) < bksge::abs(re))
		{
			// |rhs.imag()| < |rhs.real()|
            T const wr = im / re;
            T const wd = re + wr * im;

            if (bksge::isnan(wd) || wd == 0)
			{
				// set NaN result
                m_value[0] = std::numeric_limits<T>::quiet_NaN();
                m_value[1] = std::numeric_limits<T>::quiet_NaN();
            }
			else
			{
				// compute representable result
                T const tmp = (m_value[0] + m_value[1] * wr) / wd;
                m_value[1]  = (m_value[1] - m_value[0] * wr) / wd;
                m_value[0]  = tmp;
            }
        }
		else if (im == 0)
		{
			// set NaN result
            m_value[0] = std::numeric_limits<T>::quiet_NaN();
            m_value[1] = std::numeric_limits<T>::quiet_NaN();
        }
		else
		{
			// 0 < |rhs.real()| <= |rhs.imag()|
            T const wr = re / im;
            T const wd = im + wr * re;

            if (bksge::isnan(wd) || wd == 0)
			{
				// set NaN result
                m_value[0] = std::numeric_limits<T>::quiet_NaN();
                m_value[1] = std::numeric_limits<T>::quiet_NaN();
            }
			else
			{
				// compute representable result
                T const tmp = (m_value[0] * wr + m_value[1]) / wd;
                m_value[1]  = (m_value[1] * wr - m_value[0]) / wd;
                m_value[0]  = tmp;
            }
        }
    }
};

}	// namespace detail

template <>
class complex<float> : private detail::complex_base<float>
{
private:
	using base = detail::complex_base<float>;

public:
	using value_type = float;

	BKSGE_CONSTEXPR complex(float re = 0.0f, float im = 0.0f)
		: base{re, im} {}

	explicit BKSGE_CONSTEXPR complex(complex<double> const&);
	explicit BKSGE_CONSTEXPR complex(complex<long double> const&);

	BKSGE_CONSTEXPR float real() const { return GetReal(); }

	BKSGE_CONSTEXPR float imag() const { return GetImag(); }

	BKSGE_CXX14_CONSTEXPR void real(float val) { SetReal(val); }

	BKSGE_CXX14_CONSTEXPR void imag(float val) { SetImag(val); }

	BKSGE_CXX14_CONSTEXPR complex& operator=(float re)
	{
		Assign(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator+=(float re)
	{
		Add(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator-=(float re)
	{
		Sub(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator*=(float re)
	{
		Mul(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator/=(float re)
	{
		Div(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator=(complex<T> const& other)
	{
		Assign(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator+=(complex<T> const& other)
	{
		Add(other);
		return *this;
	}

	template <class T>
	BKSGE_CXX14_CONSTEXPR complex& operator-=(complex<T> const& other)
	{
		Sub(other);
		return *this;
	}

	template <class T>
	BKSGE_CXX14_CONSTEXPR complex& operator*=(complex<T> const& other)
	{
		Mul(other);
		return *this;
	}

	template <class T>
	BKSGE_CXX14_CONSTEXPR complex& operator/=(complex<T> const& other)
	{
		Div(other);
		return *this;
	}
};

template <>
class complex<double> : private detail::complex_base<double>
{
private:
	using base = detail::complex_base<double>;

public:
	using value_type = double;

	BKSGE_CONSTEXPR complex(double re = 0.0, double im = 0.0)
		: base{re, im} {}

	BKSGE_CONSTEXPR complex(complex<float> const& other)
		: base{other.real(), other.imag()} {}

	explicit BKSGE_CONSTEXPR complex(complex<long double> const&);

	BKSGE_CONSTEXPR double real() const { return GetReal(); }

	BKSGE_CONSTEXPR double imag() const { return GetImag(); }

	BKSGE_CXX14_CONSTEXPR void real(double val) { SetReal(val); }

	BKSGE_CXX14_CONSTEXPR void imag(double val) { SetImag(val); }

	BKSGE_CXX14_CONSTEXPR complex& operator=(double re)
	{
		Assign(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator+=(double re)
	{
		Add(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator-=(double re)
	{
		Sub(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator*=(double re)
	{
		Mul(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator/=(double re)
	{
		Div(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator=(complex<T> const& other)
	{
		Assign(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator+=(complex<T> const& other)
	{
		Add(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator-=(complex<T> const& other)
	{
		Sub(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator*=(complex<T> const& other)
	{
		Mul(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator/=(complex<T> const& other)
	{
		Div(other);
		return *this;
	}
};

template <>
class complex<long double> : private detail::complex_base<long double>
{
private:
	using base = detail::complex_base<long double>;

public:
	using value_type = long double;

	BKSGE_CONSTEXPR complex(long double re = 0.0L, long double im = 0.0L)
		: base{re, im} {}

	BKSGE_CONSTEXPR complex(complex<float> const& other)
		: base{other.real(), other.imag()} {}

	BKSGE_CONSTEXPR complex(complex<double> const& other)
		: base{other.real(), other.imag()} {}

	BKSGE_CONSTEXPR long double real() const { return GetReal(); }

	BKSGE_CONSTEXPR long double imag() const { return GetImag(); }

	BKSGE_CXX14_CONSTEXPR void real(long double val) { SetReal(val); }

	BKSGE_CXX14_CONSTEXPR void imag(long double val) { SetImag(val); }

	BKSGE_CXX14_CONSTEXPR complex& operator=(long double re)
	{
		Assign(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator+=(long double re)
	{
		Add(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator-=(long double re)
	{
		Sub(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator*=(long double re)
	{
		Mul(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator/=(long double re)
	{
		Div(re);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR complex& operator=(complex const&) = default;

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator=(complex<T> const& other)
	{
		Assign(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator+=(complex<T> const& other)
	{
		Add(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator-=(complex<T> const& other)
	{
		Sub(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator*=(complex<T> const& other)
	{
		Mul(other);
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR complex& operator/=(complex<T> const& other)
	{
		Div(other);
		return *this;
	}
};

inline BKSGE_CONSTEXPR
complex<float>::complex(complex<double> const& other)
	: base{static_cast<float>(other.real()), static_cast<float>(other.imag())} {}

inline BKSGE_CONSTEXPR
complex<float>::complex(complex<long double> const& other)
	: base{static_cast<float>(other.real()), static_cast<float>(other.imag())} {}

inline BKSGE_CONSTEXPR
complex<double>::complex(complex<long double> const& other)
	: base{static_cast<double>(other.real()), static_cast<double>(other.imag())} {}

template <typename T>
inline BKSGE_CONSTEXPR T
real(complex<T> const& z)
{
	return z.real();
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
real(T x)
{
	return x;
}

template <typename T>
inline BKSGE_CONSTEXPR T
imag(complex<T> const& z)
{
	return z.imag();
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<T>
imag(T)
{
	return T();
}

template <typename T>
inline T
abs(complex<T> const& z)
{
	return bksge::hypot(z.real(), z.imag());
}

template <typename T>
inline T
arg(complex<T> const& z)
{
	return bksge::atan2(z.imag(), z.real());
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline bksge::float_promote_t<T>
arg(T x)
{
	using type = bksge::float_promote_t<T>;
	return bksge::signbit(x) ? bksge::pi_t<type>() : type();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
norm(complex<T> const& z)
{
	T const re = z.real();
	T const im = z.imag();
	return re * re + im * im;
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<T>
norm(T x)
{
	using type = bksge::float_promote_t<T>;
	return type(x) * type(x);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR complex<T>
conj(complex<T> const& z)
{
	return complex<T>(z.real(), -z.imag());
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline BKSGE_CXX14_CONSTEXPR bksge::complex<bksge::float_promote_t<T>>
conj(T x)
{
	using type = bksge::float_promote_t<T>;
	return bksge::complex<type>(x, -type());
}

template <typename T>
inline bksge::complex<T>
proj(bksge::complex<T> const& z)
{
	if (bksge::isinf(z.real()) || bksge::isinf(z.imag()))
	{
		return complex<T>(std::numeric_limits<T>::infinity(), bksge::copysign(T(0), z.imag()));
	}
	return z;
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T)>
inline bksge::complex<bksge::float_promote_t<T>>
proj(T x)
{
	using type = bksge::float_promote_t<T>;
	return bksge::proj(bksge::complex<type>(x));
}

template <typename T>
inline complex<T>
polar(T const& rho, T const& theta)
{
	BKSGE_ASSERT(rho >= 0);
	return complex<T>(rho * bksge::cos(theta), rho * bksge::sin(theta));
}

template <typename T>
inline complex<T>
exp(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (1,+0)
	if (bksge::iszero(re) && bksge::iszero(im) && !bksge::signbit(im))
	{
		return complex<T>(T(1.0), T(0.0));
	}

	// If z is (x,+∞) (for any finite x), the result is (NaN,NaN) and FE_INVALID is raised.
	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	if (bksge::isfinite(re))
	{
		if (im == +inf || bksge::isnan(im))
		{
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		// If z is (+∞,+0), the result is (+∞,+0)
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			return complex<T>(inf, T(0.0));
		}
		// If z is (+∞,y) (for any finite nonzero y), the result is +∞cis(y)
		if (bksge::isfinite(im) && !bksge::iszero(im))
		{
			return +inf * complex<T>(bksge::cos(im), bksge::sin(im));
		}
		// If z is (+∞,+∞), the result is (±∞,NaN) and FE_INVALID is raised (the sign of the real part is unspecified)
		// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
		if (im == +inf || bksge::isnan(im))
		{
			return complex<T>(inf, nan);
		}
	}

	if (re == -inf)
	{
		// If z is (-∞,y) (for any finite y), the result is +0cis(y)
		if (bksge::isfinite(im))
		{
			return T(+0.0) * complex<T>(bksge::cos(im), bksge::sin(im));
		}
		// If z is (-∞,+∞), the result is (±0,±0) (signs are unspecified)
		// If z is (-∞,NaN), the result is (±0,±0) (signs are unspecified)
		if (im == +inf || bksge::isnan(im))
		{
			return complex<T>(T(0.0), T(0.0));
		}
	}

	if (bksge::isnan(re))
	{
		// If z is (NaN,+0), the result is (NaN,+0)
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			return complex<T>(nan, T(+0.0));
		}
		// If z is (NaN,NaN), the result is (NaN,NaN)
		// If z is (NaN,y) (for any nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
		if (bksge::isnan(im) || !bksge::iszero(im))
		{
			return complex<T>(nan, nan);
		}
	}
#endif

	return bksge::polar<T>(bksge::exp(re), im);
}

template <typename T>
inline complex<T>
log(complex<T> const& z)
{
#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();
	auto const pi_ = bksge::pi_t<T>();

	auto const re = z.real();
	auto const im = z.imag();

	if (bksge::iszero(im) && !bksge::signbit(im))
	{
		if (bksge::iszero(re))
		{
			if (std::signbit(re))	// TODO
			{
				// If z is (-0,+0), the result is (-∞,π) and FE_DIVBYZERO is raised
				return complex<T>(-inf, pi_);
			}
			else
			{
				// If z is (+0,+0), the result is (-∞,+0) and FE_DIVBYZERO is raised
				return complex<T>(-inf, T(+0.0));
			}
		}
	}

	if (bksge::isfinite(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
			return complex<T>(+inf, pi_/2);
		}
		if (bksge::isnan(im))
		{
			// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any finite positive y), the result is (+∞,+0)
			return complex<T>(+inf, T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (+∞,π/4)
			return complex<T>(+inf, pi_/4);
		}
	}

	if (re == -inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (-∞,y) (for any finite positive y), the result is (+∞,π)
			return complex<T>(+inf, pi_);
		}
		if (im == +inf)
		{
			// If z is (-∞,+∞), the result is (+∞,3π/4)
			return complex<T>(+inf, pi_*3/4);
		}
	}

	if (bksge::isinf(re) && bksge::isnan(im))
	{
		// If z is (±∞,NaN), the result is (+∞,NaN)
		return complex<T>(+inf, nan);
	}

	if (bksge::isnan(re))
	{
		if (bksge::isfinite(im))
		{
			// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (im == +inf)
		{
			// If z is (NaN,+∞), the result is (+∞,NaN)
			return complex<T>(+inf, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	return complex<T>(bksge::log(bksge::abs(z)), bksge::arg(z));
}

template <typename T>
inline complex<T>
log10(complex<T> const& z)
{
	// TODO log10e_v
	return bksge::log(z) * static_cast<T>(0.43429448190325182765112891891660508L);// / bksge::log(T(10.0));
}

template <typename T>
inline complex<T>
pow(complex<T> const& x, complex<T> const& y)
{
	return x == T() ? T() : bksge::exp(y * bksge::log(x));
}

template <typename T>
bksge::complex<T>
pow(bksge::complex<T> const& x, T const& y)
{
	if (x == T())
	{
		return T();
	}

	if (x.imag() == T() && x.real() > T())
	{
		return bksge::pow(x.real(), y);
	}

	bksge::complex<T> t = bksge::log(x);
	return bksge::polar<T>(bksge::exp(y * t.real()), y * t.imag());
}

template <typename T>
inline bksge::complex<T>
pow(T const& x, bksge::complex<T> const& y)
{
	return x > T() ?
		bksge::polar<T>(bksge::pow(x, y.real()), y.imag() * bksge::log(x)) :
		bksge::pow(bksge::complex<T>(x), y);
}

template <typename T, typename U>
inline bksge::complex<bksge::float_promote_t<T, U>>
pow(bksge::complex<T> const& x, bksge::complex<U> const& y)
{
	using type = bksge::float_promote_t<T, U>;
	return bksge::pow(bksge::complex<type>(x), bksge::complex<type>(y));
}

template <typename T, BKSGE_REQUIRES_PARAM(bksge::arithmetic, U)>
inline bksge::complex<bksge::float_promote_t<T, U>>
pow(bksge::complex<T> const& x, const U& y)
{
	using type = bksge::float_promote_t<T, U>;
	return bksge::pow(bksge::complex<type>(x), type(y));
}

template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, T), typename U>
inline bksge::complex<bksge::float_promote_t<T, U>>
pow(T const& x, bksge::complex<U> const& y)
{
	using type = bksge::float_promote_t<T, U>;
	return bksge::pow(type(x), bksge::complex<type>(y));
}

template <typename T>
inline complex<T>
sqrt(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();

	if (bksge::iszero(re) && bksge::iszero(im) && !bksge::signbit(im))
	{
		// If z is (±0,+0), the result is (+0,+0)
		return complex<T>(T(+0.0), T(+0.0));
	}

	if (im == +inf)
	{
		// If z is (x,+∞), the result is (+∞,+∞) even if x is NaN
		return complex<T>(+inf, +inf);
	}

	if (bksge::isfinite(re) && bksge::isnan(im))
	{
		// If z is (x,NaN), the result is (NaN,NaN) (unless x is ±∞) and FE_INVALID may be raised
		return complex<T>(nan, nan);
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y), the result is (+∞,+0) for finite positive y
			return complex<T>(+inf, T(+0.0));
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (+∞,NaN)
			return complex<T>(+inf, nan);
		}
	}

	if (re == -inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (-∞,y), the result is (+0,+∞) for finite positive y
			return complex<T>(T(+0.0), +inf);
		}
		if (bksge::isnan(im))
		{
			// If z is (-∞,NaN), the result is (NaN,∞) (sign of imaginary part unspecified)
			return complex<T>(nan, inf);
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::isfinite(im))
		{
			// If z is (NaN,y) for finite y, the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	if (re == T())
	{
		T const t = bksge::sqrt(bksge::abs(im) / 2);
		return complex<T>(t, im < T() ? -t : t);
	}
	else
	{
		T const t = bksge::sqrt(2 * (bksge::abs(z) + bksge::abs(re)));
		T const u = t / 2;
		return re > T() ?
			complex<T>(u, im / t) :
			complex<T>(bksge::abs(im) / t, im < T() ? -u : u);
	}
}

template <typename T>
inline complex<T>
sin(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();
	return complex<T>(
		bksge::sin(re) * bksge::cosh(im),
		bksge::cos(re) * bksge::sinh(im));
}

template <typename T>
inline complex<T>
cos(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();
	return complex<T>(
		 bksge::cos(re) * bksge::cosh(im),
		-bksge::sin(re) * bksge::sinh(im));
}

template <typename T>
inline complex<T>
tan(complex<T> const& z)
{
	return bksge::sin(z) / bksge::cos(z);
}

template <typename T>
inline bksge::complex<T>
asin(bksge::complex<T> const& z)
{
	auto const t = bksge::asinh(bksge::complex<T>(-z.imag(), z.real()));
	return bksge::complex<T>(t.imag(), -t.real());
}

template <typename T>
inline bksge::complex<T>
acos(bksge::complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();
	auto const pi_ = bksge::pi_t<T>();

	if (bksge::iszero(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (±0,+0), the result is (π/2,-0)
			return complex<T>(pi_/2, T(-0.0));
		}
		if (bksge::isnan(im))
		{
			// If z is (±0,NaN), the result is (π/2,NaN)
			return complex<T>(pi_/2, nan);
		}
	}

	if (bksge::isfinite(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for any finite x), the result is (π/2,-∞)
			return complex<T>(pi_/2, -inf);
		}
		if (!bksge::iszero(re) && bksge::isnan(im))
		{
			// If z is (x,NaN) (for any nonzero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
			return complex<T>(nan, nan);
		}
	}

	if (re == -inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (-∞,y) (for any positive finite y), the result is (π,-∞)
			return complex<T>(pi_, -inf);
		}
		if (im == +inf)
		{
			// If z is (-∞,+∞), the result is (3π/4,-∞)
			return complex<T>(pi_*3/4, -inf);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any positive finite y), the result is (+0,-∞)
			return complex<T>(T(+0.0), -inf);
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (π/4,-∞)
			return complex<T>(pi_/4, -inf);
		}
	}

	if (bksge::isinf(re) && bksge::isnan(im))
	{
		// If z is (±∞,NaN), the result is (NaN,±∞) (the sign of the imaginary part is unspecified)
		return complex<T>(nan, inf);
	}

	if (bksge::isnan(re))
	{
		if (bksge::isfinite(im))
		{
			// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (im == +inf)
		{
			// If z is (NaN,+∞), the result is (NaN,-∞)
			return complex<T>(nan, -inf);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

    auto const arcbig = static_cast<T>(0.25) * bksge::sqrt(std::numeric_limits<T>::max());
	auto const x = bksge::sqrt(bksge::complex<T>(1 + re, -im));
	auto const y = bksge::sqrt(bksge::complex<T>(1 - re, -im));
	auto const xr = x.real();
	auto const xi = x.imag();
	auto const yr = y.real();
	auto const yi = y.imag();
	T alfa;
	T beta;

	if (arcbig < xr)
	{
		// real parts large
		alfa = xr;
		beta = yi + xi * (yr / alfa);
	}
	else if (arcbig < xi)
	{
		// imag parts large
		alfa = xi;
		beta = xr * (yi / alfa) + yr;
	}
	else if (xi < -arcbig)
	{
		// imag part of w large negative
		alfa = -xi;
		beta = xr * (yi / alfa) - yr;
	}
	else
	{
		// shouldn't overflow
		alfa = 0;
		beta = xr * yi + xi * yr; // Im(w * z)
	}

	T v = bksge::asinh(beta);
	if (alfa != 0)
	{
		if (0 <= v)
		{
			v += bksge::log(alfa);
		}
		else
		{
			v -= bksge::log(alfa); // asinh(a*b) = asinh(a)+log(b)
		}
	}

	T const u = 2 * bksge::atan2(yr, xr);

    return bksge::complex<T>(u, v);
}

template <typename T>
inline bksge::complex<T>
atan(bksge::complex<T> const& z)
{
	auto const x = bksge::atanh(bksge::complex<T>(-z.imag(), z.real()));
	return bksge::complex<T>(x.imag(), -x.real());
}

template <typename T>
inline complex<T>
sinh(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();

	if (bksge::iszero(re) && !bksge::signbit(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+0,+0), the result is (+0,+0)
			return complex<T>(T(+0.0), T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (+0,+∞), the result is (±0,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
			return complex<T>(T(0.0), nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (+0,NaN), the result is (±0,NaN)
			return complex<T>(T(0.0), nan);
		}
	}

	if (bksge::isfinite(re) && !bksge::signbit(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID is raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (x,NaN) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+∞,+0), the result is (+∞,+0)
			return complex<T>(+inf, T(+0.0));
		}
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any positive finite y), the result is +∞cis(y)
			return +inf * complex<T>(bksge::cos(im), bksge::sin(im));
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
			return complex<T>(inf, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
			return complex<T>(inf, nan);
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (NaN,+0), the result is (NaN,+0)
			return complex<T>(nan, T(+0.0));
		}
		if (bksge::isfinite(im) && !bksge::iszero(im))
		{
			// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	return complex<T>(
		bksge::sinh(re) * bksge::cos(im),
		bksge::cosh(re) * bksge::sin(im));
}

template <typename T>
inline complex<T>
cosh(complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();

	if (bksge::iszero(re) && !bksge::signbit(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+0,+0), the result is (1,+0)
			return complex<T>(T(1.0), T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (+0,+∞), the result is (NaN,±0) (the sign of the imaginary part is unspecified) and FE_INVALID is raised
			return complex<T>(nan, T(0.0));
		}
		if (bksge::isnan(im))
		{
			// If z is (+0,NaN), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
			return complex<T>(nan, T(0.0));
		}
	}

	if (bksge::isfinite(re) && !bksge::iszero(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (x,NaN) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+∞,+0), the result is (+∞,+0)
			return complex<T>(+inf, T(+0.0));
		}
		if (bksge::isfinite(im) && !bksge::iszero(im))
		{
			// If z is (+∞,y) (for any finite non-zero y), the result is +∞cis(y)
			return +inf * complex<T>(bksge::cos(im), bksge::sin(im));
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
			return complex<T>(inf, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (+∞,NaN)
			return complex<T>(+inf, nan);
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (NaN,+0), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
			return complex<T>(nan, T(0.0));
		}
		if (bksge::isfinite(im) && !bksge::iszero(im))
		{
			// If z is (NaN,+y) (for any finite non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	return complex<T>(
		bksge::cosh(re) * bksge::cos(im),
		bksge::sinh(re) * bksge::sin(im));
}

template <typename T>
inline complex<T>
tanh(complex<T> const& z)
{
#if defined(BKSGE_IEC_559_COMPLEX)
	auto const re = z.real();
	auto const im = z.imag();

	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();

	if (bksge::iszero(re) && !bksge::signbit(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+0,+0), the result is (+0,+0)
			return complex<T>(T(+0.0), T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (0,+∞) the result is (0,NaN) and FE_INVALID is raised
			return complex<T>(T(0.0), nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (0,NaN) the result is (0,NaN)
			return complex<T>(T(0.0), nan);
		}
	}

	if (bksge::isfinite(re) && !bksge::iszero(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (x,NaN) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any finite positive y), the result is (1,+0)
			return complex<T>(T(1.0), T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (1,±0) (the sign of the imaginary part is unspecified)
			return complex<T>(T(1.0), T(0.0));
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (1,±0) (the sign of the imaginary part is unspecified)
			return complex<T>(T(1.0), T(0.0));
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (NaN,+0), the result is (NaN,+0)
			return complex<T>(nan, T(0.0));
		}
		if (!bksge::iszero(im))
		{
			// If z is (NaN,y) (for any non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	return bksge::sinh(z) / bksge::cosh(z);
}

template <typename T>
inline bksge::complex<T>
asinh(bksge::complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();
	auto const pi_ = bksge::pi_t<T>();

	if (bksge::iszero(re) && !bksge::signbit(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+0,+0), the result is (+0,+0)
			return complex<T>(T(+0.0), T(+0.0));
		}
	}

	if (bksge::isfinite(re))
	{
		if (!bksge::signbit(re) && im == +inf)
		{
			// If z is (x,+∞) (for any positive finite x), the result is (+∞,π/2)
			return complex<T>(+inf, pi_/2);
		}
		if (bksge::isnan(im))
		{
			// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
			return complex<T>(+inf, T(+0.0));
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (+∞,π/4)
			return complex<T>(+inf, pi_/4);
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (+∞,NaN)
			return complex<T>(+inf, nan);
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (NaN,+0), the result is (NaN,+0)
			return complex<T>(nan, T(+0.0));
		}
		if (bksge::isfinite(im) && !bksge::iszero(im))
		{
			// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (im == +inf)
		{
			// If z is (NaN,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified)
			return complex<T>(inf, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	auto const arcbig = static_cast<T>(0.25) * bksge::sqrt(std::numeric_limits<T>::max());
	auto const x = bksge::sqrt(complex<T>(1 - im,  re));
	auto const y = bksge::sqrt(complex<T>(1 + im, -re));
	auto const xr = x.real();
	auto const xi = x.imag();
	auto const yr = y.real();
	auto const yi = y.imag();
	T alfa;
	T beta;

	if (arcbig < xr)
	{
		// real parts large
		alfa = xr;
		beta = xi * (yr / alfa) - yi;
	}
	else if (arcbig < xi)
	{
		// imag parts large
		alfa = xi;
		beta = yr - xr * (yi / alfa);
	}
	else if (xi < -arcbig)
	{
		// imag part of w large negative
		alfa = -xi;
		beta = -yr - xr * (yi / alfa);
	}
	else
	{
		// shouldn't overflow
		alfa = 0;
		beta = xi * yr - xr * yi; // Im(w * conj(z))
	}

	T u = bksge::asinh(beta);
	if (alfa != 0)
	{
		if (0 <= u)
		{
			u += bksge::log(alfa);
		}
		else
		{
			u -= bksge::log(alfa); // asinh(a*b) = asinh(a)+log(b)
		}
	}

	T const v = bksge::atan2(im, bksge::real(x * y));

	return complex<T>(u, v);
}

template <typename T>
inline bksge::complex<T>
acosh(bksge::complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();
	auto const pi_ = bksge::pi_t<T>();

	if (bksge::iszero(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (±0,+0), the result is (+0,π/2)
			return complex<T>(T(+0.0), pi_/2);
		}
	}

	if (bksge::isfinite(re))
	{
		if (im == +inf)
		{
			// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
			return complex<T>(+inf, pi_/2);
		}

		if (bksge::isnan(im))
		{
			if (bksge::iszero(re))
			{
				// If z is (0,NaN) the result is (NaN,π/2)
				return complex<T>(nan, pi_/2);
			}
			else
			{
				// If z is (x,NaN) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised.
				return complex<T>(nan, nan);
			}
		}
	}

	if (re == -inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (-∞,y) (for any positive finite y), the result is (+∞,π)
			return complex<T>(+inf, pi_);
		}
		if (im == +inf)
		{
			// If z is (-∞,+∞), the result is (+∞,3π/4)
			return complex<T>(+inf, pi_*3/4);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
			return complex<T>(+inf, T(+0.0));
		}
	}

	if (bksge::isinf(re) && bksge::isnan(im))
	{
		// If z is (±∞,NaN), the result is (+∞,NaN)
		return complex<T>(+inf, nan);
	}

	if (bksge::isnan(re))
	{
		if (bksge::isfinite(im))
		{
			// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised.
			return complex<T>(nan, nan);
		}
		if (im == +inf)
		{
			// If z is (NaN,+∞), the result is (+∞,NaN)
			return complex<T>(+inf, nan);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	auto const arcbig = static_cast<T>(0.25) * bksge::sqrt(std::numeric_limits<T>::max());
	auto const x = bksge::sqrt(bksge::complex<T>(re - 1, -im));
	auto const y = bksge::sqrt(bksge::complex<T>(re + 1,  im));
	auto const xr = x.real();
	auto const xi = x.imag();
	auto const yr = y.real();
	auto const yi = y.imag();
	T alfa;
	T beta;

	if (arcbig < xr)
	{
		// real parts large
		alfa = xr;
		beta = yr - xi * (yi / alfa);
	}
	else if (arcbig < xi)
	{
		// imag parts large
		alfa = xi;
		beta = xr * (yr / alfa) - yi;
	}
	else if (xi < -arcbig)
	{
		// imag part of w large negative
		alfa = -xi;
		beta = xr * (yr / alfa) + yi;
	}
	else
	{
		// shouldn't overflow
		alfa = 0;
		beta = xr * yr - xi * yi; // Re(w * z)
	}

	T u = bksge::asinh(beta);
	if (alfa != 0)
	{
		if (0 <= u)
		{
			u += bksge::log(alfa);
		}
		else
		{
			u -= bksge::log(alfa); // asinh(a*b) = asinh(a)+log(b)
		}
	}

	T const v = 2 * bksge::atan2(bksge::imag(bksge::sqrt(bksge::complex<T>(re - 1, im))), yr);

	return bksge::complex<T>(u, v);
}

template <typename T>
inline bksge::complex<T>
atanh(bksge::complex<T> const& z)
{
	auto const re = z.real();
	auto const im = z.imag();

	auto const inf = std::numeric_limits<T>::infinity();
#if defined(BKSGE_IEC_559_COMPLEX)
	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const pi_ = bksge::pi_t<T>();

	if (bksge::iszero(re) && !bksge::signbit(re))
	{
		if (bksge::iszero(im) && !bksge::signbit(im))
		{
			// If z is (+0,+0), the result is (+0,+0)
			return complex<T>(T(+0.0), T(+0.0));
		}
		if (bksge::isnan(im))
		{
			// If z is (+0,NaN), the result is (+0,NaN)
			return complex<T>(T(+0.0), nan);
		}
	}

	if (re == T(+1.0) && im == T(+0.0))
	{
		// If z is (+1,+0), the result is (+∞,+0) and FE_DIVBYZERO is raised
		return complex<T>(+inf, T(+0.0));
	}

	if (bksge::isfinite(re))
	{
		if (!bksge::signbit(re) && im == +inf)
		{
			// If z is (x,+∞) (for any finite positive x), the result is (+0,π/2)
			return complex<T>(T(+0.0), pi_/2);
		}
		if (!bksge::iszero(re) && bksge::isnan(im))
		{
			// If z is (x,NaN) (for any finite nonzero x), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
	}

	if (re == +inf)
	{
		if (bksge::isfinite(im) && !bksge::signbit(im))
		{
			// If z is (+∞,y) (for any finite positive y), the result is (+0,π/2)
			return complex<T>(T(+0.0), pi_/2);
		}
		if (im == +inf)
		{
			// If z is (+∞,+∞), the result is (+0,π/2)
			return complex<T>(T(+0.0), pi_/2);
		}
		if (bksge::isnan(im))
		{
			// If z is (+∞,NaN), the result is (+0,NaN)
			return complex<T>(T(+0.0), nan);
		}
	}

	if (bksge::isnan(re))
	{
		if (bksge::isfinite(im))
		{
			// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
			return complex<T>(nan, nan);
		}
		if (im == +inf)
		{
			// If z is (NaN,+∞), the result is (±0,π/2) (the sign of the real part is unspecified)
			return complex<T>(T(+0.0), pi_/2);
		}
		if (bksge::isnan(im))
		{
			// If z is (NaN,NaN), the result is (NaN,NaN)
			return complex<T>(nan, nan);
		}
	}
#endif

	auto const arcbig = static_cast<T>(0.25) * bksge::sqrt(std::numeric_limits<T>::max());
	constexpr T half_pi = bksge::pi_t<T>() / 2;

	auto const im_abs  = bksge::abs(im);
	auto const re_abs  = bksge::abs(re);

	T u;
	T v;

	if (arcbig < re_abs)
	{
		// |re| is large
		T const f = im / re_abs;

		u = 1 / re_abs / (1 + f * f);
		v = bksge::copysign(half_pi, im);
	}
	else if (arcbig < im_abs)
	{
		// |im| is large
		T const f = re_abs / im;

		u = f / im / (1 + f * f);
		v = bksge::copysign(half_pi, im);
	}
	else if (re_abs != 1)
	{
		// |re| is small
		T const refrom1 = 1 - re_abs;
		T const imeps2  = im_abs * im_abs;

		u = static_cast<T>(0.25) * bksge::log1p(4 * re_abs / (refrom1 * refrom1 + imeps2));
		v = static_cast<T>(0.50) * bksge::atan2(2 * im, refrom1 * (1 + re_abs) - imeps2);
	}
	else if (im == 0)
	{
		// {+/-1, 0)
		u = inf;
		v = im;
	}
	else
	{
		// {+/-1, nonzero)
		u = bksge::log(bksge::sqrt(bksge::sqrt(4 + im * im)) / bksge::sqrt(im_abs));
		v = bksge::copysign(static_cast<T>(0.50) * (half_pi + bksge::atan2(im_abs, T(2))), im);
	}

	u = bksge::copysign(u, re);

	return bksge::complex<T>(u, v);
}

inline namespace literals {
inline namespace complex_literals {

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4455);	// literal suffix identifiers that do not start with an underscore are reserved
BKSGE_WARNING_DISABLE_CLANG("-Wuser-defined-literals");
BKSGE_WARNING_DISABLE_GCC("-Wliteral-suffix");

BKSGE_CONSTEXPR bksge::complex<float>
operator""if (long double num)
{
	return bksge::complex<float>{0.0F, static_cast<float>(num)};
}

BKSGE_CONSTEXPR bksge::complex<float>
operator""if (unsigned long long num)
{
	return bksge::complex<float>{0.0F, static_cast<float>(num)};
}

BKSGE_CONSTEXPR bksge::complex<double>
operator""i(long double num)
{
	return bksge::complex<double>{0.0, static_cast<double>(num)};
}

BKSGE_CONSTEXPR bksge::complex<double>
operator""i(unsigned long long num)
{
	return bksge::complex<double>{0.0, static_cast<double>(num)};
}

BKSGE_CONSTEXPR bksge::complex<long double>
operator""il(long double num)
{
	return bksge::complex<long double>{0.0L, num};
}

BKSGE_CONSTEXPR bksge::complex<long double>
operator""il(unsigned long long num)
{
	return bksge::complex<long double>{0.0L, static_cast<long double>(num)};
}

BKSGE_WARNING_POP();

} // inline namespace complex_literals
} // inline namespace literals

} // namespace bksge

#endif

#endif // BKSGE_FND_COMPLEX_COMPLEX_HPP
