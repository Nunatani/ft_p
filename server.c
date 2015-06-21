#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	create_server(int port)
{
	int			sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if(proto == 0)
		return(-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *) &sin, sizeof(sin)) == -1)
	{
		printf("Bind failed\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);
}

void	usage(char *src)
{
	printf("Usage: %s <port>\n", src);
	exit(-1);
}

int	main(int argc, char **argv)
{
	int			port;
	int			sock;
	int			cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	if (argc != 2)
		usage(argv[0]);
	port = atoi(argv[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	close(cs);
	close(sock);
	return (0);
}
