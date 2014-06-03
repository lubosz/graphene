/* graphene-simd4x4f.h: 4x4 float vector operations
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

#ifndef __GRAPHENE_SIMD4X4F_COMMON_H__
#define __GRAPHENE_SIMD4X4F_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

static inline void
graphene_simd4x4f_sum (const graphene_simd4x4f_t *a,
                       graphene_simd4f_t         *res)
{
  graphene_simd4f_t s = graphene_simd4f_add (a->x, a->y);
  s = graphene_simd4f_add (s, a->z);
  s = graphene_simd4f_add (s, a->w);
  *res = s;
}

static inline void
graphene_simd4x4f_vec4_mul (const graphene_simd4x4f_t *m,
                            const graphene_simd4f_t   *v,
                            graphene_simd4f_t         *res)
{
  const graphene_simd4f_t v_x = graphene_simd4f_splat_x (*v);
  const graphene_simd4f_t v_y = graphene_simd4f_splat_y (*v);
  const graphene_simd4f_t v_z = graphene_simd4f_splat_z (*v);
  const graphene_simd4f_t v_w = graphene_simd4f_splat_w (*v);

  const graphene_simd4f_t s_x = graphene_simd4f_mul (m->x, v_x);
  const graphene_simd4f_t s_y = graphene_simd4f_mul (m->y, v_y);
  const graphene_simd4f_t s_z = graphene_simd4f_mul (m->z, v_z);
  const graphene_simd4f_t s_w = graphene_simd4f_mul (m->w, v_w);

  *res = graphene_simd4f_add (s_x, graphene_simd4f_add (s_y, graphene_simd4f_add (s_z, s_w)));
}

static inline void
graphene_simd4x4f_vec3_mul (const graphene_simd4x4f_t *m,
                            const graphene_simd4f_t   *v,
                            graphene_simd4f_t         *res)
{
  const graphene_simd4f_t v_x = graphene_simd4f_splat_x (*v);
  const graphene_simd4f_t v_y = graphene_simd4f_splat_y (*v);
  const graphene_simd4f_t v_z = graphene_simd4f_splat_z (*v);

  const graphene_simd4f_t s_x = graphene_simd4f_mul (m->x, v_x);
  const graphene_simd4f_t s_y = graphene_simd4f_mul (m->y, v_y);
  const graphene_simd4f_t s_z = graphene_simd4f_mul (m->z, v_z);

  *res = graphene_simd4f_add (s_x, graphene_simd4f_add (s_y, s_z));
}

static inline void
graphene_simd4x4f_point3_mul (const graphene_simd4x4f_t *m,
                              const graphene_simd4f_t   *p,
                              graphene_simd4f_t         *res)
{
  const graphene_simd4f_t v_x = graphene_simd4f_splat_x (*p);
  const graphene_simd4f_t v_y = graphene_simd4f_splat_y (*p);
  const graphene_simd4f_t v_z = graphene_simd4f_splat_z (*p);

  const graphene_simd4f_t s_x = graphene_simd4f_mul (m->x, v_x);
  const graphene_simd4f_t s_y = graphene_simd4f_mul (m->y, v_y);
  const graphene_simd4f_t s_z = graphene_simd4f_mul (m->z, v_z);

  *res = graphene_simd4f_add (s_x, graphene_simd4f_add (s_y, graphene_simd4f_add (s_z, m->w)));
}

static inline void
graphene_simd4x4f_transpose (const graphene_simd4x4f_t *s,
                             graphene_simd4x4f_t       *res)
{
  *res = *s;
  graphene_simd4x4f_transpose_in_place (res);
}

static inline void
graphene_simd4x4f_inv_ortho_vec3_mul (const graphene_simd4x4f_t *a,
                                      const graphene_simd4f_t   *b,
                                      graphene_simd4f_t         *res)
{
  graphene_simd4x4f_t transpose = *a;
  graphene_simd4f_t translation = *b;

  transpose.w = graphene_simd4f_init (0.f, 0.f, 0.f, 0.f);
  graphene_simd4x4f_transpose_in_place (&transpose);

  graphene_simd4x4f_vec3_mul (&transpose, &translation, res);
}

static inline void
graphene_simd4x4f_inv_ortho_point3_mul (const graphene_simd4x4f_t *a,
                                        const graphene_simd4f_t   *b,
                                        graphene_simd4f_t         *res)
{
  graphene_simd4f_t translation = graphene_simd4f_sub (*b, a->w);
  graphene_simd4x4f_t transpose = *a;

  transpose.w = graphene_simd4f_init (0.f, 0.f, 0.f, 0.f);
  graphene_simd4x4f_transpose_in_place (&transpose);

  graphene_simd4x4f_point3_mul (&transpose, &translation, res);
}

static inline void
graphene_simd4x4f_matrix_mul (const graphene_simd4x4f_t *a,
                              const graphene_simd4x4f_t *b,
                              graphene_simd4x4f_t       *res)
{
  graphene_simd4x4f_t transposed = *a;
  graphene_simd4x4f_transpose_in_place (&transposed);

  graphene_simd4x4f_vec4_mul (&transposed, &b->x, &res->x);
  graphene_simd4x4f_vec4_mul (&transposed, &b->y, &res->y);
  graphene_simd4x4f_vec4_mul (&transposed, &b->z, &res->z);
  graphene_simd4x4f_vec4_mul (&transposed, &b->w, &res->w);
}

static inline void
graphene_simd4x4f_init_perspective (graphene_simd4x4f_t *m,
                                    float                fovy_rad,
                                    float                aspect,
                                    float                z_near,
                                    float                z_far)
{
  float delta_z = z_far - z_near;
  float cotangent = tanf (GRAPHENE_PI_2 - fovy_rad * 0.5f);

  float a = cotangent / aspect;
  float b = cotangent;
  float c = -(z_far + z_near) / delta_z;
  float d = -2 * z_near * z_far / delta_z;

  m->x = graphene_simd4f_init (   a, 0.0f, 0.0f,  0.0f);
  m->y = graphene_simd4f_init (0.0f,    b, 0.0f,  0.0f);
  m->z = graphene_simd4f_init (0.0f, 0.0f,    c, -1.0f);
  m->w = graphene_simd4f_init (0.0f, 0.0f,    d,  0.0f);
}

static inline void
graphene_simd4x4f_init_ortho (graphene_simd4x4f_t *m,
                              float                left,
                              float                right,
                              float                bottom,
                              float                top,
                              float                z_near,
                              float                z_far)
{
  float delta_x = right - left;
  float delta_y = top - bottom;
  float delta_z = z_far - z_near;

  float a = 2.0f / delta_x;
  float b = -(right + left) / delta_x;
  float c = 2.0f / delta_y;
  float d = -(top + bottom) / delta_y;
  float e = -2.0f / delta_z;
  float f = -(z_far + z_near) / delta_z;

  m->x = graphene_simd4f_init (   a, 0.0f, 0.0f, 0.0f);
  m->y = graphene_simd4f_init (0.0f,    c, 0.0f, 0.0f);
  m->z = graphene_simd4f_init (0.0f, 0.0f,    e, 0.0f);
  m->w = graphene_simd4f_init (   b,    d,    f, 1.0f);
}

static inline void
graphene_simd4x4f_init_look_at (graphene_simd4x4f_t *m,
                                graphene_simd4f_t    eye,
                                graphene_simd4f_t    center,
                                graphene_simd4f_t    up)
{
  graphene_simd4f_t z_axis = graphene_simd4f_normalize3 (graphene_simd4f_sub (center, eye));
  graphene_simd4f_t x_axis = graphene_simd4f_normalize3 (graphene_simd4f_cross3 (z_axis, up));
  graphene_simd4f_t y_axis = graphene_simd4f_cross3 (x_axis, z_axis);
  float x, y, z;

  z_axis = graphene_simd4f_sub (graphene_simd4f_init_zero (), z_axis);

  x = -graphene_simd4f_get_x (graphene_simd4f_dot3 (x_axis, eye));
  y = -graphene_simd4f_get_x (graphene_simd4f_dot3 (y_axis, eye));
  z = -graphene_simd4f_get_x (graphene_simd4f_dot3 (z_axis, eye));

  m->x = x_axis;
  m->y = y_axis;
  m->z = z_axis;
  m->w = graphene_simd4f_init (0.0f, 0.0f, 0.0f, 1.0f);

  graphene_simd4x4f_transpose_in_place (m);

  m->w = graphene_simd4f_init (x, y, z, 1.0f);
}

static inline void
graphene_simd4x4f_perspective (graphene_simd4x4f_t *m,
                               float                depth)
{
  const graphene_simd4f_t m_x = m->x;
  const graphene_simd4f_t m_y = m->y;
  const graphene_simd4f_t m_z = m->z;
  const graphene_simd4f_t m_w = m->w;

  const float p0 = graphene_simd4f_get_z (m_x) + -1.0f / depth * graphene_simd4f_get_w (m_x);
  const float p1 = graphene_simd4f_get_z (m_y) + -1.0f / depth * graphene_simd4f_get_w (m_y);
  const float p2 = graphene_simd4f_get_z (m_z) + -1.0f / depth * graphene_simd4f_get_w (m_z);
  const float p3 = graphene_simd4f_get_z (m_w) + -1.0f / depth * graphene_simd4f_get_w (m_w);

  const graphene_simd4f_t p_x = graphene_simd4f_init (graphene_simd4f_get_x (m_x),
                                                      graphene_simd4f_get_y (m_x),
                                                      graphene_simd4f_get_z (m_x),
                                                      graphene_simd4f_get_w (m_w) + p0);
  const graphene_simd4f_t p_y = graphene_simd4f_init (graphene_simd4f_get_x (m_y),
                                                      graphene_simd4f_get_y (m_y),
                                                      graphene_simd4f_get_z (m_y),
                                                      graphene_simd4f_get_w (m_y) + p1);
  const graphene_simd4f_t p_z = graphene_simd4f_init (graphene_simd4f_get_x (m_z),
                                                      graphene_simd4f_get_y (m_z),
                                                      graphene_simd4f_get_z (m_z),
                                                      graphene_simd4f_get_w (m_z) + p2);
  const graphene_simd4f_t p_w = graphene_simd4f_init (graphene_simd4f_get_x (m_w),
                                                      graphene_simd4f_get_y (m_w),
                                                      graphene_simd4f_get_z (m_w),
                                                      graphene_simd4f_get_w (m_w) + p3);

  *m = graphene_simd4x4f_init (p_x, p_y, p_z, p_w);
}

static inline void
graphene_simd4x4f_translation (graphene_simd4x4f_t *m,
                               float                x,
                               float                y,
                               float                z)
{
  *m = graphene_simd4x4f_init (graphene_simd4f_init (1.0f, 0.0f, 0.0f, 0.0f),
                               graphene_simd4f_init (0.0f, 1.0f, 0.0f, 0.0f),
                               graphene_simd4f_init (0.0f, 0.0f, 1.0f, 0.0f),
                               graphene_simd4f_init (   x,    y,    z, 1.0f));
}

static inline void
graphene_simd4x4f_scale (graphene_simd4x4f_t *m,
                         float                x,
                         float                y,
                         float                z)
{
  *m = graphene_simd4x4f_init (graphene_simd4f_init (   x, 0.0f, 0.0f, 0.0f),
                               graphene_simd4f_init (0.0f,    y, 0.0f, 0.0f),
                               graphene_simd4f_init (0.0f, 0.0f,    z, 0.0f),
                               graphene_simd4f_init (0.0f, 0.0f, 0.0f, 1.0f));

}

static inline void
graphene_simd4x4f_rotation (graphene_simd4x4f_t *m,
                            float                rad,
                            graphene_simd4f_t    axis)
{
  float sine, cosine;
  float x, y, z;
  float ab, bc, ca;
  float tx, ty, tz;
  graphene_simd4f_t i, j, k;

  rad = -rad;
  axis = graphene_simd4f_normalize3 (axis);

  sine = sinf (rad);
  cosine = cosf (rad);

  x = graphene_simd4f_get_x (axis);
  y = graphene_simd4f_get_y (axis);
  z = graphene_simd4f_get_z (axis);

  ab = x * y * (1.0f - cosine);
  bc = y * z * (1.0f - cosine);
  ca = z * x * (1.0f - cosine);

  tx = x * x;
  ty = y * y;
  tz = z * z;

  i = graphene_simd4f_init (tx + cosine * (1.0f - tx), ab - z * sine, ca + y * sine, 0.f);
  j = graphene_simd4f_init (ab + z * sine, ty + cosine * (1.0f - ty), bc - x * sine, 0.f);
  k = graphene_simd4f_init (ca - y * sine, bc + x * sine, tz + cosine * (1.0f - tz), 0.f);

  *m = graphene_simd4x4f_init (i, j, k, graphene_simd4f_init (0.0f, 0.0f, 0.0f, 1.0f));
}

#define GRAPHENE_SIMD4X4F_OP(op) \
static inline void \
graphene_simd4x4f_##op (const graphene_simd4x4f_t *a, \
                        const graphene_simd4x4f_t *b, \
                        graphene_simd4x4f_t *res) \
{ \
  res->x = graphene_simd4f_##op (a->x, b->x); \
  res->y = graphene_simd4f_##op (a->y, b->y); \
  res->z = graphene_simd4f_##op (a->z, b->z); \
  res->w = graphene_simd4f_##op (a->w, b->w); \
}

GRAPHENE_SIMD4X4F_OP (add)
GRAPHENE_SIMD4X4F_OP (sub)
GRAPHENE_SIMD4X4F_OP (mul)
GRAPHENE_SIMD4X4F_OP (div)

#undef GRAPHENE_SIMD4X4F_OP

static inline void
graphene_simd4x4f_inverse (const graphene_simd4x4f_t *m,
                           graphene_simd4x4f_t       *res)
{
  /* split rows */
  const graphene_simd4f_t r0 = m->x;
  const graphene_simd4f_t r1 = m->y;
  const graphene_simd4f_t r2 = m->z;
  const graphene_simd4f_t r3 = m->w;

  /* cofactors */
  const graphene_simd4f_t r0_wxyz = graphene_simd4f_shuffle_wxyz (r0);
  const graphene_simd4f_t r0_zwxy = graphene_simd4f_shuffle_zwxy (r0);
  const graphene_simd4f_t r0_yzwx = graphene_simd4f_shuffle_yzwx (r0);

  const graphene_simd4f_t r1_wxyz = graphene_simd4f_shuffle_wxyz (r1);
  const graphene_simd4f_t r1_zwxy = graphene_simd4f_shuffle_zwxy (r1);
  const graphene_simd4f_t r1_yzwx = graphene_simd4f_shuffle_yzwx (r1);

  const graphene_simd4f_t r2_wxyz = graphene_simd4f_shuffle_wxyz (r2);
  const graphene_simd4f_t r2_zwxy = graphene_simd4f_shuffle_zwxy (r2);
  const graphene_simd4f_t r2_yzwx = graphene_simd4f_shuffle_yzwx (r2);

  const graphene_simd4f_t r3_wxyz = graphene_simd4f_shuffle_wxyz (r3);
  const graphene_simd4f_t r3_zwxy = graphene_simd4f_shuffle_zwxy (r3);
  const graphene_simd4f_t r3_yzwx = graphene_simd4f_shuffle_yzwx (r3);

  const graphene_simd4f_t r0_wxyz_x_r1 = graphene_simd4f_mul (r0_wxyz, r1);
  const graphene_simd4f_t r0_wxyz_x_r1_yzwx = graphene_simd4f_mul (r0_wxyz, r1_wxyz);
  const graphene_simd4f_t r0_wxyz_x_r1_zwxy = graphene_simd4f_mul (r0_wxyz, r1_zwxy);

  const graphene_simd4f_t r2_wxyz_x_r3 = graphene_simd4f_mul (r2_wxyz, r3);
  const graphene_simd4f_t r2_wxyz_x_r3_yzwx = graphene_simd4f_mul (r2_wxyz, r3_yzwx);
  const graphene_simd4f_t r2_wxyz_x_r3_zwxy = graphene_simd4f_mul (r2_wxyz, r3_zwxy);

  const graphene_simd4f_t ar1 = graphene_simd4f_sub (graphene_simd4f_shuffle_wxyz (r2_wxyz_x_r3_zwxy),
                                                     graphene_simd4f_shuffle_zwxy (r2_wxyz_x_r3));
  const graphene_simd4f_t ar2 = graphene_simd4f_sub (graphene_simd4f_shuffle_zwxy (r2_wxyz_x_r3_yzwx),
                                                     r2_wxyz_x_r3_yzwx);
  const graphene_simd4f_t ar3 = graphene_simd4f_sub (r2_wxyz_x_r3_zwxy,
                                                     graphene_simd4f_shuffle_wxyz (r2_wxyz_x_r3));

  const graphene_simd4f_t br1 = graphene_simd4f_sub (graphene_simd4f_shuffle_wxyz (r0_wxyz_x_r1_zwxy),
                                                     graphene_simd4f_shuffle_zwxy (r0_wxyz_x_r1));
  const graphene_simd4f_t br2 = graphene_simd4f_sub (graphene_simd4f_shuffle_zwxy (r0_wxyz_x_r1_yzwx),
                                                     r0_wxyz_x_r1_yzwx);
  const graphene_simd4f_t br3 = graphene_simd4f_sub (r0_wxyz_x_r1_zwxy,
                                                     graphene_simd4f_shuffle_wxyz (r0_wxyz_x_r1));

  const graphene_simd4f_t r0_sum =
    graphene_simd4f_madd (r0_yzwx, ar3,
                          graphene_simd4f_madd (r0_zwxy, ar2,
                                                graphene_simd4f_mul (r0_wxyz, ar1)));
  const graphene_simd4f_t r1_sum =
    graphene_simd4f_madd (r1_wxyz, ar1,
                          graphene_simd4f_madd (r1_zwxy, ar2,
                                                graphene_simd4f_mul (r1_yzwx, ar3)));
  const graphene_simd4f_t r2_sum =
    graphene_simd4f_madd (r2_yzwx, br3,
                          graphene_simd4f_madd (r2_zwxy, br2,
                                                graphene_simd4f_mul (r2_wxyz, br1)));
  const graphene_simd4f_t r3_sum =
    graphene_simd4f_madd (r3_yzwx, br3,
                          graphene_simd4f_madd (r3_zwxy, br2,
                                                graphene_simd4f_mul (r3_wxyz, br1)));

  /* determinant and its inverse */
  const graphene_simd4f_t d0 = graphene_simd4f_mul (r1_sum, r0);
  const graphene_simd4f_t d1 = graphene_simd4f_add (d0, graphene_simd4f_merge_high (d0, d0));
  const graphene_simd4f_t det = graphene_simd4f_sub (d1, graphene_simd4f_splat_y (d1));
  const graphene_simd4f_t invdet = graphene_simd4f_splat_x (graphene_simd4f_div (graphene_simd4f_splat (1.0f), det));

  const graphene_simd4f_t o0 = graphene_simd4f_mul (graphene_simd4f_flip_sign_0101 (r1_sum), invdet);
  const graphene_simd4f_t o1 = graphene_simd4f_mul (graphene_simd4f_flip_sign_1010 (r0_sum), invdet);
  const graphene_simd4f_t o2 = graphene_simd4f_mul (graphene_simd4f_flip_sign_0101 (r3_sum), invdet);
  const graphene_simd4f_t o3 = graphene_simd4f_mul (graphene_simd4f_flip_sign_1010 (r2_sum), invdet);

  graphene_simd4x4f_t mt = graphene_simd4x4f_init (o0, o1, o2, o3);

  /* transpose the resulting matrix */
  graphene_simd4x4f_transpose (&mt, res);
}

