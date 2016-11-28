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

            println!("Bus {:03} Device {:03} ID {:04x}:{:04x}", device.bus_number(), device.address(), device_desc.vendor_id(), device_desc.product_id());
        }
    }
}
