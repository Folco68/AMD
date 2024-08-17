/*
* 
*    AMD: Alarm Mask Decoder. Print the bits triggered in the field of a 32 bits alarm
*    Copyright (C) 2024 Martial Demolins
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cstring>

// Return values
enum { NO_ERROR = 0, ERROR_WRONG_NUMBER_OF_ARGS = -1, ERROR_MASK_TOO_LONG = -2, ERROR_NOT_AN_INTEGER = -3};

int main(int argc, char* argv[])
{
    // 1. Preamble
    std::cout << std::endl;
    std::cout << "AMD is an Alarm Mask Decoder." << std::endl;
    std::cout << "Syntax: amd [alarm mask]" << std::endl;
    std::cout << "The mask is in the column \"Information Events\" of the PLMS log." << std::endl;
    std::cout << "v1.0, License GPL3,  (c)2024 Martial Demolins (Tetra Pak Service, France)." << std::endl;
    std::cout << "https://github.com/folcogh/AMD" << std::endl;
    std::cout << std::endl;

    // 2. Check the number of arguments
    if (argc != 2) {
        std::cout << "Wrong number of arguments." << std::endl;
        exit(ERROR_WRONG_NUMBER_OF_ARGS);
    }

    // 3. Check that the integer is not too big (rough check)
    char* StrMask = argv[1];
    size_t StrMaskLength = strlen(StrMask);

    if (StrMaskLength > 10) {
        std::cout << "The alarm mask is too long." << std::endl;
        exit(ERROR_MASK_TOO_LONG);
    }

    // 4. Validate integer
    for (int i = 0; i < StrMaskLength; i++) {
        if (!isdigit(StrMask[i])) {
            std::cout << "The alarm mask must be an integer." << std::endl;
            exit(ERROR_NOT_AN_INTEGER);
        }
    }

    // 5. Read and print enabled bits
    std::cout << "Bits set:" << std::endl;
    int Mask = atoi(StrMask) & 0xFFFFFFFF; 
    for (int i = 0; i < 32 ; i++) {
        if (Mask & (1 << i)) {
            std::cout << i << std::endl;
        }
    }

    return NO_ERROR;
}
