#ifndef API_CLIENT_H
#define API_CLIENT_H

int client_begin(char *hostname, char *port, char *old_local_filename, char *new_local_filename, char *new_remote_filename, char *block_size);
#endif
