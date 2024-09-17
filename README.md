# School 21. BrickGame Tetris

Implementation of the BrickGame v1.0 (Tetris) in the C programming language, adhering to structured programming principles and using the ncurses library for a terminal-based user interface.

## Features Overview

| Part                   | Description                                                              | Status |
| ---------------------- | ------------------------------------------------------------------------ |--------|
| Tetris Game Logic      | Core mechanics including piece rotation, movement, and line clearing     |   ☑️   |
| Terminal UI            | Uses ncurses library for console-based interface                         |   ☑️   |
| Finite-State Machine   | Formalizes the game logic                                                |   ☑️   |
| Unit Testing           | Full coverage of the game logic with unit tests using the Check library  |   ☑️   |
| Scoring & Records      | Tracks game score and maximum points, saving to file or embedded DBMS    |   ☑️   |
| Level Mechanics        | Increases game speed with each level, up to a maximum of 10 levels       |   ☑️   |

## Project Structure

- The program is written in C language (C11 standard) using the `gcc` compiler.
- The project is divided into two parts:
  - **Game Logic Library**: Located in the `src/brick_game/tetris` folder.
  - **Terminal Interface**: Located in the `src/gui/cli` folder, using the ncurses library.
- The Makefile supports standard GNU targets: `all`, `install`, `uninstall`, `clean`, `dvi`, `dist`, `test`, `gcov_report`.

## Mechanics Overview

- **Piece Rotation**: Rotate pieces clockwise.
- **Horizontal Movement**: Move pieces left and right.
- **Piece Fall Acceleration**: Drop the piece immediately to the bottom.
- **Next Piece Preview**: Display the upcoming piece.
- **Line Clearing**: Remove fully filled lines and update the score.
- **Game Over**: The game ends if the pieces reach the top of the playing field.
- **Piece Shapes**: Includes all classic Tetris pieces.

## Controls

- **Start Game**: Begin the game.
- **Pause**: Pause the game.
- **End Game**: Exit the game.
- **Left Arrow**: Move the piece left.
- **Right Arrow**: Move the piece right.
- **Down Arrow**: Drop the piece.
- **Action** and **Up Arrow**: Rotate the piece.

## Playing Field

- The playing field is 10 "pixels" wide and 20 "pixels" high.

## Run Locally

### Prerequisites

- A C compiler (`gcc` recommended).
- The `ncurses` library for terminal-based rendering.
- The `Check` library for unit testing.
- `gcov` and `lcov` for code coverage.

### Steps

1. **Clone the repository**

    ```bash
    git clone git@github.com:kmiakaeva/S21-tetris.git
    ```

2. **Navigate to the project directory**

    ```bash
    cd S21-tetris/src
    ```

3. **Build the project**

    ```bash
    make
    ```

4. **Run the game**

    ```bash
    ./tetris
    ```

5. **Run tests**

    ```bash
    make test
    ```

6. **Generate code coverage report**

    ```bash
    make gcov_report
    ```

### Additional Commands

1. **Clean build files**

    ```bash
    make clean
    ```

2. **Install the program**

    ```bash
    make install
    ```

3. **Uninstall the program**

    ```bash
    make uninstall
    ```

## Game Mechanics in Detail

### Scoring & Records (Bonus)
- Tracks player score based on lines cleared:
  - 1 row: 100 points
  - 2 rows: 300 points
  - 3 rows: 700 points
  - 4 rows: 1500 points
- Saves the maximum score in a file or an embedded database, persisting between game runs.
- Updates the maximum score during gameplay if the player sets a new high score.

### Level Mechanics (Bonus)
- The game level increases by 1 every 600 points.
- Each level boost speeds up the falling pieces, up to a maximum of level 10.
