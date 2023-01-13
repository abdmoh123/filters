//
// Created by Abdul on 05/01/2023.
//

#ifndef FIR_FILTER_HPP

#include "FiniteImpulseResponseFilter.hpp"

FiniteImpulseResponseFilter::FiniteImpulseResponseFilter(
    FilterType filter_type,
    double sampling_frequency,
    const std::vector<double>& cut_off_frequencies,
    int num_taps
) {
    /* FIR Filter constructor
     *
     * param filter_type: Type of filter to use (low_pass, high_pass or band_pass)
     * param sampling_frequency: Frequency at which the data (to be filtered) was sampled
     * param cut_off_frequencies: Cut off frequencies of the filter (1 value for low pass
     *     and high pass, and 2 values for band pass)
     * param num_taps: Number of filter coefficients = (2 * num_taps) + 1
     */

    this->sampling_frequency = sampling_frequency;
    this->num_taps = num_taps;

    // generates b coefficients
    generate_coefficients(filter_type, cut_off_frequencies);

    // initialises an empty vector of 0s with the same size as number of coefficients
    for (int i = 0; i < b_coefficients.size(); ++i) {
        signal_input_history.push_back(0.0);
    }
}

void FiniteImpulseResponseFilter::calculate_low_pass_coefficents(double cut_off_frequency) {
    /* Calculates coefficients for a low pass FIR filter */

    double norm_cut_off = cut_off_frequency / sampling_frequency;
    int total_taps = (2 * num_taps) + 1;

    std::vector<double> h;
    // calculates h(n) for low pass FIR filter
    for (int i = 1; i <= num_taps; ++i) {
        double impulse_response = 2.0 * norm_cut_off * sin(i  * 2 * M_PI * norm_cut_off) / (i * 2 * M_PI * norm_cut_off);
        h.push_back(impulse_response);
    }

    std::vector<double> reverse_h;
    reverse_h.resize(h.size());
    reverse_copy(h.begin(), h.end(), reverse_h.begin());

    // adds h(0) to coefficients vector
    reverse_h.push_back(2.0 * norm_cut_off);
    // concatenates h to get the complete impulse response
    reverse_h.insert(reverse_h.end(), h.begin(), h.end());

    if (reverse_h.size() != total_taps) {
        std::cerr << "Number of coefficients is not equal to number of taps!" << std::endl
             << reverse_h.size() << "!=" << total_taps << std::endl;
        exit(EXIT_FAILURE);
    }

    // sets the coefficients to be the impulse response
    b_coefficients = reverse_h;
}

void FiniteImpulseResponseFilter::calculate_high_pass_coefficents(double cut_off_frequency) {
    /* Calculates coefficients for a high pass FIR filter */

    double norm_cut_off = cut_off_frequency / sampling_frequency;
    int total_taps = (2 * num_taps) + 1;

    std::vector<double> h;
    // calculates h(n) for high pass FIR filter
    for (int i = 1; i <= num_taps; ++i) {
        double impulse_response = -2.0 * norm_cut_off * sin(i * 2.0 * M_PI * norm_cut_off) / (i * 2.0 * M_PI * norm_cut_off);
        h.push_back(impulse_response);
    }

    std::vector<double> reverse_h;
    reverse_h.resize(h.size());
    reverse_copy(h.begin(), h.end(), reverse_h.begin());

    // adds h(0) to coefficients vector
    reverse_h.push_back(1.0 -(2.0 * norm_cut_off));
    // concatenates h to get the complete impulse response
    reverse_h.insert(reverse_h.end(), h.begin(), h.end());

    if (reverse_h.size() != total_taps) {
        std::cerr << "Number of coefficients is not equal to number of taps!" << std::endl
             << reverse_h.size() << "!=" << total_taps << std::endl;
        exit(EXIT_FAILURE);
    }

    // sets the coefficients to be the impulse response
    b_coefficients = reverse_h;
}

