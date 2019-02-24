#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>


#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.1"



void usage() {
    printf("USAGE: htmlget host [page]\n\
\thost: the website hostname. ex: coding.debuntu.org\n\
\tpage: the page to retrieve. ex: index.html, default: /\n");
}

// return a file descriptor that can be used in later function calls that operate on sockets
// domain -  communications domain in which a socket is to be created.
// type of socket to be created
// particular protocol to be used with the socket
int tcp_socket() {
    int sock;
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("Can't create TCP socket.");
        exit(1);
    }
    return sock;
}
// Return string representation of the IP address of the given host
char* build_ip(char* host) {
    struct hostent* hent; // This data type is used to represent an entry in the hosts database
    int iplen = 15; // XXX.XXX.XXX.XXX

    char *ip = (char*) malloc(iplen + 1);
    memset(ip, 0, iplen + 1); // fill up ip with zeroes

    if((hent = gethostbyname(host)) == NULL) {
        herror("Can't resolve IP");
        exit(1);
    }

    // inet_ntop() converts a numeric address into a text string suitable for presentation
    // returns a pointer to the buffer containing the text string if the conversion succeeds, and NULL otherwise
    // The af argument shall specify the family of the address (either AF_INET or AF_INET6).
    // The src parameter should be a pointer to either a struct in_addr or struct in6_addr containing
    // the address you wish to convert to a string.
    // Finally dst and size are the pointer to the destination string and the maximum length of that string.
    if(inet_ntop(AF_INET, hent->h_addr_list[0], ip, iplen) == NULL) {
        perror("Can't resolve host");
        exit(1);
    }
    return ip;
}

// Return structures for handling internet addresses
struct sockaddr_in* build_remote(char* ip, int port) {
    struct sockaddr_in* remote = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in*));
    remote->sin_family = AF_INET;
    // converts the character string src into a network
    //       address structure in the af address family, then copies the network
    //       address structure to dst. dst is written in network byte order.
    int result_status = inet_pton(AF_INET, ip, &(remote -> sin_addr.s_addr));

    if (result_status < 0) {
        printf("Can't convert ip into network address");
        exit(1);
    } else if (result_status == 0) {
        printf("%s is not a valid IP address\n", ip);
        exit(1);
    }
    remote -> sin_port = htons(port); // converts the unsigned integer hostlong from host byte order to network byte order

    return remote;
}

char* get_query(char* host, char* page) {
    char* query;
    char* page_to_retrieve = page;
    char* template = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

    if(page_to_retrieve[0] == '/') {
        page_to_retrieve = page_to_retrieve + 1;
        printf("Removing leading \"/\", converting %s to %s\n", page, page_to_retrieve);
    }
    // -5 is to regard the %s %s %s in template and \0 in the end
    query = (char*) malloc(strlen(host) + strlen(page_to_retrieve) + strlen(USERAGENT) + strlen(template) - 5);
    sprintf(query, template, page_to_retrieve, host, USERAGENT);
    return query;
}

int main(int argc, char* argv[]) {
    struct sockaddr_in* remote;
    int sock, send_res, port;
    char *ip, *host, *page, *get;
    char buf[BUFSIZ + 1];

    if(argc < 2) {
        usage();
        exit(0);
    }

    host = argv[1];
    page = argc > 2 ? argv[2] : PAGE;
    port = argc > 3 ? atoi(argv[3]) : PORT;

    sock = tcp_socket();
    ip = build_ip(host);
    printf("IP:  %s, port: %d\n", ip, port);

    remote = build_remote(ip, port);

    if(connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0){
        printf("Could not connect");
        exit(1);
    }
    get = get_query(host, page);
    printf("Query:\n\n%s\n", get);

    // Send the query to the server
    send_res = (int) send(sock, get, strlen(get), 0);
    if(send_res == -1) {
        perror("Can't send query");
        exit(1);
    }

    // Get page
    memset(buf, 0, sizeof(buf)); //  Fill buffer with zeros
    int html_started = 0;
    while((send_res = (int) recv(sock, buf, BUFSIZ, 0)) > 0) {
        if (!html_started && strstr(buf, "<") != NULL) {
            html_started = 1;
        }
        if (html_started) {
            printf("%s", buf);
        }
        memset(buf, 0, send_res);
    }

    if(send_res < 0) {
        perror("Error receiving data");
    }

    // Clean up
    free(get);
    free(remote);
    free(ip);
    close(sock);

    return 0;
}
