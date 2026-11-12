//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.JumpTable;
import ghidra.program.model.symbol.*;
import java.util.*;
public class PrintStateSwitch extends GhidraScript {
 public void run()throws Exception{
  Address a=toAddr(0x080121b2L);Function f=getFunctionContaining(a);Instruction ins=getInstructionAt(a);ArrayList<Address> dest=new ArrayList<>();
  for(int i=0;i<7;i++){Address t=a.add(4+2*Byte.toUnsignedInt(getByte(a.add(4+i))));disassemble(t);if(!dest.contains(t))dest.add(t);ins.addOperandReference(0,t,RefType.COMPUTED_JUMP,SourceType.USER_DEFINED);createLabel(t,"PrintState_"+Integer.toHexString(0x81+i),false);println("State "+Integer.toHexString(0x81+i)+" -> "+t);}
  new JumpTable(a,dest,true,0).writeOverride(f);CreateFunctionCmd.fixupFunctionBody(currentProgram,f,monitor);setEOLComment(a,"TBB index is state-0x81, bounded to 7 entries by CMP/BCS. Targets decoded from original flash.");
 }
}
