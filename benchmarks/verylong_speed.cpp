/*! \file    verylong_speed.cpp
 *  \brief   Program to test performance of spica::VeryLong integers.
 *  \author  Peter Chapin <spicacality@kelseymountain.org>
 */

#include <cstdlib>
#include <iostream>
#include "Timer.hpp"
#include "VeryLong.hpp"

const int N_TRIALS = 256;

int main()
{
    std::cout << "\nMultiplication\n";
    std::cout <<   "==============\n";
    for (int n_bits = 256; n_bits <= 16384; n_bits *= 2) {

        // Allocate the necessary arrays.
        spica::VeryLong *m1 = new spica::VeryLong[N_TRIALS];
        spica::VeryLong *m2 = new spica::VeryLong[N_TRIALS];

        // Fill the the input arrays with random numbers, each n_bits in size.
        for (int i = 0; i < N_TRIALS; ++i) {
            for (spica::VeryLong::size_type j = 0; j < n_bits - 1; ++j) {
                m1[i].put_bit(j, std::rand() % 2);
                m2[i].put_bit(j, std::rand() % 2);
            }
            // Make sure most significant bits are one.
            m1[i].put_bit(n_bits - 1, 1);
            m2[i].put_bit(n_bits - 1, 1);
        }

        pcc::Timer stopwatch;
        stopwatch.start();
        for (int i = 0; i < N_TRIALS; ++i) {
            spica::VeryLong result = m1[i] * m2[i];
        }
        stopwatch.stop();
        std::cout
            << n_bits << " bits: " << stopwatch.time()/N_TRIALS << " ms.\n";

        // Clean up.
        delete [] m1;
        delete [] m2;
    }

    std::cout << "\nDivision\n";
    std::cout <<   "========\n";
    for (int n_bits = 256; n_bits <= 16384; n_bits *= 2) {

        // Allocate the necessary arrays.
        spica::VeryLong *m1 = new spica::VeryLong[N_TRIALS];
        spica::VeryLong *m2 = new spica::VeryLong[N_TRIALS];

        // Fill the the input arrays with random numbers.
        for (int i = 0; i < N_TRIALS; ++i) {

            // Make the numerator 2*n_bits in size so division requires n_bits steps.
            for (spica::VeryLong::size_type j = 0; j < 2*n_bits - 1; ++j) {
                m1[i].put_bit(j, std::rand() % 2);
            }
            m1[i].put_bit(2*n_bits - 1, 1);
            for (spica::VeryLong::size_type j = 0; j < n_bits - 1; ++j) {
                m2[i].put_bit(j, std::rand() % 2);
            }
            m2[i].put_bit(n_bits - 1, 1);
        }

        pcc::Timer stopwatch;
        stopwatch.start();
        for (int i = 0; i < N_TRIALS; ++i) {
            spica::VeryLong::vldiv_t result;
            spica::VeryLong::vldiv(m1[i], m2[i], &result);
        }
        stopwatch.stop();
        std::cout
            << n_bits << " bits: " << stopwatch.time()/N_TRIALS << " ms.\n";

        // Clean up.
        delete [] m1;
        delete [] m2;
    }

    return 0;
}
