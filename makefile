all: ttfn_server ttfn_client
	
ttfn_server: ttfn_server.c
	gcc -g ttfn_server.c -o ttfn_server

ttfn_client: ttfn_client.c
	gcc -g ttfn_client.c -o ttfn
