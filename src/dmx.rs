extern crate libusb;

pub struct Dmx {
    context: libusb::Context
}

impl Dmx {
    pub fn new() -> Dmx {
        let usb = libusb::Context::new().unwrap();

        Dmx { context: usb }
    }

    pub fn connect(&mut self) {
        for device in self.context.devices().unwrap().iter() {
            let device_desc = device.device_descriptor().unwrap();

            if device_desc.vendor_id() == 0x10cf && device_desc.product_id() == 0x8062 {
                println!("Found DMX!");
            }
        }
    }
}
