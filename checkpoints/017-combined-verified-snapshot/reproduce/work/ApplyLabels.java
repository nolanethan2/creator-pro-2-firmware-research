//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
public class ApplyLabels extends GhidraScript {
 public void run()throws Exception{
  int n=0;
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){String[] v=line.split("\t",4);if(v.length<4||v[0].equals("address"))continue;Function f=getFunctionAt(toAddr(Long.parseLong(v[0],16)));if(f==null)throw new Exception("No existing function: "+v[0]);f.setName(v[1],SourceType.USER_DEFINED);f.setComment("Static analysis confidence: "+v[2]+". Evidence: "+v[3]);n++;}
  println("Applied "+n+" reviewed function labels; preserved program bytes and types");
 }
}
