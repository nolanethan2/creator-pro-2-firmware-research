import os
from pathlib import Path
import csv,json
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
rows={r['address']:r for r in csv.DictReader((out/'function-labels.tsv').open(),delimiter='\t')}
funcs={f['address']:f for f in json.loads((out/'function-map.json').read_text())}
def add(a,name,confidence,evidence):
    assert a in funcs,a
    rows[a]=dict(address=a,name=name,confidence=confidence,evidence=evidence)
fat='''08032c90 mem_cpy
08032caa mem_set
08032cbe mem_cmp
08032ce4 chk_chr
08032cf8 sync_window
08032d4a move_window
08032d7c sync_fs
08032e44 clust2sect
08032e5e get_fat
08032f42 put_fat
08033078 remove_chain
080330e0 create_chain
080331aa clmt_clust
080331dc dir_sdi
08033278 dir_next
0803338c dir_alloc
080333e2 ld_clust
08033402 st_clust
08033412 cmp_lfn
0803349c pick_lfn
0803350c fit_lfn
08033586 gen_numname
08033644 sum_sfn
08033664 dir_find
08033742 dir_read
08033806 dir_register
08033942 dir_remove
080339a2 create_name
08033bcc get_fileinfo
08033d6c follow_path
08033e12 check_fs
08033e9c find_volume
0803422a validate
08034276 f_mount
0803429c f_open
08034400 f_read
080345da f_write
08034802 f_sync
080348b2 f_close
080348c8 f_lseek
08034ba4 f_opendir
08034c18 f_readdir
08034c74 f_stat
08034cb2 f_getfree
08034db6 f_truncate
08034e50 f_unlink
08034efe f_mkdir
08035066 f_chmod
080350be f_utime
08035118 f_rename
08035230 f_mkfs
08035830 f_gets
0803592e f_putc
080359a4 f_puts
08035c88 ff_convert
08035cfc ff_wtoupper'''
for line in fat.splitlines():
    a,n=line.split();add(a,'FatFs_'+n,'high','Semantic comparison with Elm-Chan FatFs R0.09b source: algorithm, object offsets, constants and call ordering agree; exact library revision/build not proven')
