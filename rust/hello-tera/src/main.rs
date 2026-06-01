use tera::{Context, Tera};

fn main() {
    let tera = match Tera::new("*.tmpl") {
        Ok(t) => t,
        Err(e) => {
            println!("Parsing error(s): {}", e);
            ::std::process::exit(1);
        }
    };
    let mut context = Context::new();
    context.insert("name", "John Doe");
    context.insert("email", "johndoe@example.com");

    let res = tera.render("hello.tmpl", &context);
    if let Ok(t) = res {
        print!("{}", t);
    }
}