static inline void
graphene_simd4x4f_determinant (const graphene_simd4x4f_t *m,
                               graphene_simd4f_t         *det_r,
                               graphene_simd4f_t         *invdet_r)
{
  /* split rows */
  const graphene_simd4f_t r0 = m->x;
  const graphene_simd4f_t r1 = m->y;
  const graphene_simd4f_t r2 = m->z;
  const graphene_simd4f_t r3 = m->w;

  /* cofactors */
  const graphene_simd4f_t r1_wxyz = graphene_simd4f_shuffle_wxyz (r1);
  const graphene_simd4f_t r1_zwxy = graphene_simd4f_shuffle_zwxy (r1);
  const graphene_simd4f_t r1_yzwx = graphene_simd4f_shuffle_yzwx (r1);

  const graphene_simd4f_t r2_wxyz = graphene_simd4f_shuffle_wxyz (r2);

  const graphene_simd4f_t r3_zwxy = graphene_simd4f_shuffle_zwxy (r3);
  const graphene_simd4f_t r3_yzwx = graphene_simd4f_shuffle_yzwx (r3);

  const graphene_simd4f_t r2_wxyz_x_r3 = graphene_simd4f_mul (r2_wxyz, r3);
  const graphene_simd4f_t r2_wxyz_x_r3_yzwx = graphene_simd4f_mul (r2_wxyz, r3_yzwx);
  const graphene_simd4f_t r2_wxyz_x_r3_zwxy = graphene_simd4f_mul (r2_wxyz, r3_zwxy);

  const graphene_simd4f_t ar1 = graphene_simd4f_sub (graphene_simd4f_shuffle_wxyz (r2_wxyz_x_r3_zwxy),
                                                     graphene_simd4f_shuffle_zwxy (r2_wxyz_x_r3));
  const graphene_simd4f_t ar2 = graphene_simd4f_sub (graphene_simd4f_shuffle_zwxy (r2_wxyz_x_r3_yzwx),
                                                     r2_wxyz_x_r3_yzwx);
  const graphene_simd4f_t ar3 = graphene_simd4f_sub (r2_wxyz_x_r3_zwxy,
                                                     graphene_simd4f_shuffle_wxyz (r2_wxyz_x_r3));

  const graphene_simd4f_t r1_sum =
    graphene_simd4f_madd (r1_wxyz, ar1,
                          graphene_simd4f_madd (r1_zwxy, ar2,
                                                graphene_simd4f_mul (r1_yzwx, ar3)));

  /* determinant and its inverse */
  const graphene_simd4f_t d0 = graphene_simd4f_mul (r1_sum, r0);
  const graphene_simd4f_t d1 = graphene_simd4f_add (d0, graphene_simd4f_merge_high (d0, d0));

  const graphene_simd4f_t det = graphene_simd4f_sub (d1, graphene_simd4f_splat_y (d1));

  const graphene_simd4f_t invdet = graphene_simd4f_splat_x (graphene_simd4f_div (graphene_simd4f_splat (1.0f), det));

  if (det_r != NULL)
    *det_r = det;

  if (invdet_r != NULL)
    *invdet_r = invdet;
}

