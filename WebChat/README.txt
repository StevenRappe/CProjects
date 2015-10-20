README

Project: WebChat

Authors:
	Steven Rappe
	Sam Vitello
	Thanks to Beej's Guide to Network Programming
	http://beej.us/guide/bgnet/
	
Description:
	Sets up a server that hosts a chat application, allowing multiple users
	to send textual data back and forth via a multi-threaded client program
	(One thread each for sending and receiving data).

Files:
	chatClient.c
	chatServer.c

Execution:
	First compile and run the server on a host machine. Then using separate
		control instances, compile and run chatClient.c.
	chatClient.c will prompt the user for an IP address when it first starts,
		then port number (9034), is already hard-coded into both the server
		and the client.
	Next the client will prompt the user to enter a user name with which to be
		identified during the chat session.
	After selecting a user name, users can begin chatting simply by typing
		their message and then pressing enter to send the message. The server
		will relay the message to all clients.
