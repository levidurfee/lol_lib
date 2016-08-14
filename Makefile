all: clean t_lib t_server t_client t_misc
debug: clean debug_t_lib debug_t_server debug_t_client debug_t_misc
clean:
	rm -Rf t_server
	rm -Rf t_client
	rm -Rf t_lib
	rm -Rf t_misc
t_lib:
	gcc -O3 -pthread -lcrypto -Wall -std=c99 -o t_lib t_lib.c
t_server:
	gcc -O3 -Wall -std=c99 -o t_server t_server.c
t_client:
	gcc -O3 -pthread -lcrypto -Wall -std=c99 -o t_client t_client.c
t_misc:
	gcc -O3 -Wall -std=c99 -o t_misc t_misc.c
debug_t_lib:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o t_lib t_lib.c
debug_t_server:
	gcc -O3 -g -Wall -std=c99 -o t_server t_server.c
debug_t_client:
	gcc -O3 -pthread -lcrypto -g -Wall -std=c99 -o t_client t_client.c
debug_t_misc:
	gcc -O3 -g -Wall -std=c99 -o t_misc t_misc.c