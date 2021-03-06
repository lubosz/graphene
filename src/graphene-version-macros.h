/* graphene-version.h: Versioning macros
 *
 * Copyright © 2014  Emmanuele Bassi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __GRAPHENE_VERSION_MACROS_H__
#define __GRAPHENE_VERSION_MACROS_H__

#if !defined(GRAPHENE_H_INSIDE) && !defined(GRAPHENE_COMPILATION)
#error "Only graphene.h can be included directly."
#endif

#include "graphene-version.h"

#define GRAPHENE_ENCODE_VERSION(major,minor,micro) \
  ((major) << 24 | (minor) << 16 | (micro) << 8)

#ifdef GRAPHENE_DISABLE_DEPRECATION_WARNINGS
# define GRAPHENE_DEPRECATED            _GRAPHENE_PUBLIC
# define GRAPHENE_DEPRECATED_FOR(f)     _GRAPHENE_PUBLIC
# define GRAPHENE_UNAVAILABLE(maj,min)  _GRAPHENE_PUBLIC
#else
# define GRAPHENE_DEPRECATED            G_DEPRECATED _GRAPHENE_PUBLIC
# define GRAPHENE_DEPRECATED_FOR(f)     G_DEPRECATED_FOR(f) _GRAPHENE_PUBLIC
# define GRAPHENE_UNAVAILABLE(maj,min)  G_UNAVAILABLE(maj,min) _GRAPHENE_PUBLIC
#endif

#define GRAPHENE_VERSION                \
  GRAPHENE_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION, \
                           GRAPHENE_MINOR_VERSION, \
                           GRAPHENE_MICRO_VERSION)

#define GRAPHENE_CHECK_VERSION(major,minor,micro) \
  ((major) > GRAPHENE_MAJOR_VERSION || \
   (major) == GRAPHENE_MAJOR_VERSION && (minor) > GRAPHENE_MINOR_VERSION || \
   (major) == GRAPHENE_MAJOR_VERSION && (minor) == GRAPHENE_MINOR_VERSION && (micro) >= GRAPHENE_MICRO_VERSION)

/* evaluates to the current stable release; for development cycles
 * this means the next stable target.
 */
#if (GRAPHENE_MINOR_VERSION == 99)
# define GRAPHENE_VERSION_CUR_STABLE    (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION + 1, 0))
#elif (GRAPHENE_MINOR_VERSION % 2)
# define GRAPHENE_VERSION_CUR_STABLE    (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION, GRAPHENE_MINOR_VERSION + 1))
#else
# define GRAPHENE_VERSION_CUR_STABLE    (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION, GRAPHENE_MINOR_VERSION))
#endif

/* evaluates to the previous stable version */
#if (GRAPHENE_MINOR_VERSION == 99)
# define GRAPHENE_VERSION_PREV_STABLE   (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION + 1, 0))
#elif (GRAPHENE_MINOR_VERSION % 2)
# define GRAPHENE_VERSION_PREV_STABLE   (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION, GRAPHENE_MINOR_VERSION - 1))
#else
# define GRAPHENE_VERSION_PREV_STABLE   (G_ENCODE_VERSION (GRAPHENE_MAJOR_VERSION, GRAPHENE_MINOR_VERSION - 2))
#endif

#ifndef GRAPHENE_VERSION_MIN_REQUIRED
# define GRAPHENE_VERSION_MIN_REQUIRED  (GRAPHENE_VERSION_1_0)
#endif

#ifndef GRAPHENE_VERSION_MAX_ALLOWED
# if GRAPHENE_VERSION_MIN_REQUIRED > GRAPHENE_VERSION_PREV_STABLE
#  define GRAPHENE_VERSION_MAX_ALLOWED  (GRAPHENE_VERSION_MIN_REQUIRED)
# else
#  define GRAPHENE_VERSION_MAX_ALLOWED  (GRAPHENE_VERSION_CUR_STABLE)
# endif
#endif

/* sanity checks */
#if GRAPHENE_VERSION_MAX_ALLOWED < GRAPHENE_VERSION_MIN_REQUIRED
# error "GRAPHENE_VERSION_MAX_ALLOWED must be >= GRAPHENE_VERSION_MIN_REQUIRED"
#endif
#if GRAPHENE_VERSION_MIN_REQUIRED < GRAPHENE_VERSION_1_0
# error "GRAPHENE_VERSION_MIN_REQUIRED must be >= GRAPHENE_VERSION_1_0"
#endif

/* version defines
 *
 * remember to add new macros at the beginning of each development cycle
 */

#define GRAPHENE_VERSION_1_0    (G_ENCODE_VERSION (1, 0))

/* unconditional */
#define GRAPHENE_DEPRECATED_IN_1_0              GRAPHENE_DEPRECATED
#define GRAPHENE_DEPRECATED_IN_1_0_FOR(f)       GRAPHENE_DEPRECATED_FOR(f)
#define GRAPHENE_AVAILABLE_IN_1_0               _GRAPHENE_PUBLIC

#endif /* __GRAPHENE_VERSION_MACROS_H__ */
