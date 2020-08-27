///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Lewis Baker
// Licenced under MIT license. See LICENSE.txt for details.
///////////////////////////////////////////////////////////////////////////////

#include <cppcoro/write_only_file.hpp>

#if CPPCORO_OS_WINNT
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# include <Windows.h>

cppcoro::write_only_file cppcoro::write_only_file::open(
	io_service& ioService,
	const std::experimental::filesystem::path& path,
	file_open_mode openMode,
	file_share_mode shareMode,
	file_buffering_mode bufferingMode)
{
	return write_only_file(file::open(
		GENERIC_WRITE,
		ioService,
		path,
		openMode,
		shareMode,
		bufferingMode));
}

cppcoro::write_only_file::write_only_file(
	detail::win32::safe_handle&& fileHandle) noexcept
	: file(std::move(fileHandle))
	, writable_file(detail::win32::safe_handle{})
{
}

#endif // CPPCORO_OS_WINNT

#if CPPCORO_OS_LINUX
#include <fcntl.h>

cppcoro::write_only_file cppcoro::write_only_file::open(
	io_service& ioService,
	const std::filesystem::path& path,
	file_open_mode openMode,
	file_share_mode shareMode,
	file_buffering_mode bufferingMode)
{
	return write_only_file(file::open(
		O_WRONLY,
		ioService,
		path,
		openMode,
		shareMode,
		bufferingMode));
}

cppcoro::write_only_file::write_only_file(
	detail::linux::safe_file_data&& fileData) noexcept
	: file(std::move(fileData))
	, writable_file(detail::linux::safe_file_data{})
{
}

#endif // CPPCORO_OS_LINUX
