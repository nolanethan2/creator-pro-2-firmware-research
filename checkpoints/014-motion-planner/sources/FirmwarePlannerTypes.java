//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
public class FirmwarePlannerTypes extends GhidraScript {
 void signature(long a,DataType ret,DataType...types)throws Exception{
  Function f=getFunctionAt(toAddr(a));Variable[]args=new Variable[types.length];for(int i=0;i<types.length;i++)args[i]=new ParameterImpl("arg"+i,types[i],currentProgram.getRegister("r"+i),currentProgram);
  f.updateFunction(null,ret instanceof VoidDataType?new ReturnParameterImpl(ret,currentProgram):new ReturnParameterImpl(ret,currentProgram.getRegister("r0"),currentProgram),Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,args);
 }
 public void run()throws Exception{
  DataType ui=new UnsignedIntegerDataType(),si=new IntegerDataType(),fl=new FloatDataType(),by=new ByteDataType(),sh=new ShortDataType(),vd=new VoidDataType();
  StructureDataType b=new StructureDataType("PlannerBlock_Recovered",128);
  b.replaceAtOffset(0,new ArrayDataType(ui,5,4),20,"axis_steps",null);b.replaceAtOffset(0x14,ui,4,"step_event_count",null);b.replaceAtOffset(0x18,new ArrayDataType(si,5,4),20,"start_steps",null);
  String[] n={"accelerate_until","decelerate_after","acceleration_rate_fixed"};for(int i=0;i<3;i++)b.replaceAtOffset(0x2c+i*4,si,4,n[i],null);
  String[] bytes={"direction_bits","extruder_index","request_flags_unresolved","advance_enabled"};for(int i=0;i<4;i++)b.replaceAtOffset(0x38+i,by,1,bytes[i],null);
  b.replaceAtOffset(0x3c,sh,2,"advance_initial",null);b.replaceAtOffset(0x3e,sh,2,"advance_final",null);b.replaceAtOffset(0x40,si,4,"advance_rate_adjustment",null);b.replaceAtOffset(0x44,sh,2,"advance_state_0",null);b.replaceAtOffset(0x46,sh,2,"advance_state_1",null);
  String[] floats={"nominal_speed","entry_speed","max_entry_speed","move_length","acceleration"};for(int i=0;i<5;i++)b.replaceAtOffset(0x48+i*4,fl,4,floats[i],null);
  b.replaceAtOffset(0x5c,by,1,"recalculate",null);b.replaceAtOffset(0x5d,by,1,"nominal_length",null);
  String[] ints={"nominal_rate","nominal_rate_squared","initial_rate","final_rate","acceleration_steps"};for(int i=0;i<5;i++)b.replaceAtOffset(0x60+i*4,ui,4,ints[i],null);
  String[] tail={"accelerated","lookahead_ready","busy","dominant_axis","endstop_flags_candidate"};for(int i=0;i<5;i++)b.replaceAtOffset(0x74+i,by,1,tail[i],null);b.replaceAtOffset(0x7c,ui,4,"command_marker",null);
  DataType bt=currentProgram.getDataTypeManager().addDataType(b,DataTypeConflictHandler.REPLACE_HANDLER),bp=new Pointer32DataType(bt);
  signature(0x08029d88L,vd,bp,fl,fl);signature(0x0802a066L,vd,bp,bp);signature(0x0802a132L,vd,bp,bp);
  signature(0x08049a34L,fl,fl,fl,fl);signature(0x08049b90L,fl,fl,fl,fl);signature(0x08049a24L,si,si,si,si);
  signature(0x0802b06aL,ui,ui);signature(0x08049d00L,ui);signature(0x0802a33cL,vd,fl,fl,ui);
  clearListing(toAddr(0x20009a9cL),toAddr(0x2000a29bL));createData(toAddr(0x20009a9cL),new ArrayDataType(bt,16,128));createLabel(toAddr(0x20009a9cL),"Planner_Blocks",true);
  for(long a:new long[]{0x0804b7d8L,0x0804b8a0L,0x0804b982L})setPlateComment(toAddr(a),"Explicit NG/ZR/CY/OV return signature exposes caller flag use. WARNING: Ghidra's leaf C rendering still drops finite comparison fields; use original VMOV/VCMP/VMRS instructions and comparison-flags-verification.json, not this leaf C body. No firmware bytes were changed.");
  println("Installed 128-byte motion block type, 16-entry ring and typed kinematic helpers");
 }
}
