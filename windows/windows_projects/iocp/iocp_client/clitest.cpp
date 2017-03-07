#include "../public/sockets.h"


int main()
{
	if (xsocket_init())
	{
		return -1;
	}
	xsocket_handle * connector;

	xsocket_tcp_connector_create(&connector, "127.0.0.1", 9999);


	char buff[1024] = {0};

	for (;;)
	{
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%s%s", "abcdefghijklmnopqrstuvwx", "yz0123456789");
		socket_write(connector, buff, sizeof(buff));
		
		unsigned long len = sizeof(buff);
		socket_read(connector, buff, &len);
	}
	xsocket_close(connector);

	return 0;
}