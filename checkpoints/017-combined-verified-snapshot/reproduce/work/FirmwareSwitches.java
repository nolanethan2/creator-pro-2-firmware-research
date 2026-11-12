//@category Firmware
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.JumpTable;
import ghidra.program.model.symbol.*;
import java.util.*;
public class FirmwareSwitches extends GhidraScript {
 public void run() throws Exception {
  long[][] tables={{0x08011f40L,13},{0x08012b24L,10},{0x08017ecaL,5},{0x08020c82L,7},{0x08037784L,10}};
  for(long[] t:tables){Address a=toAddr(t[0]);Instruction ins=getInstructionAt(a);Function f=getFunctionContaining(a);if(ins==null||f==null)throw new Exception("Missing switch instruction/function at "+a);ArrayList<Address> dest=new ArrayList<>();
   for(int i=0;i<t[1];i++){Address target=a.add(4+2*Byte.toUnsignedInt(getByte(a.add(4+i))));disassemble(target);if(!dest.contains(target))dest.add(target);ins.addOperandReference(0,target,RefType.COMPUTED_JUMP,SourceType.USER_DEFINED);createLabel(target,"case_"+a+"_"+i,false);}
   new JumpTable(a,dest,true,0).writeOverride(f);CreateFunctionCmd.fixupFunctionBody(currentProgram,f,monitor);setEOLComment(a,"Bounded TBB table: "+t[1]+" entries decoded directly from flash; branch targets supplied to decompiler. See bounded-switch-targets.csv for index mapping.");println("Recovered switch "+a+" in "+f.getName());
  }
 }
}
