//
// Created by Abdul on 05/01/2023.
//

#ifndef IIR_FILTER_HPP
#define IIR_FILTER_HPP

#include <vector>
#include <iostream>
#include "Filter.hpp"

// UNFINISHED
class InfiniteImpulseResponseFilter: public Filter {
    /* IIR filter class */

    private:
        std::vector<double> b_coefficients;
        std::vector<double> a_coefficients;
        // previous inputs and outputs
        std::vector<double> signal_input_history;
        std::vector<double> signal_output_history;
        double sampling_frequency;
        int filter_order;

        // UNFINISHED
        void calculate_low_pass_coefficents(double cut_off_frequency) override;
        // UNFINISHED
        void calculate_high_pass_coefficents(double cut_off_frequency) override;
        // UNFINISHED
        void calculate_band_pass_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) override;
        // UNFINISHED
        void calculate_band_stop_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) override;

    public:
        InfiniteImpulseResponseFilter(
            FilterType filter_type,
            double sampling_frequency,
            const std::vector<double>& cut_off_frequencies,
            int filter_order
        );

        void generate_coefficients(
            FilterType filter_type, const std::vector<double>& cut_off_frequencies
        ) override;

        double apply_filter(double sample) override;
};

#endif //IIR_FILTER_HPP
