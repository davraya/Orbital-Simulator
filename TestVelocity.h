#pragma once

class TestVelocity
{
public:
    void run();
private:
    void testComputeDx_positive();
    void testComputeDx_negative();
    void testComputeDy_positive();
    void testComputeDy_negative();
};