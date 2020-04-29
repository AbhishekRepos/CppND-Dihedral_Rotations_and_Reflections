#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

#define FULL_CIRCLE 360
#define HALF_CIRCLE FULL_CIRCLE/2
#define ROTATION_ANGLE(N,K) (FULL_CIRCLE/N)*K
#define REFLECTION_ANGLE(N,K) (HALF_CIRCLE/N)*K

static const int MIN_ANGLE = 0;
static const int INT_TWO = 2;

#endif // COMMON_DEFINES_H
