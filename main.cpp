#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#ifndef DATA_HANDLER_HPP
#include "data_handler.hpp"
#endif

#ifndef WAV_HANDLER_HPP
#include "wav_handler.hpp"
#endif

#ifndef FILTER_HPP
#include "classes/Filter.hpp"
#endif

#ifndef FIR_FILTER_HPP
#include "classes/FiniteImpulseResponseFilter.hpp"
#endif

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

typedef vector<vector<double>> vector_2d_double;

tuple<vector<double>, vector_2d_double> run_experiment(
    FilterType filter_type,
    double sampling_frequency,
    const vector<double>& cut_off_frequencies,
    const vector_2d_double& wave_data,
    int num_taps = 50  // total number of coefficients (N) = (2 * num_taps) + 1
) {
    /* Runs an experiment (applying an FIR filter to inputted data). */

    cout << endl << "Calculating coefficients..." << endl;
    auto t1 = high_resolution_clock::now();
    // initialises a low pass FIR filter
    FiniteImpulseResponseFilter filter = FiniteImpulseResponseFilter(
        filter_type, sampling_frequency, {cut_off_frequencies}, num_taps
    );
    auto t2 = high_resolution_clock::now();

    duration<double, milli> coeff_time = t2 - t1;
    cout << "Took " << coeff_time.count() << " ms" << endl;

    cout << "Filtering signal..." << endl;
    t1 = high_resolution_clock::now();
    // the filter is applied to the generated signal and saved to a vector
    vector_2d_double filtered_data;
    filtered_data.resize(wave_data.size());
    for (int i = 0; i < wave_data.size(); ++i) {
        for (double data_sample : wave_data[i]) {
            filtered_data[i].push_back(filter.apply_filter(data_sample));
        }
    }
    t2 = high_resolution_clock::now();

    duration<double, milli> filter_time = t2 - t1;
    cout << "Took " << filter_time.count() << " ms" << endl;

    return make_tuple(filter.get_coefficients(), filtered_data);
}

void run_experiment_wrapper(
    const string& file_name,
    FilterType filter_type,
    double sample_rate,
    const vector<double>& cut_off_frequencies,
    const vector<double>& x_vector,
    const vector_2d_double& data_vector,
    bool is_wav = false,
    int num_taps = 50
) {
    /* Wrapper function for run_experiment() - Records results produced by run_experiment(). */

    string filter_type_initials;
    if (filter_type == low_pass) filter_type_initials = "LP";
    else if (filter_type == high_pass) filter_type_initials = "HP";
    else if (filter_type == band_pass) filter_type_initials = "BP";
    else if (filter_type == band_stop) filter_type_initials = "BS";
    else throw runtime_error("Unknown filter type!");

    vector<double> coeffs;
    vector_2d_double filtered_data;
    // runs low pass filter on inputted data
    tie(coeffs, filtered_data) = run_experiment(
        filter_type,
        sample_rate,
        {cut_off_frequencies},
        data_vector,
        num_taps
    );

    // generates an index vector for the filter coefficients
    vector<double> x_axis;
    for (int i = 0; i < coeffs.size(); ++i) {
        x_axis.push_back(double(i));
    }
    // writes the filter coefficients to a .csv file
    string coeff_file_name = filter_type_initials + " coefficients for " + file_name + ".csv";
    write_csv_file(coeff_file_name, x_axis, {coeffs});

    string filtered_file_name = filter_type_initials + " " + file_name;
    // the filtered signal is written to a .csv file
    write_csv_file(
        (filtered_file_name + ".csv"),
        x_vector,
        filtered_data
    );

    if (is_wav) {
        // only asks if the user wants to write WAV file if they inputted a WAV file
        while (true) {
            cout << endl << "Would you like to save the filtered WAV file? (y/n)" << endl;
            char wav_choice;
            cin.ignore();
            cin >> wav_choice;

            if (wav_choice == 'y') {
                // creates a WAV file of the signal
                WavFile filtered_wav = generate_wav(filtered_data, filtered_data.size(), sample_rate);
                write_wav(filtered_wav, (filtered_file_name + ".wav"));
                break;
            } else if (wav_choice == 'n') {
                break;
            }
            cout << "Please select a valid choice ('y' for yes, 'n' for no)" << endl;
        }
    }
}

