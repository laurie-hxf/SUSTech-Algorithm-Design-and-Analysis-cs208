//
// Created by laurie on 25-5-15.
//
#include <complex>
#include <iostream>
#include <vector>
using namespace std;
const double PI = 3.141592653589793238460;

typedef complex<double> Complex;
typedef vector<Complex> CArray;


void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    vector<complex<double>> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; ++i) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

int main() {
    int N;
    cin >> N;
    int size = 1 << N;
    vector<complex<double>> a(size);

    for (int i = 0; i < size; ++i) {
        double val;
        cin >> val;
        a[i] = complex<double>(val, 0.0);
    }
    fft(a);
    for (int i = 0; i < size; ++i) {
        printf("%.10f\n", abs(a[i]));
    }
    return 0;
}
