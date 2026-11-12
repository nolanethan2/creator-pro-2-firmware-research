//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
public class FirmwareDoubleMath extends GhidraScript {
 VariableStorage pair(String high,String low)throws Exception{return new VariableStorage(currentProgram,currentProgram.getRegister(high),currentProgram.getRegister(low));}
 void sig(long a,String name,DataType ret,VariableStorage rs,DataType...argTypes)throws Exception{
  Function f=getFunctionAt(toAddr(a));if(f==null)throw new Exception("Missing function "+Long.toHexString(a));f.setName(name,SourceType.USER_DEFINED);Variable[]args=new Variable[argTypes.length];int reg=0;
  for(int i=0;i<args.length;i++){DataType t=argTypes[i];VariableStorage s=t.getLength()==8?pair("r"+(reg+1),"r"+reg):new VariableStorage(currentProgram,currentProgram.getRegister("r"+reg));args[i]=new ParameterImpl("arg"+i,t,s,currentProgram);reg+=t.getLength()/4;}
  f.updateFunction(null,new ReturnParameterImpl(ret,rs,currentProgram),Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,args);
 }
 public void run()throws Exception{
  DataType db=new DoubleDataType(),fl=new FloatDataType(),si=new IntegerDataType(),ui=new UnsignedIntegerDataType(),ul=new UnsignedLongLongDataType();VariableStorage d=pair("r1","r0"),one=new VariableStorage(currentProgram,currentProgram.getRegister("r0"));
  sig(0x0804a9f4L,"Math_F64_Add",db,d,db,db);sig(0x0804ab6cL,"Math_F64_Divide",db,d,db,db);sig(0x0804b0a4L,"Math_F64_Multiply",db,d,db,db);sig(0x0804b3c0L,"Math_F64_ReverseSubtract",db,d,db,db);sig(0x0804b570L,"Math_F64_Subtract",db,d,db,db);
  sig(0x0804b744L,"Math_F32_ToF64",db,d,fl);sig(0x0804a990L,"Math_F64_ToF32",fl,one,db);sig(0x0804ae94L,"Math_F64_ToI32",si,one,db);sig(0x0804b832L,"Math_U64_ToF32",fl,one,ul);
  sig(0x08049fccL,"Math_F64_SqrtWithStatus",db,d,db);sig(0x0804b3d8L,"Math_F64_SqrtCore",db,d,db);sig(0x0804b30cL,"Math_F64_RoundNearestEven",db,d,db);
  for(long a:new long[]{0x0804ae1cL,0x0804b02cL,0x0804b2a0L})getFunctionAt(toAddr(a)).setName(a==0x0804b2a0L?"Math_F64_CompareReverseFlags":"Math_F64_CompareFlags_"+Long.toHexString(a),SourceType.USER_DEFINED);
  int count=0;for(var ref:currentProgram.getReferenceManager().getReferencesTo(toAddr(0x0804b1f8L))){Instruction ins=getInstructionAt(ref.getFromAddress());if(ins!=null&&ins.getFlowType().isCall()){ins.setFlowOverride(FlowOverride.CALL_RETURN);setEOLComment(ins.getAddress(),"Runtime helper restores the saved outer caller PC; embedded LR descriptor is data, not call fallthrough. Modeled as call-return; exceptional returned values still need context.");count++;}}
  println("Typed 12 double/conversion helpers; modeled "+count+" exception-dispatch calls as call-return, preserving bytes");
 }
}
