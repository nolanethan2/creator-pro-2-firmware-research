//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import java.nio.file.*;
public class VerifyPlanner extends GhidraScript {
 public void run()throws Exception{
  var dt=currentProgram.getDataTypeManager().getDataType("/PlannerBlock_Recovered");if(dt==null||dt.getLength()!=128)throw new Exception("Block type missing");
  var d=getDataAt(toAddr(0x20009a9cL));if(d==null||d.getLength()!=2048)throw new Exception("Ring data missing");
  int flags=0;for(long a:new long[]{0x0804b7d8L,0x0804b8a0L,0x0804b982L,0x0804b02cL,0x0804ae1cL,0x0804b2a0L}){var f=getFunctionAt(toAddr(a));if(!f.getReturnType().getName().equals("ComparisonFlags_Recovered")||f.getReturn().getVariableStorage().size()!=4)throw new Exception("Flag signature missing");flags++;}
  int tails=0;for(var ref:currentProgram.getReferenceManager().getReferencesTo(toAddr(0x0804b1f8L))){var i=getInstructionAt(ref.getFromAddress());if(i!=null&&i.getFlowOverride()==FlowOverride.CALL_RETURN)tails++;}if(tails!=12)throw new Exception("Expected 12 exception call-return overrides");
  if(getFunctionAt(toAddr(0x0803c9d8L))==null||getFunctionAt(toAddr(0x0803ca30L)).getBody().contains(toAddr(0x0803c9d8L)))throw new Exception("Shared tail split missing");
  String s="{\"planner_block_bytes\":128,\"planner_ring_elements\":16,\"comparison_flag_signatures\":"+flags+",\"exception_call_return_overrides\":"+tails+",\"reviewed_shared_tail_split\":true,\"checks_passed\":true}";Files.writeString(Path.of(getScriptArgs()[0]),s);println(s);
 }
}
