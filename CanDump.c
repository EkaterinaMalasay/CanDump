#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>

int main(int argc, char **argv)
{
	int sockfd;
	int nbytes;
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if( sockfd == -1 ) {
			printf("%s\n", "socket error");
		}

	strcpy(ifr.ifr_name, "can0");
	ioctl(sockfd, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	//start reading
	nbytes = read(sockfd, &frame, CANFD_MTU);
	printf("%x\n", frame.can_id);

	if (nbytes < 0) {
		perror("can raw socket read");
		return 1;
	}
	return 0;
}