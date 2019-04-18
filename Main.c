#include "main.h"

// Function to compare two peers and see if their ip addresses and ports are the same
int peer_cmp(Peer p1, Peer p2) {
    int acc;
    acc = strcmp(p1.ip_address, p2.ip_address);
    if (acc == 0 && p1.port == p2.port)
        return TRUE;
    else
        return FALSE;
}

int find_peer_by_ip(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0)
        return FALSE;
    else {
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && strcmp(item.ip_address, cur->value.ip_address) != 0) {
            cur = cur->next;
        }
        if (cur == NULL) {
            return FALSE;
        }
        return TRUE;
    }
}


// Add peer to the linked peer list
void add_peer(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0) {
        list->self = (struct LinkedPeerNode *) malloc(sizeof(struct LinkedPeerNode));
        list->self->value = item;
        list->self->previous = NULL;
        list->self->next = NULL;
    } else {
        struct LinkedPeerNode *prev = list->self;
        struct LinkedPeerNode *cur = list->self->next;
        while (cur != NULL) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = (struct LinkedPeerNode *) malloc(sizeof(struct LinkedPeerNode));
        prev->next->previous = prev;
        prev->next->next = NULL;
        prev->next->value = item;
    }
    list->length++;
}

// Find peer in the linked peer list
int find_peer(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0)
        return FALSE;
    else if (peer_cmp(item, this_node.self) == TRUE) {
        return TRUE;
    } else {
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && peer_cmp(item, cur->value) == FALSE) {
            cur = cur->next;
        }
        if (cur == NULL) {
            return FALSE;
        }
        return TRUE;
    }
}

//Remove peer from the linked peer list
void remove_peer(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0) {
        return;
    } else {
        struct LinkedPeerNode *prev = NULL;
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && peer_cmp(item, cur->value) == FALSE) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == NULL)
            return;
        else {
            if (prev == NULL) {
                list->self = cur->next;
            } else
                prev->next = cur->next;
            if (cur->next != NULL) {
                cur->next->previous = cur->previous;
            }
            free(cur);
        }
    }
    list->length--;
}

//Get list of all peers in the linked list and store it in the items
void get_peers(struct LinkedPeerList list, struct Peer *items) {
    struct LinkedPeerNode *cur = list.self;
    for (int i = 0; i < list.length; ++i) {
        items[i] = cur->value;
        cur = cur->next;
    }
}

//Check if two files are the same
int file_cmp(struct PeerFile p1, struct PeerFile p2) {
    int acc;
    acc = strcmp(p1.name, p2.name);
    if (acc == 0)
        return TRUE;
    else
        return FALSE;
}

//Add file to the linked file list
void add_file(struct LinkedFileList *list, struct PeerFile file) {
    if (list->length == 0) {
        list->self = (struct LinkedFileNode *) malloc(sizeof(struct LinkedFileNode));
        list->self->value = file;
        list->self->previous = NULL;
        list->self->next = NULL;
    } else {
        struct LinkedFileNode *prev = list->self;
        struct LinkedFileNode *cur = list->self->next;
        while (cur != NULL) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = (struct LinkedFileNode *) malloc(sizeof(struct LinkedFileNode));
        prev->next->previous = prev;
        prev->next->next = NULL;
        prev->next->value = file;
    }
    list->length++;
}

int change_conn(struct LinkedPeerList *list, struct Peer item, int incr) {
    if (list->length == 0)
        return -1;
    else {
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && strcmp(item.ip_address, cur->value.ip_address) != 0) {
            cur = cur->next;
        }
        if (cur == NULL) {
            return -1;
        }
        cur->value.num_of_con += incr;
        return cur->value.num_of_con;
    }
}

int get_con_by_ip(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0)
        return -1;
    else {
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && strcmp(item.ip_address, cur->value.ip_address) != 0) {
            cur = cur->next;
        }
        if (cur == NULL) {
            return -1;
        }
        return cur->value.num_of_con;
    }
}

