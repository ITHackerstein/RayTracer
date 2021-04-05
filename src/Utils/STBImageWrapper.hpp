#pragma once

// Disables warnings when loading this library
// Remember to include this in a source file.

#ifdef _MSC_VER
	#pragma warning (push, 0)
#elif defined(__GNUC__) || defined(__GNUG__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wsign-compare"
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef _MSC_VER
	#pragma warning (pop)
#elif defined(__GNUC__) || defined(__GNUG__)
	#pragma GCC diagnostic pop
#endif
