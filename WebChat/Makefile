CC = gcc
CFLAGS = -g
LDFLAGS = -pthread


%.o: %.c
	$(CC) -c $(CFLAGS) $<

tests: chatClient chatServer
	
chatClient: chatClient.o
	$(CC) -o $@ chatClient.o

chatServer: chatServer.o
	$(CC) -o $@ chatServer.o
	
clean: 
	$(RM) chatServer chatClient *.o
