#include <Trundle/Math/general.h>


uint64_t Trundle::math::fibonacci(uint64_t n) {
    double phi = (1.0 + sqrt(5)) / 2.0; 
    return round(pow(phi, n) / sqrt(5)); 
}

// Slow linear time algorithm. Used for testing purposes only
uint64_t Trundle::math::fibonacci_linear(uint64_t n) {
    uint64_t total = 0;
    uint64_t minus1 = 0;
    uint64_t minus2 = 1;

    for (uint64_t i = 0; i < n; ++i) {
        total = minus1 + minus2;
        minus2 = minus1;
        minus1 = total;
    }

    return total;
}
