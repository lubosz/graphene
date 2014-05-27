/* graphene-macros.h: Public macros
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

#ifndef __GRAPHENE_MACROS_H__
#define __GRAPHENE_MACROS_H__

#if !defined(GRAPHENE_H_INSIDE) && !defined(GRAPHENE_COMPILATION)
#error "Only graphene.h can be included directly."
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _GRAPHENE_PUBLIC
#define _GRAPHENE_PUBLIC        extern
#endif

#define GRAPHENE_FLOAT_EPSILON  (1e-15)

#define GRAPHENE_PI             3.1415926535897932384626434f
#define GRAPHENE_PI_2           1.5707963267948966192313217f

#ifdef GRAPHENE_COMPILATION
# define GRAPHENE_PRIVATE_FIELD(type,name)      type name
#else
# define GRAPHENE_PRIVATE_FIELD(type,name)      type __graphene_private_##name
#endif

#if defined(__GNUC__)
# define GRAPHENE_ALIGN16  __attribute__((aligned(16)))
#elif defined(_MSC_VER)
# define GRAPHENE_ALIGN16  __declspec(align(16))
#else
# define GRAPHENE_ALIGN16
#endif

#ifdef __cplusplus
#define GRAPHENE_BEGIN_DECLS    extern "C" {
#define GRAPHENE_END_DECLS      }
#else
#define GRAPHENE_BEGIN_DECLS
#define GRAPHENE_END_DECLS
#endif

#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#define likely(x)       (__builtin_expect((x), 1))
#define unlikely(x)     (__builtin_expect((x), 0))
#endif

#if defined (__GNUC__) && defined (__cplusplus)
#define _GRAPHENE_STRFUNC       ((const char*) (__PRETTY_FUNCTION__))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define _GRAPHENE_STRFUNC       ((const char*) (__func__))
#elif defined (__GNUC__) || (defined(_MSC_VER) && (_MSC_VER > 1300))
#define _GRAPHENE_STRFUNC       ((const char*) (__FUNCTION__))
#else
#define _GRAPHENE_STRFUNC       ((const char*) ("???"))
#endif

#ifdef G_DISABLE_CHECKS
#define graphene_return_if_fail(x)
#define graphene_return_val_if_fail(x,res)
#else
#define graphene_return_if_fail(x) \
  if (likely (x)) { } \
  else { \
    fprintf (stderr, "Graphene: %s: '%s' failed\n", _GRAPHENE_STRFUNC, #x); \
    return; \
  }
#define graphene_return_val_if_fail(x,res) \
  if (likely (x)) { } \
  else { \
    fprintf (stderr, "Graphene: %s: '%s' failed\n", _GRAPHENE_STRFUNC, #x); \
    return (res); \
  }
#endif

#ifdef G_DISABLE_ASSERT
#define graphene_assert(x)
#define graphene_assert_not_reached()
#else
#define graphene_assert(x) \
  if (likely (x)) { } \
  else { \
    fprintf (stderr, "Graphene: %s: assertion '%s' failed\n", _GRAPHENE_STRFUNC, #x); \
    abort (); \
  }
#define graphene_assert_not_reached() \
  fprintf (stderr, "Graphene: %s: code should not be reached.\n", _GRAPHENE_STRFUNC)
#endif

#endif /* __GRAPHENE_MACROS_H__ */
