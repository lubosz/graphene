/* graphene-types.h: Shared types
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

#ifndef __GRAPHENE_TYPES_H__
#define __GRAPHENE_TYPES_H__

#if !defined(GRAPHENE_H_INSIDE) && !defined(GRAPHENE_COMPILATION)
#error "Only graphene.h can be included directly."
#endif

#include <glib.h>
#include "graphene-config.h"
#include "graphene-macros.h"
#include "graphene-version-macros.h"

G_BEGIN_DECLS

#define GRAPHENE_VEC2_LEN       2
#define GRAPHENE_VEC3_LEN       3
#define GRAPHENE_VEC4_LEN       4

typedef struct _graphene_vec2_t         graphene_vec2_t;
typedef struct _graphene_vec3_t         graphene_vec3_t;
typedef struct _graphene_vec4_t         graphene_vec4_t;

typedef struct _graphene_point_t        graphene_point_t;
typedef struct _graphene_size_t         graphene_size_t;
typedef struct _graphene_rect_t         graphene_rect_t;

typedef struct _graphene_point3d_t      graphene_point3d_t;
typedef struct _graphene_quad_t         graphene_quad_t;
typedef struct _graphene_quaternion_t   graphene_quaternion_t;

typedef struct _graphene_matrix_t       graphene_matrix_t;

G_END_DECLS

#endif /* __GRAPHENE_TYPES_H__ */
