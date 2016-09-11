#ifndef LMI_H
#define LMI_H

#include <cmath>

#include "detail/matrix.h"
#include "detail/quaternion.h"
#include "detail/vector.h"

#include "algorithm/decomposition.h"
#include "gfx/transform.h"

#if defined(__SSE4_1__)
#include "detail/vector/sse.h"
//#include "detail/matrix/sse.h"
//#endif
#elif defined(__AVX__)
//#include "detail/vector/avx.h"
//#include "detail/matrix/avx.h"
#elif defined(__MIC__)
//#include "detail/vector/mic.h"
//#include "detail/matrix/mic.h"
#endif


#endif
