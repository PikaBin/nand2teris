@256
D=A
@SP
M = D
@ARG
D=M
@1
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@1
 D=A
@3
 D=D+A
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@0
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@0
 D=A
@THAT
 D=D+M
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@1
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@1
 D=A
@THAT
 D=D+M
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@ARG
D=M
@0
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@2
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 M=M-1
 A=M
 D=M
@SP
 M=M-1
 A=M
D=M-D
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@0
 D=A
@ARG
 D=D+M
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
(null$MAIN_LOOP_START)
@ARG
D=M
@0
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@SP
AM=M-1
D=M
@null$COMPUTE_ELEMENT
D;JNE 
@null$END_PROGRAM
0;JMP
(null$COMPUTE_ELEMENT)
@THAT
D=M
@0
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@THAT
D=M
@1
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@SP
 M=M-1
 A=M
 D=M
@SP
 M=M-1
 A=M
D=M+D
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@2
 D=A
@THAT
 D=D+M
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@3
D=A
@1
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@1
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 M=M-1
 A=M
 D=M
@SP
 M=M-1
 A=M
D=M+D
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@1
 D=A
@3
 D=D+A
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@ARG
D=M
@0
D=D+A
 A=D
 D=M
@SP
 A=M
 M=D
 @SP
 M=M+1
@1
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 M=M-1
 A=M
 D=M
@SP
 M=M-1
 A=M
D=M-D
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
 AM=M-1
 D=M
@13
 M=D
@0
 D=A
@ARG
 D=D+M
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@null$MAIN_LOOP_START
0;JMP
(null$END_PROGRAM)
