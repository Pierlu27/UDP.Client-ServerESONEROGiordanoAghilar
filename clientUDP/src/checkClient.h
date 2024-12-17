/*
 ============================================================================
 Name        : checkClient.h
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Header file defining functions for input validation and password checks.
 ============================================================================
 */

#ifndef CHECK
#define CHECK

#include <stdbool.h>
#include "support.h"   // Header file for client-side support functions

/**
 * @brief Checks if the specified password length is valid.
 *
 * This function verifies whether the `length` parameter is within the allowed range.
 * A valid length must be between 6 and a predefined maximum length `PASS_LENGTH`.
 *
 * @param[in] length: the desired password length to be validated.
 * @return `true` if the length is within the valid range.
 * @return `false` if the length is out of range, with an error message displayed.
 */
bool pass_lenght(int length);

/**
 * @brief Checks if the input matches the quit command.
 *
 * This function compares the user input to the predefined quit character ('q').
 * If the input matches, it signals that the process should close.
 *
 * @param[in] input: an array of characters representing the user input.
 * @return `true` if the input matches the quit command.
 * @return `false` otherwise.
 */
bool checkClose(char input[]);

/**
 * @brief Validates the initial character of the password type.
 *
 * This function checks if the character provided matches one of the allowed
 * initial characters for password types: 'n', 'a', 'm', or 's'.
 *
 * @param[in] character: the character to validate.
 * @return `true` if the character is valid.
 * @return `false` otherwise.
 */
bool checkFirst(char character);

/**
 * @brief Checks if the input string contains a space character.
 *
 * This function searches for the presence of a space (' ') in the provided string.
 * It uses the `strchr` function to perform the search.
 *
 * @param[in] input: the input string to be checked.
 * @return `true` if a space character is found in the input string.
 * @return `false` otherwise.
 */
bool checkSpace(char* input);

/**
 * @brief Checks if the input length exceeds the allowed buffer size.
 *
 * This function verifies whether the input provided by the user fits within the buffer size.
 * It specifically checks if the last character in the input is a newline character (`\n`),
 * indicating that the input did not exceed the buffer limit. If the input exceeds the limit,
 * it clears the remaining characters in the standard input buffer.
 *
 * @param[in] input An array of characters representing the user's input.
 *                  The array should be null-terminated (`\0`).
 * @param[in] BUFFER_SIZE The maximum size of the input buffer, including space for the
 *                        null-terminator (`\0`) and newline (`\n`).
 * @param[in] hflag A boolean variable indicating whether the help menu is being used
 *
 * @return `true` if the input length is within the allowed buffer size, `false` otherwise.
 *
 * @warning The function assumes that the input array is properly null-terminated and valid.
 *          Passing an invalid or uninitialized pointer may result in undefined behavior.
 */
bool checkLength(char input[], int BUFFER_SIZE, bool hflag);

#endif /* CHECK */
