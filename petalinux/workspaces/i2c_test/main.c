#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


int main()
{
	int i2c_fd;
	uint8_t data[2];
	int temp;

	i2c_fd = open("/dev/i2c-0", O_RDWR);
	if (i2c_fd < 0) {
		perror("open err\n");
		return i2c_fd;
	}

	if (ioctl(i2c_fd, I2C_SLAVE, 0x4b) < 0) {
		perror("ioctl slave error");
		return -1;
	}

	while (1) {
		read(i2c_fd, data, 2);
		temp = (data[0] << 8) | data[1];
		printf("temp = %d\n", temp);

		sleep(1);
	}

	return 0;
}
