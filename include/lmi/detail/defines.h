#ifndef LMI_DEFINES_H
#define LMI_DEFINES_H

// TODO ARM NEON
namespace lmi
{
	const int simd_alignment =

#if defined(__SSE4_1__) && !defined(__AVX__)	//&& !defined(__AVX512__)
		16;
#elif defined(__AVX__)	//&& !defined(__AVX512__)
		32;
#elif /*defined(__AVX512__) ||*/ defined(__MIC__)
		64;
#else
		0;
#endif
}

#endif
