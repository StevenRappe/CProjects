/*
 *	chatClient.c
 *	Web Server Project
 *
 *	Sam Vitello and Steven Rappe
 *	Also thanks to Beej
 *
 *	chatClient.c handles all client side responsibilities. Sends and
 *	and receives data as chat messages via two seperate threads. Has 
 *  methods sendall(), sendChats(), and getChats().
 *	
 */

#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <pthread.h>
#include <stdlib.h>

struct sendInfo {
	int sock;
	char message[1000];
	char username[200];
};

struct recvInfo {
	int sock;
	char server_reply[2000];
};

// Sends the entire message.
int sendall(int s, char *buf, int *len)
{
    int total = 0; // how many bytes sent
    int bytesleft = *len; // how many bytes there are left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
      
        if (n == -1) { 
            printf("%s\n", "send failed");
            break; 
        }
        total += n;
        bytesleft -= n;
       
    }
    
    *len = total; // return number sent
    return n==-1?-1:0; // return -1 on failure, 0 on success
}

// Sends chat data
void *sendChats(void *data){
	struct sendInfo *info = data;
	
	// Attempt to fix spacing issue
	
    /*char clear[1000];
    int k = 0;
    for (k; k < 1000; k++){
        clear[k] = '\b';
    }*/


	while(1)
    {
        int j = 0;
        for (j; j < strlen(info->message); j++){
            info->message[j] = ' ';
        }
        
        fgets(info->message,1000,stdin);
        strtok(info->message, "\n");
      
        int i = 0;
        char toSend[256];
       
   	    for (i; i < strlen(toSend); i++){
            toSend[i] = ' ';
        }
       
        strcpy (toSend, info->username);
        strcat (toSend, ": "); 
        strcat (toSend, info->message);

        int sendAmt = 0;
        int sendLgth = strlen(toSend);
        
        //Send some data
        if( (sendAmt = sendall(info->sock , toSend , &sendLgth) < 0))
        {
            puts("Send failed");
            return NULL;
        }
    }
    return NULL;
}

// Receives chat data.
void *getChats(void *data)
{
	struct recvInfo *info = data;
	while(1){
        int i = 0;
        for (i; i<strlen(info->server_reply); i++){
            info->server_reply[i] = ' '; 
        }
		if( recv((info->sock) , info->server_reply , 2000 , 0) < 0)
	        {
	            puts("recv failed");
	            break;
	        }
	        
	    puts(info->server_reply);
	}
	return NULL;

}

// Main function. Creates and handles threads
int main(int argc , char *argv[])
{
	fd_set readfds;
    int sock;
    struct sockaddr_in server;
    char message[2000] , server_reply[2000];
    char username[200];
    pthread_t send;
    pthread_t receive;
    struct sendInfo *send_info = malloc(sizeof(struct sendInfo));
    struct recvInfo *recv_info = malloc(sizeof(struct recvInfo));

	// ip address
    char ipAddress[20];

    //create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

	// ask user for ip address
    printf("Please enter the server ip address: ");
    fgets(ipAddress, 20, stdin); //#1#
	
    server.sin_addr.s_addr = inet_addr(ipAddress); 	// #1# 
	// connect to host server write in. Useful for testing. Uncomment #1# above.
    // server.sin_addr.s_addr = inet_addr("192.168.1.20");
	
    server.sin_family = AF_INET;
	server.sin_port = htons( 9034 );
	
    //connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");

    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    int sockSize = sock + 1;

    puts("Welcome to the Mighty Web Server Chat Client\n");
    puts("Please enter a username: ");
    fgets(username,200,stdin);
    strtok(username, "\n");

    send_info->sock = sock;
    strcpy(send_info->username, username);

    recv_info->sock = sock;

    pthread_create(&send, NULL, sendChats, send_info);
    pthread_create(&receive, NULL, getChats, recv_info);

	
    while(1);
     
    close(sock);
    return 0;
}
