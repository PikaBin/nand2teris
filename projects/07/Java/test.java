


/**
 * test
 * try run java on vscode
 */
public class test {

    public static void main(String[] args) {
        
        String s = "\r";
        boolean isa = s.matches("^@[a-zA-Z0-9_$.:]*$"); // 这个也可以匹配例如 "@  "带空格的形式
        
        //() 伪命令regex
        //boolean isL = s.matches("^\\([^0-9][a-zA-Z0-9_$.:]*\\)$");
        

        // 匹配空格
        //Boolean isSpace = s.matches("\s");
        //System.out.print(isSpace+"\t"+"hel");

        // 根据空格拆分出dest 和 comp
        // String C_command = "D = D+1";
        // String [] compoents = C_command.split("=");
        // for(String compoent:compoents) {
        //     System.out.println(compoent.trim());
        // }

        //匹配含有=号的命令
        // String c = "d=jgt";
        // String compoents[] = c.split(";");
        // System.out.println(compoents[1]);
        
        //去除字符间的空格
        // String c = " d  +m";
        // String textC = c.replaceAll(" *", "");
        // System.out.println("**"+textC+"****");

        //提取@之后的symbol
        String a = "@128";
        String symbol = a.substring(1);
        Integer b = Integer.valueOf(symbol);
        //The idea here is to get the zero padding by putting a 1 in the 17th place of your value, 
        //and then use String.substring() to chop off the leading 1 this creates, 
        //thus always giving you exactly 16 binary digits. 
        //(This works, of course, only when you are certain that the input is a 16-bit number.)
        String binary_String = Integer.toBinaryString(0x10000 | b).substring(2);
        System.out.print("0"+binary_String);
        // int binary = 3|10000;
        // System.out.println(binary);
    }
}