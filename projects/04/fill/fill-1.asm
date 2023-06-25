//写一个监听键盘的程序，只要有键被press,那么屏幕就会变黑

//if KBD != 0,就黑屏，

@SCREEN
D = A
@arr
M = D // arr = SCREEN

@8191
D = A
@i
M = D // i = 512 = 16*32

(LOOP)
@KBD
D = M

@BALCK
D;JNE

@CLEAR
0;JMP

(BLACK)
@i
D = M
@LOOP
D;JLE

@arr
A = M 
M =-1
@1
D = A 
@arr
M = D+M

@i
M = M -1



@LOOP
0;JMP


(CLEAR)

@8191
D = A
@i
D = D-M
@LOOP
D;JLE //如无填充，则重新回到loop

@arr
A = M 
M =0
@1
D = A 
@arr
M = M-D

@i
M = M + 1

@LOOP
0;JMP
