# Click the Cat
A simple "Click the Cat" game developed for **Garbage Jam #4** using **C** and **Raylib**.

## Gameplay
- Use **WASD** keys to move the cat around the screen
- Click on the cat with your mouse before time runs out
- Each successful click increases your score
- The cat's eyes follow your mouse cursor for extra cuteness

## Features
- Simple, intuitive controls
- Cute animated cat with interactive eyes
- Score tracking with timer
- Sound effects (meow, wilhelm scream) and background music
- Three game states: Start Screen, Playing, Game Over

## How to Build and Run

### Prerequisites
- **Raylib** (https://www.raylib.com/)
- A C compiler (GCC, Clang, etc.)

### Building
1. Clone this repository
2. Install Raylib on your system
3. Build using the provided Makefile:
   ```bash
   make
   ```
   The Makefile generates executables in the `dist/` directory for macOS, Windows, and Web.

### Running
- **macOS**: `./dist/clickthecat-macos`
- **Windows**: `dist\clickthecat.exe`
- **Web**: Open `dist/web/ctc.html` in a browser

## Controls
- **WASD** - Move the cat
- **Mouse** - Aim (cat's eyes follow cursor)
- **Left Click** - Click the cat to score
- **ENTER** - Start game / Restart after game over
- **ESC** - Close window/exit game

## Project Structure
```
src/
├── main.c          # Main entry point
├── game.c          # Game logic and state management
├── player.c        # Cat movement and drawing
├── cat.c           # Cat drawing with interactive eyes
├── audio.c         # Sound effects and music
├── constants.h     # Game constants and configuration
├── player.h        # Player struct and function declarations
├── cat.h           # Cat drawing function declaration
└── audio.h         # Audio resource management
```

## Garbage Jam #4
This game was created as an entry for **Garbage Jam #4**, a game jam focused on creating simple, fun games with limited resources.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## ASSETS USED:
Can be found within the Docs folder in Licenses

## Author
**CieloForge** - https://cieloforge.itch.io | https://github.com/cieloforge

---
*Last updated: 2026-05-25*