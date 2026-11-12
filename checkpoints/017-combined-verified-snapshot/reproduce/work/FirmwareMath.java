//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
public class FirmwareMath extends GhidraScript {
 void sig(long addr,String name,DataType ret,DataType...types)throws Exception{
  Function f=getFunctionAt(toAddr(addr));if(f==null){disassemble(toAddr(addr));f=createFunction(toAddr(addr),name);}f.setName(name,SourceType.USER_DEFINED);
  Variable[] args=new Variable[types.length];for(int i=0;i<args.length;i++)args[i]=new ParameterImpl("arg"+i,types[i],currentProgram.getRegister("r"+i),currentProgram);
  Variable rv=ret instanceof VoidDataType?new ReturnParameterImpl(ret,currentProgram):new ReturnParameterImpl(ret,currentProgram.getRegister("r0"),currentProgram);
  f.updateFunction(null,rv,Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,args);
 }
 public void run()throws Exception{
  DataType fl=new FloatDataType(),si=new IntegerDataType(),ui=new UnsignedIntegerDataType(),vd=new VoidDataType();
  long[] two={0x0804b79aL,0x0804b7c4L,0x0804b8d0L,0x0804b9bcL,0x0804b9aaL};String[] nm={"Math_F32_Add","Math_F32_Divide","Math_F32_Multiply","Math_F32_Subtract","Math_F32_ReverseSubtract"};
  for(int i=0;i<two.length;i++)sig(two[i],nm[i],fl,fl,fl);
  sig(0x0804b808L,"Math_F32_ToI32",si,fl);sig(0x0804b816L,"Math_F32_ToU32",ui,fl);sig(0x0804b824L,"Math_I32_ToF32",fl,si);sig(0x0804b892L,"Math_U32_ToF32",fl,ui);
  for(long a:new long[]{0x0804b7d8L,0x0804b8a0L,0x0804b982L}){sig(a,"Math_F32_CompareFlags_"+Long.toHexString(a),vd,fl,fl);getFunctionAt(toAddr(a)).setInline(false);setPlateComment(toAddr(a),"Flags-returning hardware VFP comparison. 0x0804B982 compares operands in reverse order. Caller NZCV propagation is not represented by the ordinary C signature. Inlining was tested and reverted because exceptional NaN fallback destabilizes decompilation.");}
  StructureDataType pid=new StructureDataType("PIDState_Recovered",0x34);
  for(int i=0;i<3;i++)pid.replaceAtOffset(i*4,fl,4,new String[]{"Kp","Ki","Kd"}[i],null);
  pid.replaceAtOffset(0xc,new ArrayDataType(fl,4,4),16,"delta_history",null);pid.replaceAtOffset(0x1c,fl,4,"delta_sum",null);pid.replaceAtOffset(0x20,new ByteDataType(),1,"history_index",null);pid.replaceAtOffset(0x24,fl,4,"last_error",null);pid.replaceAtOffset(0x28,fl,4,"integral",null);pid.replaceAtOffset(0x2c,si,4,"target",null);pid.replaceAtOffset(0x30,si,4,"output",null);
  DataType pt=currentProgram.getDataTypeManager().addDataType(pid,DataTypeConflictHandler.REPLACE_HANDLER);DataType pp=new Pointer32DataType(pt);
  sig(0x08015c10L,"PID_Update",si,pp,fl);sig(0x08015bdcL,"PID_Reset",vd,pp);sig(0x08015cdeL,"PID_SetTarget",vd,pp,si);
  DataType ht=currentProgram.getDataTypeManager().getDataType("/HeaterState_Recovered");
  if(ht!=null){DataType hp=new Pointer32DataType(ht);sig(0x08017e7cL,"Heater_UpdateControlAndChecks",vd,hp);sig(0x08017e52L,"Heater_LatchFaultAndDisable",vd,hp);sig(0x08017c98L,"Heater_SetTarget",vd,hp,si);sig(0x08017bc8L,"Heater_InitializeController",vd,hp);}
  sig(0x080105faL,"Command_ParseNumericValue",fl);
  println("Typed float wrappers, PID and heater parameters; comparison wrappers remain non-inline");
 }
}
