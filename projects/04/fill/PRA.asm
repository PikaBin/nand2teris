/**mult**/

@R0
D = M
@End
D;JLT

@R1
D=M
@End
D;JLT

@R2
M=0

(Loop)
@R2
D=M
@R1
D = M+D
@R2
M=D
@R0
M=M-1
@R0
D = M

@Loop
D;JGT


(End)
@End
0;JMP


//第二种方法
@i
M = 0; // i = 0

@R2
M = 0; // R2 = 0

(LOOPMULT)

//if i<R1 goto ADD，在这里R1被当作加法的计数上限（因为乘法是用加法来实现的）

@i
D = M; //D = i
@R1
D = D - M; // D = i-R1

@END
D;JGE // if i>=R1 goto END

// R2 = R2+R0

@R0
D = M; // D = R0

@R2
M = D + M; //R2 = R2+R0

@i
M = M+1; // i++

@LOOPMULT
0;JMP

(END)
@END
0;JMP



/***fill.asm**/

@SCREEN
D=A
@i
M = D



(LOOP)
@KEYBOARD
D = A

@Black
D;JGT

(White)
@i
D = M;
@SCREEN
D = D-A
@LOOP
D;JLE

@i
D=M
M=0
M = D-1
@White
0;JMP

(Black)
@i
D = M;
@24576
D = D-A
@LOOP
D;JEQ

@i
D = M
M=-1
M = D+1
@Black
0;JMP
/***************2022-12-11****************/

 // 24576为键盘的地址 16384-24575 刚好8K 为屏幕的地址
    @24575
    D = A

    // R0存储屏幕最大地址
    @0
    M = D

    // R1存储屏幕当前地址，初始值为屏幕基地址
    @SCREEN
    D = A
    @1
    M = D
(LOOP)
    @KBD
    D = M
    @FILL
    D;JGT

    @CLEAR
    0;JMP
(FILL)
    // 判断屏幕是否为满
    @0
    D = M
    @1
    D = D - M
    @LOOP
    D;JLT //R0 - R1<0

    @1

    // 将当前地址推入A
    A = M
    // 将地址对应的屏幕位置变黑
    // 如果使用 1，翻译成二进制是 0000000000000001
    // -1 翻译成二进制是 1111111111111111
    // 如果表示在屏幕上，1 有 15 位是空白的，1位是黑的
    // -1 则屏幕上的 16 位全是黑色
    M = -1

    // 当前地址+1

    @1
    M =  M + 1

    @LOOP
    0;JMP

(CLEAR)
    // 判断屏幕是否为空
    @SCREEN
    D = A
    @1
    D = D - M
    @LOOP
    D;JGT

    @1
    // 缓存当前地址
    //D = M
    // 将当前地址推入A
    A = M
    // 将地址对应的屏幕位置变白
    M = 0

    // 当前地址-1
    @1
    M = M - 1;

    @LOOP
    0;JMP