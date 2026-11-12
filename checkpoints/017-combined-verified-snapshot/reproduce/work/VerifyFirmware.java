//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.nio.file.*;
import java.security.*;
public class VerifyFirmware extends GhidraScript {
 public void run() throws Exception {
  int size=Integer.parseInt(getScriptArgs()[1]);byte[] data=new byte[size];currentProgram.getMemory().getBytes(toAddr(0x08000000L),data);
  StringBuilder hash=new StringBuilder();for(byte v:MessageDigest.getInstance("SHA-256").digest(data))hash.append(String.format("%02x",v));
  int good=0,bad=0;for(Function f:currentProgram.getFunctionManager().getFunctions(true)){if(f.getName().startsWith("FUN_")||f.getName().startsWith("App_IRQ")||f.getName().startsWith("Boot_IRQ"))bad++;else good++;}
  String result="{\"flash_size\":"+size+",\"flash_sha256\":\""+hash+"\",\"function_count\":"+currentProgram.getFunctionManager().getFunctionCount()+",\"named_functions\":"+good+",\"automatic_names\":"+bad+",\"program\":\""+currentProgram.getName()+"\"}";
  Files.writeString(Path.of(getScriptArgs()[0]),result);println(result);
 }
}
