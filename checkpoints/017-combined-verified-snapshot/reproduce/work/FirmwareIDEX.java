//@category Firmware
import ghidra.app.script.GhidraScript;
public class FirmwareIDEX extends GhidraScript {
 public void run()throws Exception{
  String[][] names={{"20000001","IDEX_Carriage0Enabled"},{"20000002","IDEX_Carriage1Enabled"},{"2000000e","Job_UsesDifferentFirstLastTools"},{"20000011","IDEX_RequestedJobMode"},{"20000012","IDEX_CompensationPassMode"},{"20000013","IDEX_ActiveSynchronizedMode"},{"2000001d","IDEX_ZCompensationRequired"},{"2000001e","IDEX_SetupScanPending"},{"2000002a","IDEX_SetupPhase"},{"20000217","Job_ExtentsRejected"},{"20000684","IDEX_Carriage0PositionSteps"},{"20000688","IDEX_Carriage1PositionSteps"},{"2000010c","CaseVariantProfileIndex"}};
  for(String[] v:names)createLabel(toAddr(Long.parseLong(v[0],16)),v[1],true);
  setPlateComment(toAddr(0x08011266L),"M118 job-header setup. First T uses strchr; last T uses strrchr. D1/D2 arm compensation workflow; omitted D does not clear old mode. Extents and XYZ values expected; missing fields leave incoming registers. Offline tests with number-conversion stub confirm logic only. Do not treat as a one-line complete printer initialization sequence.");
  setPlateComment(toAddr(0x080114b8L),"M111 Tn enables both carriage flags and sets active synchronized mode. Original-instruction step tests: T1 produces opposite logical X count changes (mirror); T2 same logical changes (duplicate). Requires appropriate job/calibration initialization; not hardware validated.");
  setPlateComment(toAddr(0x08013ab4L),"Profile options shown by UI are Silver (0x11/index0) and Black (0x12/index1). The two initialized profile-table rows are byte-identical in this dump. Changes profile byte and reloads fields/planner; not a discovered performance unlock.");
  println("Added IDEX globals and tested selector evidence; firmware bytes unchanged");
 }
}
