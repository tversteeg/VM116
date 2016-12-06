extern crate gtk;

mod dmx;

use gtk::prelude::*;
use gtk::{Box, Scale, Orientation, Button, Window, WindowType};
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    if gtk::init().is_err() {
        println!("Failed to initialize GTK.");
        return;
    }

    let dmx: Rc<RefCell<dmx::Dmx>> = Rc::new(RefCell::new(dmx::Dmx::new()));
    let captured_dmx = dmx.clone();

    let window = Window::new(WindowType::Toplevel);
    window.set_title("VM116/K8062 test");
    window.set_default_size(350, 500);
    
    let grid = Box::new(Orientation::Horizontal, 1);

    for _ in 0..10 {
        let scale = Scale::new_with_range(Orientation::Vertical, 0.0, 255.0, 1.0);
        grid.add(&scale);

        scale.connect_value_changed(|scale| {

            println!("Scale {}", scale.get_value());
        });
    }

    let button = Button::new_with_label("Connect");

    button.connect_clicked(move |_| {
        let local_dmx = &mut *captured_dmx.borrow_mut();
        local_dmx.connect();
    });

    grid.add(&button);
    window.add(&grid);
    window.show_all();

    window.connect_delete_event(|_, _| {
        gtk::main_quit();
        Inhibit(false)
    });

    gtk::main();
}
