use crate::events::{AppEvent, Event, EventHandler};
use crossterm::event::{KeyCode, KeyEvent, KeyModifiers};
use ratatui::{
    DefaultTerminal,
    buffer::Buffer,
    layout::{Alignment, Rect},
    style::{Color, Stylize},
    widgets::{Block, BorderType, Paragraph, Widget},
};

#[derive(Debug)]
pub struct App {
    running: bool,
    counter: u8,
    events: EventHandler,
}

impl Default for App {
    fn default() -> Self {
        Self {
            running: true,
            counter: 0,
            events: EventHandler::default(),
        }
    }
}

impl App {
    pub async fn run(mut self, mut terminal: DefaultTerminal) -> anyhow::Result<()> {
        while self.running {
            terminal.draw(|frame| frame.render_widget(&self, frame.area()))?;
            self.handle_events().await?;
        }
        Ok(())
    }

    async fn handle_events(&mut self) -> anyhow::Result<()> {
        match self.events.next().await? {
            Event::Tick => self.tick(),
            #[allow(clippy::single_match)]
            Event::Crossterm(event) => match event {
                crossterm::event::Event::Key(key_event) => self.handle_key_events(key_event)?,
                _ => {}
            },
            Event::App(app_event) => match app_event {
                AppEvent::Increment => self.increment_counter(),
                AppEvent::Decrement => self.decrement_counter(),
                AppEvent::Quit => self.quit(),
            },
        }
        Ok(())
    }

    fn handle_key_events(&mut self, key_event: KeyEvent) -> anyhow::Result<()> {
        match key_event.code {
            KeyCode::Esc | KeyCode::Char('q') => self.events.send(AppEvent::Quit),
            KeyCode::Char('c' | 'C') if key_event.modifiers == KeyModifiers::CONTROL => {
                self.events.send(AppEvent::Quit)
            }
            KeyCode::Right => self.events.send(AppEvent::Increment),
            KeyCode::Left => self.events.send(AppEvent::Decrement),
            _ => {}
        }
        Ok(())
    }

    fn tick(&self) {}

    fn quit(&mut self) {
        self.running = false;
    }

    fn increment_counter(&mut self) {
        self.counter = self.counter.saturating_add(1);
    }

    fn decrement_counter(&mut self) {
        self.counter = self.counter.saturating_sub(1);
    }
}

impl Widget for &App {
    fn render(self, area: Rect, buf: &mut Buffer) {
        let block = Block::bordered()
            .title(" Counter ")
            .title_alignment(Alignment::Center)
            .border_type(BorderType::Rounded);

        let text = format!(
            "Press `Esc`, `Ctrl-C` or `q` to stop running.\n\
            Press right and left to increment and decrement the counter respectively.\n\
            Counter: {}",
            self.counter
        );

        let paragraph = Paragraph::new(text)
            .block(block)
            .fg(Color::Cyan)
            .bg(Color::Black)
            .centered();
        paragraph.render(area, buf);
    }
}
