use evdev::{AttributeSet, EventType, InputEvent, KeyCode, uinput::VirtualDevice};
use std::{thread::sleep, time::Duration};

fn main() -> anyhow::Result<()> {
    let mut device = VirtualDevice::builder()?
        .name("Virtual Mouse")
        .with_keys(&AttributeSet::from_iter([KeyCode::BTN_LEFT]))?
        .build()?;

    for path in device.enumerate_dev_nodes_blocking()? {
        let path = path?;
        println!("Available as {}", path.display());
    }

    println!("Waiting for Ctrl-C...");
    loop {
        device.emit(&[InputEvent::new_now(
            EventType::KEY.0,
            KeyCode::BTN_LEFT.0,
            1,
        )])?;
        device.emit(&[InputEvent::new_now(
            EventType::KEY.0,
            KeyCode::BTN_LEFT.0,
            0,
        )])?;

        sleep(Duration::from_millis(1));
    }
}
