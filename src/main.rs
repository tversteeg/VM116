extern crate gtk;

use gtk::prelude::*;


use gtk::{Box, Scale, Orientation, Button, Window, WindowType};

fn main() {
    if gtk::init().is_err() {
        println!("Failed to initialize GTK.");
        return;
    }

    let window = Window::new(WindowType::Toplevel);
    window.set_title("VM116/K8062 test");
    window.set_default_size(350, 500);
    
    let grid = Box::new(Orientation::Horizontal, 1);

    for _ in 0..6 {
        let scale = Scale::new_with_range(Orientation::Vertical, 0.0, 255.0, 1.0);
        grid.add(&scale);
    }

    let button = Button::new_with_label("Click me!");

    grid.add(&button);
    window.add(&grid);
    window.show_all();

    window.connect_delete_event(|_, _| {
        gtk::main_quit();
        Inhibit(false)
    });

    button.connect_clicked(|_| {
        println!("Clicked!");
    });

    gtk::main();
}
