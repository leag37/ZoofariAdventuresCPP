// Filename: Platform.h
// Copyright 2015 Gael Huber
#pragma once

#define ZOOFARI_BEGIN_NAMESPACE(_namespace) \
	namespace _namespace					\
	{

#define ZOOFARI_END_NAMESPACE()	}

/*#define _ZOOFARI_CONCATENATE(_x, _y) _x ## _y

#define ZOOFARI_CONCATENATE(_x, _y)	_ZOOFARI_CONCATENATE(_x,_y)

#define _ZOOFARI_STRINGIFY(_x) #_x

#define ZOOFARI_STRINGIFY(_x) _ZOOFARI_STRINGIFY(_x)*/

#define ZOOFARI_INCLUDE(_include) #_include

#define ZOOFARI_INCLUDE_STL(_include) <_include>

#define ZOOFARI_TODO(x)

#define ZOOFARI_COPY_PROTECT(_class)				\
	_class(_class const &) = delete;				\
	_class & operator=(_class const &) = delete;

#define ZOOFARI_MOVE_PROTECT(_class)			\
	_class(_class &&) = delete;					\
	_class & operator=(_class &&) = delete;

#define ZOOFARI_INLINE inline

#if defined(ZOOFARI_WINDOWS)
    #define THREADLOCAL thread_local
    #define ZOOFARI_GLOBAL inline

#elif defined(ZOOFARI_DARWIN)
    #define THREADLOCAL __thread
    #define ZOOFARI_GLOBAL

#endif
