# Image_to_matrix_converter
Class Project for Advanced C Course

My tasks were:
  - Create a module that represents a stack
  - Create a module that takes a picture and converts it into a 0-1 matrix
  - Create a module that finds the longest line in a picture 

The stack is implemented in stacklib.c file. The module for converting a picture (which must be a monochromatic bmp) into a 0-1 matrix is implemented in bmp.c.
The file encoding_decoding.c contains two functions, encodePoint and decodePoint, which are used to store coordinates in a single int value and decode them from that value. This simplifies handling coordinates in situations where we need to add or remove them from the stack.
The file longest_line.c contains function dfs which performs a depth-first search, and the function findLongestLine, which uses dfs to find the longest line.