//Remove peer from the linked peer list by ip
void remove_peer_by_ip(struct LinkedPeerList *list, struct Peer item) {
    if (list->length == 0) {
        return;
    } else {
        struct LinkedPeerNode *prev = NULL;
        struct LinkedPeerNode *cur = list->self;
        while (cur != NULL && strcmp(item.ip_address, cur->value.ip_address) != 0) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == NULL)
            return;
        else {
            if (prev == NULL) {
                list->self = cur->next;
            } else
                prev->next = cur->next;
            if (cur->next != NULL) {
                cur->next->previous = cur->previous;
            }
            free(cur);
        }
    }
    list->length--;
}

//Find file in the linked file list
struct PeerFile *find_file(struct LinkedFileList *list, struct PeerFile file) {
    if (list->length == 0)
        return NULL;
    else {
        struct LinkedFileNode *cur = list->self;
        while (cur != NULL && file_cmp(file, cur->value) == FALSE) {
            cur = cur->next;
        }
        if (cur == NULL) {
            return NULL;
        }
        return &cur->value;
    }
}

//Remove file from the linked file list
void remove_file(struct LinkedFileList *list, struct PeerFile file) {
    if (list->length == 0) {
        return;
    } else {
        struct LinkedFileNode *prev = NULL;
        struct LinkedFileNode *cur = list->self;
        while (cur != NULL && file_cmp(file, cur->value) == TRUE) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == NULL)
            return;
        else {
            if (prev == NULL) {
                list->self = cur->next;
            } else
                prev->next = cur->next;
            if (cur->next != NULL) {
                cur->next->previous = cur->previous;
            }
            free(cur);
        }
    }
    list->length--;
}

//Get list of all files and store in the *files
void get_file(struct LinkedFileList list, struct PeerFile *files) {
    struct LinkedFileNode *cur = list.self;
    for (int i = 0; i < list.length; ++i) {
        files[i] = cur->value;
        cur = cur->next;
    }
}

int not_yours_files(void) {
    int i = 0;
    struct LinkedFileNode *cur = this_node.files.self;
    while (cur != NULL) {
        if (peer_cmp(cur->value.owner, this_node.self) == FALSE) {
            i++;
        }
        cur = cur->next;
    }
    return i;
}

void remove_files(Peer peer) {
    struct LinkedFileNode *cur = this_node.files.self;
    while (cur != NULL) {
        if (peer_cmp(cur->value.owner, peer) == TRUE) {
            remove_file(&this_node.files, cur->value);
        }
        cur = cur->next;
    }
}

