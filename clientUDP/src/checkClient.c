/*
 ============================================================================
 Name        : checkClient.h
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : C file defining functions for input validation and password checks.
 ============================================================================
 */

#ifndef CHECK
#define CHECKH

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "checkClient.h"

#define PASS_LENGHT 32

/**
 * @brief Checks if the specified password length is valid.
 * @param[in] length: the desired password length to be validated.
 * @return `true` if the length is within the valid range.
 * @return `false` if the length is out of range, with an error message displayed.
 */
bool pass_lenght(int length)
{
	if(length < 6 || length > PASS_LENGHT)
	{
		return false;
	}else return true;
}

/**
 * @brief Checks if the input matches the quit command.
 * @param[in] input: an array of characters representing the user input.
 * @return `true` if the input matches the quit command.
 * @return `false` otherwise.
 */
bool checkClose(char input[]){

	if (strcmp(input, "q") == 0) {
		const char *closMsg = "Closing the process. . .\n";
		typewriterEffect(closMsg,15000);
		return true;
	 }else return false;
}

/**
 * @brief Validates the initial character of the password type.
 * @param[in] character: the character to validate.
 * @return `true` if the character is valid.
 * @return `false` otherwise.
 */
bool checkFirst(char character)
{
	return (character == 'n' || character == 'a' ||  character == 'm' || character == 's' || character == 'u' || character == 'h');
}

/**
 * @brief Checks if the input string contains a space character.
 * @param[in] input: the input string to be checked.
 * @return `true` if a space character is found in the input string.
 * @return `false` otherwise.
 */
bool checkSpace(char* input)
{
	if(input[0]=='h')
	 return true;
	return strchr(input, ' ') != NULL;
}


/**
 * @brief Validates input length against the buffer size.
 * Checks if the user's input fits within the allowed buffer size, ensuring the last
 * character is a newline (`\n`). If the input exceeds the limit, it clears the
 * input buffer using `fflush(stdin)` and returns `false`.
 * @param[in] input The user's input string (null-terminated).
 * @param[in] BUFFER_SIZE The maximum size of the input buffer.
 * @return `true` if the input is valid, `false` if it exceeds the limit.
 * @note `fflush(stdin)` may not work on all platforms. For portability, consider
 *       using `getchar` to clear the buffer.
 */
bool checkLength(char input[], int BUFFER_SIZE, bool hflag)
{
	if(hflag)
	 return true;
	    if (input[strlen(input) - 1] != '\n') {
	    	const char *invLeng = "Error, Input exceeds the allowed";
	    	typewriterEffect(invLeng,15000);
	        printf(" %d characters (with space).\nPress Enter to continue.", BUFFER_SIZE - 2);
	        fflush(stdin);
	        return false;
	    }else
	     {
	    	fflush(stdin);
	    	return true;
	     }
}

#endif /* CHECKH */