static inline gboolean
graphene_simd4x4f_is_identity (const graphene_simd4x4f_t *m)
{
  const graphene_simd4f_t r0 = graphene_simd4f_init (1.0f, 0.0f, 0.0f, 0.0f);
  const graphene_simd4f_t r1 = graphene_simd4f_init (0.0f, 1.0f, 0.0f, 0.0f);
  const graphene_simd4f_t r2 = graphene_simd4f_init (0.0f, 0.0f, 1.0f, 0.0f);
  const graphene_simd4f_t r3 = graphene_simd4f_init (0.0f, 0.0f, 0.0f, 1.0f);

  return graphene_simd4f_cmp_eq (m->x, r0) &&
         graphene_simd4f_cmp_eq (m->y, r1) &&
         graphene_simd4f_cmp_eq (m->z, r2) &&
         graphene_simd4f_cmp_eq (m->w, r3);
}

static inline gboolean
graphene_simd4x4f_is_2d (const graphene_simd4x4f_t *m)
{
  graphene_simd4x4f_t t;

  if (graphene_simd4f_cmp_neq (m->z, graphene_simd4f_init (0.f, 0.f, 1.f, 0.f)))
    return FALSE;

  graphene_simd4x4f_transpose (m, &t);

  if (graphene_simd4f_cmp_neq (t.z, graphene_simd4f_init (0.f, 0.f, 1.f, 0.f)))
    return FALSE;

  if (graphene_simd4f_cmp_neq (t.w, graphene_simd4f_init (0.f, 0.f, 0.f, 1.f)))
    return FALSE;

  return TRUE;
}

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHENE_SIMD4X4F_COMMON_H__ */
