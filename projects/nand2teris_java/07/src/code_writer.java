

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.lang.model.element.Element;




/**
 * Generates assembly code from the parsed VM command
 */
public class code_writer {
    
    // 输出的文件内容
    private FileWriter outputFile;

    //open the outfile/stream and get ready to write into it
    //根据传入的参数来创建输出文件
    public code_writer(String outputFileName) throws IOException {
        File f = new File(outputFileName);
        this.outputFile = new FileWriter(f);

    }

    // write into output file the assembly that implements the given arithmetic command
    public String writerArithmetic(String arithmeticCommand) {
        String type=""; //命令的具体类型add,sub...etc
        String outputCode=""; // 存储输出的汇编代码
        int index = 0; // diff label 

        //因为前面的空格也会写入，所以顶格写
        String universal1 = """
@SP
AM = M -1
D = M
A=A-1                                                       
        """;

        String universal2 = """
@SP
AM=M-1
        """;

        String universal3 = """
@SP
M= M+1
        """;

        switch (type) {
            case "add":
                outputCode = universal1+"M = M+D\r\n";
                break;           
            case"sub":
                outputCode = universal1+"M = M-D\r\n";
                break;
            case "neg":
                outputCode = universal2 + "M = -M\r\n";
                break;

            case "eq":
                outputCode = createRelationString("JEQ",index++);
                break;
            case "lt":
                outputCode = createRelationString("JLT",index++);
                break;
            case "gt":
                outputCode = createRelationString("JGT",index++);
                break;

            case "and":
                outputCode = universal1+"M = M&&D\r\n";
                break;
            case "or":
                outputCode = universal1+"M = M||D\r\n";
                break;
            case "not":
                outputCode = universal2+"M = !M\r\n"+universal3;  
                break;
            default:
                break;
        }

        return outputCode;
    }

    public String createRelationString(String relation,int index) {
        String relationCode = "@SP\r\n"
                            + "AM = M-1\r\n"
                            + "D = M\r\n"
                            + "A = A-1\r\n"
                            + "D = M-D\r\n"
                            + "@TRUE\r\n"
                            + "D;"+relation+"\r\n"
                            + "@SP\r\n"
                            + "AM = M-1\r\n"                            
                            + "M=0\r\n"
                            + "@SP\r\n"
                            + "M = M+1\r\n"
                            + "@LOOP\r\n"
                            + "0;JMP\r\n"
                            + "(TRUE)\r\n"
                            + "@SP\r\n"
                            + "AM = M-1\r\n"
                            + "M=-1\r\n"
                            + "@SP\r\n"
                            + "M=M+1\r\n"
                            + "(LOOP)\r\n";

        return relationCode;
    }

    public String writePushPop(String commandType,String arg1,String arg2,String filename) {
        String outputcode = "";

        switch (arg1) {
            case "CONSTANT":
                outputcode = "@"+arg2+"\r\n"
                            +"D = A\r\n"
                            +"@SP\r\n"
                            +"A=M\r\n"
                            +"M=D\r\n"
                            +"@SP\r\n"
                            +"M=M+1\r\n";                
                break;

                case "STATIC":
                    if(commandType =="push") {
                        outputcode = "@"+filename+"."+arg2+"\r\n"
                                    +"D = M\r\n"
                                    +"@SP\r\n"
                                    +"A = M\r\n"
                                    +"M =D\r\n"
                                    +"@SP\r\n"
                                    +"M = M+1\r\n";
                    }else {
                        outputcode = "@SP\r\n"
                                    +"AM = M-1\r\n"
                                    +"D = M\r\n"
                                    +"@"+filename+"."+arg2+"\r\n"
                                    +"M = D\r\n";
                    }
                    break;

                    case "POINTER":
                        if(arg2 =="1") {
                            arg1 = "that";
                        } else if(arg2 == "0") {
                            arg1 = "this";
                        }

                        if(commandType =="push") {
                            outputcode = "@" + arg1 +"\r\n"
                                        + "D=M\r\n"
                                        + "@SP\r\n"
                                        + "A=M\r\n"
                                        + "M=D\r\n"
                                        + "@SP\r\n"
                                        + "M=M+1\r\n";
                        } else{
                            //此处采用jiao'jian
                            outputcode = "@SP\r\n"
                            +"AM = M-1\r\n"
                            +"D = M\r\n"
                            +"@"+arg1+"\r\n"
                            +"M = D\r\n";
                        }
        
            default:
                break;
        }
        
        return outputcode;

    }

    public String processSegment() {
        String outputSegment = "";
        return outputSegment;
    }
}
