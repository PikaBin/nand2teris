@256
D=A
@SP
M = D
@Sys.init_returnAdress_
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@ARG
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THIS
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THAT
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
D=M
@LCL
M=D
@5
 D=D-A
@ARG
M=D
@Sys.init
0;JMP
(Sys.init_returnAdress_)
(Class1.set)
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
@13
 M=D
@0
 D=A
@Class1.vm.0
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
@Class1.vm.1
 D=D+M
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
@LCL
 D=M
@FRAME1
 M=D
@5
 D=D-A
 A=D
 D=M
@ret1
 M=D
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
@ARG
 D=M
@SP
 M=D+1
@FRAME1
 A=M-1
 D=M
@THAT
 M=D
@FRAME1
 D=M
 @2
 D=D-A
 A=D
 D=M
@THIS
 M=D
@FRAME1
 D=M
 @3
 D=D-A
 A=D
 D=M
@ARG
 M=D
@FRAME1
 D=M
 @4
 D=D-A
 A=D
 D=M
@LCL
 M=D
@ret1
 A=M
 0;JMP
(Class1.get)
@Class1.vm.0
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
@Class1.vm.1
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
D=M-D
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
 D=M
@FRAME2
 M=D
@5
 D=D-A
 A=D
 D=M
@ret2
 M=D
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
@ARG
 D=M
@SP
 M=D+1
@FRAME2
 A=M-1
 D=M
@THAT
 M=D
@FRAME2
 D=M
 @2
 D=D-A
 A=D
 D=M
@THIS
 M=D
@FRAME2
 D=M
 @3
 D=D-A
 A=D
 D=M
@ARG
 M=D
@FRAME2
 D=M
 @4
 D=D-A
 A=D
 D=M
@LCL
 M=D
@ret2
 A=M
 0;JMP
(Class2.set)
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
@13
 M=D
@0
 D=A
@Class2.vm.0
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
@Class2.vm.1
 D=D+M
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
@LCL
 D=M
@FRAME3
 M=D
@5
 D=D-A
 A=D
 D=M
@ret3
 M=D
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
@ARG
 D=M
@SP
 M=D+1
@FRAME3
 A=M-1
 D=M
@THAT
 M=D
@FRAME3
 D=M
 @2
 D=D-A
 A=D
 D=M
@THIS
 M=D
@FRAME3
 D=M
 @3
 D=D-A
 A=D
 D=M
@ARG
 M=D
@FRAME3
 D=M
 @4
 D=D-A
 A=D
 D=M
@LCL
 M=D
@ret3
 A=M
 0;JMP
(Class2.get)
@Class2.vm.0
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
@Class2.vm.1
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
D=M-D
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
 D=M
@FRAME4
 M=D
@5
 D=D-A
 A=D
 D=M
@ret4
 M=D
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
@ARG
 D=M
@SP
 M=D+1
@FRAME4
 A=M-1
 D=M
@THAT
 M=D
@FRAME4
 D=M
 @2
 D=D-A
 A=D
 D=M
@THIS
 M=D
@FRAME4
 D=M
 @3
 D=D-A
 A=D
 D=M
@ARG
 M=D
@FRAME4
 D=M
 @4
 D=D-A
 A=D
 D=M
@LCL
 M=D
@ret4
 A=M
 0;JMP
(Sys.init)
@6
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@8
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@Class1.set_returnAdress_0
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@ARG
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THIS
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THAT
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
D=M
@LCL
M=D
@5
 D=D-A
@2
D=D-A
@ARG
M=D
@Class1.set
0;JMP
(Class1.set_returnAdress_0)
@SP
 AM=M-1
 D=M
@13
 M=D
@0
 D=A
@5
 D=D+A
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@23
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@15
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@Class2.set_returnAdress_1
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@ARG
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THIS
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THAT
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
D=M
@LCL
M=D
@5
 D=D-A
@2
D=D-A
@ARG
M=D
@Class2.set
0;JMP
(Class2.set_returnAdress_1)
@SP
 AM=M-1
 D=M
@13
 M=D
@0
 D=A
@5
 D=D+A
 @14
 M=D
@13
 D=M
@14
 A=M
 M=D
@Class1.get_returnAdress_2
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@ARG
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THIS
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THAT
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
D=M
@LCL
M=D
@5
 D=D-A
@0
D=D-A
@ARG
M=D
@Class1.get
0;JMP
(Class1.get_returnAdress_2)
@Class2.get_returnAdress_3
D=A
@SP
 A=M
 M=D
@SP
 M=M+1
@LCL
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@ARG
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THIS
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@THAT
D=M
@SP
 A=M
 M=D
@SP
 M=M+1
@SP
D=M
@LCL
M=D
@5
 D=D-A
@0
D=D-A
@ARG
M=D
@Class2.get
0;JMP
(Class2.get_returnAdress_3)
(Sys.init$WHILE)
@Sys.init$WHILE
0;JMP