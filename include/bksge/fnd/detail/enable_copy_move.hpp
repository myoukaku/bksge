/**
 *	@file	enable_copy_move.hpp
 *
 *	@brief	enable_copy_move の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DETAIL_ENABLE_COPY_MOVE_HPP
#define BKSGE_FND_DETAIL_ENABLE_COPY_MOVE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <
	bool CopyConstructible, bool CopyAssignable,
	bool MoveConstructible, bool MoveAssignable,
	typename Tag = void
>
struct enable_copy_move {};

template <typename Tag>
struct enable_copy_move<false, true, true, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<true, false, true, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<false, false, true, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<true, true, false, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<false, true, false, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<true, false, false, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<false, false, false, true, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = default;
};

template <typename Tag>
struct enable_copy_move<true, true, true, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<false, true, true, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<true, false, true, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<false, false, true, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<true, true, false, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<false, true, false, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = default;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<true, false, false, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

template <typename Tag>
struct enable_copy_move<false, false, false, false, Tag>
{
	BKSGE_CONSTEXPR enable_copy_move()                                 BKSGE_NOEXCEPT = default;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move const&) BKSGE_NOEXCEPT = delete;
	BKSGE_CONSTEXPR explicit enable_copy_move(enable_copy_move&&)      BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move const&)               BKSGE_NOEXCEPT = delete;
	enable_copy_move& operator=(enable_copy_move&&)                    BKSGE_NOEXCEPT = delete;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_DETAIL_ENABLE_COPY_MOVE_HPP
