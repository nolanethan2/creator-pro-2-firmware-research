//@category Firmware
import ghidra.app.script.GhidraScript;
import ghidra.app.util.exporter.GzfExporter;
import java.io.File;
public class FirmwareArchive extends GhidraScript {
 public void run() throws Exception {
  File file=new File(getScriptArgs()[0]);
  GzfExporter exporter=new GzfExporter();
  if(!exporter.export(file,currentProgram.getDomainFile(),monitor))throw new Exception("GZF export failed: "+exporter.getMessageLog());
  println("Saved analyzed program to "+file);
 }
}
