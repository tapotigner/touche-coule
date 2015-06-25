#ifndef __NETWORKMANAGER_HPP__
#define __NETWORKMANAGER_HPP__

#include <stdio.h>
#include <climits>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class NetworkManager {

private:
	struct sockaddr_in	serv_addr, cli_addr;
    struct hostent 		*server; // For the client
	char 				hostname[128];
    char 				buffer[256];
    int 				newsockfd, sockfd, port, n;
    bool				isServ;

public:
	NetworkManager(int port) {
		this->port = port;
		isServ = false;
	}
	~NetworkManager() {
        close(sockfd);
        if (isServ) {
        	close(newsockfd);
        }
	}

	bool run() {
		createSocket();
	    confServ();
	    gethostname(hostname, sizeof(hostname));
		if (startClient()) {
			std::cout << "Client started !" << std::endl;
			myWrite("Le message");
			std::cout << "Message sent !" << std::endl;
			//while(1);
			return (false);
		} else {
	        startServer();
			std::cout << "Connexion Established ! Starting reading..." << std::endl;
	       	std::cout << myRead() << std::endl;
	       	return (true);
	       	//while (1);
		}
	}

private:

	void myWrite(std::string s) {
		if (isServ){
			n = send(newsockfd, s.c_str(), strlen(s.c_str()), 0);
		} else {
			n = send(sockfd, s.c_str(), strlen(s.c_str()), 0);
		}
		if (n < 0) error("ERROR writing to socket");
	}

	char *myRead() {
		bzero(buffer,256);
		if (isServ) {
			n = recv(newsockfd, buffer, 255, 0);
		} else {
			n = recv(sockfd, buffer, 255, 0);
		}
		if (n < 0) error("ERROR reading from socket");
		return (buffer);
	}

	void createSocket() {
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	    if (sockfd < 0) {
	        error("ERROR opening socket");
	    }
	}

	void confServ() {
		bzero((char *) &serv_addr, sizeof(serv_addr));
	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_addr.s_addr = INADDR_ANY;
	    serv_addr.sin_port = htons(port);
	}

	bool startClient() {
		server = gethostbyname(hostname);
	    if (server == NULL) {
	         fprintf(stderr,"ERROR, no such host\n");
	         exit(0);
	    }
	    bcopy((char *)server->h_addr, 
	            (char *)&serv_addr.sin_addr.s_addr,
	            server->h_length);
	    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	    	return (false);
	    }
	    return (true);
	}

	void startServer() {
		isServ = true;
		socklen_t clilen;

	    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	    	error("ERROR on binding");
	    listen(sockfd,5);
	    clilen = sizeof(cli_addr);
		std::cout << "Server started ! Waiting for clients..." << std::endl;
	    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	    if (newsockfd < 0) 
	        error("ERROR on accept");
	}

	void error(const char *msg) {
    	perror(msg);
    	exit(1);
	}

};

#endif