/*
 ============================================================================
 Name        : client.h (CLIENT)
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Header file for client-side constants and declarations
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "checkClient.h" // Header file for client-side functions
#include "clientData.h" // Header file for client-side data

#define BUFFER_SIZE 6	// Define the maximum buffer size for input data

#define PASS_LENGHT 33	// Maximum length of the password

#define port 57015 // The port number used for the server

#define SERVER_ADDR "passwdgen.uniba.it" // Server address
