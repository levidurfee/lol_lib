all: clean lol_lib t_server t_client
clean:
	rm -Rf t_server
	rm -Rf t_client
	rm -Rf lol_lib
lol_lib:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o lol_lib lol_lib.c
t_server:
	gcc -O3 -g -Wall -std=c99 -o t_server t_server.c
t_client:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o t_client t_client.c