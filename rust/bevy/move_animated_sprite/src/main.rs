use std::time::Duration;

use benimator::{AnimationPlugin, Play, SpriteSheetAnimation};
use bevy::{
    core::FixedTimestep, input::system::exit_on_esc_system, prelude::*,
};

const TIME_STEP: f32 = 1.0 / 60.0;
const SPRITESHEET_SIZE: (usize, usize) = (4, 3);

#[derive(Component, Debug)]
struct Player;

#[derive(Component, PartialEq, Copy, Clone, Debug)]
enum CharacterState {
    Idle,
    Moving,
}

#[derive(Component, Debug)]
struct Speed(f32);

#[derive(Component, Copy, Clone, Debug)]
enum Direction {
    Up,
    Right,
    Down,
    Left,
}

#[derive(Default)]
struct PlayerAnimations {
    up: Handle<SpriteSheetAnimation>,
    right: Handle<SpriteSheetAnimation>,
    down: Handle<SpriteSheetAnimation>,
    left: Handle<SpriteSheetAnimation>,
}

fn create_player_animations(
    mut handles: ResMut<PlayerAnimations>,
    mut assets: ResMut<Assets<SpriteSheetAnimation>>,
) {
    handles.up = assets.add(SpriteSheetAnimation::from_range(
        0..=2,
        Duration::from_millis(150),
    ));
    handles.right = assets.add(SpriteSheetAnimation::from_range(
        3..=5,
        Duration::from_millis(150),
    ));
    handles.down = assets.add(SpriteSheetAnimation::from_range(
        6..=8,
        Duration::from_millis(150),
    ));
    handles.left = assets.add(SpriteSheetAnimation::from_range(
        9..=11,
        Duration::from_millis(150),
    ));
}

fn setup_camera(mut command: Commands) {
    command.spawn_bundle(OrthographicCameraBundle::new_2d());
}

fn setup_player(
    mut command: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
    animations: ResMut<PlayerAnimations>,
) {
    let texture_handle = asset_server.load("player/spritesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::new(64.0, 64.0),
        SPRITESHEET_SIZE.1,
        SPRITESHEET_SIZE.0,
    );
    let texture_atlas_handle = texture_atlases.add(texture_atlas);

    command
        .spawn_bundle(SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 0.0),
                ..Default::default()
            },
            ..Default::default()
        })
        .insert(Player)
        .insert(Speed { 0: 300.0 })
        .insert(CharacterState::Idle)
        .insert(Direction::Down)
        .insert(animations.down.clone());
}

fn move_player(
    input: Res<Input<KeyCode>>,
    mut query: Query<
        (&Speed, &mut CharacterState, &mut Direction, &mut Transform),
        With<Player>,
    >,
) {
    for (speed, mut state, mut direction, mut transform) in query.iter_mut() {
        let mut velocity = Vec3::ZERO;

        if input.pressed(KeyCode::Left) {
            velocity.x -= 1.0;
            *direction = Direction::Left;
        }
        if input.pressed(KeyCode::Right) {
            velocity.x += 1.0;
            *direction = Direction::Right;
        }
        if input.pressed(KeyCode::Up) {
            velocity.y += 1.0;
            *direction = Direction::Up;
        }
        if input.pressed(KeyCode::Down) {
            velocity.y -= 1.0;
            *direction = Direction::Down;
        }

        if velocity == Vec3::ZERO {
            *state = CharacterState::Idle;
            return;
        }

        *state = CharacterState::Moving;
        transform.translation += velocity.normalize() * speed.0 * TIME_STEP;
    }
}

fn change_animation(
    mut command: Commands,
    animations: Res<PlayerAnimations>,
    mut query: Query<(
        Entity,
        &Direction,
        &CharacterState,
        &mut TextureAtlasSprite,
        &mut Handle<SpriteSheetAnimation>,
    )>,
) {
    for (entity, direction, character_state, mut sprite, mut animation) in
        query.iter_mut()
    {
        let row = *direction as usize;

        command.entity(entity).remove::<Play>();
        if *character_state == CharacterState::Idle {
            sprite.index = row * SPRITESHEET_SIZE.1;
            continue;
        }

        command.entity(entity).insert(Play);

        match direction {
            Direction::Up => {
                *animation = animations.up.clone();
            }
            Direction::Right => {
                *animation = animations.right.clone();
            }
            Direction::Down => {
                *animation = animations.down.clone();
            }
            Direction::Left => {
                *animation = animations.left.clone();
            }
        }
    }
}

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Move Animated Character".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            vsync: true,
            ..Default::default()
        })
        .init_resource::<PlayerAnimations>()
        .add_plugins(DefaultPlugins)
        .add_plugin(AnimationPlugin::default())
        .add_startup_system_to_stage(
            StartupStage::PreStartup,
            create_player_animations,
        )
        .add_startup_system(setup_camera)
        .add_startup_system(setup_player)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIME_STEP as f64))
                .with_system(move_player),
        )
        .add_system(change_animation)
        .add_system(exit_on_esc_system)
        .run();
}
