/* 
 *	chatServer.c
 *	Web Server Project
 *
 *	Steven Rappe and Sam Vitello
 *  Also thanks to Beej
 *	
 *	chatServer.c performs all server responsibilities. Connects to 
 *  port 9034 and listens for connections. Once it receives a connection
 *  it adds the connection to a set and listens for messages. When it
 *  receives a message it relays the message to all active clients.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT "9034" // port number

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
 	if (sa->sa_family == AF_INET) {
 		return &(((struct sockaddr_in*)sa)->sin_addr);
 	}
 return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
 	fd_set master; // master file descriptor list
 	fd_set tempfd; // temporary file descriptor list for select() function
 	int fdmax; // maximum file descriptor number

 	int listener; // listening socket descriptor
 	int newfd; // newly accept()ed socket descriptor
 	struct sockaddr_storage remoteaddr; // client address
 	socklen_t addrlen;

 	char buf[256]; // buffer for client data
 	int numbytes; // size of passed information
 	
 	char remoteIP[INET6_ADDRSTRLEN];
 	int yes = 1; // for use with setsockopt() and SO_REUSEADDR, below
 	int i, j, k, rv;
 	struct addrinfo info, *ai, *p;
 	FD_ZERO(&master); // clear the master and temporary sets for use
 	FD_ZERO(&tempfd);
	
 	// get and bind a socket
 	memset(&info, 0, sizeof info);
 	info.ai_family = AF_UNSPEC;
 	info.ai_socktype = SOCK_STREAM;
 	info.ai_flags = AI_PASSIVE;

 	if ((rv = getaddrinfo(NULL, PORT, &info, &ai)) != 0) {
 		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
 		exit(1);
 	}

 	for(p = ai; p != NULL; p = p->ai_next) {
 		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
 		if (listener < 0) {
 			continue;
 		}
 		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
 		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
 			close(listener);
 			continue;
 		}
 		break;
 	}
 	// bound checkpoint
    
 	if (p == NULL) {
 		fprintf(stderr, "selectserver: failed to bind\n");
 		exit(2);
 	}
 	
 	freeaddrinfo(ai); // free used connection information.
 	
 	// listen for input
 	if (listen(listener, 10) == -1) {
		 perror("listen");
 		exit(3);
 	}
 
 	// add the listener to the master set
 	FD_SET(listener, &master);
 
 	// keep track of the biggest file descriptor
 	fdmax = listener;
 	
 	// main loop
 	for(;;) {
 		tempfd = master; // copy master fd list
 		if (select(fdmax+1, &tempfd, NULL, NULL, NULL) == -1) {
 			perror("select");
 			exit(4);
 		}
 		// run through the existing connections looking for data to read
 		for(i = 0; i <= fdmax; i++) {
 			if (FD_ISSET(i, &tempfd)) { 
 				if (i == listener) {
 				// handle new connections
 					addrlen = sizeof remoteaddr;
 					newfd = accept(listener,(struct sockaddr *)&remoteaddr,&addrlen);
 					if (newfd == -1) {
 						perror("accept");
 					} else {
 						FD_SET(newfd, &master); // add to master set

 						if (newfd > fdmax) { // keep track of the max
 							fdmax = newfd;
 						}

 						printf("selectserver: new connection from %s on "
 							"socket %d\n",
 							inet_ntop(remoteaddr.ss_family,
 								get_in_addr((struct sockaddr*)&remoteaddr),
 								remoteIP, INET6_ADDRSTRLEN),
 							newfd);
 					}
 				} else {
 				// handle data from client
				
				// clear buffer
				for (k=0; k<strlen(buf); k++) {
					buf[k] = ' ';
				}
 				if ((numbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
 					printf("%d\n", numbytes);
					// got error or connection closed by client
					if (numbytes == 0) {
						// connection closed
						printf("selectserver: socket %d hung up\n", i);
					} else {
					 perror("recv");
					}
					close(i);
					FD_CLR(i, &master); // remove from master set
 				} else {
 					// received data from a client
 					for(j = 0; j <= fdmax; j++) {
 						// send to everyone.
 						if (FD_ISSET(j, &master)) {
 						// except the listener.
 							if (j != listener) {
								if (send(j, buf, numbytes, 0) == -1) {
 									perror("send");
 								}
 							}
 						}
 					}
 				}
 			}
 		}
 	}
 }

 return 0;
}