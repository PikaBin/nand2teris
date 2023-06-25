// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/06/rect/Rect.asm

// Draws a rectangle at the top-left corner of the screen.
// The rectangle is 16 pixels wide and R0 pixels high.

//重写
@R0
D = M
@END
D;JLE // IF R0 <=0

@SCREEN
D = A
@arr
M=D //arr = screen




(LOOP)
@arr
A = M
M=-1
@32
D = A
@arr
M = M+D







@i
M= M+1

@R0
D = M
@i
D=D - M// R0 = i
@LOOP
D;JGT



(END)
@END
0;JMP


