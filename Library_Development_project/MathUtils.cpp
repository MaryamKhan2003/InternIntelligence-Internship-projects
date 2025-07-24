// #include "MathUtils.h"

// int MathUtils::factorial(int n) {
//     if (n < 0) return -1;
//     int result = 1;
//     for (int i = 2; i <= n; ++i)
//         result *= i;
//     return result;
// }

// bool MathUtils::isPrime(int n) {
//     if (n <= 1) return false;
//     for (int i = 2; i * i <= n; ++i)
//         if (n % i == 0) return false;
//     return true;
// }

// int MathUtils::gcd(int a, int b) {
//     while (b != 0) {
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }

// int MathUtils::power(int base, int exp) {
//     int result = 1;
//     for (int i = 0; i < exp; ++i)
//         result *= base;
//     return result;
// }