void FiniteImpulseResponseFilter::calculate_band_pass_coefficents(
    double cut_off_frequency_1, double cut_off_frequency_2
) {
    /* Calculates coefficients for a band pass FIR filter */

    double norm_cut_off_1 = cut_off_frequency_1 / sampling_frequency;
    double norm_cut_off_2 = cut_off_frequency_2 / sampling_frequency;
    int total_taps = (2 * num_taps) + 1;

    std::vector<double> h;
    // calculates h(n) for band pass FIR filter
    for (int i = 1; i <= num_taps; ++i) {
        double impulse_response_1 = 2.0 * norm_cut_off_1 * sin(i * 2.0 * M_PI * norm_cut_off_1) / (i * 2.0 * M_PI * norm_cut_off_1);
        double impulse_response_2 = 2.0 * norm_cut_off_2 * sin(i * 2.0 * M_PI * norm_cut_off_2) / (i * 2.0 * M_PI * norm_cut_off_2);
        h.push_back(impulse_response_2 - impulse_response_1);
    }

    std::vector<double> reverse_h;
    reverse_h.resize(h.size());
    reverse_copy(h.begin(), h.end(), reverse_h.begin());

    // adds h(0) to coefficients vector
    reverse_h.push_back((2.0 * norm_cut_off_2) - (2.0 * norm_cut_off_1));
    // concatenates h to get the complete impulse response
    reverse_h.insert(reverse_h.end(), h.begin(), h.end());

    if (reverse_h.size() != total_taps) {
        std::cerr << "Number of coefficients is not equal to number of taps!" << std::endl
             << reverse_h.size() << "!=" << total_taps << std::endl;
        exit(EXIT_FAILURE);
    }

    // sets the coefficients to be the impulse response
    b_coefficients = reverse_h;
}

void FiniteImpulseResponseFilter::calculate_band_stop_coefficents(
    double cut_off_frequency_1, double cut_off_frequency_2
) {
    /* Calculates coefficients for a band stop FIR filter */

    double norm_cut_off_1 = cut_off_frequency_1 / sampling_frequency;
    double norm_cut_off_2 = cut_off_frequency_2 / sampling_frequency;
    int total_taps = (2 * num_taps) + 1;

    std::vector<double> h;
    // calculates h(n) for band stop FIR filter
    for (int i = 1; i <= num_taps; ++i) {
        double impulse_response_1 = 2.0 * norm_cut_off_1 * sin(i * 2.0 * M_PI * norm_cut_off_1) / (i * 2.0 * M_PI * norm_cut_off_1);
        double impulse_response_2 = 2.0 * norm_cut_off_2 * sin(i * 2.0 * M_PI * norm_cut_off_2) / (i * 2.0 * M_PI * norm_cut_off_2);
        h.push_back(1.0 - (impulse_response_2 - impulse_response_1));
    }

    std::vector<double> reverse_h;
    reverse_h.resize(h.size());
    reverse_copy(h.begin(), h.end(), reverse_h.begin());

    // adds h(0) to coefficients vector
    reverse_h.push_back(1.0 - ((2.0 * norm_cut_off_2) - (2.0 * norm_cut_off_1)));
    // concatenates h to get the complete impulse response
    reverse_h.insert(reverse_h.end(), h.begin(), h.end());

    if (reverse_h.size() != total_taps) {
        std::cerr << "Number of coefficients is not equal to number of taps!" << std::endl
              << reverse_h.size() << "!=" << total_taps << std::endl;
        exit(EXIT_FAILURE);
    }

    // sets the coefficients to be the impulse response
    b_coefficients = reverse_h;
}