periph='''08030042 GPIO_ReadOutputDataBit
0803007a GPIO_PinAFConfig
08030136 RCC_GetFlagStatus
08030172 RCC_WaitForHSEStartUp
080301c4 RCC_LSEConfig
080303ac RCC_RTCCLKConfig
080303e2 RCC_RTCCLKCmd
080303fe RCC_AHB1PeriphClockCmd
08030420 RCC_AHB2PeriphClockCmd
08030442 RCC_AHB3PeriphClockCmd
08030464 RCC_APB1PeriphClockCmd
08030486 RCC_APB2PeriphClockCmd
080304a8 RCC_AHB1PeriphResetCmd
08030538 RCC_APB1PeriphResetCmd
0803055a RCC_APB2PeriphResetCmd
08030728 SDIO_GetResponse
080307ea SDIO_ITConfig
0803082a SDIO_GetFlagStatus
08030840 SDIO_ClearFlag
080308f0 SPI_Init
0803092c I2S_Init
08030ab6 SPI_Cmd
08030bb2 SPI_ReceiveData
08030bb8 SPI_SendData
08030bf4 SPI_I2S_DMACmd
08030c06 SPI_I2S_ITConfig
08030c26 SPI_I2S_GetFlagStatus
08030c5e SPI_I2S_GetITStatus
08030c92 SPI_I2S_ClearITPendingBit
08030ca8 TIM_DeInit
08030e02 TIM_TimeBaseInit
08030e7c TIM_PrescalerConfig
08030ed8 TIM_ARRPreloadConfig
08030f14 TIM_Cmd
08030f2c TIM_OC1Init
08030f9e TIM_OC2Init
08031038 TIM_OC3Init
08031104 TIM_OC4Init
08031188 TIM_SelectOCxM
08031272 TIM_OC3PreloadConfig
08031284 TIM_OC4PreloadConfig
08031332 TIM_ClearOC4Ref
0803142c TIM_IC4PrescalerConfig
08031446 TIM_TI4Configure
08031496 TIM_IC3PrescalerConfig
080314a8 TIM_TI3Configure
080314f0 TIM_IC2PrescalerConfig
0803150a TIM_TI2Configure
08031564 TIM_IC1PrescalerConfig
08031576 TIM_TI1Configure
080316f6 TIM_CtrlPWMOutputs
08031744 TIM_ITConfig
080317da TIM_SelectInputTrigger
08031804 TIM_TIxExternalClockConfig
08031842 TIM_ETRConfig
0803185e TIM_ETRClockMode1Config
08031894 TIM_ETRClockMode2Config
080318ea TIM_EncoderInterfaceConfig
08031962 PWR_BackupAccessCmd
08031988 PWR_BackupRegulatorCmd
080319a8 PWR_EnterSTOPMode
08031a38 RTC_WaitForSynchro
08031a94 RTC_EnterInitMode
08031ae8 RTC_DeInit
08031bb4 RTC_ExitInitMode
08031bc6 RTC_Init
08031c48 RTC_RefClockCmd
08031cca RTC_ByteToBcd2
08031ce6 RTC_Bcd2ToByte
08031cfc RTC_SetTime
08031dd0 RTC_GetTime
08031e38 RTC_SetDate
08031f04 RTC_GetDate
08031f4a RTC_SetAlarm
08032046 RTC_GetAlarm
080320b8 RTC_AlarmCmd
08032128 RTC_AlarmSubSecondConfig
080321c2 RTC_WakeUpCmd
080322b0 RTC_CoarseCalibConfig
080322e4 RTC_CoarseCalibCmd
08032390 RTC_SmoothCalibConfig
080323ea RTC_TimeStampCmd
08032420 RTC_GetTimeStamp
0803259a RTC_WriteBackupRegister
080325b4 RTC_ReadBackupRegister
0803261e RTC_SynchroShiftConfig
080326fe RTC_GetFlagStatus
08032720 RTC_ClearFlag
0803273c RTC_GetITStatus
080328aa EXTI_ClearITPendingBit
080328bc IWDG_WriteAccessCmd
080328c2 IWDG_SetPrescaler
080328c8 IWDG_SetReload
080328d8 IWDG_Enable'''
for line in periph.splitlines():
    a,n=line.split();add(a,n,'high' if funcs[a]['size']<80 else 'medium','STM32F407 register base, offsets and bit operations match named peripheral operation; semantic identification, not an exact source/build match')
