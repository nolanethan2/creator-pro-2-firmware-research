//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
public class FirmwareUITypes extends GhidraScript {
 public void run()throws Exception{
  StructureDataType msg=new StructureDataType("GUIMessage_Recovered",16);
  String[] fields={"message_id","window_handle","source_handle","data_value_or_pointer"};
  for(int i=0;i<4;i++)msg.replaceAtOffset(i*4,new UnsignedIntegerDataType(),4,fields[i],null);
  DataType mt=currentProgram.getDataTypeManager().addDataType(msg,DataTypeConflictHandler.REPLACE_HANDLER);
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){if(line.isBlank())continue;Function f=getFunctionAt(toAddr(Long.parseLong(line.trim(),16)));if(f==null)continue;f.updateFunction(null,new ReturnParameterImpl(new VoidDataType(),currentProgram),Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,new ParameterImpl("message",new Pointer32DataType(mt),currentProgram.getRegister("r0"),currentProgram));}
  StructureDataType wi=new StructureDataType("GUIWidgetCreateInfo_Recovered",28);
  wi.replaceAtOffset(0,new Pointer32DataType(),4,"constructor",null);wi.replaceAtOffset(4,new Pointer32DataType(new CharDataType()),4,"initial_name",null);
  String[] shorts={"widget_id","x","y","width","height","flags"};for(int i=0;i<6;i++)wi.replaceAtOffset(8+i*2,new ShortDataType(),2,shorts[i],null);
  wi.replaceAtOffset(20,new IntegerDataType(),4,"parameter",null);wi.replaceAtOffset(24,new IntegerDataType(),4,"extra_bytes",null);currentProgram.getDataTypeManager().addDataType(wi,DataTypeConflictHandler.REPLACE_HANDLER);
  setPlateComment(toAddr(0x08028688L),"Expert Mode manual XY calibration. Tested +/-0.05 staging at RAM 0x200004B0/4. OK adds to saved offsets 0x20001028/2C and calls EEPROM writers for offsets 0/4. Cancel clears staging without writes. GUI/EEPROM interfaces intercepted in tests; no hardware writes performed.");
  println("Installed recovered message/widget record types and explicit callback pointer parameters");
 }
}
