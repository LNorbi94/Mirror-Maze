# Mirror-Maze
The task of the 2023 ZEISS hackathon, with an additional visualization

## Description of task
There is a rectangular room with mirror walls (marked with 1). Inside the room there can also be walls (marked with 1) and empty spaces (marked with 0). On any sides of the room there is an entry hole (marked with 2) and an exit hole (marked with 3). Entry or exit cannot be on the corner of the maze. Light starts at the entry (marked with 2) and moves in the direction of the next empty neighbor (0). Light always travels either horizontally or vertically. If the entry is on the left or right side of the maze, the light starts moving horizontally. If the entry is on the top or bottom of the maze, the light starts moving vertically. When the light hits the wall (1) it is reflected with 180 degrees. Laser light continues its travel through the empty positions (0) till it reaches a wall (1), a mirror (4,5,6,7), exit (3) or entry (2) position.

The competitor shall place mirrors in the room to guide the light through the room from the entry (2) to the exit (3) point. The goal is to find the shortest route by using the fewest additional reflecting surfaces.
There are two kinds of mirrors the competitor can use. First type (marked with 4) reflects light coming from left or right to upwards or downwards respectively, and light coming from up or down to leftwards or rightwards respectively (/). Second type (marked with 5) reflects light coming from left or right to downwards or upwards respectively, and light coming from up or down to rightwards or leftwards respectively (\). The competitor can place those mirrors in empty spaces (0) only.

There are two other kinds of mirrors (marked with 6 and 7). Those mirrors are placed in the maze and cannot be moved. They reflect light the same way as mirrors marked with 4 and 5 respectively, but they do not mean penalties at score calculation.
The width and height of the maze are between 3 and 200 blocks.
Meaning of characters:
1. no wall or reflection on the position
2. wall which reflects with 180 degrees
3. entry of light
4. exit of light
5. mirror in 45 degree diagonal (\/), the competitor can add it to the maze
6. mirror in –45 degree diagonal (\\), the competitor can add it to the maze
7. mirror in 45 degree diagonal (\/), part of the maze
8. mirror in –45 degree diagonal (\\), part of the maze

### Goal
The competitor shall place mirrors in the empty spaces (0) of the room to guide the light through the room from entry (2) to the exit (3) point. The goal is to find the shortest route by using the fewest additional reflection (4, 5).

### Implementation
The solution shall be implemented as a command line application.
Input is passed as process arguments in the following order and meaning: \<width\> \<height\> \<maze\>
* \<width\>: width of the maze (3 <= width <= 200)
* \<height\>: height of the maze (3 <= height <= 200)
* \<maze\>: maze representation as continuous character chain.
The updated maze shall be written to the standard output (STDOUT) without width and height. No other content shall be written to the standard output.
Exit Code of the process shall be 0 for successfully solved maze, or a different value otherwise.

### Scoring
Organizers execute the competitor's uploaded code against a set of mazes not known by the competitor. The execution of each maze shall be finished within 60 seconds. The solution is executed on a single processor core.
The competitor can upload code multiple times to improve his score.
The lower the score is the better.
The score is calculated with the formula:
Reflection penalty * Mirror count + Light length
Reflection penalty value is 5.
Only mirrors placed by the competitor are counted (4,5), the existing mirrors are not (6,7).
1000 points penalty is added to the score for each maze where the code produces invalid result:
Execution is not finished within 60 seconds
The code returns non-zero exit-code
The light does not leave the maze on exit point (3)
Invalid modifications are made to the maze (e.g. mirrors were placed to non-empty (not 0) places etc.)
In case of equal scores, the following judging criteria is used:
The solution wins which is reproducibly and significantly faster
If the speed of the solutions is similar, a code review is performed checking the following aspects:
Uniqueness of the algorithm
Code quality according to Clean Code principles
