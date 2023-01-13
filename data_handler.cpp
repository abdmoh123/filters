//
// Created by Abdul on 02/01/2023.
//

#ifndef DATA_HANDLER_HPP

#include "data_handler.hpp"

using namespace std;

tuple<vector<double>, double> generate_sine_signal(
    vector<double> frequencies,
    vector<double> amplitudes,
    vector<double> phase_offsets,
    int signal_length,
    double begin_value,
    double end_value
) {
    /* Generates a signal using multiple input frequencies
     *
     * param frequencies: Vector of frequencies to generate within the signal
     * param amplitudes: Amplitudes for each frequency in the signal
     * param phase_offsets: Phase offset for each frequency in the signal
     * param signal_length: Length of the signal vector (number of .csv rows)
     * param begin_value: First value of input vector x
     * param end_value: Final value of input vector x
     * return: Tuple containing sine signal and its sample rate
     */

    // checks if the inputted vectors have the same length
    if (frequencies.size() != amplitudes.size() || amplitudes.size() != phase_offsets.size()) {
        cerr << "Error: Number of frequencies, amplitudes and offsets are not equal!" << endl;
        exit(EXIT_FAILURE);
    }

    vector<double> signal;
    vector<double> x_vector;
    double x = begin_value;
    double iteration = (end_value - begin_value) / double(signal_length);
    while (x < end_value) {
        signal.push_back(0.0);
        x_vector.push_back(x);
        x += iteration;
    }

    // generates a combined waveform using inputted frequencies and amplitudes
    for (int i = 0; i < frequencies.size(); ++i) {
        double frequency = frequencies[i];
        double amplitude = amplitudes[i];
        double x_offset = phase_offsets[i];
        // generates sine wave for each amplitude and frequency pair
        for (int j = 0; j < signal_length; ++j) {
            double y = amplitude * sin(frequency * x_vector[j] - x_offset);
            // adding to signal value allows the multiple frequencies to be superimposed
            signal[j] = signal[j] + y;
        }
    }

    // gets sample rate by assuming sin(x) has a frequency of 1Hz
    double sample_rate = signal_length / (end_value / (2.0 * M_PI));
    return make_tuple(signal, sample_rate);
}

void write_csv_file(
    const string& file_name,
    vector<double> x_vector,
    vector<vector<double>> y_vectors
) {
    /* Saves the inputted vector to a .csv file
     *
     * param file_name: Name of file
     * param x_vector: Input data used to generate sine signal (x)
     * param y_vectors: Output signal (y) - can be multiple vectors
     */

    // adds .csv suffix if it doesn't already exist
    string full_file_name = file_name;
    if (file_name.substr(file_name.length() - 4, 4) != ".csv") {
        full_file_name = file_name + ".csv";
    }

    // creates a file holding the [x, y] values of the simulated tremor wave
    ofstream csv_file(full_file_name.c_str());

    // crashes the program if the file cannot be opened
    if (!csv_file.is_open()) {
        string message = "Unable to open file " + string(full_file_name) + "!";
        throw runtime_error(message);
    }

    // writes values to the file
    for (int i = 0; i < x_vector.size(); ++i) {
        csv_file << x_vector[i];
        // csv file will have each channel separate
        for (auto & channel : y_vectors) {
            csv_file << "," << channel[i];
        }
        csv_file << endl;
    }

    csv_file.close(); // closes file after finishing writing
}

vector<vector<double>> read_csv_file(const string& file_name) {
    /* Reads CSV file
     *
     * param file_name: Name of file
     * return: CSV file contents in 2D vector form
     */

    // adds .csv suffix if it doesn't already exist
    string full_file_name = file_name;
    if (file_name.substr(file_name.length() - 4, 4) != ".csv") {
        full_file_name = file_name + ".csv";
    }

    // creates a file holding the [x, y] values of the simulated tremor wave
    ifstream csv_file(full_file_name);

    // crashes the program if the file cannot be opened
    if (!csv_file.is_open()) {
        string message = "Unable to open file " + string(full_file_name) + "!";
        throw runtime_error(message);
    }

    vector<vector<double>> data_matrix;
    vector<double> row_vector;
    // reads first row (to get number of columns)
    string row_string;
    getline(csv_file, row_string);

    stringstream str(row_string);
    string dat;
    // splits row using ',' delimiter
    while (getline(str, dat, ',')) {
        // sub-vectors for each column are created
        data_matrix.push_back({stod(dat)});
    }

    // fills the 2D vector with the rest of the data
    while (getline(csv_file, row_string)) {
        stringstream str_2(row_string);
        int i = 0;
        while (getline(str_2, dat, ',')) {
            data_matrix[i].push_back(stod(dat));
            ++i;
        }
    }
    csv_file.close();  // closes file after finishing reading

    return data_matrix;
}

#endif
