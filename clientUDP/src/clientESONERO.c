/*
 ============================================================================
 Name        : clientESONERO.c
 Author      : Giordano, Aghilar
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Client main
 ============================================================================
 */

#include "client.h"


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

/**
 * @brief Displays the help menu for the password generator application.
 *
 * This function prints a detailed help menu to the standard output, listing
 * available commands and their descriptions. It explains password generation
 * options, input requirements, and character exclusions for unambiguous passwords.
 */
void help_menu()
{
	 const char *helpMsg = "\nPassword Generator Help Menu \nCommands: \n"
			 	 	 	 	     "h: show this help menu \n"
			 	 	 	 	     "n LENGTH : generate numeric password (digits only)\n"
			 	 	 	 	     "a LENGTH : generate alphabetic password (lowercase letters)\n"
			 	 	 	 	     "m LENGTH : generate mixed password (lowercase letters and numbers)\n"
			 	 	 	 	     "s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)\n"
			 	 	 	 	     "u LENGTH : generate unambiguous secure password (no similar-looking characters)\n"
			 	 	 	 	     "q        : quit application\n"
			 	 	 	 	     "LENGTH must be between 6 and 32 characters\n"
			 	 	 	 	     "Ambiguous characters excluded in 'u' option:\n"
			 	 	 	 	     "0 O o (zero and letters O)\n"
			 	 	 	 	     "1 l I i (one and letters l, I)\n"
			 	 	 	 	     "2 Z z (two and letter Z)\n"
			 	 	 	 	     "5 S s (five and letter S)\n"
			 	 	 	 	     "8 B (eight and letter B)\n\n";
	         	    typewriterEffect(helpMsg,5000);
}


int main(void) {

    //Winsock inizialization
    #if defined WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        errorhandler("WSAStartup failed.");
        return 0;
    }
    #endif

    int client_socket;
    client_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //socket creation
    if (client_socket < 0) {
        errorhandler("socket creation failed.\n");
        clearwinsock();
        return -1;
    }

    // Resolve server hostname and handle errors if the host is not found.
    struct hostent *serverAddr;
    serverAddr = gethostbyname(SERVER_ADDR);
    	 if (serverAddr == NULL) {
    		 errorhandler("Error, no such host\n");
			#if defined WIN32
    	     	system("pause");
			#endif
    	     exit(EXIT_FAILURE);
    	 }

    // Define the server address structure
    struct sockaddr_in server_addr;  // // Specify IPv4 address family
    memset(&server_addr, 0, sizeof(server_addr)); // Initialize server_addr
    server_addr.sin_family = AF_INET;  // Set server IP address
    server_addr.sin_port = htons(57015); // Set server port in network byte order

    memcpy(&server_addr.sin_addr.s_addr, serverAddr->h_addr, serverAddr->h_length);

    // Define buffers for input and received password
	char pass[PASS_LENGHT];
	char input[BUFFER_SIZE];
	unsigned int server_addr_length = sizeof(server_addr);

		while (1)
	    {
			bool closeFlag;  	   // Flag to indicate if the user wants to quit
			bool flagInput; 	  // Flag to indicate a correct input
			bool lengthflag;	 // Flag to indicate a correct input length
			bool hflag;			// Flag to indicate if help or additional options are requested
			bool passlength;   // Flag to indicate if the password length matches the required length
			msg m; // Structure to hold message type and length

             do{

            	 closeFlag = false;
            	 flagInput = true;
            	 lengthflag = true;
            	 hflag = false;
            	 passlength = true;

            	 //  Display a prompt for the user
            	 const char *menu =
            	         "\n Enter password type followed by space, length between 6 and 32 (e.g. n 8): "
            	         "\n - a: alphabetic "
            	         "\n - n: numeric "
            	         "\n - m: mixed "
            	         "\n - s: secure "
            			 "\n - u: unambiguous"
            	         "\n - h: help menu "
            	         "\n - q: quit "
            	         "\n ";

            	 typewriterEffect(menu, 15000);	// Simulate typing with a delay of 15ms per character

					memset(input, 0, sizeof(input)); // Clear the input buffer

					// Loop to get valid input or display help menu if 'h' is entered.
				    do
				      {
					   fgets(input, BUFFER_SIZE, stdin);
					     if(input[0]=='h')
					     {
					    	 hflag = true;
					    	 help_menu();
					     }
					   lengthflag = checkLength(input,BUFFER_SIZE,hflag);
				      }while(!lengthflag && hflag);

				        // Remove the newline character at the end of the string.
				        input[strcspn(input, "\n")] = '\0';


				        // Check if the user wants to quit.
				        if(checkClose(input))
				        {
				          closeFlag = true;
				          break;
				        }

				       // Validate the input format.
				       if(!checkSpace(input))
				        {
				         printf("Error, input not valid, you must insert the correct input (e.g. n 8) \n");
				         memset(input, 0, sizeof(input));
				         continue;
				        }

				       	// Handle help flag or validate user input format.
				       	if(hflag)
				       	hflag = true;
				       	else if (sscanf(input, " %c %d", &m.type, &m.length) != 2) {
				        	const char *invInp = "Invalid input. Please try again.\n";
				        	typewriterEffect(invInp,15000);
				        	flagInput = false;
				        	fflush(stdin);
				        	continue;
				        }fflush(stdin);

				        // Ensure the first character is a valid type.
				        if(hflag)
				        hflag = true;
				        else if(!checkFirst(m.type))
				        {
				          printf("Error, %c is not a correct input \n", m.type);
				          continue;
				        }

				        // Handle help flag or validate user input format.
				        if(hflag)
				        hflag = true;
				        else if(!pass_lenght(m.length))
				        {
				        	passlength = false;
				        	 const char *errMsg = "Enter a length between 6 and 32 \n";
				        	 typewriterEffect(errMsg,15000);
				        }

             	 }while(!passlength || !checkFirst(m.type) || !checkSpace(input) || !flagInput	|| hflag ); // Repeat until input is valid

             	 	 if(closeFlag)
             	      break;		// Exit the loop if the user wants to quit

             	 	 	// Convert message length to network byte order (Big-endian)
				        m.length = htonl(m.length);

				        if (sendto(client_socket, (void *)&m, sizeof(m), 0,(struct sockaddr*)&server_addr,server_addr_length) < 0) {
				            perror("Error occurred while sending the message.");
				            break;
				        }

				        // Convert the length back to host byte order
				        m.length = ntohl(m.length);

				        const char *reqMsg = "Request sent: ";
				        typewriterEffect(reqMsg,15000);
				        printf("type = %c, length = %d\n", m.type, m.length);

				        // Receive the generated password from the server
				        int recval = recvfrom(client_socket, pass, PASS_LENGHT, 0 , (struct sockaddr*)&server_addr, &server_addr_length);
				        if (recval > 0) {
				        	pass[recval] = '\0';
				        	const char *passRecv = "Password received: ";
				        	typewriterEffect(passRecv,15000);
				            printf("%s\n", pass);
				        } else {
				            perror("Error receiving the response from the server.\n");
				            break;
				        }
			   // Clear the password buffer for the next iteration
			   memset(pass, 0, sizeof(pass));
			 }

	// Close the socket and cleanup
    closesocket(client_socket);
    clearwinsock();
	#if defined WIN32
    system("pause");
	#endif
    exit(0);

}

