package Java;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

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
        String type; //命令的具体类型add,sub...etc
        String outputCode; // 存储输出的汇编代码

        String universal1 = 


        return null;
    }
}