//Download new file
void download_file(struct Peer peer, struct PeerFile file) {
    ssize_t bytes_sent, bytes_received;
    int client_socket, file_size;
    char file_buf[BUF_SIZE];
    int p;
    struct sockaddr_in destination_addr;
    // Create client's socket from which he will connect
    socklen_t addr_len = sizeof(struct sockaddr);
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        fprintf(stderr, "failed to create a socket to download a file: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    destination_addr.sin_family = AF_INET;
    destination_addr.sin_addr.s_addr = inet_addr(peer.ip_address);
    destination_addr.sin_port = htons(peer.port);

    //Connect to the server
    if (connect(client_socket, (struct sockaddr *) &destination_addr, addr_len) == -1) {
        fprintf(stderr, "failed to connect to server to download a file:%d\n", errno);
        exit(EXIT_FAILURE);
    }
    p = htonl(PROT_REQUEST);

    //Send protocol type
    bytes_sent = sendto(client_socket, (void *) &p, sizeof(p), 0,
                        (struct sockaddr *) &destination_addr,
                        sizeof(struct sockaddr));
    if (bytes_sent == -1) {
        fprintf(stderr, "error on send protocol to load a file: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    strcpy(file_buf, file.name);
    //Send file name
    bytes_sent = sendto(client_socket, (void *) &file_buf, sizeof(file_buf), 0,
                        (struct sockaddr *) &destination_addr,
                        sizeof(struct sockaddr));
    if (bytes_sent == -1) {
        fprintf(stderr, "error on send to send file name: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    //Get the size of the file
    bytes_received = recvfrom(client_socket, (void *) &file_size, sizeof(file_size), 0,
                              (struct sockaddr *) &destination_addr,
                              &addr_len);
    file_size = ntohl(file_size);
    if (bytes_received == -1) {
        fprintf(stderr, "error on receive file size errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    //If server doesn't have such file
    if (file_size == -1) {
        printf("Server doesn't have file %s in their system!\n", file.name);
        close(client_socket);
        return;
        // If server has such file
    } else {
        printf("Beginning the download of %s with size %d\n", file.name, file_size);


        FILE *load_file;
        //Open/create the file
        load_file = fopen(file.name, "w+");
        while (file_size > 0) {
            char buf[BUF_SIZE];
            memset(buf, 0, sizeof(buf));
            //Get next word
            bytes_received = recvfrom(client_socket, (void *) &buf, sizeof(buf), 0,
                                      (struct sockaddr *) &destination_addr,
                                      &addr_len);
            if (bytes_received == -1) {
                fprintf(stderr, "error on receive next word number %d errno: %d\n", file_size, errno);
                exit(EXIT_FAILURE);
            }

            //Write it to the file
            fwrite(buf, sizeof(char), strlen(buf), load_file);
            file_size--;
            if (file_size != 0) {
                //Write space in the end
                fwrite(" ", sizeof(char), strlen(" "), load_file);
            }
        }
        fclose(load_file);
        printf("Loaded file %s\n", file.name);
        close(client_socket);
    }
}

//Count the words in the file
//Sets current position to the begnning
int words_count(FILE *file) {
    int num_words = 0;
    int c;
    rewind(file);
    if (feof(file))
        return 0;

    while ((c = getc(file)) != EOF) {
        if (isalpha(c)) {
            continue;
        } else if (c == ' ' || c == '\n') {
            num_words++;
        }
    }
    rewind(file);
    return num_words + 1;
}

//Add peer to a list
void add_peer_to_a_list(struct Peer peer) {
    if (peer_cmp(peer, this_node.self) == FALSE && find_peer(&this_node.peers, peer) == FALSE) {
        // Add address to the list (address of the server)
        add_peer(&this_node.peers, peer);
        printf("Got new node! ip: %s:%u\n", peer.ip_address, peer.port);
    } else {
        //Reset name
        struct LinkedPeerNode *cur = this_node.peers.self;
        if (peer_cmp(cur->value, peer) == TRUE)
            strcpy(cur->value.name, peer.name);
    }
}

//Initialise server
void *initialise_server(void *data) {
    //Create socket and server addresses for binding
    int server_socket, clients_fd, current_connect = 0;
    pthread_t clients[CONNECT_N], pinger;
    socklen_t addrlen;
    struct sockaddr_in server_addr;

    addrlen = sizeof(struct sockaddr_in);
    //Create server socket that is datagram for tcp transmissions
    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        fprintf(stderr, "failed to create a server socket errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr)); //Clean up server address
    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(MY_IP_ADDRESS);

    //Bind server socket to server
    if ((bind(server_socket, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1)) {
        if (errno == EADDRNOTAVAIL)
            fprintf(stderr, "Failed to bind, check that MY_IP_SERVER corresponds to your IP");
        else if (errno == EADDRINUSE)
            fprintf(stderr, "Address already in use, check that port SERVER_PORT is free");
        else {
            fprintf(stderr, "failed to bind server socket errno: %d\n", errno);
        }
        exit(EXIT_FAILURE);
    }

    // Copy node information about us to the self part
    memset(this_node.self.ip_address, 0, sizeof(this_node.self.ip_address));
    strcpy(this_node.self.ip_address, MY_IP_ADDRESS);
    this_node.self.port = SERVER_PORT;

    //Begin listening
    if (listen(server_socket, CONNECT_N) < 0) {
        fprintf(stderr, "failed to listen server errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // Create thread of the pinger
    pthread_create(&pinger, NULL, ping_clients, NULL);
    while (TRUE) {
        struct greet_client_data c_data;
        struct sockaddr_in client_addr;
        clients_fd = accept(server_socket,
                            (struct sockaddr *) &client_addr,
                            &addrlen);
        struct Peer new_client;
        new_client.num_of_con = 0;
        memset(&new_client, 0, sizeof(new_client));
        strcpy(new_client.ip_address, inet_ntoa(client_addr.sin_addr));
        if (find_peer_by_ip(&black_list, new_client) == TRUE) {
            close(clients_fd);
            continue;
        }

        //Check current list
        int number_of_cons;
        if ((number_of_cons = get_con_by_ip(&current_list, new_client)) != -1) {

            if (number_of_cons > 5) {
                // Add to blacklist
                printf("Blacklisted %s\n", new_client.ip_address);
                pthread_mutex_lock(&bldb_lock);
                add_peer(&black_list, new_client);
                pthread_mutex_unlock(&bldb_lock);
                //Remove from current list connect
                pthread_mutex_lock(&cdb_lock);
                remove_peer_by_ip(&current_list, new_client);
                pthread_mutex_unlock(&cdb_lock);
                close(clients_fd);
                continue;
            } else {
                //Increment current
                pthread_mutex_lock(&cdb_lock);
                change_conn(&current_list, new_client, 1);
                pthread_mutex_unlock(&cdb_lock);
            }
        } else {
            pthread_mutex_lock(&cdb_lock);
            new_client.num_of_con = 1;
            add_peer(&current_list, new_client);
            pthread_mutex_unlock(&cdb_lock);
        }
        //Relocate every new client to the new thread
        c_data.client_socket = clients_fd;
        c_data.client_addr = client_addr;
        pthread_create(&clients[current_connect], NULL, handle_client, (void *) &c_data);
        current_connect = (current_connect + 1) % CONNECT_N;
    }
}

//Pinger
void *ping_clients(void *data) {
    struct Peer *peers = malloc(sizeof(char) * 0);
    int p;
    ssize_t bytes_sent;
    int connect_fd, peer_num;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    size_t cur_len;

    while (TRUE) {
        sleep(PING_INTERVAL);

        peer_num = this_node.peers.length;
        peers = (Peer *) realloc(peers, sizeof(Peer) * peer_num);
        get_peers(this_node.peers, peers);
        for (int i = 0; i < peer_num; i++) {

            addr_len = sizeof(server_addr);
            p = htonl(PROT_SYN);
            //Create new socket for the ping duration
            if ((connect_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
                fprintf(stderr, "failed to create a socket to ping clients errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }

            //Setup server address
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(peers[i].port);
            server_addr.sin_addr.s_addr = inet_addr(peers[i].ip_address);

            //Try to connect to the node
            if (connect(connect_fd, (struct sockaddr *) &server_addr, addr_len) == -1) {
                if (errno == ECONNREFUSED) {
                    printf("Node Name:%s:%s:%u left\n", peers[i].name,
                           peers[i].ip_address, peers[i].port);
                    //Remove item from the list
                    remove_peer(&this_node.peers, peers[i]);
                    remove_files(peers[i]);
                    close(connect_fd);
                    continue;
                } else if (errno == ENETUNREACH) {
                    printf("Node Name:%s:%s:%u is unreachable\n", peers[i].name,
                           peers[i].ip_address, peers[i].port);
                    //Remove item from the list
                    remove_peer(&this_node.peers, peers[i]);
                    remove_files(peers[i]);
                    close(connect_fd);
                    continue;
                } else {
                    fprintf(stderr, "failed to connect to ping errno:%d\n", errno);
                    exit(EXIT_FAILURE);
                }
            }
            //Send protocol type
            bytes_sent = sendto(connect_fd, (void *) &p, sizeof(p), 0,
                                (struct sockaddr *) &server_addr,
                                sizeof(struct sockaddr));
            if (bytes_sent == -1) {
                fprintf(stderr, "error on send ping errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            //If successfully pinged - begin SYNC
            char syn_buffer[BUF_SIZE], p_buf[BUF_SIZE], port_buf[BUF_SIZE];
            struct LinkedFileNode *cur = this_node.files.self;
            memset(syn_buffer, 0, sizeof(syn_buffer));
            //Begin sync process
            strcat(syn_buffer, this_node.self.name);
            strcat(syn_buffer, ":");
            strcat(syn_buffer, this_node.self.ip_address);
            strcat(syn_buffer, ":");
            sprintf(port_buf, "%hu", this_node.self.port);
            strcat(syn_buffer, port_buf);
            strcat(syn_buffer, ":");
            //Build files info
            cur_len = strlen(syn_buffer);
            while (cur != NULL) {
                if (cur->next == NULL)
                    sprintf(syn_buffer + cur_len, "%s", cur->value.name);
                else
                    sprintf(syn_buffer + cur_len, "%s,", cur->value.name);
                cur = cur->next;
                cur_len = strlen(syn_buffer);
            }
            if (DEBUG)
                printf("sending self info %s\n", syn_buffer);
            //send self info
            bytes_sent = sendto(connect_fd, (void *) &syn_buffer, sizeof(syn_buffer), 0,
                                (struct sockaddr *) &server_addr,
                                sizeof(struct sockaddr));
            if (bytes_sent == -1) {
                fprintf(stderr, "Error on sending peer size errno : %d\n", errno);
                exit(EXIT_FAILURE);
            }


            int peer_size = this_node.peers.length;
            struct Peer *sync_peers = malloc(peer_size * sizeof(struct Peer));
            peer_size = htonl(peer_size);
            //send number of peers
            bytes_sent = sendto(connect_fd, (void *) &peer_size, sizeof(peer_size), 0,
                                (struct sockaddr *) &server_addr,
                                sizeof(struct sockaddr));
            if (bytes_sent == -1) {
                fprintf(stderr, "Error on sending peer size errno : %d\n", errno);
                exit(EXIT_FAILURE);
            }
            if (DEBUG)
                printf("sending %d\n", peer_size);
            get_peers(this_node.peers, sync_peers);
            //Send one peer at a time
            peer_size = ntohl(peer_size);
            int j = 0;
            while (peer_size > 0) {
                //Send peers buffer
                char port_buf2[BUF_SIZE];
                memset(p_buf, 0, sizeof(p_buf));
                strcat(p_buf, sync_peers[j].name);
                strcat(p_buf, ":");
                strcat(p_buf, sync_peers[j].ip_address);
                strcat(p_buf, ":");
                sprintf(port_buf2, "%hu", sync_peers[j].port);
                strcat(p_buf, port_buf2);
                strcat(p_buf, ":");
                bytes_sent = sendto(connect_fd, (void *) &p_buf, sizeof(p_buf), 0,
                                    (struct sockaddr *) &server_addr,
                                    sizeof(struct sockaddr));
                if (bytes_sent == -1) {
                    fprintf(stderr, "Error on sending peer buf errno : %d\n", errno);
                    exit(EXIT_FAILURE);
                }
                j++;
                peer_size--;
            }
            close(connect_fd);
        }
    }
}

//Server client handler
void *handle_client(void *data) {
    struct greet_client_data *client_data = (struct greet_client_data *) data;
    socklen_t addr_len;
    ssize_t bytes_received, bytes_sent;
    struct PeerFile tmp_file;
    struct Peer new_node, peer_buf;
    size_t cur_len;
    int peer_sync_num;
    int p;

    //Receive protocol data from client
    bytes_received = recvfrom(client_data->client_socket, (void *) &p, sizeof(p), 0,
                              (struct sockaddr *) &client_data->client_addr, &addr_len);
    if (bytes_received == -1) {
        fprintf(stderr, "Error on recv protocol errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    p = ntohl(p);
    //Check protocol type, do appropriate things according to it
    if (p == 1) {
        //SYNC PEERS
        char syn_buf[BUF_SIZE], small_file_buf[BUF_SIZE], p_buf[BUF_SIZE];
        memset(syn_buf, 0, sizeof(syn_buf));
        // Get self info
        bytes_received = recvfrom(client_data->client_socket, (void *) &syn_buf, sizeof(syn_buf), 0,
                                  (struct sockaddr *) &client_data->client_addr,
                                  &addr_len);

        if (DEBUG)
            printf("got self info %s\n", syn_buf);
        if (bytes_received == -1) {
            fprintf(stderr, "error on receive number of peers errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        char port[10];
        //Set up name and files
        sscanf(syn_buf, "%[^:]:%[^:]:%[^:]:", new_node.name, new_node.ip_address, port);
        sscanf(port, "%hu", &new_node.port);
        cur_len = strlen(new_node.name) + strlen(new_node.ip_address) + strlen(port) + 3;
        //Set name

        add_peer_to_a_list(new_node);
        while (sscanf(syn_buf + cur_len, "%[^,],", small_file_buf) != EOF) {
            cur_len += strlen(small_file_buf) + 1;
            memset(&tmp_file, 0, sizeof(tmp_file));
            strcpy(tmp_file.name, small_file_buf);
            if (find_file(&this_node.files, tmp_file) == FALSE) {

                //Add file if not present
                if (DEBUG)
                    printf("Got new file %s \n", tmp_file.name);
                tmp_file.owner = new_node;
                add_file(&this_node.files, tmp_file);
            }
        }

        // Get num of peers
        bytes_received = recvfrom(client_data->client_socket, (void *) &peer_sync_num, sizeof(peer_sync_num), 0,
                                  (struct sockaddr *) &client_data->client_addr,
                                  &addr_len);
        if (bytes_received == -1) {
            fprintf(stderr, "error on receive number of peers errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        if (DEBUG)
            printf("%d peers from %s\n", peer_sync_num, new_node.name);
        //Get peer one at a time
        peer_sync_num = ntohl(peer_sync_num);
        while (peer_sync_num > 0) {
            memset(p_buf, 0, sizeof(p_buf));
            //Receive buffer of peers
            bytes_received = recvfrom(client_data->client_socket, (void *) &p_buf, sizeof(p_buf), 0,
                                      (struct sockaddr *) &client_data->client_addr,
                                      &addr_len);
            if (bytes_received == -1) {
                fprintf(stderr, "error on receive peer buf errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            sscanf(p_buf, "%[^:]:%[^:]:%hu", peer_buf.name, peer_buf.ip_address, &peer_buf.port);
            //Try to connect to new peers
            if (DEBUG)
                printf("peer %s from %s\n", p_buf, new_node.name);
            add_peer_to_a_list(peer_buf);
            peer_sync_num--;
        }
    } else if (p == 0) {
        //Steps if file was requested
        int num_words;
        char words_buf[BUF_SIZE];
        char file_buf[BUF_SIZE];
        FILE *send_file;

        //Get file name
        bytes_received = recvfrom(client_data->client_socket, (void *) &file_buf, sizeof(file_buf), 0,
                                  (struct sockaddr *) &client_data->client_addr, &addr_len);
        if (bytes_received == -1) {
            fprintf(stderr, "Error on recv self info about client errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Got request for %s\n", file_buf);
        //Check if file is present
        send_file = fopen(file_buf, "r+");
        //If not return PROT_NO
        if (send_file == NULL) {
            num_words = -1;
        } else {
            num_words = words_count(send_file);
        }
        //Send number of words
        num_words = htonl(num_words);
        bytes_sent = sendto(client_data->client_socket, (void *) &num_words, sizeof(num_words), 0,
                            (struct sockaddr *) &client_data->client_addr,
                            sizeof(struct sockaddr));
        if (bytes_sent == -1) {
            fprintf(stderr, "Error on sending num words errno : %d\n", errno);
            exit(EXIT_FAILURE);
        }
        //Close if no file
        if (num_words == -1) {
            close(client_data->client_socket);
            return NULL;
        }
        printf("Beginning to send file %s \n", file_buf);
        num_words= ntohl(num_words);
        for (int i = 0; i < num_words; ++i) {
            //Send words by one words at the time
            memset(words_buf, 0, sizeof(words_buf));
            fscanf(send_file, "%s", words_buf);

            bytes_sent = sendto(client_data->client_socket, (void *) &words_buf, BUF_SIZE, 0,
                                (struct sockaddr *) &client_data->client_addr,
                                sizeof(struct sockaddr));
            if (bytes_sent == -1) {
                fprintf(stderr, "Error on sending words buf errno : %d\n", errno);
                exit(EXIT_FAILURE);
            }

        }
        printf("Ended transmitting\n");

    }
    close(client_data->client_socket);
    int conn;
    struct Peer new_client;
    memset(&new_client, 0, sizeof(new_client));
    strcpy(new_client.ip_address, inet_ntoa(client_data->client_addr.sin_addr));

    pthread_mutex_lock(&cdb_lock);
    if ((conn = get_con_by_ip(&current_list, new_client)) == 1) {
        remove_peer_by_ip(&current_list, new_client);
    } else {
        //Decrement current
        change_conn(&current_list, new_client, -1);
    }
    pthread_mutex_unlock(&cdb_lock);
    return 0;
}


int main(int argc, char **argv) {
    pthread_t client, server;
    ssize_t bytes_read;
    memset(&this_node, 0, sizeof(this_node));
    if (argc != 2){
    printf("Incorrect number of arguments. Your shoulld enter only your name!");
    exit(0);}
    strcpy(this_node.self.name, argv[1]);
    this_node.self.name[bytes_read - 1] = '\0';
    printf("Your name is: %s\n", this_node.self.name);
    pthread_create(&server, NULL, initialise_server, NULL);
    printf("If you want add file enter 0\n");
    printf("If you want add peer enter 1\n");
    printf("If you want get file enter 2\n");
    printf("If you want see all available files enter 3\n");

    while (TRUE) {
        struct Peer new_peer;
        char ip[20];
        uint16_t port;
        char buf[2];
        read(0, buf, sizeof(buf));
        fflush(stdin);
        buf[1] = '\0';
        if (strcmp(buf, "0") == 0) {
            char file_buf[26];
            FILE *file;
            printf("Enter filename\n");
            bytes_read = read(0, file_buf, sizeof(file_buf) - 1);
            file_buf[bytes_read - 1] = '\0';
            file = fopen(file_buf, "r+");
            fflush(stdin);
            if (file == NULL) {
                printf("No such file exists\n");
            } else {
                printf("Added file %s\n", file_buf);
                struct PeerFile file1;
                memset(&file1, 0, sizeof(struct PeerFile));
                strcpy(file1.name, file_buf);
                fclose(file);
                file1.owner = this_node.self;
                add_file(&this_node.files, file1);
            }
        } else if (strcmp(buf, "1") == 0) {
            printf("Enter IP:Port of the server\n");
            scanf("%[^:]:%hu", ip, &port);
            memset(&new_peer, 0, sizeof(new_peer));
            strcpy(new_peer.ip_address, ip);
            new_peer.port = port;
            new_peer.name[0] = ' ';
            add_peer_to_a_list(new_peer);
        } else if (strcmp(buf, "2") == 0) {
            char file_buf[26];
            struct PeerFile *file, file_b;
            printf("Enter filename\n");
            bytes_read = read(0, file_buf, sizeof(file_buf) - 1);
            file_buf[bytes_read - 1] = '\0';
            fflush(stdin);
            memset(&file_b, 0, sizeof(file_b));
            strcpy(file_b.name, file_buf);
            if ((file = find_file(&this_node.files, file_b)) == NULL) {
                printf("No such file available\n");
            } else {
                printf("%s %s\n", file->owner.name, file->owner.ip_address);
                download_file(file->owner, *file);
            }
        } else if (strcmp(buf, "3") == 0) {
            //Show list of files
            if (not_yours_files() == 0) {
                printf("No files available\n");
            } else {
                printf("All possible files:\n");
                struct LinkedFileNode *cur = this_node.files.self;
                while (cur != NULL) {
                    if (peer_cmp(cur->value.owner, this_node.self) == FALSE) {
                        printf("%s from %s\n", cur->value.name, cur->value.owner.name);
                    }
                    cur = cur->next;
                }
            }
        } else if (strcmp(buf, "4") == 0) {
            //Show list of files
            if (not_yours_files() != 0) {
                printf("No files available\n");
            } else {
                printf("Your files:\n");
                struct LinkedFileNode *cur = this_node.files.self;
                while (cur != NULL) {
                    if (peer_cmp(cur->value.owner, this_node.self) == TRUE) {
                        printf("%s\n", cur->value.name);
                    }
                    cur = cur->next;
                }
            }
        } else {
            fflush(stdin);
        }
    }
}
