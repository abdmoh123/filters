//
// Created by Abdul on 02/01/2023.
//

#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>

std::tuple<std::vector<double>, double> generate_sine_signal(
    std::vector<double> frequencies,
    std::vector<double> amplitudes,
    std::vector<double> phase_offsets,
    int signal_length,
    double begin_value,
    double end_value
);

void write_csv_file(
    const std::string& file_name,
    std::vector<double> x_vector,
    std::vector<std::vector<double>> y_vectors
);
std::vector<std::vector<double>> read_csv_file(const std::string& file_name);

#endif //DATA_HANDLER_HPP
