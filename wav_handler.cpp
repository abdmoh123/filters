//
// Created by Abdul on 07/01/2023.
//

#ifndef WAV_HANDLER_HPP
#include "wav_handler.hpp"

using namespace std;

bool is_WAV(const char * actual_value, const char * expected_value) {
    /* Checks if WavFile object follows WAV format (correct chunk IDs) */

    if (strcmp(actual_value, expected_value) != 0) {
        cerr << "Error: File not WAV file!" << endl << actual_value << " != " << expected_value << endl;
        return false;
    }
    return true;
}

vector<vector<double>> convert_data_to_double(const vector<vector<signed short>> & data) {
    /* Converts 2D int vector into 2D double vector */

    double max_value = 32767;
    vector<vector<double>> double_data;
    for (const vector<signed short> & channel : data) {
        vector<double> double_channel;
        for (signed short sample : channel) {
            // normalises the signal between 1 and -1
            double_channel.push_back(sample / max_value);
        }
        double_data.push_back(double_channel);
    }
    return double_data;
}

vector<vector<signed short>> convert_data_to_short(const vector<vector<double>> & data) {
    /* Converts 2D double vector into 2D int vector */

    int max_value = 32767;
    int min_value = -32767;
    bool clipped = false;
    vector<vector<signed short>> short_data;
    for (const vector<double> & channel : data) {
        vector<signed short> short_channel;
        for (double sample : channel) {
            // reverses normalisation and rounds double values into integers
            int unclipped_sample = lround(sample * max_value);
            // clips sample values between +32767 and -32768
            if (unclipped_sample > max_value) {
                unclipped_sample = max_value;
                clipped = true;
            }
            else if (unclipped_sample < min_value) {
                unclipped_sample = min_value;
                clipped = true;
            }
            // clipped int is cast to signed short datatype
            auto short_sample = (signed short) unclipped_sample;
            short_channel.push_back(short_sample);
        }
        short_data.push_back(short_channel);
    }
    if (clipped) cout << "Warning: Some data was clipped while writing the file" << endl;
    return short_data;
}

