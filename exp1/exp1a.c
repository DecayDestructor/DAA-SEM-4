#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Function to calculate log base 2
void logbasetwo(int n) {
    printf("Logarithm base 2 of %d is %lf\n", n, log(n) / log(2));
}

// Function to calculate n^3 manually
void cube(int n) {
    int result = n * n * n;
    printf("Cube of %d is %d\n", n, result);
}

// Function to calculate lg^2(n) (log base 2 squared)
void log_squared(int n) {
    double log2n = log(n) / log(2);
    double result = log2n * log2n;
    printf("Log base 2 squared of %d is %lf\n", n, result);
}

// Function to calculate lg(n!) manually
void log_factorial(int n) {
    double result = 0;
    for (int i = 1; i <= n; i++) {
        result += log(i) / log(2);  // Sum log2(i) for all i
    }
    printf("Log base 2 of factorial of %d is %lf\n", n, result);
}

// Function to calculate 2^n manually
void power_of_two(int n) {
    long long result = 1;
    for (int i = 0; i < n; i++) {
        result *= 2;
    }
    printf("2 raised to the power %d is %lld\n", n, result);
}

// Function to calculate ln(ln(n))
void natural_log_of_log(int n) {
    double result = log(log(n));
    printf("Natural log of log of %d is %lf\n", n, result);
}

// Function to calculate 2^(lg n) manually
void two_power_log(int n) {
    double log2n = log(n) / log(2);
    double result = 1;
    for (int i = 0; i < (int)log2n; i++) {
        result *= 2;
    }
    printf("2 raised to the power log2(%d) is %lf\n", n, result);
}

// Function to calculate lg(n)^lg(n) manually
void log_power_log(int n) {
    double log2n = log(n) / log(2);
    double result = 1;
    for (int i = 0; i < (int)log2n; i++) {
        result *= log2n;
    }
    printf("Log base 2 of %d raised to itself is %lf\n", n, result);
}

// Function to calculate n * 2^n manually
void n_times_two_power_n(int n) {
    long long power = 1;
    for (int i = 0; i < n; i++) {
        power *= 2;
    }
    long long result = n * power;
    printf("n * 2^n for %d is %lld\n", n, result);
}

// Function to calculate square root of lg(n)
void sqrt_of_log(int n) {
    double log2n = log(n) / log(2);
    double result = sqrt(log2n);
    printf("Square root of log base 2 of %d is %lf\n", n, result);
}
void factorial(int a) {
    int result = 1;
    for (int i = 1; i <= a; i++)
        result = result * i;
    printf("Factorial of %d is %d \n", a, result);
}
// Function to calculate 2^(2^(lg n)) manually
void two_power_two_power_log(int n) {
    double log2n = log(n) / log(2);
    long long inner_power = 1;
    for (int i = 0; i < (int)log2n; i++) {
        inner_power *= 2;
    }
    long long result = 1;
    for (int i = 0; i < inner_power; i++) {
        result *= 2;
    }
    printf("2^(2^(log2(%d))) is %lld\n", n, result);
}

// Function to calculate lg(lg(n))
void log_of_log(int n) {
    double log2n = log(n) / log(2);
    double result = log(log2n) / log(2);
    printf("Log base 2 of log base 2 of %d is %lf\n", n, result);
}

// Function to calculate n^2 manually
void square(int n) {
    int result = n * n;
    printf("Square of %d is %d\n", n, result);
}

// Function to calculate 2^(n+1) manually
void two_power_n_plus_1(int n) {
    long long result = 1;
    for (int i = 0; i <= n; i++) {
        result *= 2;
    }
    printf("2^(n+1) for %d is %lld\n", n, result);
}
void exponential(int n) {
    double a = 2.718;
    double result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * a;
    }
    printf("e exponent %d is %lf \n", n, result);
}
void linear(int n) {
    printf("Linear is %d \n", n);
}
int main() {
    for (int n = 1; n <= 100; n++) {
        linear(n);
        logbasetwo(n);
        cube(n);
        log_squared(n);
        power_of_two(n);
        natural_log_of_log(n);
        sqrt_of_log(n);
        log_of_log(n);
        square(n);
    }
    for (int n = 1; n <= 15; n++) {
        log_factorial(n);
        two_power_log(n);
        log_power_log(n);
        n_times_two_power_n(n);
        two_power_two_power_log(n);
        two_power_n_plus_1(n);
        factorial(n);
        exponential(n);
    }
    return 0;
}
