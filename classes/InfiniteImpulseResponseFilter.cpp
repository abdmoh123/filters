//
// Created by Abdul on 05/01/2023.
//

#ifndef IIR_FILTER_HPP
#include "InfiniteImpulseResponseFilter.hpp"

InfiniteImpulseResponseFilter::InfiniteImpulseResponseFilter(
    FilterType filter_type,
    double sampling_frequency,
    const std::vector<double> &cut_off_frequencies,
    int filter_order
) {
    /* IIR Filter constructor
     *
     * param filter_type: Type of filter to use (low_pass, high_pass or band_pass)
     * param b_coefficients: Vector of b coefficients used to generate an output
     * param a_coefficients: Vector of a coefficients used to generate an output
     */

    this->sampling_frequency = sampling_frequency;
    this->filter_order = filter_order;

    // fills previous input vectors with 0s to have the same size as b_coefficients
    for (int i = 0; i < b_coefficients.size(); ++i) {
        signal_input_history.push_back(0.0);
    }
    // fills previous output vectors with 0s to have the same size as a_coefficients
    for (int i = 0; i < a_coefficients.size(); ++i) {
        signal_output_history.push_back(0.0);
    }
}

void InfiniteImpulseResponseFilter::generate_coefficients(
    FilterType filter_type, const std::vector<double> &cut_off_frequencies
) {
    /* The coefficients are calculated depending on the type of filter specified
     *
     * param filter_type: Type of filter to use (low_pass, high_pass or band_pass)
     */

    if (filter_type == low_pass) {
        calculate_low_pass_coefficents(cut_off_frequencies[0]);
    }
    else if (filter_type == high_pass) {
        calculate_high_pass_coefficents(cut_off_frequencies[0]);
    }
    else if (filter_type == band_pass) {
        calculate_band_pass_coefficents(cut_off_frequencies[0], cut_off_frequencies[1]);
    }
    else if (filter_type == band_stop) {
        calculate_band_stop_coefficents(cut_off_frequencies[0], cut_off_frequencies[1]);
    }
    else {
        std::cerr << "Invalid filter type!" << std::endl
             << "Valid filter types: low_pass, high_pass, band_pass and band_stop.";
        exit(EXIT_FAILURE);
    }
}

double InfiniteImpulseResponseFilter::apply_filter(double sample) {
    /* Generates output for IIR filter
     *
     * param sample: Newly inputted sample of data to filter
     */

    // updates input history vector before calculation so inputted sample is used
    signal_input_history.push_back(sample);
    signal_input_history.erase(signal_input_history.begin());

    // performs sum{k=0->N}(b_k * x[n - k]) - sum{k=1->M}(a_k * y[n - k])
    double result = 0.0;
    for (int i = 0; i < b_coefficients.size(); ++i) {
        result += (b_coefficients[i] * signal_input_history[signal_input_history.size() - 1 - i]);
    }
    // new loop is done because sizes of a_coefficients and b_coefficients may not be equal
    for (int i = 0; i < a_coefficients.size(); ++i) {
        result -= (a_coefficients[i] * signal_output_history[signal_output_history.size() - 1 - i]);
    }

    // updates output history vector after calculation
    // so k => 1 in -sum{k=1->M}(a_k * y[n - k])
    signal_output_history.push_back(result);
    signal_output_history.erase(signal_output_history.begin());

    return result;
}

// UNFINISHED
void InfiniteImpulseResponseFilter::calculate_low_pass_coefficents(double cut_off_frequency) {
    /* Calculates coefficients for a low pass IIR filter */
}

// UNFINISHED
void InfiniteImpulseResponseFilter::calculate_high_pass_coefficents(double cut_off_frequency) {
    /* Calculates coefficients for a high pass IIR filter */
}

// UNFINISHED
void InfiniteImpulseResponseFilter::calculate_band_pass_coefficents(
    double cut_off_frequency_1, double cut_off_frequency_2
) {
    /* Calculates coefficients for a band pass IIR filter */
}

// UNFINISHED
void InfiniteImpulseResponseFilter::calculate_band_stop_coefficents(
    double cut_off_frequency_1, double cut_off_frequency_2
) {
    /* Calculates coefficients for a band stop IIR filter */
}

#endif
