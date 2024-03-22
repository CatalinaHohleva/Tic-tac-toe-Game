# Tic-tac-toe Game

This is a simple implementation of the classic Tic-tac-toe game using C++ and the graphics.h library.

## Description
This implementation of the Tic-tac-toe game is intended for local multiplayer for 2 players on a single device, such as a computer or laptop. It does not include an option for playing against the computer.
After launching the game, you'll first encounter the menu, where you'll have the option to select the board size, ranging from 3 X 3 to 8 X 8.
In each game, X starts first, then O follows.
The player who aligns a sequence of X's or O's matching the size of the board in a column, row, or diagonal wins.
To initiate a new game, simply click on the 'Replay' button.
In the event of an unexpected closure, the game state is automatically saved.
However, if the closure occurs after the game has concluded (either due to a victory or a draw), the menu will reopen, allowing you to start a new game. 
To exit the game entirely, navigate to the menu and select the 'Exit' button.

## Features
- Supports local multiplayer for 2 players on the same device.
- Allows players to choose the board size, ranging from 3 X 3 to 8 X 8.
- Provides a replay option to restart the game.
- Automatically saves the game state in case of a forced closure.

## How to Use
1. Clone or download the repository.
2. Compile the code using a C++ compiler that supports the graphics.h library.
3. Run the executable file to start the game.
4. Follow the on-screen instructions to play the game.

## Dependencies
- This code uses the graphics.h library, which may not be available in all C++ compilers.
- Tested on Windows platform with the Code::Blocks IDE.

## Contribution
Contributions to improve the code or add new features are welcome! Please fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the MIT License.
