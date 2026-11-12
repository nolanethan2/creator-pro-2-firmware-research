//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.*;
import ghidra.program.model.lang.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.data.*;
import java.math.BigInteger;

public class FirmwareSeed extends GhidraScript {
 public void run() throws Exception {
  Memory mem=currentProgram.getMemory();
  MemoryBlock flash=mem.getBlock(toAddr(0x08000000L)); flash.setName("FLASH"); flash.setWrite(false); flash.setExecute(true);
  mem.createUninitializedBlock("SRAM",toAddr(0x20000000L),0x20000,false);
  mem.createUninitializedBlock("CCM",toAddr(0x10000000L),0x10000,false);
  MemoryBlock per=mem.createUninitializedBlock("PERIPHERALS",toAddr(0x40000000L),0x61000,false);per.setVolatile(true);
  MemoryBlock usb=mem.createUninitializedBlock("USB_OTG_FS",toAddr(0x50000000L),0x40000,false);usb.setVolatile(true);
  MemoryBlock core=mem.createUninitializedBlock("CORTEX_SYSTEM",toAddr(0xe000e000L),0x2000,false);core.setVolatile(true);
  String[] exc={"Initial_MSP","Reset","NMI","HardFault","MemManage","BusFault","UsageFault","Reserved7","Reserved8","Reserved9","Reserved10","SVC","DebugMon","Reserved13","PendSV","SysTick"};
  Register tm=currentProgram.getProgramContext().getRegister("TMode");
  currentProgram.getProgramContext().setValue(tm,toAddr(0x08000000L),toAddr(0x080fffffL),BigInteger.ONE);
  for(long vb:new long[]{0x08000000L,0x08010000L}) {
   String prefix=vb==0x08000000L?"Boot_":"App_";
   for(int i=0;i<98;i++){
    Address slot=toAddr(vb+i*4);long val=Integer.toUnsignedLong(getInt(slot));createData(slot,new DWordDataType());
    if(i==0)continue;if(val==0)continue;
    Address target=toAddr(val&~1L);String name=i<16?exc[i]:"IRQ"+(i-16);
    if(getSymbolAt(target)==null)createLabel(target,prefix+name,true);
    addEntryPoint(target);
    DisassembleCommand cmd=new DisassembleCommand(target,null,true);cmd.setInitialContext(new RegisterValue(tm,BigInteger.ONE));cmd.applyTo(currentProgram,monitor);
    if(getFunctionAt(target)==null)createFunction(target,null);
   }
  }
  createLabel(toAddr(0xe000ed08L),"SCB_VTOR",true);
  long[] regs={0x40000000L,0x40000400L,0x40000800L,0x40000c00L,0x40001000L,0x40001400L,0x40001c00L,0x40002000L,0x40010000L,0x40010400L,0x40011000L,0x40011400L,0x40011800L,0x40012000L,0x40012400L,0x40012800L,0x40012c00L,0x40020000L,0x40020400L,0x40020800L,0x40020c00L,0x40021000L,0x40021400L,0x40021800L,0x40023800L,0x40023c00L,0x40026000L,0x40026400L};
  String[] rn={"TIM2","TIM3","TIM4","TIM5","TIM6","TIM7","TIM13","TIM14","TIM1","TIM8","TIM9","TIM10","TIM11","ADC1","ADC2","ADC3","SDIO","GPIOA","GPIOB","GPIOC","GPIOD","GPIOE","GPIOF","GPIOG","RCC","FLASH_CTRL","DMA1","DMA2"};
  for(int i=0;i<regs.length;i++)createLabel(toAddr(regs[i]),rn[i],true);
  println("Seeded vectors, RAM and hardware map");
 }
}
