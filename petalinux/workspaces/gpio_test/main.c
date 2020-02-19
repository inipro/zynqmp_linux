#include <stdio.h>
#include <stdlib.h>
#include "gpio_utils.h"

#define GPIO_BASE_PIN	504

int main(int argc, char *argv[])
{
	int i, val;
	if (argc != 2) {
		fprintf(stderr, "Usage: gpio_test val\n");
		return -1;
	}

	val = atoi(argv[1]);

	for (i=0; i<8; i++) {
		gpio_export(GPIO_BASE_PIN+i);
		gpio_dir_out(GPIO_BASE_PIN+i);
	}
	for (i=0; i<8; i++) {
		if ((val>>i)&0x1) gpio_value(GPIO_BASE_PIN+i, 1);
		else gpio_value(GPIO_BASE_PIN+i, 0);
	}
	for (i=0; i<8; i++) {
		gpio_unexport(GPIO_BASE_PIN+i);
	}
	return 0;
}
