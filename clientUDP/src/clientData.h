/*
 ============================================================================
 Name        : clientData.h (CLIENT)
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Header file for client-side data
 ============================================================================
 */
#ifndef DATA_H
#define DATA_H

// Structure representing a message with type and length
typedef struct {
    char type;      // Password type, for example: 'a', 'n', 's', 'm'
    int length;     // Length of the password
} msg;

#endif /* DATA_H */
