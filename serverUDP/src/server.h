/*
 ============================================================================
 Name        : server.h (SERVER)
 Author      : Giordano, Aghilar
 Version     :
 Copyright   : Your copyright notice
 Description : Header file for server-side constants and declarations
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "serverData.h" // Header file for server-side data
#include "support.h"   // Header file for server-side support functions

#define BUFFER_SIZE 6 // Buffer size for sent/received data

#define PASS_SIZE 33  // Defines the size of the password buffer (33 characters with \n included)

#define PORT 57015 // Default port number