WavFile read_wav(const string& file_name) {
    /* Reads a WAV file and stores its data in a WavFile object */

    // adds .wav suffix if it doesn't already exist
    string full_file_name = file_name;
    if (file_name.substr(file_name.length() - 4, 4) != ".wav") {
        full_file_name = file_name + ".wav";
    }

    // initialises a wav file object
    WavFile wav_file;

    // prepares reader
    FILE * fp = fopen(full_file_name.c_str(), "rb");
    // checks if file was read successfully
    if (fp == nullptr) {
        string message = "Error: Failed to read file " + string(full_file_name) + "!";
        throw runtime_error(message);
    }
    cout << endl << "Reading WAV file..." << endl;

    // assigns the chunk_id
    size_t len = fread(wav_file.chunk_id, sizeof(unsigned char), 4, fp);
    wav_file.chunk_id[len] = '\0';  // removes excess data read
    cout << "WAV file chunk_id: " << wav_file.chunk_id << endl;
    // checks if WAV format is followed
    if (!is_WAV((char *) wav_file.chunk_id, "RIFF")) {
        exit(EXIT_FAILURE);
    }

    // assigns the chunk_size
    fread(&wav_file.chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file chunk_size: " << wav_file.chunk_size << endl;

    // assigns the file_format
    len = fread(wav_file.file_format, sizeof(unsigned char), 4, fp);
    wav_file.file_format[len] = '\0';  // removes excess data read
    cout << "WAV file format: " << wav_file.file_format << endl;
    // checks if WAV format is followed
    if (!is_WAV((char *) wav_file.file_format, "WAVE")) {
        exit(EXIT_FAILURE);
    }

    // checks for JUNK header
    len = fread(wav_file.junk_chunk_id, sizeof(unsigned char), 4, fp);
    wav_file.junk_chunk_id[len] = '\0';
    if (strcmp((const char *) wav_file.junk_chunk_id, "JUNK") == 0) {
        cout << "JUNK header found!" << endl;

        // gets number of bytes in the JUNK header
        fread(&wav_file.junk_chunk_size, sizeof(unsigned int), 1, fp);
        cout << "Skipping " << wav_file.junk_chunk_size << " bytes..." << endl;
        // skips through JUNK header
        fseek(fp, (int) wav_file.junk_chunk_size, SEEK_CUR);

        cout << "WAV file junk_chunk_id: " << wav_file.junk_chunk_id << endl;
        cout << "WAV file junk_chunk_size: " << wav_file.junk_chunk_size << endl;

        // assigns the fmt_chunk_id
        len = fread(wav_file.fmt_chunk_id, sizeof(unsigned char), 4, fp);
        wav_file.fmt_chunk_id[len] = '\0';
        cout << "WAV file fmt_chunk_id: " << wav_file.fmt_chunk_id << endl;
    }
    else {
        // moves "fmt " value in junk_chunk_id to fmt_chunk_id
        strcpy((char *) wav_file.fmt_chunk_id, (const char *) wav_file.junk_chunk_id);
        // changes value in junk_chunk_id to "JUNK"
        strcpy((char *) wav_file.junk_chunk_id, "JUNK");
        // junk_chunk_size is 0 (no JUNK chunk was found in WAV file)
        wav_file.junk_chunk_size = 0;
    }
    // checks if WAV format is followed
    if (!is_WAV((char *) wav_file.fmt_chunk_id, "fmt ")) {
        exit(EXIT_FAILURE);
    }

    // assigns the fmt_chunk_size
    fread(&wav_file.fmt_chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file fmt_chunk_size: " << wav_file.fmt_chunk_size << endl;

    // assigns the audio_format
    fread(&wav_file.audio_format, sizeof(unsigned short), 1, fp);
    cout << "WAV file audio_format: " << wav_file.audio_format << endl;

    // assigns the num_channels
    fread(&wav_file.num_channels, sizeof(unsigned short), 1, fp);
    cout << "WAV file num_channels: " << wav_file.num_channels << endl;

    // assigns the sample_rate
    fread(&wav_file.sample_rate, sizeof(unsigned int), 1, fp);
    cout << "WAV file sample_rate: " << wav_file.sample_rate << endl;

    // assigns the byte_rate
    fread(&wav_file.byte_rate, sizeof(unsigned int), 1, fp);
    cout << "WAV file byte_rate: " << wav_file.byte_rate << endl;

    // assigns the block_align
    fread(&wav_file.block_align, sizeof(unsigned short), 1, fp);
    cout << "WAV file block_align: " << wav_file.block_align << endl;

    // assigns the bits_per_sample
    fread(&wav_file.bits_per_sample, sizeof(unsigned short), 1, fp);
    cout << "WAV file bits_per_sample: " << wav_file.bits_per_sample << endl;

    // skips through extra params if they exist
    if (wav_file.fmt_chunk_size > 16) {
        auto extra_dats = (int) wav_file.fmt_chunk_size - 16;
        fseek(fp, extra_dats, SEEK_CUR);
    }

    // assigns the data_chunk_id
    fread(wav_file.data_chunk_id, sizeof(unsigned char), 4, fp);
    wav_file.data_chunk_id[len] = '\0';
    cout << "WAV file data_chunk_id: " << wav_file.data_chunk_id << endl;
    // checks if WAV format is followed
    if (!is_WAV((char *) wav_file.data_chunk_id, "data")) {
        exit(EXIT_FAILURE);
    }

    // assigns data_chunk_size
    fread(&wav_file.data_chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file data_chunk_size: " << wav_file.data_chunk_size << endl;

    // reads data and puts it into a vector
    vector<vector<signed short>> data_vector;
    data_vector.resize(wav_file.num_channels);  // splits into 2D vector based on number of channels
    for (int _ = 0; _ < (wav_file.data_chunk_size) / sizeof(signed short) / wav_file.num_channels; ++_) {
        signed short temp;
        // separates data samples by channel
        for (int j = 0; j < wav_file.num_channels; ++j) {
            // 16 bit samples are saved as 2's complement signed integers (each channel is a short)
            fread(&temp, sizeof(signed short), 1, fp);
            data_vector[j].push_back(temp);
        }
    }
    wav_file.data = data_vector;

    // closes file reader
    fclose(fp);

    return wav_file;
}

void write_wav(WavFile wav_file, const std::string& file_name) {
    /* Writes a WAV file using data stored in a WavFile object (+ inputted file name) */

    // adds .wav suffix if it doesn't already exist
    string full_file_name = file_name;
    if (file_name.substr(file_name.length() - 4, 4) != ".wav") {
        full_file_name = file_name + ".wav";
    }

    // prepares reader
    FILE * fp = fopen(full_file_name.c_str(), "wb");
    // checks if file was read successfully
    if (fp == nullptr) {
        cerr << "Error: Failed to read file!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << endl << "Writing WAV file " << full_file_name << "..." << endl;

    // writes the chunk_id ("RIFF")
    fwrite(wav_file.chunk_id, sizeof(unsigned char), 4, fp);
    cout << "WAV file chunk_id: " << wav_file.chunk_id << endl;

    // writes the chunk_size
    fwrite(&wav_file.chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file chunk_size: " << wav_file.chunk_size << endl;

    // writes the file_format ("WAVE")
    fwrite(wav_file.file_format, sizeof(unsigned char), 4, fp);
    cout << "WAV file format: " << wav_file.file_format << endl;

    // writes the fmt_chunk_id ("fmt ")
    fwrite(wav_file.fmt_chunk_id, sizeof(unsigned char), 4, fp);
    cout << "WAV file fmt_chunk_id: " << wav_file.fmt_chunk_id << endl;

    // writes the fmt_chunk_size
    fwrite(&wav_file.fmt_chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file fmt_chunk_size: " << wav_file.fmt_chunk_size << endl;

    // writes the audio_format
    fwrite(&wav_file.audio_format, sizeof(unsigned short), 1, fp);
    cout << "WAV file audio_format: " << wav_file.audio_format << endl;

    // writes the num_channels
    fwrite(&wav_file.num_channels, sizeof(unsigned short), 1, fp);
    cout << "WAV file num_channels: " << wav_file.num_channels << endl;

    // writes the sample_rate
    fwrite(&wav_file.sample_rate, sizeof(unsigned int), 1, fp);
    cout << "WAV file sample_rate: " << wav_file.sample_rate << endl;

    // writes the byte_rate
    fwrite(&wav_file.byte_rate, sizeof(unsigned int), 1, fp);
    cout << "WAV file byte_rate: " << wav_file.byte_rate << endl;

    // writes the block_align
    fwrite(&wav_file.block_align, sizeof(unsigned short), 1, fp);
    cout << "WAV file block_align: " << wav_file.block_align << endl;

    // writes the bits_per_sample
    fwrite(&wav_file.bits_per_sample, sizeof(unsigned short), 1, fp);
    cout << "WAV file bits_per_sample: " << wav_file.bits_per_sample << endl;

    // writes extra empty bytes if the size of the fmt chunk is larger than expected
    unsigned char extra_dat = 0;
    if (wav_file.fmt_chunk_size > 16) {
        unsigned int extra_dats = wav_file.fmt_chunk_size - 16;
        for (int _ = 0; _ < extra_dats; ++_) {
            fwrite(&extra_dat, sizeof(unsigned char), 1, fp);
        }
    }

    // writes the data_chunk_id ("data")
    fwrite(wav_file.data_chunk_id, sizeof(unsigned char), 4, fp);
    cout << "WAV file data_chunk_id: " << wav_file.data_chunk_id << endl;

    // writes the data_chunk_size
    fwrite(&wav_file.data_chunk_size, sizeof(unsigned int), 1, fp);
    cout << "WAV file data_chunk_size: " << wav_file.data_chunk_size << endl;

    // writes the data content
    int count = 0;
    for (int i = 0; i < (wav_file.data_chunk_size) / sizeof(signed short) / wav_file.num_channels; ++i) {
        signed short temp;
        for (int j = 0; j < wav_file.num_channels; ++j) {
            temp = wav_file.data[j][i];
            // 16 bit samples are saved as 2's complement signed integers
            fwrite(&temp, sizeof(signed short), 1, fp);
        }
        ++count;
    }

    // closes file writer
    fclose(fp);
}

WavFile generate_wav(
    const vector<vector<double>> & data,
    unsigned short num_channels,
    double sample_rate
) {
    /* Generates a WAV file using a vector of data (signal) */

    cout << endl << "Generating WAV file..." << endl;

    WavFile wav_file;

    // converts inputted data to correct type (signed short)
    wav_file.data = convert_data_to_short(data);

    // header chunk IDs
    strcpy((char *) wav_file.chunk_id, "RIFF");
    strcpy((char *) wav_file.file_format, "WAVE");
    strcpy((char *) wav_file.fmt_chunk_id, "fmt ");
    strcpy((char *) wav_file.data_chunk_id, "data");

    wav_file.audio_format = (unsigned short) 1;  // PCM is used
    wav_file.num_channels = (unsigned short) num_channels;
    wav_file.sample_rate = (unsigned int) lround(sample_rate);  // converts sample rate to int
    wav_file.bits_per_sample = (unsigned short) 16;  // 16 bit signals are used

    // block align = number of channels * bytes per sample
    wav_file.block_align = (unsigned short) (num_channels * wav_file.bits_per_sample / 8);
    // byte rate = sample rate * number of channels * bytes per sample
    wav_file.byte_rate = (unsigned int) (sample_rate * wav_file.block_align);

    // JUNK header will not be used so size is set to 0 bytes
    strcpy((char *) wav_file.junk_chunk_id, "JUNK");
    wav_file.junk_chunk_size = 0;

    // size of data chunk content = bytes per data * number of data
    wav_file.data_chunk_size = wav_file.num_channels * wav_file.data[0].size() * sizeof(signed short);
    wav_file.fmt_chunk_size = 16;  // 16 for PCM
    int id_bytes = 3 * 5;  // 20 bytes for IDs excluding "RIFF"

    // total chunk size = (bytes of IDs) + (bytes of chunk sizes) + (fmt chunk size) + (data chunk size)
    wav_file.chunk_size = id_bytes + (sizeof(unsigned int) * 2) + wav_file.fmt_chunk_size + wav_file.data_chunk_size;

    return wav_file;
}

#endif