void run_tests() {
    /* This function runs various experiments to help with testing the program */

    /* Generated sine signal */
    /* ======================================================== */

    int signal_length = 400;
    double begin_value = 0.0;
    double end_value = 4.0 * M_PI;  // signal contains 2 full oscillations
    // 1Hz base signal is equal to a standard sine wave with wavelength = 2PI
    vector<double> frequencies = {1.0, 10.0, 50.0};
    vector<double> amplitudes = {1.0, 0.1, 0.01};
    vector<double> phase_offsets = {0.0, 0.0, 0.0};

    vector<double> sine_x_vector, sine_wave_data;
    double sine_sampling_frequency;
    // generates a sine based signal based on inputted frequencies
    tie(sine_wave_data, sine_sampling_frequency) = generate_sine_signal(
        frequencies,  // Hz
        amplitudes,
        phase_offsets,
        signal_length,
        begin_value,
        end_value
    );
    // creates x-axis for data (measured in seconds)
    for (int i = 0; i < sine_wave_data.size(); ++i) {
        sine_x_vector.push_back(double(i / sine_sampling_frequency));
    }
    cout << "Sine sample rate = " << sine_sampling_frequency << endl;

    string sine_file_name = "noisy_sine";
    // writes the generated data to a .csv file
    write_csv_file(
        (sine_file_name + ".csv"),
        sine_x_vector,
        {sine_wave_data}  // only 1 channel
    );

    /* Runs experiments on generated data */
    /* ---------------------------------- */

    /* Low pass experiment */
    cout << endl << "Sine low pass experiment" << endl;
    // should keep 1Hz frequency (amp = 1)
    run_experiment_wrapper(
        sine_file_name,
        low_pass,
        sine_sampling_frequency,
        {5.0},
        sine_x_vector,
        {sine_wave_data}
    );

    /* High pass experiment */
    cout << endl << "Sine high pass experiment" << endl;
    // should keep 50Hz frequency (amp = 0.01)
    run_experiment_wrapper(
        sine_file_name,
        high_pass,
        sine_sampling_frequency,
        {15.0},
        sine_x_vector,
        {sine_wave_data}
    );

    /* Band pass experiment */
    cout << endl << "Sine band pass experiment" << endl;
    // should keep 10Hz frequency (amp = 0.1)
    run_experiment_wrapper(
        sine_file_name,
        band_pass,
        sine_sampling_frequency,
        {5.0, 15.0},
        sine_x_vector,
        {sine_wave_data}
    );

    /* Inputted WAV file */
    /* ======================================================== */

    // reads WAV file using path
    WavFile wav_file = read_wav("test_recording.wav");
    vector_2d_double wave_data = convert_data_to_double(wav_file.data);
    double sampling_frequency = 1.0 * wav_file.sample_rate;

    // generates x-axis for .csv file
    vector<double> x_vector;
    // all channels should have the same length
    for (int i = 0; i < wave_data[0].size(); ++i) {
        x_vector.push_back(double(i / sampling_frequency));
    }
    string file_name = "test_recording";

    // writes WAV data to .csv file
    write_csv_file((file_name + ".csv"), x_vector, wave_data);

    /* Runs experiments on WAV file */
    /* ---------------------------- */

    /* Low pass experiment */
    cout << endl << "WAV low pass experiment" << endl;
    run_experiment_wrapper(
        file_name,
        low_pass,
        sampling_frequency,
        {150.0},
        x_vector,
        {wave_data},
        true
    );

    /* High pass experiment */
    cout << endl << "WAV high pass experiment" << endl;
    run_experiment_wrapper(
        file_name,
        high_pass,
        sampling_frequency,
        {3500.0},
        x_vector,
        {wave_data},
        true
    );

    /* Band pass experiment */
    cout << endl << "WAV band pass experiment" << endl;
    run_experiment_wrapper(
        file_name,
        band_pass,
        sampling_frequency,
        {200.0, 3000.0},
        x_vector,
        {wave_data},
        true
    );
}

