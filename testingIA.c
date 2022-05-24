#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define PORT "17"
#define BACKLOG 10


void *get_in_addr(struct sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *) sa)->sin_addr);
	} else {
		return &(((struct sockaddr_in6 *) sa)->sin6_addr);
	}
}

int main(int argc, char* argv[]) {
	vector<string> quotes;
	string filename = "../qotd.txt";
	if(argc == 2) {
		filename = argv[1];
	}
	ifstream file(filename.c_str());
	string line;
	while(getline(file, line)) {
		int k = line.find("|");
		string quote = line.substr(0, k);
		string author = line.substr(k+1);
		quotes.push_back("\n\"" + quote + "\"\n\n- " + author + "\n\n");
	}

	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		printf("getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	for(p = servinfo; p != NULL; p = p->ai_next) {
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("socket: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo);

	if(p == NULL) {
		printf("Server failed to bind\n");
		exit(1);
	}

	if(listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server: waiting for connections on port %s...\n", PORT);

	srand(time(NULL));

	while(true) {
		struct sockaddr_storage their_addr;
		socklen_t sin_size = sizeof(their_addr);
		int new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if(new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
		printf("server: got connection from %s\n", s);

		int daysSinceEpoch = rand() % quotes.size();
		string k = quotes[daysSinceEpoch];
		if(send(new_fd, k.c_str(), k.length(), 0) == -1) {
			perror("send");
		}
		close(new_fd);
	}

	return 0;
}
