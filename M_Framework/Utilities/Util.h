#pragma once
//fileName:: Util.h

#define EPSILON 0.0001f
//abs -> 절대값 (양수로 표기해주는 녀석)
//abs(-10 ) -> 10
//abs( 20 ) -> 20
#define FLOATZERO(a) (abs(a) < EPSILON)
#define FLOATEQUAL(a,b) (abs((a) - (b)) < EPSILON)
#define COLOREQAUL(c1,c2) (FLOATEQUAL(c1.r,c2.r) && FLOATEQUAL(c1.g,c2.g) && FLOATEQUAL(c1.b,c2.b))
#define VEC2ZERO(v) (FLOATZERO(v.x) && FLOATZERO(v.y))