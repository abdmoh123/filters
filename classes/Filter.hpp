//
// Created by Abdul on 05/01/2023.
//

#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>

/* Types of filters */
enum FilterType { low_pass, high_pass, band_pass, band_stop };

class Filter {
    /* Abstract filter class */

    private:
        virtual void calculate_low_pass_coefficents(double cut_off_frequency) = 0;
        virtual void calculate_high_pass_coefficents(double cut_off_frequency) = 0;
        virtual void calculate_band_pass_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) = 0;
        virtual void calculate_band_stop_coefficents(
            double cut_off_frequency_1, double cut_off_frequency_2
        ) = 0;

    public:
        virtual void generate_coefficients(
            FilterType filter_type, const std::vector<double>& cut_off_frequencies
        ) = 0;
        virtual double apply_filter(double sample) = 0;
};

#endif //FILTER_HPP
