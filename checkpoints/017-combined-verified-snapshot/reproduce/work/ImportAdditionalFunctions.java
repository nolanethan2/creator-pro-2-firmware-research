//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import java.nio.file.*;
public class ImportAdditionalFunctions extends GhidraScript {
 public void run()throws Exception{
  int before=currentProgram.getFunctionManager().getFunctionCount(),added=0,conflict=0;StringBuilder report=new StringBuilder("address\tname\tstatus\n");
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){String[]v=line.split("\t");if(v.length<3||v[0].equals("address"))continue;var a=toAddr(Long.parseLong(v[0],16));if(getFunctionAt(a)!=null)continue;
   AddressSet body=new AddressSet();boolean safe=true;for(String pair:v[2].split(",")){String[]p=pair.split("-");long lo=Long.parseLong(p[0],16),hi=Long.parseLong(p[1],16);if(lo<0x08000000L||hi>=0x0804c000L)safe=false;body.add(toAddr(lo),toAddr(hi));}
   if(currentProgram.getFunctionManager().getFunctionsOverlapping(body).hasNext())safe=false;
   if(!safe){conflict++;report.append(v[0]+"\t"+v[1]+"\tdeferred: overlap or outside inspected code span\n");continue;}
   DisassembleCommand dis=new DisassembleCommand(a,body,true);dis.applyTo(currentProgram,monitor);
   var f=currentProgram.getFunctionManager().createFunction(v[1],a,body,SourceType.ANALYSIS);f.setComment("Additional function recovered by user's completed Ghidra analysis; imported nonoverlapping body only. Automatic role and boundaries require review. Firmware bytes unchanged.");added++;report.append(v[0]+"\t"+v[1]+"\timported\n");
  }
  Files.writeString(Path.of(getScriptArgs()[1]),report.toString());println("Before="+before+" imported="+added+" deferred="+conflict+" after="+currentProgram.getFunctionManager().getFunctionCount());
 }
}
