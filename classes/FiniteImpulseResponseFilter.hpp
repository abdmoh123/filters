//
// Created by Abdul on 05/01/2023.
//

#ifndef FIR_FILTER_HPP
#define FIR_FILTER_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>
#include <complex>

#ifndef FILTER_HPP
#include "Filter.hpp"
#endif

enum WindowFunction { rectangular, hanning, hamming, blackman };

class FiniteImpulseResponseFilter: public Filter {
    /* FIR filter class */

    private:
        std::vector<double> b_coefficients;
        std::vector<double> signal_input_history;  // previous inputs
        double sampling_frequency;
        int num_taps;

        void calculate_low_pass_coefficents(double cut_off_frequency) override;
        void calculate_high_pass_coefficents(double cut_off_frequency) override;
        void calculate_band_pass_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) override;
        void calculate_band_stop_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) override;

    public:
        FiniteImpulseResponseFilter(
            FilterType filter_type,
            double sampling_frequency,
            const std::vector<double>& cut_off_frequencies,
            int num_taps
        );

        void generate_coefficients(
            FilterType filter_type, const std::vector<double>& cut_off_frequencies
        ) override;

        void apply_window(WindowFunction window_function = rectangular);

        double apply_filter(double sample) override;

        std::vector<double> get_coefficients();
};

#endif //FIR_FILTER_HPP
