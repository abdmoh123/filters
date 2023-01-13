# Digital Filtering project

**By Abdul Hawisa**

## Details

- Program was built on windows, so it may be difficult to compile on other devices (e.g. MacOs and Linux).
- To access debug mode, you must enter 4 (hidden option) in the main menu.
  - Warning: If certain CSV or WAV files are missing, the tests will not work!
    - Add a WAV file (2 channel 16 bit) named "test_recording.wav" to the same directory as the program (.exe) if it fails.
- FIR filters have been implemented
  - Low pass, High pass, Band pass
  - They do not use FFT based convolution, so it may be slow on a very large/long signal.
  - Although Band stop exists in the code, it may be inaccessible right now.
- IIR filters exist in the code, but they are not properly implemented (they do not work).

## Todo

- Add IIR filters.
- Improve performance of filters on larger data by utilising FFT.
- Improve reading and writing of WAV files.
- Improve testing.
- Add plotting feature?
