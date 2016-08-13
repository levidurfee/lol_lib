all: clean t_lib t_server t_client
clean:
	rm -Rf t_server
	rm -Rf t_client
	rm -Rf t_lib
t_lib:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o t_lib t_lib.c
t_server:
	gcc -O3 -g -Wall -std=c99 -o t_server t_server.c
t_client:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o t_client t_client.c