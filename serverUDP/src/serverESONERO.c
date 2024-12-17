/*
 ============================================================================
 Name        : serverESONERO.c (SERVER)
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Implements server-side socket communication and password generation
 ============================================================================
 */

#include "server.h"

/**
 * @brief Handles errors by printing the specified error message.
 *
 * This function outputs an error message to the standard output to indicate
 * an issue in the program.
 *
 * @param[in] error_message: the error message to display.
 */
void errorhandler(char *errorMessage) {
    printf("%s", errorMessage);
}

/**
 * @brief Clears the Windows Sockets library.
 *
 * This function is specifically for Windows-based systems.
 * It cleans up the resources used by the Windows Sockets API.
 */
void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

/* - - - - - - - - - - - - - - - - - - PASSWORD GENERATION - - - - - - - - - - - - - - - - - - */

/**
 * @brief Generates a numeric character set for password creation.
 *
 * This function initializes a character set containing only numeric digits (0-9)
 * and provides its length to be used for password generation.
 *
 * @param[out] characters: a pointer to the character set.
 * @param[out] length: the length of the character set.
 */
void generate_numeric(const char **character, int* length)
{
	static const char digits[] = "0123456789";
	 *character = digits;
	 *length = sizeof(digits) - 1;
}

/**
 * @brief Generates an alphabetic character set for password creation.
 *
 * This function initializes a character set containing only lowercase alphabetic
 * characters (a-z) and provides its length to be used for password generation.
 *
 * @param[out] characters: a pointer to the character set.
 * @param[out] length: the length of the character set.
 */
void generate_alpha(const char **character, int* length)
{
	static const char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz";
	 *character = lowercase_letters;
	 *length = sizeof(lowercase_letters) - 1;
}
/**
 * @brief Generates a mixed alphanumeric character set for password creation.
 *
 * This function initializes a character set containing both alphabetic characters
 * (a-z) and numeric digits (0-9), and provides its length to be used for password generation.
 *
 * @param[out] characters: a pointer to the character set.
 * @param[out] length: the length of the character set.
 */
void generate_mixed(const char **character, int* length)
{
	static const char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	 *character = lowercase_letters;
	 *length = sizeof(lowercase_letters) - 1;
}
/**
 * @brief Generates a secure character set for password creation.
 *
 * This function initializes a comprehensive character set containing uppercase
 * letters, lowercase letters, numbers, and special characters. It also provides
 * the length of the set for password generation.
 *
 * @param[out] characters: a pointer to the character set.
 * @param[out] length: the length of the character set.
 */
void generate_secure(const char **character, int* length)
{
	static const char complete_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=,./<>?";
	 *character = complete_letters;
	 *length = sizeof(complete_letters) - 1;
}

/**
 * @brief Generates an unambiguous character set for password creation.
 *
 * This function initializes a character set that excludes visually similar
 * characters to minimize confusion (e.g., '0' and 'O', '1' and 'l'). It provides
 * the character set and its length to be used for generating unambiguous passwords.
 *
 * @param[out] characters: a pointer to the character set.
 * @param[out] length: the length of the character set.
 */
void generate_unambiguous(const char **character, int* length)
{
	static const char unambiguous_letters[] = "ACDEFGHJKLMNPQRTUVWXYabcdefghjkmnpqrtuvwxy34679!@#$%^&*()_+-=,./<>?";
	 *character = unambiguous_letters;
	 *length = sizeof(unambiguous_letters) - 1;
}

/**
 * @brief Generates a password based on the specified type and length.
 *
 * This function creates a password using a character set determined by the type parameter.
 * Supported types include:
 * - 'n': numeric characters only.
 * - 'a': alphabetic characters only.
 * - 'm': mixed alphanumeric characters.
 * - 's': secure characters (alphanumeric + special characters).
 *
 * @param[in] type: the type of characters to include in the password.
 * @param[in] length: the length of the password to generate.
 * @param[out] password: the generated password string.
 */
void generate_password(char type, int lenght, char *password) {

    const char *character;
    int set_length;

    switch (type) {
        case 'n':
        	generate_numeric(&character, &set_length);
        	break;
        case 'a':
        	generate_alpha(&character, &set_length);
            break;
        case 'm':
        	generate_mixed(&character, &set_length);
            break;
        case 's':
        	generate_secure(&character, &set_length);
            break;
        case 'u':
        	generate_unambiguous(&character, &set_length);
        	break;
        default:
            snprintf(password, PASS_SIZE, "Error, password not generated");
            return;
    }

    for (int i = 0; i < lenght; i++) {
        password[i] = character[rand() % set_length];
    }
    password[lenght] = '\0';
}

/* - - - - - - - - - - - - - - - - - - END PASSWORD GENERATION - - - - - - - - - - - - - - - - - - */

int main(void) {

	// Inizializzazione di Winsock
     #if defined WIN32
	 WSADATA wsa_data;
	    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
	        errorhandler("WSAStartup failed.");
	        return 0;
	    }
	#endif

    srand(time(NULL));

	int my_socket; // "welcome" socket
	my_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // Create socket

	if (my_socket < 0) {
	 errorhandler("socket creation failed.\n");
	 clearwinsock();
	 return -1;
	}

	struct sockaddr_in sad;     // sockaddr_in type variable
	sad.sin_family = AF_INET;  // Using IPv4 address
	sad.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // Sets the IP address (localhost in this case) and the inet_addr() function converts the IP address from a dot-decimal string to a network byte order numeric value.
	sad.sin_port = htons( 57015 ); // The port the socket will listen on, using htons() to convert the port number from host byte order to network byte order

	// Bind call to associate the address and port to the socket (my_socket)
	if ( bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0 )
	{
	 errorhandler("bind() failed.\n");	// If it fails, it's probably because the port is already in use or there are permission issues.
	  closesocket(my_socket);	// Close socket
	  clearwinsock();
	 return -1;
	}

	const char *listenMsg = "\nThe server is listening on the: ";
	typewriterEffect(listenMsg,15000);
	printf("%d port . . .\n", PORT);

	    struct sockaddr_in cad;      // Struct to store the client's address
	    unsigned int client_len = sizeof(cad);
	    int client_socket;

    msg m;
    char password[PASS_SIZE];

        while (1)
        {
              int bytes_received = recvfrom(my_socket, (void *)&m, sizeof(m), 0,(struct sockaddr*)&cad, &client_len);
               if(bytes_received>0)
               {
            	   const char *connectMsg = "\n\nNew request from ";
            	           		typewriterEffect(connectMsg,15000);
            	           		printf("%s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port)); // print IP address and port
               }

				m.length = ntohl(m.length); // Convert the length from network byte order to host byte order
				const char *reqMsg = "\n\nRequest from client: ";
				typewriterEffect(reqMsg,15000);
				printf("%c %d\n", m.type, m.length);

				generate_password(m.type, m.length, password);  // Generate password

				if (sendto(my_socket, password, strlen(password), 0, (struct sockaddr*)&cad, client_len) < 0)
				    perror("Error, password send failed.");
				else {
					const char *respMsg = "Response sent . . .";
				    typewriterEffect(respMsg, 15000);
				}

        }

    closesocket(client_socket);	// Close the client socket
    closesocket(my_socket);    // Close the server socket
	#if defined WIN32
    system("pause");
	#endif
    exit(0);
}
