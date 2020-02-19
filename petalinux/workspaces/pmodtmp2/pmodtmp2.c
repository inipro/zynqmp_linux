#include <linux/err.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of.h>

#define DRIVER_NAME "pmodtmp2"

static ssize_t pmodtmp2_adc_show(struct device *dev, 
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client;
	struct i2c_msg msg[1];
	unsigned char data[2];
	unsigned int val;
	
	client = container_of(dev, struct i2c_client, dev);

	msg[0].addr = client->addr;
	msg[0].flags = I2C_M_RD;
	msg[0].len = 2;
	msg[0].buf = data;

	if (i2c_transfer(client->adapter, msg, 1) < 0)
		dev_err(dev, "i2c_tranfer failed");

	val = (data[0] << 8) | data[1];
	
	return sprintf(buf, "%d\n", val);
}

static DEVICE_ATTR(adc, 0644, pmodtmp2_adc_show, NULL);

static struct attribute *attributes[] = {
	&dev_attr_adc.attr,
	NULL,
};

static const struct attribute_group attr_group = {
	.attrs = attributes,
};

static int pmodtmp2_probe(struct i2c_client *client,
							const struct i2c_device_id *id)
{
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	ret = sysfs_create_group(&client->dev.kobj, &attr_group);
	if (ret)
		return ret;

	return 0;
}

static int pmodtmp2_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &attr_group);

	return 0;
}

static const struct i2c_device_id pmodtmp2_i2c_ids[] = {
	{"pmodtmp2", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, pmodtmp2_i2c_ids);

static const struct of_device_id pmodtmp2_of_ids[] = {
	{ .compatible = "inipro,pmodtmp2", },
	{}
};
MODULE_DEVICE_TABLE(of, pmodtmp2_of_ids);

static struct i2c_driver pmodtmp2_i2c_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(pmodtmp2_of_ids),
	},
	.probe = pmodtmp2_probe,
	.remove = pmodtmp2_remove,
	.id_table = pmodtmp2_i2c_ids,
};

module_i2c_driver(pmodtmp2_i2c_driver);

MODULE_AUTHOR("Hyunok Kim <hokim@inipro.net>");
MODULE_LICENSE("GPL");
