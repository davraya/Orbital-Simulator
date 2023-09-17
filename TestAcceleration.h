#pragma once

class TestAcceleration
{
public:
    void run();
private:
    void testComputeDdx_positive();
    void testComputeDdx_negative();
    void testComputeDdx_positive_decimal();
    void testComputeDdy_positive();
    void testComputeDdy_negative();
    void testComputeDdy_positive_decimal();
};