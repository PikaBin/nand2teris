package src;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;

/**
 * 无符号翻译器的入口
 * 1.根据传入的文件路径，读取汇编指令文件，然后将其翻译成机器指令
 * 2.将机器指令存入到后缀为.hack的文件中
 */
public class App {


    //获取指令文本
    

    public static void main(String[] args) {
        //new File("E:\\nand2tetris\\projects\\06", "add\\Add.asm")
        ArrayList<String> machineTexts = toMachineCommand("E:\\nand2tetris\\projects\\06\\add\\Add.asm");
        // for(String machineText:machineTexts) {
        //     System.out.print(machineText);
        // }

        //将机器指令写入文件中
        File machineText = new File("E:\\nand2tetris\\projects\\06\\add\\Add.hack");
        try (OutputStream outMachine = new FileOutputStream(machineText,true)){
            for(String singleMachine:machineTexts) {
                outMachine.write(singleMachine.getBytes("UTF-8"));                
            }
        } catch (Exception e) {
            //TODO: handle exception
            e.printStackTrace();
        }
        
    }

    //将编译指令转为机器指令
    public static ArrayList<String> toMachineCommand(String path) {
        Parser p = new Parser(new File(path));
        src.Code code = new Code();
        ArrayList<String> machineCommands = new ArrayList<>();
        String singleMachine = null;


        ArrayList<String> commandText = p.getCommands();
        for(String singleCommand:commandText) {
            String commandType = p.commandType(singleCommand);
            if(commandType.equals("A_type")) {
                singleMachine = p.symbol(singleCommand)+"\n";
                
            } else {
                String dest = code.destBits(p.dest(singleCommand));
                String comp = code.compBits(p.comp(singleCommand));
                String jump = code.jumpBits(p.jump(singleCommand));
                singleMachine = "111" + comp+dest+jump+"\n";
            }
            machineCommands.add(singleMachine);
        }
        
        return machineCommands;
    }
     
}
