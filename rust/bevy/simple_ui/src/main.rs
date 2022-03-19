use bevy::{input::system::exit_on_esc_system, prelude::*};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Simple UI".to_string(),
            width: 500.0,
            height: 500.0,
            resizable: false,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_startup_system(setup)
        .add_system(button_system)
        .add_system(exit_on_esc_system)
        .run();
}

const NORMAL_BUTTON: Color = Color::rgb(0.0, 0.5, 0.0);
const HOVERED_BUTTON: Color = Color::rgb(0.20, 0.80, 0.20);
const PRESSED_BUTTON: Color = Color::rgb(0.0, 0.40, 0.0);

fn setup(mut commands: Commands) {
    commands.spawn_bundle(UiCameraBundle::default());

    let full_size = Size::new(Val::Percent(100.0), Val::Percent(100.0));
    let base_style = Style {
        align_items: AlignItems::Center,
        justify_content: JustifyContent::Center,
        size: full_size,
        ..Default::default()
    };

    commands
        .spawn_bundle(NodeBundle {
            style: Style {
                size: full_size,
                flex_direction: FlexDirection::ColumnReverse,
                ..Default::default()
            },
            ..Default::default()
        })
        .with_children(|parent| {
            for _ in 0..3 {
                parent
                    .spawn_bundle(NodeBundle {
                        style: base_style.clone(),
                        ..Default::default()
                    })
                    .with_children(|parent| {
                        for _ in 0..3 {
                            parent.spawn_bundle(ButtonBundle {
                                style: base_style.clone(),
                                color: NORMAL_BUTTON.into(),
                                ..Default::default()
                            });
                        }
                    });
            }
        });
}

fn button_system(
    mut interaction_query: Query<
        (&Interaction, &mut UiColor),
        (Changed<Interaction>, With<Button>),
    >,
) {
    for (interaction, mut color) in interaction_query.iter_mut() {
        match *interaction {
            Interaction::Clicked => {
                *color = PRESSED_BUTTON.into();
            }
            Interaction::Hovered => {
                *color = HOVERED_BUTTON.into();
            }
            Interaction::None => {
                *color = NORMAL_BUTTON.into();
            }
        }
    }
}
