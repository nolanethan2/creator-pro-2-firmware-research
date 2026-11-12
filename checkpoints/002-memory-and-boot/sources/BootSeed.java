//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.math.BigInteger;
import java.nio.file.*;
public class BootSeed extends GhidraScript {
 public void run() throws Exception {
  Memory mem=currentProgram.getMemory();MemoryBlock flash=mem.getBlock(toAddr(0x08000000L));flash.setName("BOOT_FLASH");flash.setWrite(false);
  MemoryBlock init=mem.createInitializedBlock("BOOT_INITIALIZED_DATA",toAddr(0x20000000L),0xb0,(byte)0,monitor,false);byte[] bytes=new byte[0xb0];mem.getBytes(toAddr(0x0800c640L),bytes);mem.setBytes(toAddr(0x20000000L),bytes);
  mem.createUninitializedBlock("SRAM",toAddr(0x200000b0L),0x1ff50,false);
  mem.createUninitializedBlock("APPLICATION_FLASH_NOT_CAPTURED_IN_THIS_PROGRAM",toAddr(0x08010000L),0xf0000,false).setWrite(false);
  mem.createUninitializedBlock("PERIPHERALS",toAddr(0x40000000L),0x61000,false).setVolatile(true);
  mem.createUninitializedBlock("CORE",toAddr(0xe000e000L),0x2000,false).setVolatile(true);
  currentProgram.getProgramContext().setValue(currentProgram.getProgramContext().getRegister("TMode"),toAddr(0x08000000L),toAddr(0x0800ffffL),BigInteger.ONE);
  for(int i=0;i<98;i++){Address a=toAddr(0x08000000L+i*4);long val=Integer.toUnsignedLong(getInt(a));createData(a,new DWordDataType());if(i>0&&val!=0){Address t=toAddr(val&~1L);disassemble(t);createFunction(t,null);addEntryPoint(t);}}
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){String[] v=line.split("\t",4);if(v.length<4||v[0].equals("address"))continue;long addr=Long.parseLong(v[0],16);if(addr>=0x08010000L)continue;Address a=toAddr(addr);disassemble(a);Function f=getFunctionAt(a);if(f==null)f=createFunction(a,v[1]);if(f!=null){f.setName(v[1],SourceType.USER_DEFINED);f.setComment(v[3]);}}
  setPlateComment(toAddr(0x20000000L),"Bootloader startup RAM copied from 0x0800C640, length 0xB0. This program models bootloader state; use application analysis for post-handoff state.");
 }
}
