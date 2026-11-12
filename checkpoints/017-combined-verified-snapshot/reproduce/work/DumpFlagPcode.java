//@category Firmware
import ghidra.app.script.GhidraScript;
import java.nio.file.*;
public class DumpFlagPcode extends GhidraScript {
 public void run()throws Exception{
  StringBuilder s=new StringBuilder();for(String x:new String[]{"NG","ZR","CY","OV","fpscr"}){var r=currentProgram.getRegister(x);s.append(x+" "+r.getAddress()+" bits="+r.getBitLength()+" minbytes="+r.getMinimumByteSize()+"\n");}
  for(long a:new long[]{0x0804b7d8L,0x0804b7dcL,0x0804b7e0L,0x0804b7e4L,0x0804b7eaL}){var i=getInstructionAt(toAddr(a));s.append(i.getAddress()+" "+i+"\n");for(var p:i.getPcode())s.append(p+"\n");}
  Files.writeString(Path.of(getScriptArgs()[0]),s.toString());println(s.toString());
 }
}
