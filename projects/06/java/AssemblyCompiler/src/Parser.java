package src;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

/**
 * 无符号版本的编译器 目标功能： 1.读取汇编语言命令并对其进行解析； 2.提供访问汇编命令成分（域和符号）的方法； 3.去掉所有的空格和注释
 */

public class Parser {

    private ArrayList<String> commands; // 汇编命令的文本内容

    public Parser(File file) {

        this.commands = new ArrayList<>();

        // 读取汇编文件
        try (BufferedReader assembleReader = new BufferedReader(new FileReader(file))) {

            String singleCommand = null;
            while ((singleCommand = assembleReader.readLine()) != null) {
                //// 去除注释
                singleCommand = singleCommand.replaceAll("//.*|(\"(?:\\\\[^\"]|\\\\\"|.)*?\")|(?s)/\\*.*?\\*/", " ");
                // 过滤掉文件中的空白行
                if (!singleCommand.matches("\s") && !singleCommand.matches("")) {
                    String commandText = singleCommand.trim();
                    commands.add(commandText);

                }

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // 获取读入内存的汇编命令内容
    public ArrayList<String> getCommands() {
        return this.commands;
    }

    // 判别是A指令还是C指令，L指令,凡是以@符号开头紧跟符号与十进制数字的命令认为是A指令
    public String commandType(String singleCommand) {
        Boolean isA = singleCommand.matches("^@[a-zA-Z0-9_$.:]*$");
        Boolean isL = singleCommand.matches("^\\([^0-9][a-zA-Z0-9_$.:]*\\)$");

        if (singleCommand == "") {
            return "";
        } else if (isA) {
            return "A_type";
        } else if (isL) {
            return "L_type";
        } else {
            return "C_type";
        }

    }

    // 返回C指令的dest助记符,获取= 之前的指令文本，去掉空格，然后返回；(c指令细分为两类，一类带等号，一类不带)
    public String dest(String C_command) {
        
        if( C_command.contains("=")){
            String[] compoents = C_command.split("=");
            String dest = compoents[0].trim();
            return dest;
        }
        return null;
    }

    // 返回C指令的comp助记符,获取， =之后的指令文本，或者;之前的文本 并去掉空格，然后返回
    public String comp(String C_command) {
        if( C_command.contains("=")){
            String[] compoents = C_command.split("=");
            String comp = compoents[1].trim().replaceAll(" *", "");//去除首尾及字符间的空格
            return comp;
        } else if(C_command.contains(";")) {
            String []comp = C_command.split(";");
            return comp[0].trim();
        }
        return null;
    }

    //返回jump助记符,类似 D;JGT这种形式，;前应该是comp ;后应该是jump
    public String jump(String C_command) {
        if(C_command.contains(";")) {

            String compoents[] = C_command.split(";");      
            return compoents[1].trim();
        }

        return null;

    }

    //返回A指令@后的符号symbol的15位二进制
    public String symbol(String A_command) {
        String symbol = A_command.substring(1);
        Integer symbol_Integer = Integer.valueOf(symbol);
        String symbol_binary = Integer.toBinaryString(symbol_Integer | 0x10000).substring(2);
        return "0"+symbol_binary;
    }


 
    public static void main(String[] args) {

        Parser p = new Parser(new File("E:\\nand2tetris\\projects\\06\\add\\Add.asm"));
        ArrayList<String> CommandText = p.getCommands();

        for (String command : CommandText) {
            if(p.commandType(command).equals("C_type")) {
                String dest = p.dest(command);
                String comp = p.comp(command);
                String jump = p.jump(command);
                // System.out.println("dest:"+dest+"\tcomp:"+comp+"jump:"+jump);


                System.out.println("comp:"+comp+"***");
            }
            System.out.println("other type command");
        }
    }


}