#include "support.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Simulates a typewriter effect.
 *
 * This function prints a string character by character to the console,
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
void typewriterEffect(const char *text, int delayMicroseconds) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);  // Ensure output is printed immediately
        usleep(delayMicroseconds);  // Wait for the specified delay
    }
}
