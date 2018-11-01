#pragma once
//filename:: Util.h

//엡실론: 두값의 차이가 엡실론만큼보다 작으면 그 둘의 차이는 무시하고 같다고 취급하겠다
#define EPSILON 0.0001f
//abs() -> 절대값
//abs(-10) -> 10
//abs(20) -> 20
#define FLOATZERO(a) (abs(a) < EPSILON)
#define FLOATEQUAL(a, b) (abs((a) - (b))) < EPSILON
#define COLOREQUAL(c1, c2) (FLOATEQUAL(c1.r, c2.r) && FLOATEQUAL(c1.g, c2.g) && FLOATEQUAL(c1.b, c2.b))
#define VEC2ZERO(v) (FLOATZERO(v.x) && FLOATZERO(v.y))