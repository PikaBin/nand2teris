package src;


/**
 * 将HACK语言助记符翻译成机器指令（二进制码）
 */
public class Code {
    public String command;

    public String destBits(String destText){
        String destBit = null;
        if(destText == null) {destBit = "000";}
        else {
        switch (destText) {

            case "M": destBit = "001";break;
            case "D": destBit = "010";break;
            case "MD": destBit = "011";break;//有MD吗？怎么没有见过
            case "A": destBit = "100";break;
            case "AM": destBit = "101";break;
            case "AD": destBit = "110";break;
            case "AMD": destBit = "111";break;

                
        }
    }
        return destBit;
    }

    public String jumpBits(String jumpText) {
        String jumpBits = null;
        
        if(jumpText ==null) {jumpBits = "000";}
        else{
        switch (jumpText) {
            case "JGT":
                jumpBits = "001";
                break;
            case "JEQ": jumpBits = "010";break;
            case "JGE": jumpBits = "011";break;
            case "JLT": jumpBits = "100";break;
            case "JNE": jumpBits = "101";break;
            case "JLE": jumpBits = "110";break;
            case "JMP": jumpBits = "111";break;

        }
    }
        return jumpBits;
    }

    public String compBits(String compText) {
        String compBits=null;
        String a = "0";
        // String param = "A";
        //如果comptext含有 M 那么a=1，否则a=0,同理，当含有表示A/M的变量就是M,否则就是A
        if(compText.contains("M")) {
            a="1";
        }

        switch (compText) {
            case "0":
                compBits = "101010";
                break;
            case "1":compBits = "111111"; break;
            case "-1":compBits = "111010"; break;
            case "D":compBits = "001100"; break;
            case "A":compBits = "110000"; break;
            case "M":compBits = "110000"; break;
            case "!D":compBits = "001101"; break;
            case "!A":compBits = "110001"; break;
            case "!M":compBits = "110001"; break;
            case "-D":compBits = "001111"; break;
            case "-A":compBits = "110011"; break;
            case "-M":compBits = "110011"; break;
            case "D+1":compBits = "011111"; break;
            case "A+1":compBits = "110111"; break;
            case "M+1":compBits = "110111"; break;
            case "D-1":compBits = "001110"; break;
            case "A-1":compBits = "110010"; break;
            case "M-1":compBits = "110010"; break;
            case "D+A":compBits = "000010"; break;
            case "D+M":compBits = "000010"; break;
            case "D-A":compBits = "010011"; break;
            case "D-M":compBits = "010011"; break;
            case "A-D":compBits = "000111"; break;
            case "M-D":compBits = "000111"; break;
            case "D&A":compBits = "000000"; break;
            case "D&M":compBits = "000000"; break;
            case "D|A":compBits = "010101"; break;
            case "D|M":compBits = "010101"; break;
        
            default:
                compBits = "error";
                break;
        }

        
        return a+compBits;
    }

     public static void main(String[] args) {
        Code code = new Code();
        String destBit = code.destBits("D");
        System.out.println(destBit);

    }
}
