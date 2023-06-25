

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;



/**
 * Handles the parsing of a single .vm file; Reads a VM command, parses the
 * command into its lexical components, and provides convenient access to these
 * components ; Ignores all white space and comments;
 * 
 * 
 * question: java translator inputfilename.vm
 */
public class Parser {

    private ArrayList<String> commands; // vm指令内容
    //private String outputContext;//输出的全部内容
    private String currentCommand; //当前命令

    // 打开翻译文件，并获取文件内容(通过文件所在目录下编译，不用加磁盘符等前缀路径)
    public  Parser(String fileName) {
        // 初始化时获取vm文件内容
        File f = new File(fileName);
        this.commands = new ArrayList<>();
        this.currentCommand = null;
        try(BufferedReader input = new BufferedReader(new FileReader(f))) {
            //按行读取，读取的过程中将一条指令当作一个数组元素存储到成员变量commands[],末尾不带换行符
            
            String inputcontext;//读取的每一行内容
            while(( inputcontext = input.readLine())!= null) {
                inputcontext.replaceAll( "//.*|(\"(?:\\\\[^\"]|\\\\\"|.)*?\")|(?s)/\\*.*?\\*/", "" );//去除注释,包含那种嵌入在语句之后的
                commands.add(inputcontext);
                
            }

        }
        catch( Exception e) {
            e.printStackTrace();
        }
        
    }

    public ArrayList<String> getCommands() {
        return this.commands;
    }

    // Are there more commands in the inputs，
    //采用编译一条，删除一条的办法，如果链表里仍存在元素，则说明还有未翻译指令
    public boolean hasMoreCommands()  {
        return commands.isEmpty();
    }

    // 读取下一个命令，并且使其成为当前命令,只有当hasMoreCommands()为true时才执行
    // 返回之前，要判断该条语句是不是注释或者含有注释
    public String advance() throws FileNotFoundException,IOException {
        //编译一条，删除一条,从第一条开始编译
        if(hasMoreCommands()){
            this.currentCommand = commands.remove(0).trim();
            return currentCommand;
        }
        
        return null;
    }

    // 返回当前命令类型(目前只含push,pop,arithmethic)，使用正则表达式
    //如果命令含有push,pop就返回push,pop，否则返回arithmethic,
    public String commandType() {
        String push_reg = "push\\s\\w*\\s\\d*";
        String pop_reg = "pop\\s\\w*\\s\\d*";
        if(currentCommand.matches(push_reg)){
            return "push";
        } else if(currentCommand.matches(pop_reg)) {
            return "pop";
        } else {
            return "arithmethic";
        }

    }

    // 获取 arg1,当命令类型为return时不能使用
    public String arg1() {
        String [] components = currentCommand.split("\\s*");

        if(commandType() == "arithmethic") {
            return currentCommand;
        }

        return components[1];
    }

    // 获取arg2,只有当pop push return call类型的命令才可以使用
    public String arg2() {
        String [] components = currentCommand.split("\\s*");
        return components[2];
    }

    public static void main(String[] args) {
        Parser newParser = new Parser("BasicTest.vm");
        ArrayList<String> commands = newParser.getCommands();
         //"push\\s\\w*\\s\\d*"
        for(String command:commands) {
            System.out.println(command);
           
        }

    }

}


    enum type {
        C_ARITHMETIC,
        C_PUSH,
        C_POP,
        C_LABEL,
        C_GOTO,
        C_IF,
        C_RETURN,
        C_CALL,
        C_FUNCTION,

    }
