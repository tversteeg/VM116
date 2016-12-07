#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/usb.h>

#define USB_DMX_MINOR_BASE 192

#define USB_DMX_VENDOR_ID	0x10cf
#define USB_DMX_PRODUCT_ID 0x8062

static struct usb_device_id usb_dmx_table [] = {
	{USB_DEVICE(USB_DMX_VENDOR_ID, USB_DMX_PRODUCT_ID)},
	{}
};
MODULE_DEVICE_TABLE(usb, usb_dmx_table);

static void dmx_delete(struct kref *kref)
{

}

static int dmx_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int dmx_release(struct inode *inode, struct file *file)
{
	return 0;
}

static int dmx_flush(struct file *file, fl_owner_t id)
{
	return 0;
}

static ssize_t dmx_read(struct file *file, char *buffer, size_t count, loff_t *ppos)
{
	return 0;
}

static ssize_t dmx_write(struct file *file, const char *user_buffer, size_t count, loff_t *ppos)
{
	return 0;
}

static const struct file_operations dmx_fops = {
	.owner =   THIS_MODULE,
	.read =    dmx_read,
	.write =   dmx_write,
	.open =    dmx_open,
	.release = dmx_release,
	.flush =   dmx_flush,
	.llseek =  noop_llseek,
};

static struct usb_class_driver dmx_class = {
	.name =       "dmx%d",
	.fops =       &dmx_fops,
	.minor_base = USB_DMX_MINOR_BASE,
};

static int usb_dmx_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	if(!udev){
		printk(KERN_DEBUG "[debug] udev is null");
		return -ENODEV;
	}

	return 0;
}

static void usb_dmx_disconnect(struct usb_interface *interface)
{
	printk(KERN_DEBUG "disconnect");
}

static struct usb_driver usb_dmx_driver = {
	.name =       "dmx",
	.probe =      usb_dmx_probe,
	.disconnect = usb_dmx_disconnect,
	.id_table =   usb_dmx_table,
};

static int __init dmx_init(void)
{
	printk(KERN_DEBUG "init");

	return 0;
}

static void __exit dmx_exit(void)
{
	printk(KERN_DEBUG "exit");

	usb_deregister(&usb_dmx_driver);
}

module_init(dmx_init);
module_exit(dmx_exit);

MODULE_LICENSE("GPL");
