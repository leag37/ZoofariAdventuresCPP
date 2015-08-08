// Filename: Platform.h
// Copyright 2015 Gael Huber
#pragma once

#define ZOOFARI_BEGIN_NAMESPACE(_namespace) \
	namespace _namespace					\
	{

#define ZOOFARI_END_NAMESPACE()	}

#define _ZOOFARI_CONCATENATE(_x, _y) _x ## _y

#define ZOOFARI_CONCATENATE(_x, _y)	_ZOOFARI_CONCATENATE(_x, _y)

#define _ZOOFARI_STRINGIFY(_x) #_x

#define ZOOFARI_STRINGIFY(_x) _ZOOFARI_STRINGIFY(_x)

#define ZOOFARI_HEADER_EXTENSION .h
#define ZOOFARI_INLINE_EXTENSION .inl

#if defined(_WIN32) || defined(_WIN64)
#define ZOOFARI_PLATFORM_HEADER_EXTENSION _win.h
#define ZOOFARI_PLATFORM_INLINE_EXTENSION _win.inl
#endif

#define ZOOFARI_INCLUDE_HEADER(_include) ZOOFARI_STRINGIFY(ZOOFARI_CONCATENATE(_include, ZOOFARI_HEADER_EXTENSION))

#define ZOOFARI_INCLUDE_INLINE(_include) ZOOFARI_STRINGIFY(ZOOFARI_CONCATENATE(_include, ZOOFARI_INLINE_EXTENSION))

#define ZOOFARI_INCLUDE_STL(_include) <_include>

#define ZOOFARI_INCLUDE_PLATFORM_HEADER(_include) ZOOFARI_STRINGIFY(ZOOFARI_CONCATENATE(_include, ZOOFARI_PLATFORM_HEADER_EXTENSION))

#define ZOOFARI_INCLUDE_PLATFORM_INLINE(_include) ZOOFARI_STRINGIFY(ZOOFARI_CONCATENATE(_include, ZOOFARI_PLATFORM_INLINE_EXTENSION))

#define ZOOFARI_TODO(x)

#define ZOOFARI_COPY_PROTECT(_class)				\
	_class(_class const &) = delete;				\
	_class & operator=(_class const &) = delete;

#define ZOOFARI_MOVE_PROTECT(_class)			\
	_class(_class &&) = delete;					\
	_class & operator=(_class &&) = delete;