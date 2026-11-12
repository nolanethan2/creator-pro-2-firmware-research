//@category Firmware
import ghidra.app.script.GhidraScript;
import java.nio.file.*;
public class ExportFunctionBodies extends GhidraScript {
 public void run()throws Exception{
  StringBuilder s=new StringBuilder("address\tname\tranges\n");for(var f:currentProgram.getFunctionManager().getFunctions(true)){s.append(f.getEntryPoint()+"\t"+f.getName()+"\t");boolean first=true;for(var r:f.getBody().getAddressRanges()){if(!first)s.append(",");s.append(r.getMinAddress()+"-"+r.getMaxAddress());first=false;}s.append("\n");}Files.writeString(Path.of(getScriptArgs()[0]),s.toString());println("Exported function bodies");
 }
}
