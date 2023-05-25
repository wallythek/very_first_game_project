# Very First Game Project
It is a text-based RPG project coded in Year 1.\
I am in charge of 70% of game design and logic.\
Problems: Considerable amount of hard code, Bad variable naming, Excessive game randomness

## Group Members
Kwok Chun Shek Wally\
Shum Ho Yeung Andrew

## Game Concept
The concept of the game is simple, the player would role-play as the character on the map, helping it face difficulties such as puzzles or enemy fights. The player would need to fulfill the in-game requirements in order to help the character win the game.

## Game Description
This text-based game is designed to be an RPG, because it will be fun to implement a game based on enemy fight and movement in a grid map. The whole world is in danger due to an evil kingdom. Game character Donkey embarks on a thrilling journey to find treasure and fragments of a super machine to restore prosperity of the world. However, some fragments are owned by enemies and bosses from the evil kingdom. Donkey has to kill enemies and bosses to obtain the fragments. Before Donkey can activate the super machine, he has to annihilate the final boss. The gameplay gives a good or bad ending depending on whether Donkey can kill the final boss in 3 lives.\
\
The game is based on a 2D map consisting of 2 worlds, each divided into zones, e.g. World 2 Zone C. Donkey moves in a 2D 10 x 10 grid of a particular zone, containing various features, puzzles and challenges, including enemies and traps.\
\
Once a chosen game file is loaded, a map grid showing the current location will be printed. There is a user interface below the map with 8 options (with a unique command character), namely move up ('w'), move left ('a'), move down ('s'), move right ('d'), interact ('x'), help ('h'), save ('z') and quit ('q'). Every time the user can choose an option to execute, if the map settings allow.\
\
A useful helper is there to guide Donkey throughout the journey. The helper first gives an introduction to the storyline and hints Donkey if anything happens on the grid. The helper can also list all the current information if asked by the user (using command 'h').\

## Game Rules
By default, The map has 2 worlds. Donkey has 3 lives from the start. Donkey and all enemies / bosses have stats such as health (HP), attack power (POW), critical (CRT) chance, dodge chance and tools. When facing enemies, Donkey can choose to attack ('a') or use tools ('t'), the tools have special power-ups such as counter-attack or health boosts. Timed text messages will appear to indicate any actions from either side. If the enemy dies, Donkey gets a random stat boost. If he dies in any way (HP <= 0), e.g. enemies, bosses, spikes, he will lose a life and respawn in the top left corner of Zone A of the current world he is in. If he loses all his life, it will be game over, and all data of the game file will be deleted.\
\
The user can enter a char command one by one each time. The user can also enter a string of command characters in a single line of input in order to save time, but only moving options ('w'/'a'/'s'/'d') and interact ('x') are allowed. If a command character is invalid (e.g. interact ('x') a coordinate with nothing, move towards a barrier " X "), or if the execution of a command character triggers any game setting, (e.g. interact ('x') a treasure / question mark, move towards an enemy / spike), characters following the command on the same line will be ignored (cin ignore).\

## List of Implemented Features

#### 1. Three different save files
When the game starts, the user has to choose a game file to play (1-3), either unused or previously saved. If the file has been saved before, the user will continue the game in that file with the saved progress and stats.
#### 2. Allowing user to save / delete any game file
Anywhere in a zone (except boss zones), the user can choose to save the game progress and quit. At the game file selection interface (game start), the user may delete all data from a previously saved game file with a confirmation message.
#### 3. Random nature of certain game features
There are treasures in zones to be opened, which gives a random stat boost such as HP increase / recovery, CRT chance / dodge chance increase and tools. The critical chance indicates the possibility of dealing double damage to enemies. The dodge chance indicates the possibility of dodging enemy attack. Random nature also applies to enemy stats in a zone, based on default enemy stats range tailor-made for each zone. Even the speech enemies give is randomly selected from a list of speech. Whether or not the enemy / boss decides to regenerate their HP if they have suitable tools ("full HP"), is random in nature.
#### 4. Printing of zone grid upon input
Every time after input, the zone grid's expected output is printed, which means the outcome of an attack or loot from treasure is displayed. Sometimes customized printing (e.g. in boss zones) can auto (timed) print the grid without user input.
#### 5. Required puzzles / challenges to proceed
Pathways across zones or within a zone may be blocked by entities. The user has to observe and complete the puzzles / challenges to proceed. Examples may include a moving maze and interactive mechanism to clear the road. For some scenarios, even the helper cannot tell everything that happened / what is happening (customized speech), and the puzzle is left for the user alone to solve.

## How the Features are Supported

#### 1. Generation of random game sets or events
There are many types of random events such as randomness in crt, dodge, treasure and enemy stats.
#### 2. Data structures for storing game status
Data structures such as 2D (static) arrays are used to store and update the grids of a zone. Vectors are used to (dynamically) store data of tools for both Donkey and enemies. Various structs are used to store different kinds of zone and stats information (zone: zonename, grid, enemy stats range (a size 2 array of stats); stats: fullhp, hp, crt, defence, dodge, tools; pos: x coordinate (vertical direction), y coordinate (horizontal direction)). Most importantly, all loaded zones information is stored in a map (associative containers) with key corresponding zonename (e.g. zones\["A2"]). A struct zone type pointer points to a map element showing the current zone, and changes when Donkey changes zone / world.
#### 3. Dynamic memory management
Vectors are used for tools management. Commands such as "push_back", "erase", "pop_back", e.t.c are used to dynamically manage memory (in runtime). When the game is over / the user wins / the user quits a gameplay, the tools vector is cleared, in which the destructor is automatically called.
#### 4. File input/output (e.g. for loading / saving game status)
We have created three save (.txt) files for storing game status. It requires fstream to manipulate. We use ofstream to output the data into the save file in carefully spaced / lined numbers, strings and grid, overwriting the current data (either last save information or nothing). We then use ifstream to get back the data and store them in the data structures.
#### 5. Program codes in multiple files
Multiple files are allocated for different functions and memory, such as printing the grid (printgrid.cpp), original game/map settings (default.cpp), file I/O manipulation (filemanip.cpp), manipulating stats (stats.cpp), e.t.c.

## Sample I/O file
We have provided 3 sample output files to show some expected input-output relationship. We provide 2 possible save/load file I/O, in files 2 and 3. File 1 is a raw file that requires the user to start from scratch. 

## Compilation and Execution Instructions
For compilation, simply type "make game" as the shell command, the makefile will automatically compile the whole game. Then do ./game to play.\
\
For execution, as mentioned, most commands are inputted as characters or a string of characters. Every possible character command is shown on the screen most of the time. In select file interface, simply input the file number to play. In a normal zone, 'w', 'a', 's', 'd' gives one movement if valid, while "aawwx", if valid, moves the character two spots left, then two spots up, then interact. In a fight scene, only a character of command is accepted, since the character cannot double attack. However for tools, after typing 't', the tool commands are a line of string with instructions such as "h+34" for HP boost +34.
