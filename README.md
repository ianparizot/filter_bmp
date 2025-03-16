# Filters for bmp files

## Description

This project is meant to transform bmp files to blurred files, or with an edge detection, a grayscale filter and a reflected filter.

- **Windows Operating System**: This project is designed to run on Windows.
- **CMake**: You need to have CMake installed. You can download it from [CMake's official website](https://cmake.org/download/).
- **Compiler**: You will need a C++ compiler. Options include:
    - [MinGW](http://www.mingw.org/) (Minimalist GNU for Windows)
    - [Visual Studio](https://visualstudio.microsoft.com/) (Community edition is free)

## Installation

1. **Clone the Repository**: Open a terminal (Command Prompt or PowerShell) and run the following command:

   ```bash
   git clone https://github.com/ianparizot/filters.git

2. **Navigate to the cloned directory**: Open a terminal and run:

   ```bash
   cd filter
3. **Make sure you have the correct version of cmake:
   ```bash
   cmake --version
   ```
   If it's not 3.30 or higher, please update cmake.
4. **Create a build directory and navigate into it**:
   ```bash
   mkdir build
   cd build
   ```
5. **If you are using Visual Studio**:
   ```bash
   cmake .. -G "Visual Studio 16 2019"  # Adjust the version as necessary
   cmake --build . --config Release
   ```
6. **If you are using MinGW**:
   ```bash
   cmake .. -G "MinGW Makefiles"
   mingw32-make
   ```
The executable will be in the build directory, so add this path to PATH in the system environment variables.
## Usage
```bash
filter_bmp -(filters: b (blurr), g (grayscale), e (edges) and r (reverse)) path/to/your/image [name of your output files, if none: it will be output.bmp]
```
## License
This application is under the MIT License
For more information, se the LICENSE file
## Acknowledgements
I have been inspired by CS50's week 5 problem filter-more.
For other libraries, they are displayed in code comments.