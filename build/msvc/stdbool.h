#ifndef __GRAPHENE_STDBOOL_H__
#define __GRAPHENE_STDBOOL_H__

#ifndef __cplusplus
#ifndef __bool_true_false_are_defined

#if !defined(_MSC_VER)
#error "This file should only be included when compiling with MSVC."
#endif

typedef unsigned char _Bool

#define false 0
#define true 1

#define __bool_true_false_are_defined

#ifndef C_ASSERT
# define C_ASSERT(expr,name)     typedef int assert_ ## name [(expr) ? 1 : -1];
#endif

C_ASSERT (sizeof (bool) == 1, bool_is_one_byte)
C_ASSERT (true, true_is_true)
C_ASSERT (!false, false_is_false)

#endif /* __bool_true_false_are_defined */
#endif /* __cplusplus */

#endif /* __GRAPHENE_STDBOOL_H__ */
