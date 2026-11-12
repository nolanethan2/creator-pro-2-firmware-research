//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.util.exporter.GzfExporter;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.nio.file.*;
import java.io.File;

public class FirmwareAnnotate extends GhidraScript {
 public void run() throws Exception {
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){String[] v=line.split("\t",4);if(v.length<4||v[0].equals("address"))continue;Address a=toAddr(Long.parseLong(v[0],16));Function f=getFunctionAt(a);if(f==null){disassemble(a);f=createFunction(a,v[1]);}if(f!=null){f.setName(v[1],SourceType.USER_DEFINED);f.setComment("Static analysis confidence: "+v[2]+". Evidence: "+v[3]);}else createLabel(a,v[1],true);}
  StructureDataType heater=new StructureDataType("HeaterState_Recovered",0xac);
  heater.replaceAtOffset(0x24,new ShortDataType(),2,"measured_temperature","Inferred temperature units from table and command use");
  heater.replaceAtOffset(0x26,new ShortDataType(),2,"temperature_at_target_change",null);
  heater.replaceAtOffset(0x30,new FloatDataType(),4,"Kp",null);heater.replaceAtOffset(0x34,new FloatDataType(),4,"Ki",null);heater.replaceAtOffset(0x38,new FloatDataType(),4,"Kd",null);
  heater.replaceAtOffset(0x5c,new IntegerDataType(),4,"target_temperature",null);
  int[] offs={0x64,0x65,0x66,0x67,0x68,0x8c,0x8e,0x8f,0x90};String[] fields={"full_power_mode","fault_disabled","sensor_fault_counter","thermal_fault_counter","fault_code","rise_confirmed","thermal_checks_bypass","control_bypass","heater_id"};
  for(int i=0;i<offs.length;i++)heater.replaceAtOffset(offs[i],new ByteDataType(),1,fields[i],"Recovered field role; not a source-code symbol");
  DataType ht=currentProgram.getDataTypeManager().addDataType(heater,DataTypeConflictHandler.REPLACE_HANDLER);
  for(long addr:new long[]{0x20001e40L,0x20001eecL,0x20001f98L}){clearListing(toAddr(addr),toAddr(addr+0xab));createData(toAddr(addr),ht);}
  createLabel(toAddr(0x20001e40L),"Heater_Extruder0",true);createLabel(toAddr(0x20001eecL),"Heater_Extruder1",true);createLabel(toAddr(0x20001f98L),"Heater_Bed",true);
  for(long addr:new long[]{0x08017bc8L,0x08017c98L,0x08017e52L,0x08017e7cL,0x0801819aL}){Function f=getFunctionAt(toAddr(addr));if(f!=null&&f.getParameterCount()>0)f.getParameter(0).setDataType(new Pointer32DataType(ht),SourceType.USER_DEFINED);}
  String[][] labels={{"20000250","Time_Microseconds"},{"2000003c","CommandQueue_ReadIndex"},{"2000003e","CommandQueue_WriteIndex"},{"20000040","CommandQueue_Count"},{"20000b9c","CommandQueue_Lines"},{"200005bc","Stepper_PinTable"},{"2000a29c","Stepper_AxisStates"},{"20009a9c","Planner_BlockRing"},{"200005b1","Planner_Head"},{"200005b2","Planner_Tail"},{"200004fc","USB_DeviceDescriptor"},{"20000384","UI_LanguageTableBase"},{"20000374","UI_CurrentPageCallback"},{"20000110","MachineConfig"},{"20000248","HeaterFaultWord"}};
  for(String[] pair:labels)createLabel(toAddr(Long.parseLong(pair[0],16)),pair[1],true);
  println("Applied semantic labels and recovered heater structure");
 }
}
