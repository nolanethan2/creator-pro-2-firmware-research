//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
public class FixReviewedSharedTail extends GhidraScript {
 public void run()throws Exception{
  // Original 0x0803CA30 loads four signed rectangle fields then B.W 0x0803C9D8.
  // The user run recovered that shared implementation as its own function.
  var wrapper=getFunctionAt(toAddr(0x0803ca30L));wrapper.setBody(new AddressSet(toAddr(0x0803ca30L),toAddr(0x0803ca43L)));
  var core=currentProgram.getFunctionManager().createFunction("FUN_0803c9d8",toAddr(0x0803c9d8L),new AddressSet(toAddr(0x0803c9d8L),toAddr(0x0803ca2bL)),SourceType.ANALYSIS);
  core.setComment("Recovered by user deep analysis; reviewed shared-tail split. Wrapper 0x0803CA30 loads four signed fields then tail-branches here; implementation ends at POP PC 0x0803CA28. No bytes changed.");
  Path p=Path.of(getScriptArgs()[0]);String s=Files.readString(p).replace("0803c9d8\tFUN_0803c9d8\tdeferred: overlap or outside inspected code span","0803c9d8\tFUN_0803c9d8\timported after reviewed shared-tail split");Files.writeString(p,s);
  println("Reviewed shared-tail split imported final additional entry; count="+currentProgram.getFunctionManager().getFunctionCount());
 }
}
