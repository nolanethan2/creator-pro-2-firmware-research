//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.nio.file.*;

public class FirmwareRefine extends GhidraScript {
 public void run() throws Exception {
  byte[] data=Files.readAllBytes(Path.of(getScriptArgs()[0]));
  Memory mem=currentProgram.getMemory();MemoryBlock old=mem.getBlock(toAddr(0x20000000L));
  if(old.getEnd().getOffset()>=0x20000b68L)mem.split(old,toAddr(0x20000b68L));if(!old.isInitialized())mem.convertToInitialized(old,(byte)0);mem.setBytes(toAddr(0x20000000L),data);old.setName("APP_INITIALIZED_DATA");
  // These bytes are reconstructed from flash, not a live RAM capture.
  for(int i=0;i<data.length-3;i+=4){long value=Integer.toUnsignedLong(mem.getInt(toAddr(0x20000000L+i)));if(value>=0x08010000L&&value<0x080e4edcL){Address slot=toAddr(0x20000000L+i);clearListing(slot,slot.add(3));createData(slot,new Pointer32DataType());if((value&1)!=0&&value<0x0804c000L){Address a=toAddr(value&~1L);disassemble(a);if(getFunctionAt(a)==null)createFunction(a,null);}}}
  String[][] names={
   {"08010188","App_Runtime_Entry"},{"08010190","App_ScatterLoad"},{"080101c4","App_Decompress_InitializedData"},{"08010220","App_ZeroFill"},
   {"0802c310","App_Reset"},{"0802c42c","App_SystemInit"},{"0801033e","App_Main"},{"080102cc","App_InitializeSubsystems"},
   {"08017120","App_TIM13_IRQHandler"},{"0801713a","App_TIM14_IRQHandler"},{"0801619a","App_SysTick_Handler"},
   {"080161c6","App_USB_OTG_FS_IRQHandler"},{"080161d0","App_SDIO_IRQHandler"},{"080161d8","App_DMA2_Stream3_IRQHandler"},
   {"0801030e","App_SetVectorBase"},{"08010302","SCB_SetVTOR"},{"08000230","Boot_Reset"},{"0800256c","Boot_SystemInit"}
  };
  for(String[] n:names){Address a=toAddr(Long.parseLong(n[0],16));Function f=getFunctionAt(a);if(f==null){Function enclosing=getFunctionContaining(a);if(enclosing!=null){AddressSet body=new AddressSet(enclosing.getBody());body.deleteRange(a,body.getMaxAddress());if(!body.isEmpty())enclosing.setBody(body);}disassemble(a);f=createFunction(a,n[1]);}if(f!=null)f.setName(n[1],SourceType.USER_DEFINED);}
  Function main=getFunctionAt(toAddr(0x0801033eL));if(main!=null)main.setNoReturn(true);
  setPlateComment(toAddr(0x20000000L),"Reconstructed application startup data: decompress 0x080E4B78..0x080E4EDB -> 0x20000000..0x20000B67. Not captured runtime RAM; not valid for bootloader state.");
  setPlateComment(toAddr(0x080e4a24L),"Scatter load descriptors: compressed init data (0xB68 bytes); zero fill 0x20000B68 length 0x1CE20. Stack top 0x2001D988.");
  println("Applied reconstructed application data and startup labels");
 }
}
