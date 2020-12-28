#ifndef CLIENT_H
#define CLIENT_H
#include "md5.h"
#include "read_file.h"

int send_hash(int sockfd, const char *hash);
int request(int sockfd);

#endif
