cmake_minimum_required(VERSION 3.17)
project(Digital_filterer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Digital_filterer main.cpp data_handler.cpp data_handler.hpp classes/FiniteImpulseResponseFilter.cpp classes/FiniteImpulseResponseFilter.hpp classes/Filter.hpp classes/InfiniteImpulseResponseFilter.cpp classes/InfiniteImpulseResponseFilter.hpp wav_handler.cpp wav_handler.hpp)