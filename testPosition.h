#pragma once

class TestPosition
{
public:
    void run();
private:
    void testComputeX_positive();
    void testComputeX_negative();
    void testComputeX_positive_decimal();
    void testComputeY_positive();
    void testComputeY_negative();
    void testComputeY_positive_decimal();
};