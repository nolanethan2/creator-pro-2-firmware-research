//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
public class FirmwareFlagReturns extends GhidraScript {
 public void run()throws Exception{
  StructureDataType st=new StructureDataType("ComparisonFlags_Recovered",4);
  String[] flags={"NG","ZR","CY","OV"};for(int i=0;i<4;i++)st.replaceAtOffset(i,new BooleanDataType(),1,flags[i],null);
  DataType ft=currentProgram.getDataTypeManager().addDataType(st,DataTypeConflictHandler.REPLACE_HANDLER);
  for(String x:flags)println(x+" register "+currentProgram.getRegister(x));
  VariableStorage rv=new VariableStorage(currentProgram,currentProgram.getRegister("OV"),currentProgram.getRegister("CY"),currentProgram.getRegister("ZR"),currentProgram.getRegister("NG"));
  for(long a:new long[]{0x0804b7d8L,0x0804b8a0L,0x0804b982L,0x0804b02cL,0x0804b2a0L,0x0804ae1cL}){
   Function f=getFunctionAt(toAddr(a));f.setInline(false);
   Variable[] args;
   if(a>=0x0804b700L){args=new Variable[]{new ParameterImpl("arg0",new FloatDataType(),currentProgram.getRegister("r0"),currentProgram),new ParameterImpl("arg1",new FloatDataType(),currentProgram.getRegister("r1"),currentProgram)};}
   else{args=new Variable[]{new ParameterImpl("arg0",new DoubleDataType(),new VariableStorage(currentProgram,currentProgram.getRegister("r1"),currentProgram.getRegister("r0")),currentProgram),new ParameterImpl("arg1",new DoubleDataType(),new VariableStorage(currentProgram,currentProgram.getRegister("r3"),currentProgram.getRegister("r2")),currentProgram)};}
   f.updateFunction(null,new ReturnParameterImpl(ft,rv,currentProgram),Function.FunctionUpdateType.CUSTOM_STORAGE,true,SourceType.USER_DEFINED,args);
  }
  println("Modeled six comparison helpers with explicit flag-register returns; no flash bytes changed");
 }
}
