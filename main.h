#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define CONNECT_N       10
#define PROT_REQUEST 0
#define PROT_SYN 1
#define SERVER_PORT     2005
#define MY_IP_ADDRESS "127.0.0.1"
#define TRUE 1
#define FALSE 0
#define PING_INTERVAL 5
#define DEBUG FALSE

#define BUF_SIZE 1024
typedef struct Peer {
    char name[BUF_SIZE];
    char ip_address[20];
    uint16_t port;
} Peer;
struct LinkedPeerNode {
    struct LinkedPeerNode *next, *previous;
    struct Peer value;
};
struct LinkedPeerList {
    int length;
    struct LinkedPeerNode *self;
};


struct PeerFile {
    char name[BUF_SIZE];
    Peer owner;
};
struct LinkedFileNode {
    struct LinkedFileNode *next, *previous;
    struct PeerFile value;
};
struct LinkedFileList {
    int length;
    struct LinkedFileNode *self;
};
struct Protocol {
    int type;
};

struct greet_client_data {
    int client_socket;
    struct sockaddr_in client_addr;
};
struct PeerNode {
    Peer self;
    struct LinkedPeerList peers;
    struct LinkedFileList files;
};
struct PeerNode this_node;


void *initialise_client(void *);

void *initialise_server(void *);

void *handle_client(void *);

void *ping_clients(void *);

void add_peer_to_a_list(struct Peer peer);
