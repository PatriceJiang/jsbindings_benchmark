#include "color.h"

static int dynI = 0;

uint32_t Color::intValue() const{
    return (r << 24) | (g << 16) | (b << 8) | a;
}


uint32_t Color::dyn() const {
    static int reidx[] = { 3, 2, 0, 2 };
    auto i = reidx[dynI % 4];
    dynI++;
    if (i == 0) {
        return r;
    }
    else if (i == 1) {
        return g + r;
    }
    else if (i == 2) {
        return b + a;
    }
    else {
        return a + g;
    }
}

#define EMPTY_BODY 1

void Color::add2(Color* c1, Color* c2)
{
#if !EMPTY_BODY
    r = c1->r + c2->r;
    g = c1->g + c2->g;
    b = c1->b + c2->b;
    a = c1->a + c2->a;
#endif
}

void Color::add3(Color* c1, Color* c2, Color* c3)
{
#if !EMPTY_BODY
    this->add2(c1, c2);
    this->add2(this, c3);
#endif
}


void Color::add4(Color* c1, Color* c2, Color* c3, Color* c4)
{
#if !EMPTY_BODY
    this->add3(c1, c2, c3);
    this->add2(this, c4);
#endif
}

void Color::mul1(int x)
{
#if !EMPTY_BODY
    r *= x;
    g *= x;
    b *= x;
    a *= x;
#endif
}

void Color::mul2(int x1, int x2)
{
#if !EMPTY_BODY
    mul1(x1 * x2);
#endif
}

void Color::mul3(int x1, int x2, int x3)
{
#if !EMPTY_BODY
    mul1(x1 * x2 * x3);
#endif
}

void Color::mul4(int x1, int x2, int x3, int x4)
{
#if !EMPTY_BODY
    mul1(x1 * x2 * x3 * x4);
#endif
}

