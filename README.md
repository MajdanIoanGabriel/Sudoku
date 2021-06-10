# Sudoku C++

## Structure

The project consists of 2 windows, called MainWindow and GameWindow. When run by the user, the first window is displayed, MainWindow, in which he has several options, to log in, continue the game, start a new one, choose the difficulty (for new games), and close the application .
If he chooses to continue a game or start a new one, he is taken to the second window, Game window, where the game grid is present, with which he can interact, as well as 4 buttons:
  - clear, which resets the game grid
  - solve, which solves the grid
  - back, returns to the main menu,
  - quit, which closes the application

![image](https://user-images.githubusercontent.com/53294181/121597047-e4cc9180-ca48-11eb-8eed-db6f00b425d9.png)

## Concepts used in the project

The project implements the simple rules of this game, namely: each row, column or region must contain only once the numbers from one to nine.
Methods are implemented that check each rule, which are called each time an item in the grid is changed, and which alerts the user in case of a rule violation.
The application also allows the generation of a grid according to a difficulty chosen by the user, as well as saving a grid for any user, using a text file, to be able to access the same level, along with the progress made by the player. 

## Architecture

In the base folder of the project, called Sudoku, there is the build.sh script, and a folder with the project implementation, impl.
In impl we have the file CMakeLists.txt, which is used by the build script, and 2 folders, src (for source files - .cpp) and inc (for header files - .hpp). 

This project was written in C ++, the QT5 library was used for the graphical interface, and was compiled using a CMake script, run by a script written in bash, for a better organization of the project structure. 

## Installation

To compile the game simply run in bash:
./build.sh
Then, in order to generate a new game, go in the game folder and run:
./sudoku

## Screenshots

![image](https://user-images.githubusercontent.com/53294181/121546593-14ad7200-ca14-11eb-982d-6d2fdfe097d5.png)

![image](https://user-images.githubusercontent.com/53294181/121546817-458da700-ca14-11eb-99e4-68e0b9738227.png)

![image](https://user-images.githubusercontent.com/53294181/121546867-4f170f00-ca14-11eb-9148-6515c4e27008.png)
