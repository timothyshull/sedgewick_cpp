
#ifndef TRANSFER_H
#define TRANSFER_H


int send_comp(int s, const unsigned char *data, int size, int flags);

int recv_comp(int s, unsigned char **data, int *size, int flags);

#endif