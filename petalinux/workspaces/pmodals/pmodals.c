#include <linux/err.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/of.h>

#define DRIVER_NAME "pmodals"

static ssize_t pmodals_adc_show(struct device *dev, 
				struct device_attribute *attr, char *buf)
{
	struct spi_device *spi;
	unsigned char data[2];
	unsigned int val;
	
	spi = container_of(dev, struct spi_device, dev);

	if (spi_read(spi, data, 2) < 0)
		dev_err(dev, "spi_read failed");

	val = ((data[0] << 8) | data[1])>>4;
	
	return sprintf(buf, "%d\n", val);
}

static DEVICE_ATTR(adc, 0644, pmodals_adc_show, NULL);

static struct attribute *attributes[] = {
	&dev_attr_adc.attr,
	NULL,
};

static const struct attribute_group attr_group = {
	.attrs = attributes,
};

static int pmodals_probe(struct spi_device *spi)
{
	int ret;

	/*
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret)
		return ret;
	*/

	ret = sysfs_create_group(&spi->dev.kobj, &attr_group);
	if (ret)
		return ret;

	return 0;
}

static int pmodals_remove(struct spi_device *spi)
{
	sysfs_remove_group(&spi->dev.kobj, &attr_group);

	return 0;
}

static const struct spi_device_id pmodals_spi_ids[] = {
	{"pmodals", 0},
	{}
};
MODULE_DEVICE_TABLE(spi, pmodals_spi_ids);

static const struct of_device_id pmodals_of_ids[] = {
	{ .compatible = "inipro,pmodals", },
	{}
};
MODULE_DEVICE_TABLE(of, pmodals_of_ids);

static struct spi_driver pmodals_spi_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(pmodals_of_ids),
	},
	.probe = pmodals_probe,
	.remove = pmodals_remove,
	.id_table = pmodals_spi_ids,
};

module_spi_driver(pmodals_spi_driver);

MODULE_AUTHOR("Hyunok Kim <hokim@inipro.net>");
MODULE_LICENSE("GPL");
