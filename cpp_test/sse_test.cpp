#include <nmmintrin.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    float op1[4] = {1.0, 2.0, 3.0, 4.0};
    float op2[4] = {1.0, 2.0, 3.0, 4.0};
    float result[4];

    __m128  a;
    __m128  b;
    __m128  c;

    // Load
    a = _mm_loadu_ps(op1);
    b = _mm_loadu_ps(op2);

    // Calculate
    c = _mm_add_ps(a, b);   // c = a + b

    // Store
    _mm_storeu_ps(result, c);

    /*      // Using the __m128 union to get the result.
    printf("0: %lf\n", c.m128_f32[0]);
    printf("1: %lf\n", c.m128_f32[1]);
    printf("2: %lf\n", c.m128_f32[2]);
    printf("3: %lf\n", c.m128_f32[3]);
    */
    printf("0: %lf\n", result[0]);
    printf("1: %lf\n", result[1]);
    printf("2: %lf\n", result[2]);
    printf("3: %lf\n", result[3]);

    return 0;
}
