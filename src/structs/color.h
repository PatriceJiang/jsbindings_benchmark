#pragma once

#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    uint32_t intValue() const;

    uint32_t dyn() const;

    void add2(Color* c1, Color* c2);
    void add3(Color* c1, Color* c2, Color *c3);
    void add4(Color* c1, Color* c2, Color * c3, Color *c4);

    void mul1(int a);
    void mul2(int a, int b);
    void mul3(int a, int b, int c);
    void mul4(int a, int b, int c, int d);
};