void FiniteImpulseResponseFilter::generate_coefficients(
    FilterType filter_type, const std::vector<double>& cut_off_frequencies
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

void FiniteImpulseResponseFilter::apply_window(WindowFunction window_function) {
    /* Applies a window function to the filter coefficients
     *
     * param window_function: Type of window function to use, defaults to rectangular
     */

    int N = (2 * num_taps) + 1;
    std::vector<double> win_function;

    // rectangular window function does nothing to the coefficients (default)
    if (window_function == rectangular) {
        for (int i = 0; i < N; ++i) {
            win_function[i] = 1.0;
        }
    }
    else if (window_function == hanning) {
        for (int i = 0; i < N; ++i) {
            double temp = (2.0 * M_PI * i) / (N - 1);
            win_function[i] = 0.5 - 0.5 * cos(temp);
        }
    }
    else if (window_function == hamming) {
        for (int i = 0; i < N; ++i) {
            double temp = (2.0 * M_PI * i) / (N - 1);
            win_function[i] = 0.54 - 0.46 * cos(temp);
        }
    }
    else if (window_function == blackman) {
        for (int i = 0; i < N; ++i) {
            double temp = (2.0 * M_PI * i) / (N - 1);
            win_function[i] = 0.42 - 0.5 * cos(temp) + 0.08 * cos(temp);
        }
    }
    else {
        std::cerr << "Invalid window function!" << std::endl
             << "Valid window functions: rectangular, hanning, hamming and blackman";
        exit(EXIT_FAILURE);
    }

    // applies the window function to the coefficients
    for (int i = 0; i < N; ++i) {
        b_coefficients[i] = win_function[i] * b_coefficients[i];
    }
}

void fft(std::valarray<std::complex<double>> & data) {
    unsigned int N = data.size();
    if (N <= 1) return;

    // separates the even and odd indices
    std::valarray<std::complex<double>> even_data = data[std::slice(0, N / 2, 2)];
    std::valarray<std::complex<double>> odd_data = data[std::slice(1, N / 2, 2)];
    // recursively splits the data until pairs are left
    fft(even_data);
    fft(odd_data);

    for (int i = 0; i < N / 2; ++i) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * i / N) * odd_data[i];
        data[i] = even_data[i] + t;
        data[i + N / 2] = even_data[i] - t;
    }
}

void inv_fft(std::valarray<std::complex<double>> & data) {
    // reverses sign of imaginary part (conjugation)
    data = data.apply(std::conj);

    // applies fft to data
    fft(data);

    // reverses sign of imaginary part again (conjugation)
    data = data.apply(std::conj);
}

double FiniteImpulseResponseFilter::apply_filter(double sample) {
    /* Generates output for FIR filter (filters inputted sample)
     *
     * param sample: Newly inputted sample of data to filter
     * return: Filtered version of the inputted sample
     */

    // updates vector before calculation so inputted sample is used
    signal_input_history.push_back(sample);
    signal_input_history.erase(signal_input_history.begin());

//    // converts double vector to complex double valarray
//    std::valarray<std::complex<double>> complex_coeff(b_coefficients.size());
//    std::valarray<std::complex<double>> complex_input_history(b_coefficients.size());
//    for (int i = 0; i < b_coefficients.size(); ++i) {
//        complex_coeff[i] = (std::complex<double>) b_coefficients[i];
//        complex_input_history[i] = (std::complex<double>) signal_input_history[i];
//    }
//    fft(complex_coeff);
//    fft(complex_input_history);
//    std::valarray<std::complex<double>> result_array = complex_coeff * complex_input_history;
//    inv_fft(result_array);
//    std::complex<double> result_value = result_array.sum();
//    std::cout << result_value << std::endl;

    // performs sum{k=0->N}(b_k * x[n - k])
    double result = 0.0;
    int final_index = (int) signal_input_history.size() - 1;
    for (int i = 0; i < b_coefficients.size(); ++i) {
        result += b_coefficients[i] * signal_input_history[final_index - i];
    }
    return result;
}

std::vector<double> FiniteImpulseResponseFilter::get_coefficients() {
    /*
     * return: Vector containing the filter coefficients
     */
    return b_coefficients;
}

#endif