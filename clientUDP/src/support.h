#ifndef SUPPORT_H
#define SUPPORT_H

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Simulates a typewriter effect.
 *
 * Prints a string character by character to the console,
 * introducing a configurable delay between each character to simulate
 * a typewriter effect.
 *
 * @param text The string to be printed. It must be null-terminated (`\0`).
 * @param delayMicroseconds The pause duration between consecutive characters,
 *        expressed in microseconds (1 second = 1,000,000 microseconds).
 *
 * @warning Ensure the `text` parameter is a valid pointer. Passing a null pointer
 *          can result in undefined behavior.
 */
void typewriterEffect(const char *text, int delayMicroseconds);

#endif // SUPPORT_H
