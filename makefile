all:
	gcc --std=c99 tp.c api_socket.c api_server.c api_client.c api_checksum.c api_file_checksum_parser.c api_comunication_formatter.c -o tp
	

