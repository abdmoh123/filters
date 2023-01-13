//
// Created by Abdul on 07/01/2023.
//

#ifndef WAV_HANDLER_HPP
#define WAV_HANDLER_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

typedef struct wav_file {
    unsigned char chunk_id[4];  // contains "RIFF"
    unsigned int chunk_size;  // size of file excluding chunk_id and chunk_size
    unsigned char file_format[4];  // contains "WAVE"
    unsigned char junk_chunk_id[4];  // contains "JUNK"
    unsigned int junk_chunk_size;  // size of "JUNK" chunk (padding)
    unsigned char fmt_chunk_id[4];  // contains "fmt " (including trailing space)
    unsigned int fmt_chunk_size;  // size of the subchunk below (16 for PCM)
    unsigned short audio_format;  // 1 for PCM (other values indicate compression)
    unsigned short num_channels;  // 1 = Mono, 2 = Stereo etc.
    unsigned int sample_rate;  // in Hz
    unsigned int byte_rate;  // sample_rate * num_channels * bits_per_sample / 8
    unsigned short block_align;  // num_channels * bits_per_sample / 8
    unsigned short bits_per_sample;
    unsigned char data_chunk_id[4];  // contains "data"
    unsigned int data_chunk_size;  // size of data (in bytes)
    std::vector<std::vector<signed short>> data;  // actual sound data
} WavFile;

std::vector<std::vector<double>> convert_data_to_double(const std::vector<std::vector<signed short>> & data);
std::vector<std::vector<signed short>> convert_data_to_short(const std::vector<std::vector<double>> & data);

WavFile read_wav(const std::string& file_name);
void write_wav(WavFile wav_file, const std::string& file_name);
WavFile generate_wav(
    const std::vector<std::vector<double>> & data,
    unsigned short num_channels,
    double sample_rate
);

#endif //WAV_HANDLER_HPP
