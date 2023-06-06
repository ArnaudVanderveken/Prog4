Design choices:
- Level file format:
    The text format consists of the level layout, as a string of digits ranging from 0 to 3, representing the different types of tiles.
    The next lines contains the x and y corrdinates for spawning the player 1, separated by a space.
    The next lines contains the x and y corrdinates for spawning the player 2, separated by a space.
    The next line first contains the number of regular enemies, then all the X and Y coordinates of their respective spawn points, all separated by a space.
    Finally, the last line first contains the number of recognizer enemies, then all the X and Y coordinates of their respective spawn points, all separated by a space.

    For the binary, the overall layout is the same, but the level layout is compressed by storing four tiles per byte, as each tile take only 2 bits.
    The coordinates are stored in a binary format as well, each as a 16 bits unsigned integer.
    The number of enemies is only an 8 bits unsigned integer.
    The bianry format was generated from the text file, using a homemade converter. 

    The engine accepts both file formats, and checks the extension to know which parser to use.