void debug_mode() {
    /* Somewhat hidden menu for testing the program and converting WAV files to CSV */

    cout << "Debug mode" << endl;
    cout << "=======================================" << endl;

    while(true) {
        cout << endl << "Please select one of the following:" << endl;
        cout << "1. Convert WAV to CSV" << endl << "2. Run tests" << endl << "3. Back to main menu" << endl;
        int selection;
        cin >> selection;

        bool quit = false;
        switch (selection) {
            case 1: {
                cout << "Please enter name of WAV file (including .wav):" << endl;
                string wav_path;
                cin.ignore();
                getline(cin, wav_path, '\n');

                try {
                    // reads wav file (can throw exception)
                    WavFile wav_file = read_wav(wav_path);
                    // removes .wav suffix
                    if (wav_path.substr(wav_path.length() - 4, 4) == ".wav") {
                        wav_path.erase(wav_path.end() - 4, wav_path.end());
                    }

                    // converts data and sample rate to doubles
                    vector_2d_double wave_data = convert_data_to_double(wav_file.data);
                    double sample_rate = 1.0 * wav_file.sample_rate;

                    // generates x-axis for .csv file
                    vector<double> x_vector;
                    // all channels should have the same length
                    for (int i = 0; i < wave_data[0].size(); ++i) {
                        x_vector.push_back(double(i / sample_rate));
                    }

                    // writes WAV data to csv file (can throw exception)
                    write_csv_file((wav_path + ".csv"), x_vector, wave_data);
                }
                catch (exception &e) {
                    // exception occurs when file is not found, or is inaccessible
                    cout << "Exception occurred: " << e.what() << endl;
                    cout << "Please make sure the file is in the same directory as this program (.exe)" << endl;
                }
                break;
            }
            case 2: {
                try {
                    run_tests();
                }
                catch (exception &e) {
                    // exception can occur when certain WAV/CSV files are missing, or are inaccessible
                    cout << "Exception occurred: " << e.what() << endl;
                }
                break;
            }
            case 3:
                // allows the while true loop to be broken
                quit = true;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        // quit = true when user selects option 3
        if (quit) break;
    }
}

void filtering_menu(vector_2d_double& data_vector, double sample_rate, const string& file_name, bool is_wav = false) {
    /* Menu for filtering a signal */

    // generates x-axis for .csv file
    vector<double> x_vector;
    // all channels should have the same length
    for (int i = 0; i < data_vector[0].size(); ++i) {
        x_vector.push_back(double(i / sample_rate));
    }

    while (true) {
        cout << endl << "Please select a filter:" << endl;
        cout << "1. Low pass FIR" << endl << "2. High pass FIR" << endl << "3. Band pass FIR" << endl << "4. Go back" << endl;
        int selection;
        cin >> selection;
        bool quit = false;

        switch (selection) {
            case 1: {
                /* Low pass */

                cout << "Please enter your cut-off frequency in Hz (e.g. 5, 10, 150):" << endl;
                double cut_off;
                cin >> cut_off;

                run_experiment_wrapper(
                    file_name,
                    low_pass,
                    sample_rate,
                    {cut_off},
                    x_vector,
                    {data_vector},
                    is_wav
                );
                break;
            }
            case 2: {
                /* High pass */

                cout << "Please enter your cut-off frequency in Hz (e.g. 15, 120, 3500):" << endl;
                double cut_off;
                cin >> cut_off;

                run_experiment_wrapper(
                    file_name,
                    high_pass,
                    sample_rate,
                    {cut_off},
                    x_vector,
                    {data_vector},
                    is_wav
                );
                break;
            }
            case 3: {
                /* Band pass */

                cout << "Please enter your first cut-off frequency in Hz (e.g. 5, 30, 200):" << endl;
                double cut_off1;
                cin >> cut_off1;
                cout << "Please enter your second cut-off frequency in Hz (e.g. 15, 100, 3000):" << endl;
                double cut_off2;
                cin >> cut_off2;

                run_experiment_wrapper(
                    file_name,
                    band_pass,
                    sample_rate,
                    {cut_off1, cut_off2},
                    x_vector,
                    {data_vector},
                    is_wav
                );
                break;
            }
            case 4:
                // allows the while true loop to be broken
                quit = true;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        // quit = true when user selects option 4
        if (quit) break;
    }
}

int main() {
    cout << "Digital signal filtering tool" << endl;
    cout << "=======================================" << endl;

    while (true) {
        cout << endl << "Please select one of the following:" << endl;
        cout << "1. Read WAV file" << endl << "2. Read CSV file" << endl << "3. Quit" << endl;
        int selection;
        cin >> selection;

        bool quit = false;
        switch (selection) {
            case 1: {
                cout << "Please enter name of WAV file (including .wav):" << endl;
                string wav_path;
                cin.ignore();
                getline(cin, wav_path, '\n');

                try {
                    // reads wav file (can throw exception)
                    WavFile wav_file = read_wav(wav_path);

                    // converts data and sample rate to doubles
                    vector_2d_double wave_data = convert_data_to_double(wav_file.data);
                    double sampling_frequency = 1.0 * wav_file.sample_rate;

                    // removes .wav suffix
                    if (wav_path.substr(wav_path.length() - 4, 4) == ".wav") {
                        wav_path.erase(wav_path.end() - 4, wav_path.end());
                    }
                    filtering_menu(wave_data, sampling_frequency, wav_path, true);
                }
                catch (exception &e) {
                    // exception occurs when file is not found, or is inaccessible
                    cout << "Exception occurred: " << e.what() << endl;
                    cout << "Please make sure the file is in the same directory as this program (.exe)" << endl;
                }
                break;
            }
            case 2: {
                cout << "Please enter name of CSV file (including .csv):" << endl;
                string csv_path;
                cin.ignore();
                getline(cin, csv_path, '\n');

                try {
                    // reads csv file into a 2D vector (can throw exception)
                    vector_2d_double csv_data = read_csv_file(csv_path);
                    vector_2d_double wave_data;
                    // selects all but the first column (x-axis) in csv file
                    for (int i = 1; i < csv_data.size(); ++i) {
                        wave_data.push_back(csv_data[i]);
                    }
                    // sample rate = 1 / time period
                    double sampling_frequency = 1.0 / (csv_data[0][1] - csv_data[0][0]);

                    // removes .csv suffix
                    if (csv_path.substr(csv_path.length() - 4, 4) == ".csv") {
                        csv_path.erase(csv_path.end() - 4, csv_path.end());
                    }
                    filtering_menu(wave_data, sampling_frequency, csv_path, false);
                }
                catch (exception &e) {
                    // exception occurs when file is not found, or is inaccessible
                    cout << "Exception occurred: " << e.what() << endl;
                    cout << "Please make sure the file is in the same directory as this program" << endl;
                }
                break;
            }
            case 3:
                // allows the while true loop to be broken
                quit = true;
                break;
            case 4:
                debug_mode();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        // quit = true when user selects option 3
        if (quit) break;
    }
    return 0;
}
