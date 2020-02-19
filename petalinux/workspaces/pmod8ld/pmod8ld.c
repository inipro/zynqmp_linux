#include <linux/err.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>

#define DRIVER_NAME "pmod8ld"

struct pmod8ld {
	struct gpio_descs *gpios;
};

static ssize_t pmod8ld_bits_show(struct device *dev, 
				struct device_attribute *attr, char *buf)
{
	struct pmod8ld *leds = dev_get_drvdata(dev);
	int val[8];
	int i;
	unsigned int bits;
	gpiod_get_array_value_cansleep(8, leds->gpios->desc, val);
	bits = 0;
	for (i=0; i<8; i++) {
		bits |= (val[i]&1) << i;
	}
	return sprintf(buf, "%d\n", bits);
}

static ssize_t pmod8ld_bits_store(struct device *dev, 
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct pmod8ld *leds = dev_get_drvdata(dev);
	int val[8];
	int ret;
	int i;
	unsigned int bits;

	ret = kstrtouint(buf, 0, &bits);
	if (ret) return ret;

	for (i=0; i<8; i++)
		val[i] = (bits >> i) & 1;

	gpiod_set_array_value_cansleep(8, leds->gpios->desc, val);

	return count;
}
				 
static DEVICE_ATTR(bits, 0644, pmod8ld_bits_show, pmod8ld_bits_store);

static struct attribute *attributes[] = {
	&dev_attr_bits.attr,
	NULL,
};

static const struct attribute_group attr_group = {
	.attrs = attributes,
};

static int pmod8ld_probe(struct platform_device *pdev)
{
	struct pmod8ld *leds;
	struct device *dev = &pdev->dev;
	int ret;

	leds = devm_kzalloc(&pdev->dev, sizeof(*leds), GFP_KERNEL);
	if (!leds)
		return -ENOMEM;

	leds->gpios = devm_gpiod_get_array(dev, "led", GPIOD_OUT_LOW);
	if (IS_ERR(leds->gpios)) {
		ret = PTR_ERR(leds->gpios);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get gpios\n");
		return ret;
	}

	ret = sysfs_create_group(&dev->kobj, &attr_group);
	if (ret) {
		devm_gpiod_put_array(dev, leds->gpios);
		return ret;
	}

	platform_set_drvdata(pdev, leds);

	return 0;
}

static int pmod8ld_remove(struct platform_device *pdev)
{
	struct pmod8ld *leds = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	devm_gpiod_put_array(dev, leds->gpios);

	sysfs_remove_group(&dev->kobj, &attr_group);

	return 0;
}


static const struct of_device_id pmod8ld_ids[] = {
	{ .compatible = "inipro,pmod8ld", },
	{}
};
MODULE_DEVICE_TABLE(of, pmod8ld_ids);

static struct platform_driver pmod8ld_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(pmod8ld_ids),
	},
	.probe = pmod8ld_probe,
	.remove = pmod8ld_remove,
};

module_platform_driver(pmod8ld_driver);

MODULE_AUTHOR("Hyunok Kim <hokim@inipro.net>");
MODULE_LICENSE("GPL");
