#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <linux/spi/spidev.h>

int main()
{
	int spi_fd;
	int spi_mode;
	struct spi_ioc_transfer xfer;
	uint8_t data[2];
	int light;

	spi_fd = open("/dev/spidev0.0", O_RDWR);
	if (spi_fd < 0) {
		perror("open err\n");
		return spi_fd;
	}

	spi_mode = SPI_MODE_3;
	if (ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode) < 0) {
		perror("ioctl mode error");
		return -1;
	}

	while (1) {
		data[0] = data[1] = 0;
		memset(&xfer, 0, sizeof(xfer));
		xfer.tx_buf =(uint64_t)NULL;
		xfer.rx_buf =(uint64_t)data;
		xfer.len = 2;

		ioctl(spi_fd, SPI_IOC_MESSAGE(1), &xfer);

		light = ((data[0] << 8) | data[1]) >> 4; 
		printf("light = %d\n", light);

		sleep(1);
	}

	close(spi_fd);
	return 0;
}
