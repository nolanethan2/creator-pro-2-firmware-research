//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class FirmwareExport extends GhidraScript {
 public void run() throws Exception {
  File out=new File(getScriptArgs()[0]);out.mkdirs();
  DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  try(PrintWriter c=new PrintWriter(new File(out,"decompiled.c"),StandardCharsets.UTF_8);
      PrintWriter idx=new PrintWriter(new File(out,"functions.tsv"),StandardCharsets.UTF_8);
      PrintWriter refs=new PrintWriter(new File(out,"references.tsv"),StandardCharsets.UTF_8);
      PrintWriter asm=new PrintWriter(new File(out,"disassembly.txt"),StandardCharsets.UTF_8)) {
   idx.println("address\tname\tsize\tdecompile_ok\tcallers\tcallees");refs.println("from\tto\ttype\tfunction");
   FunctionIterator funcs=currentProgram.getFunctionManager().getFunctions(true);int count=0;
   while(funcs.hasNext()&&!monitor.isCancelled()){
    Function f=funcs.next();DecompileResults r=dec.decompileFunction(f,20,monitor);
    idx.printf("%s\t%s\t%d\t%b\t%s\t%s%n",f.getEntryPoint(),f.getName(),f.getBody().getNumAddresses(),r.decompileCompleted(),f.getCallingFunctions(monitor),f.getCalledFunctions(monitor));
    c.printf("\n/* FUNCTION %s %s SIZE %d */\n",f.getEntryPoint(),f.getName(),f.getBody().getNumAddresses());
    if(r.decompileCompleted()&&r.getDecompiledFunction()!=null)c.println(r.getDecompiledFunction().getC());else c.println("/* "+r.getErrorMessage()+" */");
    if(++count%100==0)println("Exported "+count+" functions");
   }
   InstructionIterator ins=currentProgram.getListing().getInstructions(true);
   while(ins.hasNext()){
    Instruction i=ins.next();Function f=getFunctionContaining(i.getAddress());asm.println(i.getAddress()+"  "+i);
    for(Reference ref:i.getReferencesFrom())refs.printf("%s\t%s\t%s\t%s%n",i.getAddress(),ref.getToAddress(),ref.getReferenceType(),f==null?"":f.getEntryPoint());
   }
   println("TOTAL FUNCTIONS "+count);
  }finally{dec.dispose();}
 }
}