custom=[
('08032944','Disk_Initialize','Two drives: drive 0 serial flash JEDEC ID 0xEF4018; drive 1 SD initialization'),
('08032990','Disk_StatusAlwaysReady','Returns zero; used by filesystem validation'),
('080329ba','Disk_ReadSectors','Drive selection, 512-byte sector addressing and SD/serial-flash read backends'),
('08032ab6','Disk_WriteSectors','Drive selection and 512-byte sector write backends'),
('08032ba6','Disk_Ioctl','Sector count, 512-byte sector size and erase block queries'),
('08032c2a','FatFs_GetFatTime','Packs RTC date/time into FAT timestamp bit layout'),
('08010e9c','GCode_M906_SetMotorCurrent','Parses R/L, calls 0x080171AC with selector 0/5'),
('08010ede','GCode_M6_StartWait','Sets command wait state 4 and microsecond timeout from P; default 900 seconds'),
('08010f16','GCode_M7_StartWait','Sets command wait state 5 and microsecond timeout from P; default 1800 seconds'),
('08010f4e','GCode_M132_ResetExtruderCoordinates','Zeros extrusion coordinates and resynchronizes motion positions'),
('08011112','GCode_M147_QueueTone','Parses F/L and enqueues frequency/duration pair'),
('08011154','GCode_M148_PlaySound','Parses S and selects stored sound pattern or repeated two-tone pattern'),
('08011198','GCode_M611_SetMachineSelector','Parses S and updates persisted selector at configuration base+0x0E'),
('080111f8','GCode_M610_SetMachineName','Passes command text+5 to persisted machine-name setter'),
('08011210','GCode_M0M1_StartPauseWait','Optional P seconds, wait state 6 and prompt flag'),
('08011266','GCode_M118_SetIDEXFlags','Parses coordinate/tool/duplication flags and build-volume checks; detailed mode meaning remains partial'),
('08013658','Config_WriteU16','Writes two little-endian bytes to selected settings backend'),
('08013696','Config_WriteU32','Writes four bytes to selected settings backend'),
('080136d4','Config_WriteFloat','Stores float using selected settings backend'),
('08013710','Config_WriteBlock','Source pointer, storage address, length; serial EEPROM or backup SRAM'),
('080137a0','Config_ReadU16WithDefault','0xFFFF sentinel selects caller default'),
('080137e6','Config_ReadU32WithDefault','0xFFFFFFFF sentinel selects caller default'),
('08013828','Config_ReadFloatWithDefault','Float read and sentinel/default selection; flags-returning comparison requires instruction review'),
('08013870','Config_ReadBlock','Destination pointer, storage address, length; serial EEPROM or backup SRAM'),
('08013940','Config_SetMachineSelector','Stores selector 1/2 at base+0x0E and changes machine dimensions'),
('080139ba','Config_ApplyOutputColorSelector_Candidate','Reads base+0x28 and applies PG5/PG6/PG7 patterns; physical load unverified'),
('08013a8a','Config_SetMachineName','Copies name to 0x200001CA, writes/reads 34 bytes at storage base+0x40'),
('08013ab4','Config_SelectProfile','0x11/0x12 select profile 0/1, persist at base+0x26 and reload limit tables'),
('0801b58e','EEPROM_ReadFloatBits','Reads four bytes through byte-addressed EEPROM backend and returns assembled word'),
('080171ac','MotorCurrent_SetChannel','Clamps current byte and sends serial control sequence; exact driver unverified'),
('0801838a','Sound_QueueTone','20-entry queue of 16-bit frequency/duration pairs'),
('08018402','Sound_PlayStoredPattern','Selects flash frequency/duration sequence terminated by zero duration'),
('08018488','Sound_QueueRepeatedTwoTone','Repeated 494/440 pairs with duration 300'),
('0804b1f8','Runtime_F64_ExceptionDispatch','Reads packed descriptor at aligned LR, dispatches exceptional float64 cases, restores caller stack; nonstandard return convention')]
for a,n,e in custom:add(a,n,'medium' if 'Candidate' in n or a in ['08011266','08013828','080171ac'] else 'high',e)
math={0x0804b79a:'Add',0x0804b7c4:'Divide',0x0804b8d0:'Multiply',0x0804b9bc:'Subtract',0x0804b9aa:'ReverseSubtract',0x0804b808:'ToI32',0x0804b816:'ToU32',0x0804b824:'I32_ToF32',0x0804b892:'U32_ToF32'}
for a,n in math.items():add(f'{a:08x}',('Math_'+n if '_ToF32' in n else 'Math_F32_'+n),'high','VFP instruction and register transfer inspected; arithmetic finite cases also checked by offline instruction emulation')
for a in ['0804b7d8','0804b8a0','0804b982']:add(a,'Math_F32_CompareFlags_'+a,'high','VCMP/VMRS returns comparison in processor flags; ordinary C ABI loses NZCV relationship; 0x0804B982 reverses operands')
with (out/'function-labels.tsv').open('w',newline='',encoding='utf-8') as f:
    w=csv.DictWriter(f,fieldnames=['address','name','confidence','evidence'],delimiter='\t');w.writeheader();w.writerows(rows[a]for a in sorted(rows))
print('Curated labels:',len(rows))
