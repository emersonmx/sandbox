use bevy::{prelude::*, window::close_on_esc, window::PresentMode};

const TILE_SIZE: usize = 64;
const SPRITESHEET_SIZE: (usize, usize) = (3, 4);

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(Time::<Fixed>::from_hz(60.0))
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Move Animated Character".to_string(),
                resolution: (640.0, 480.0).into(),
                resizable: false,
                present_mode: PresentMode::Immediate,
                ..default()
            }),
            ..default()
        }))
        .add_systems(Startup, setup)
        .add_systems(Update, animate_sprite)
        .add_systems(Update, move_player)
        // .add_systems(Update, change_animation)
        .add_systems(Update, close_on_esc)
        // .add_startup_system_to_stage(StartupStage::PreStartup, create_player_animations)
        // .add_systems(setup_camera)
        // .add_systems(setup_ground)
        // .add_systems(setup_player)
        // .add_system_set(
        //     SystemSet::new()
        //         .with_run_criteria(FixedTimestep::step(TIME_STEP as f64))
        //         .with_system(move_player),
        // )
        // .add_system(change_animation)
        // .add_system(exit_on_esc_system)
        .run();
}

#[derive(Component)]
struct Player;

#[derive(Component, PartialEq, Copy, Clone, Debug)]
enum CharacterState {
    Idle,
    Moving,
}

#[derive(Component, Debug, Deref, DerefMut)]
struct Speed(f32);

#[derive(Component, Copy, Clone, Debug)]
enum Direction {
    Up,
    Right,
    Down,
    Left,
}

#[derive(Component)]
struct AnimationIndices(usize, usize);

#[derive(Component, Deref, DerefMut)]
struct AnimationTimer(Timer);

fn setup(
    mut commands: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
) {
    let texture_handle = asset_server.load("player/spritesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::splat(TILE_SIZE as f32),
        SPRITESHEET_SIZE.0,
        SPRITESHEET_SIZE.1,
        None,
        None,
    );
    let texture_atlas_handle = texture_atlases.add(texture_atlas);
    let animation_indices = AnimationIndices(6, 8);

    commands.spawn(Camera2dBundle::default());

    commands.spawn((
        Player,
        Speed(300.0),
        SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            sprite: TextureAtlasSprite::new(animation_indices.0),
            transform: Transform::from_translation(Vec3::new(0.0, 0.0, 1.0)),
            ..default()
        },
        animation_indices,
        AnimationTimer(Timer::from_seconds(0.15, TimerMode::Repeating)),
        CharacterState::Idle,
        Direction::Down,
    ));
}

fn animate_sprite(
    time: Res<Time>,
    mut query: Query<(
        &AnimationIndices,
        &mut AnimationTimer,
        &mut TextureAtlasSprite,
        &CharacterState,
    )>,
) {
    for (indices, mut timer, mut sprite, state) in &mut query {
        if state == &CharacterState::Idle {
            sprite.index = indices.0;
            continue;
        }
        timer.tick(time.delta());
        if timer.just_finished() {
            sprite.index = if sprite.index == indices.1 {
                indices.0
            } else {
                sprite.index + 1
            };
        }
    }
}

fn move_player(
    time: Res<Time>,
    input: Res<Input<KeyCode>>,
    mut query: Query<(&Speed, &mut CharacterState, &mut Direction, &mut Transform), With<Player>>,
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
        transform.translation += velocity.normalize() * speed.0 * time.delta_seconds();
    }
}

fn change_animation(
    mut query: Query<(
        &Direction,
        &CharacterState,
        &mut AnimationIndices,
        &mut TextureAtlasSprite,
    )>,
) {
    for (direction, state, mut indices, mut sprite) in &mut query {
        if state == &CharacterState::Moving {
            *indices = match direction {
                Direction::Left => AnimationIndices(9, 11),
                Direction::Right => AnimationIndices(3, 5),
                Direction::Up => AnimationIndices(0, 2),
                Direction::Down => AnimationIndices(6, 8),
            };
            sprite.index = indices.0;
        }
    }
}

// fn setup_ground(mut commands: Commands, asset_server: Res<AssetServer>) {
//     for i in -4..=4 {
//         for j in -5..=5 {
//             commands.spawn_bundle(SpriteBundle {
//                 texture: asset_server.load("ground/ground_06.png"),
//                 transform: Transform {
//                     translation: Vec3::new(
//                         (TILE_SIZE as i32 * j) as f32,
//                         (TILE_SIZE as i32 * i) as f32,
//                         0.0,
//                     ),
//                     ..Default::default()
//                 },
//                 ..Default::default()
//             });
//         }
//     }
// }
//
// fn move_player(
//     input: Res<Input<KeyCode>>,
//     mut query: Query<(&Speed, &mut CharacterState, &mut Direction, &mut Transform), With<Player>>,
// ) {
//     for (&Speed(speed), mut state, mut direction, mut transform) in query.iter_mut() {
//         let mut velocity = Vec3::ZERO;
//
//         if input.pressed(KeyCode::Left) {
//             velocity.x -= 1.0;
//             *direction = Direction::Left;
//         }
//         if input.pressed(KeyCode::Right) {
//             velocity.x += 1.0;
//             *direction = Direction::Right;
//         }
//         if input.pressed(KeyCode::Up) {
//             velocity.y += 1.0;
//             *direction = Direction::Up;
//         }
//         if input.pressed(KeyCode::Down) {
//             velocity.y -= 1.0;
//             *direction = Direction::Down;
//         }
//
//         if velocity == Vec3::ZERO {
//             *state = CharacterState::Idle;
//             return;
//         }
//
//         *state = CharacterState::Moving;
//         transform.translation += velocity.normalize() * speed * TIME_STEP;
//     }
// }

// fn change_animation(
//     mut commands: Commands,
//     animations: Res<PlayerAnimations>,
//     mut query: Query<(
//         Entity,
//         &Direction,
//         &CharacterState,
//         &mut TextureAtlasSprite,
//         &mut Handle<SpriteSheetAnimation>,
//     )>,
// ) {
//     for (entity, direction, character_state, mut sprite, mut animation) in query.iter_mut() {
//         let row = *direction as usize;
//
//         if *character_state == CharacterState::Idle {
//             sprite.index = row * SPRITESHEET_SIZE.0;
//             commands.entity(entity).remove::<Play>();
//             continue;
//         }
//
//         commands.entity(entity).insert(Play);
//
//         *animation = match direction {
//             Direction::Up => animations.up.clone(),
//             Direction::Right => animations.right.clone(),
//             Direction::Down => animations.down.clone(),
//             Direction::Left => animations.left.clone(),
//         }
//     }
// }
