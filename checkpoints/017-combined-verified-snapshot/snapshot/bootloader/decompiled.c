
/* FUNCTION 08000188 Boot_Runtime_Entry SIZE 8 */

/* Reset branches here after SystemInit */

void Boot_Runtime_Entry(void)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  undefined4 *puVar3;
  
  FUN_08000190();
  FUN_08000212();
  iVar1 = DAT_080001bc;
  puVar3 = (undefined4 *)((int)&DAT_080001bc + DAT_080001bc);
  iVar2 = DAT_080001bc + 0x80001bb;
  if (puVar3 == (undefined4 *)((int)&DAT_080001bc + DAT_080001c0)) {
    FUN_08000212();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0x80001c8);
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)(iVar2 - (int)UNRECOVERED_JUMPTABLE);
  }
                    /* WARNING: Could not recover jumptable at 0x080001ba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)
            (*puVar3,*(undefined4 *)((int)&DAT_080001c0 + iVar1),
             *(undefined4 *)(&LAB_080001c4 + iVar1));
  return;
}



/* FUNCTION 08000190 FUN_08000190 SIZE 44 */

void FUN_08000190(void)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = DAT_080001bc;
  puVar3 = (undefined4 *)((int)&DAT_080001bc + DAT_080001bc);
  iVar2 = DAT_080001bc + 0x80001bb;
  if (puVar3 == (undefined4 *)((int)&DAT_080001bc + DAT_080001c0)) {
    FUN_08000212();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(iVar1 + 0x80001c8);
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)(iVar2 - (int)UNRECOVERED_JUMPTABLE);
  }
                    /* WARNING: Could not recover jumptable at 0x080001ba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)
            (*puVar3,*(undefined4 *)((int)&DAT_080001c0 + iVar1),
             *(undefined4 *)(&LAB_080001c4 + iVar1));
  return;
}



/* FUNCTION 080001fc FUN_080001fc SIZE 38 */

undefined4 FUN_080001fc(int param_1,int param_2,undefined4 *param_3)

{
  if (param_2 != 0x73) {
    return 0;
  }
  if (*(int *)(param_1 + 0x14) == 0) {
    FUN_0800b8d4(param_1,*param_3,0xffffffff);
  }
  return 1;
}



/* FUNCTION 08000206 FUN_08000206 SIZE 8 */

undefined8 FUN_08000206(undefined4 param_1,undefined4 param_2)

{
  FUN_0800bb54();
  return CONCAT44(param_2,param_1);
}



/* FUNCTION 0800020e FUN_0800020e SIZE 4 */

void FUN_0800020e(void)

{
  return;
}



/* FUNCTION 08000212 FUN_08000212 SIZE 18 */

void FUN_08000212(void)

{
  undefined4 uVar1;
  undefined4 extraout_r2;
  undefined8 uVar2;
  
  uVar1 = FUN_0800bad8();
  FUN_08000206(uVar1,extraout_r2);
  Boot_Main();
  uVar2 = FUN_0800bb22();
  FUN_0800020e();
  FUN_0800bb30((int)uVar2,(int)((ulonglong)uVar2 >> 0x20));
  (*DAT_08000258)();
                    /* WARNING: Could not recover jumptable at 0x08000236. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_0800025c)();
  return;
}



/* FUNCTION 08000224 FUN_08000224 SIZE 12 */

void FUN_08000224(undefined4 param_1,undefined4 param_2)

{
  FUN_0800020e();
  FUN_0800bb30(param_1,param_2);
  (*DAT_08000258)();
                    /* WARNING: Could not recover jumptable at 0x08000236. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_0800025c)();
  return;
}



/* FUNCTION 08000230 Boot_Reset SIZE 8 */

/* Boot vector slot 1 */

void Boot_Reset(void)

{
  (*DAT_08000258)();
                    /* WARNING: Could not recover jumptable at 0x08000236. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_0800025c)();
  return;
}



/* FUNCTION 08000248 FUN_08000248 SIZE 2 */

void FUN_08000248(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 0800024a FUN_0800024a SIZE 2 */

void FUN_0800024a(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 0800024c FUN_0800024c SIZE 10 */

undefined8 FUN_0800024c(void)

{
  return CONCAT44(DAT_08000264,DAT_08000260);
}



/* FUNCTION 08000270 FUN_08000270 SIZE 10 */

void FUN_08000270(uint param_1)

{
  *DAT_08000340 = DAT_0800033c | param_1;
  return;
}



/* FUNCTION 0800027a FUN_0800027a SIZE 106 */

void FUN_0800027a(byte *param_1)

{
  uint uVar1;
  
  if (param_1[3] == 0) {
    *(int *)(DAT_08000348 + ((int)(uint)*param_1 >> 5) * 4) = 1 << (*param_1 & 0x1f);
  }
  else {
    uVar1 = (0x700 - (*DAT_08000340 & 0x700) & 0xffff) >> 8;
    *(char *)(DAT_08000344 + (uint)*param_1) =
         (char)((((uint)param_1[1] << (4 - uVar1 & 0xff) & 0xff | (uint)param_1[2] & 0xf >> uVar1) &
                0xf) << 4);
    *(int *)(&DAT_e000e100 + ((int)(uint)*param_1 >> 5) * 4) = 1 << (*param_1 & 0x1f);
  }
  return;
}



/* FUNCTION 08000350 FUN_08000350 SIZE 324 */

void FUN_08000350(uint *param_1)

{
  *param_1 = *param_1 & 0xfffffffe;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0x21;
  if (param_1 == DAT_080006d8) {
    DAT_080006d8[-2] = 0x3d;
  }
  else if (param_1 == DAT_080006d8 + 6) {
    DAT_080006d8[-2] = 0xf40;
  }
  else if (param_1 == DAT_080006d8 + 0xc) {
    DAT_080006d8[-2] = 0x3d0000;
  }
  else if (param_1 == DAT_080006d8 + 0x12) {
    DAT_080006d8[-2] = 0xf400000;
  }
  else if (param_1 == DAT_080006d8 + 0x18) {
    DAT_080006d8[-1] = DAT_080006dc;
  }
  else if (param_1 == DAT_080006d8 + 0x1e) {
    DAT_080006d8[-1] = DAT_080006e0;
  }
  else if (param_1 == DAT_080006d8 + 0x24) {
    DAT_080006d8[-1] = DAT_080006e4;
  }
  else if (param_1 == DAT_080006d8 + 0x2a) {
    DAT_080006d8[-1] = 0x2f400000;
  }
  else if (param_1 == DAT_080006e8) {
    DAT_080006e8[-2] = 0x3d;
  }
  else if (param_1 == DAT_080006e8 + 6) {
    DAT_080006e8[-2] = 0xf40;
  }
  else if (param_1 == DAT_080006e8 + 0xc) {
    DAT_080006e8[-2] = 0x3d0000;
  }
  else if (param_1 == DAT_080006e8 + 0x12) {
    DAT_080006e8[-2] = 0xf400000;
  }
  else if (param_1 == DAT_080006e8 + 0x18) {
    DAT_080006e8[-1] = DAT_080006dc;
  }
  else if (param_1 == DAT_080006e8 + 0x1e) {
    DAT_080006e8[-1] = DAT_080006e0;
  }
  else if (param_1 == DAT_080006e8 + 0x24) {
    DAT_080006e8[-1] = DAT_080006e4;
  }
  else if (param_1 == DAT_080006e8 + 0x2a) {
    DAT_080006e8[-1] = 0x2f400000;
  }
  return;
}



/* FUNCTION 08000494 FUN_08000494 SIZE 82 */

void FUN_08000494(uint *param_1,uint *param_2)

{
  *param_1 = *param_1 & DAT_080006ec |
             *param_2 | param_2[3] | param_2[5] | param_2[6] | param_2[7] | param_2[8] | param_2[9]
             | param_2[10] | param_2[0xd] | param_2[0xe];
  param_1[5] = param_1[5] & 0xfffffff8 | param_2[0xb] | param_2[0xc];
  param_1[1] = param_2[4];
  param_1[2] = param_2[1];
  param_1[3] = param_2[2];
  return;
}



/* FUNCTION 08000508 FUN_08000508 SIZE 22 */

void FUN_08000508(uint *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xfffffffe;
  }
  else {
    *param_1 = *param_1 | 1;
  }
  return;
}



/* FUNCTION 08000534 FUN_08000534 SIZE 22 */

void FUN_08000534(uint *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xffffffdf;
  }
  else {
    *param_1 = *param_1 | 0x20;
  }
  return;
}



/* FUNCTION 080005c2 FUN_080005c2 SIZE 56 */

bool FUN_080005c2(uint param_1,uint param_2)

{
  uint uVar1;
  
  if (param_1 < DAT_080006e8) {
    uVar1 = DAT_080006d8;
  }
  else {
    uVar1 = DAT_080006e8;
  }
  if ((param_2 & 0x20000000) == 0) {
    uVar1 = *(uint *)(uVar1 - 0x10);
  }
  else {
    uVar1 = *(uint *)(uVar1 - 0xc);
  }
  return (uVar1 & DAT_080006f0 & param_2) != 0;
}



/* FUNCTION 080005fa FUN_080005fa SIZE 40 */

void FUN_080005fa(uint param_1,uint param_2)

{
  uint uVar1;
  
  if (param_1 < DAT_080006e8) {
    uVar1 = DAT_080006d8;
  }
  else {
    uVar1 = DAT_080006e8;
  }
  if ((param_2 & 0x20000000) == 0) {
    *(uint *)(uVar1 - 8) = DAT_080006f0 & param_2;
  }
  else {
    *(uint *)(uVar1 - 4) = DAT_080006f0 & param_2;
  }
  return;
}



/* FUNCTION 08000622 FUN_08000622 SIZE 58 */

void FUN_08000622(uint *param_1,uint param_2,int param_3)

{
  if ((param_2 & 0x80) != 0) {
    if (param_3 == 0) {
      param_1[5] = param_1[5] & 0xffffff7f;
    }
    else {
      param_1[5] = param_1[5] | 0x80;
    }
  }
  if (param_2 != 0x80) {
    if (param_3 == 0) {
      *param_1 = *param_1 & ~(param_2 & 0x1e);
    }
    else {
      *param_1 = *param_1 | param_2 & 0x1e;
    }
  }
  return;
}



/* FUNCTION 0800065c FUN_0800065c SIZE 84 */

undefined4 FUN_0800065c(uint *param_1,uint param_2)

{
  undefined4 uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 < DAT_080006e8) {
    puVar2 = DAT_080006d8;
  }
  else {
    puVar2 = DAT_080006e8;
  }
  if ((DAT_080006f4 & param_2) == 0) {
    uVar4 = param_1[5] & 0x80;
  }
  else {
    uVar4 = *param_1 & param_2 >> 0xb & 0x1e;
  }
  if ((param_2 & 0x20000000) == 0) {
    uVar3 = puVar2[-4];
  }
  else {
    uVar3 = puVar2[-3];
  }
  if (((uVar3 & DAT_080006f0 & param_2) == 0) || (uVar4 == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* FUNCTION 08000774 FUN_08000774 SIZE 26 */

void FUN_08000774(void)

{
  undefined4 *puVar1;
  
  if ((*(uint *)(DAT_08000ad8 + 0x10) & 0x80000000) != 0) {
    puVar1 = (undefined4 *)(DAT_08000ad8 + 4);
    *puVar1 = DAT_08000adc;
    *puVar1 = DAT_08000ae0;
  }
  return;
}



/* FUNCTION 0800078e FUN_0800078e SIZE 18 */

void FUN_0800078e(void)

{
  *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) | 0x80000000;
  return;
}



/* FUNCTION 080007a0 FUN_080007a0 SIZE 74 */

undefined4 FUN_080007a0(void)

{
  undefined4 uVar1;
  
  if ((*(uint *)(DAT_08000ad8 + 0xc) & 0x10000) == 0x10000) {
    uVar1 = 1;
  }
  else if ((*(uint *)(DAT_08000ad8 + 0xc) & 0x10) == 0) {
    if ((*(uint *)(DAT_08000ad8 + 0xc) & 0xe0) == 0) {
      if ((*(uint *)(DAT_08000ad8 + 0xc) & 2) == 0) {
        uVar1 = 8;
      }
      else {
        uVar1 = 7;
      }
    }
    else {
      uVar1 = 6;
    }
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



/* FUNCTION 080007ea FUN_080007ea SIZE 34 */

char FUN_080007ea(void)

{
  char cVar1;
  
  cVar1 = FUN_080007a0();
  while (cVar1 == '\x01') {
    cVar1 = FUN_080007a0();
  }
  return cVar1;
}



/* FUNCTION 0800080c FUN_0800080c SIZE 140 */

int FUN_0800080c(uint param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (param_2 != 0) {
    if (param_2 == 1) {
      uVar4 = 0x100;
    }
    else if (param_2 == 2) {
      uVar4 = 0x200;
    }
    else {
      uVar4 = 0x300;
    }
  }
  iVar1 = FUN_080007ea();
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2 | uVar4;
    *puVar2 = *puVar2 & 0xffffff07;
    puVar3 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar3 = *puVar2 | param_1 | 2;
    *puVar3 = *puVar3 | 0x10000;
    iVar1 = FUN_080007ea();
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffd;
    *puVar2 = *puVar2 & 0xffffff07;
  }
  return iVar1;
}



/* FUNCTION 08000898 FUN_08000898 SIZE 112 */

int FUN_08000898(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint *puVar2;
  int extraout_r2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (extraout_r2 != 0) {
    if (extraout_r2 == 1) {
      uVar3 = 0x100;
    }
    else if (extraout_r2 == 2) {
      uVar3 = 0x200;
    }
    else {
      uVar3 = 0x300;
    }
  }
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2 | uVar3;
    *puVar2 = *puVar2 | 4;
    *puVar2 = *puVar2 | 0x10000;
    iVar1 = FUN_080007ea();
    *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffb;
  }
  return iVar1;
}



/* FUNCTION 08000908 FUN_08000908 SIZE 86 */

int FUN_08000908(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = FUN_080007ea(param_1,param_2,8);
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2 | 0x300;
    *puVar2 = *puVar2 | 1;
    *param_1 = param_3;
    param_1[1] = param_4;
    iVar1 = FUN_080007ea();
    *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffe;
  }
  return iVar1;
}



/* FUNCTION 0800095e FUN_0800095e SIZE 82 */

int FUN_0800095e(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint *puVar2;
  undefined4 *extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2 | 0x200;
    *puVar2 = *puVar2 | 1;
    *extraout_r2 = param_2;
    iVar1 = FUN_080007ea();
    *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffe;
  }
  return iVar1;
}



/* FUNCTION 080009b0 FUN_080009b0 SIZE 82 */

int FUN_080009b0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint *puVar2;
  undefined2 *extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2 | 0x100;
    *puVar2 = *puVar2 | 1;
    *extraout_r2 = (short)param_2;
    iVar1 = FUN_080007ea();
    *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffe;
  }
  return iVar1;
}



/* FUNCTION 08000a02 FUN_08000a02 SIZE 78 */

int FUN_08000a02(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint *puVar2;
  undefined1 *extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    puVar2 = (uint *)(DAT_08000ad8 + 0x10);
    *puVar2 = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffcff;
    *puVar2 = *puVar2;
    *puVar2 = *puVar2 | 1;
    *extraout_r2 = (char)param_2;
    iVar1 = FUN_080007ea();
    *(uint *)(DAT_08000ad8 + 0x10) = *(uint *)(DAT_08000ad8 + 0x10) & 0xfffffffe;
  }
  return iVar1;
}



/* FUNCTION 08000a50 FUN_08000a50 SIZE 26 */

void FUN_08000a50(void)

{
  undefined4 *puVar1;
  
  if ((*(uint *)(DAT_08000ad8 + 0x14) & 1) != 0) {
    puVar1 = (undefined4 *)(DAT_08000ad8 + 8);
    *puVar1 = DAT_08000ae4;
    *puVar1 = DAT_08000ae8;
  }
  return;
}



/* FUNCTION 08000a7c FUN_08000a7c SIZE 54 */

void FUN_08000a7c(undefined4 param_1,int param_2)

{
  int iVar1;
  ushort extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    if (param_2 == 0) {
      *(ushort *)(DAT_08000ad8 + 0x16) = *(ushort *)(DAT_08000ad8 + 0x16) | extraout_r2;
    }
    else {
      *(ushort *)(DAT_08000ad8 + 0x16) = *(ushort *)(DAT_08000ad8 + 0x16) & ~extraout_r2;
    }
  }
  return;
}



/* FUNCTION 08000ab2 FUN_08000ab2 SIZE 50 */

void FUN_08000ab2(undefined4 param_1,int param_2)

{
  int iVar1;
  ushort extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    if (param_2 == 0) {
      *DAT_08000bf4 = *DAT_08000bf4 | extraout_r2;
    }
    else {
      *(ushort *)(DAT_08000ad8 + 0x1a) = *(ushort *)(DAT_08000ad8 + 0x1a) & ~extraout_r2;
    }
  }
  return;
}



/* FUNCTION 08000afa FUN_08000afa SIZE 24 */

void FUN_08000afa(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 extraout_r2;
  
  iVar1 = FUN_080007ea(param_1,param_2,param_1);
  if (iVar1 == 8) {
    *(undefined1 *)(DAT_08000bf4 + -5) = extraout_r2;
  }
  return;
}



/* FUNCTION 08000b12 FUN_08000b12 SIZE 46 */

void FUN_08000b12(byte param_1,byte param_2)

{
  int iVar1;
  byte extraout_r2;
  
  iVar1 = FUN_080007ea();
  if (iVar1 == 8) {
    *(byte *)(DAT_08000bf4 + -6) =
         param_2 | *(byte *)(DAT_08000bf4 + -6) & 0xf | extraout_r2 | param_1;
  }
  return;
}



/* FUNCTION 08000bea FUN_08000bea SIZE 8 */

void FUN_08000bea(undefined4 param_1)

{
  *(undefined4 *)(DAT_08000bf4 + -0xe) = param_1;
  return;
}



/* FUNCTION 08000c2e FUN_08000c2e SIZE 230 */

void FUN_08000c2e(int *param_1)

{
  *(int *)(*param_1 * 4 + -0x60000000) =
       param_1[1] | param_1[2] | param_1[3] | param_1[4] | param_1[5] | param_1[6] | param_1[7] |
       param_1[8] | param_1[9] | param_1[10] | param_1[0xb] | param_1[0xc];
  if (param_1[2] == 8) {
    *(uint *)(*param_1 * 4 + -0x60000000) = *(uint *)(*param_1 * 4 + -0x60000000) | 0x40;
  }
  *(uint *)((*param_1 + 1) * 4 + -0x60000000) =
       *(uint *)param_1[0xd] | *(int *)(param_1[0xd] + 4) << 4 | *(int *)(param_1[0xd] + 8) << 8 |
       (uint)*(ushort *)(param_1[0xd] + 0xc) << 0x10 |
       (uint)*(ushort *)(param_1[0xd] + 0x10) << 0x14 | (uint)*(byte *)(param_1[0xd] + 0x14) << 0x18
       | *(uint *)(param_1[0xd] + 0x18);
  if (param_1[0xb] == 0x4000) {
    *(uint *)(*param_1 * 4 + -0x5ffffefc) =
         *(uint *)param_1[0xe] | *(int *)(param_1[0xe] + 4) << 4 | *(int *)(param_1[0xe] + 8) << 8 |
         (uint)*(ushort *)(param_1[0xe] + 0x10) << 0x14 |
         (uint)*(byte *)(param_1[0xe] + 0x14) << 0x18 | *(uint *)(param_1[0xe] + 0x18);
  }
  else {
    *(undefined4 *)(*param_1 * 4 + -0x5ffffefc) = 0xfffffff;
  }
  return;
}



/* FUNCTION 08000d86 FUN_08000d86 SIZE 46 */

void FUN_08000d86(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 * 4 + -0x60000000) = *(uint *)(param_1 * 4 + -0x60000000) & DAT_0800118c;
  }
  else {
    *(uint *)(param_1 * 4 + -0x60000000) = *(uint *)(param_1 * 4 + -0x60000000) | 1;
  }
  return;
}



/* FUNCTION 08001172 FUN_08001172 SIZE 62 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_08001172(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_1 == 0x10) {
    uVar2 = _DAT_a0000064;
  }
  else if (param_1 == 0x100) {
    uVar2 = *DAT_080011fc;
  }
  else {
    uVar2 = DAT_080011fc[8];
  }
  if (((uVar2 & param_2) == 0) || ((uVar2 & param_2 >> 3) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* FUNCTION 08001200 FUN_08001200 SIZE 220 */

void FUN_08001200(int param_1)

{
  if (param_1 == DAT_08001438) {
    FUN_08001820(1);
    FUN_08001820(1,0);
  }
  else if (param_1 == DAT_0800143c) {
    FUN_08001820(2,1);
    FUN_08001820(2,0);
  }
  else if (param_1 == DAT_08001440) {
    FUN_08001820(4,1);
    FUN_08001820(4,0);
  }
  else if (param_1 == DAT_08001444) {
    FUN_08001820(8,1);
    FUN_08001820(8,0);
  }
  else if (param_1 == DAT_08001448) {
    FUN_08001820(0x10,1);
    FUN_08001820(0x10,0);
  }
  else if (param_1 == DAT_0800144c) {
    FUN_08001820(0x20,1);
    FUN_08001820(0x20,0);
  }
  else if (param_1 == DAT_08001450) {
    FUN_08001820(0x40,1);
    FUN_08001820(0x40,0);
  }
  else if (param_1 == DAT_08001454) {
    FUN_08001820(0x80,1);
    FUN_08001820(0x80,0);
  }
  else if (param_1 == DAT_08001458) {
    FUN_08001820(DAT_08001458 >> 0x16,1);
    FUN_08001820(param_1 >> 0x16,0);
  }
  return;
}



/* FUNCTION 080012dc FUN_080012dc SIZE 144 */

void FUN_080012dc(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  
  for (uVar1 = 0; uVar1 < 0x10; uVar1 = uVar1 + 1) {
    uVar2 = 1 << (uVar1 & 0xff);
    if ((*param_2 & uVar2) == uVar2) {
      *param_1 = *param_1 & ~(3 << ((uVar1 & 0x7f) << 1));
      *param_1 = (uint)(byte)param_2[1] << ((uVar1 & 0x7f) << 1) | *param_1;
      if (((char)param_2[1] == '\x01') || ((char)param_2[1] == '\x02')) {
        param_1[2] = param_1[2] & ~(3 << ((uVar1 & 0x7f) << 1));
        param_1[2] = (uint)*(byte *)((int)param_2 + 5) << ((uVar1 & 0x7f) << 1) | param_1[2];
        param_1[1] = param_1[1] & ~(1 << (uVar1 & 0xff));
        param_1[1] = param_1[1] | (uint)*(byte *)((int)param_2 + 6) << (uVar1 & 0xff) & 0xffff;
      }
      param_1[3] = param_1[3] & ~(3 << ((uVar1 & 0x7f) << 1));
      param_1[3] = (uint)*(byte *)((int)param_2 + 7) << ((uVar1 & 0x7f) << 1) | param_1[3];
    }
  }
  return;
}



/* FUNCTION 080013d4 FUN_080013d4 SIZE 4 */

void FUN_080013d4(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0x18) = param_2;
  return;
}



/* FUNCTION 080013d8 FUN_080013d8 SIZE 4 */

void FUN_080013d8(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0x1a) = param_2;
  return;
}



/* FUNCTION 080013f2 FUN_080013f2 SIZE 70 */

void FUN_080013f2(int param_1,uint param_2,int param_3)

{
  int iVar1;
  
  iVar1 = (int)param_2 >> 3;
  *(uint *)(param_1 + 0x20 + iVar1 * 4) =
       *(uint *)(param_1 + 0x20 + iVar1 * 4) & ~(0xf << ((param_2 & 7) << 2));
  *(uint *)(param_1 + 0x20 + iVar1 * 4) =
       *(uint *)(param_1 + 0x20 + iVar1 * 4) | param_3 << ((param_2 & 7) << 2);
  return;
}



/* FUNCTION 080014ae FUN_080014ae SIZE 60 */

bool FUN_080014ae(uint param_1)

{
  uint uVar1;
  
  if ((int)param_1 >> 5 == 1) {
    uVar1 = *DAT_08001844;
  }
  else if ((int)param_1 >> 5 == 2) {
    uVar1 = DAT_08001844[0x1c];
  }
  else {
    uVar1 = DAT_08001844[0x1d];
  }
  return (1 << (param_1 & 0x1f) & uVar1) != 0;
}



/* FUNCTION 080014ea FUN_080014ea SIZE 56 */

bool FUN_080014ea(void)

{
  int iVar1;
  int local_10;
  
  local_10 = 0;
  do {
    iVar1 = FUN_080014ae(0x31);
    local_10 = local_10 + 1;
    if (local_10 == 0x500) break;
  } while (iVar1 == 0);
  iVar1 = FUN_080014ae(0x31);
  return iVar1 != 0;
}



/* FUNCTION 08001776 FUN_08001776 SIZE 34 */

void FUN_08001776(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x30) = *(uint *)(DAT_08001844 + 0x30) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x30) = *(uint *)(DAT_08001844 + 0x30) | param_1;
  }
  return;
}



/* FUNCTION 08001798 FUN_08001798 SIZE 34 */

void FUN_08001798(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x34) = *(uint *)(DAT_08001844 + 0x34) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x34) = *(uint *)(DAT_08001844 + 0x34) | param_1;
  }
  return;
}



/* FUNCTION 080017ba FUN_080017ba SIZE 34 */

void FUN_080017ba(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x38) = *(uint *)(DAT_08001844 + 0x38) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x38) = *(uint *)(DAT_08001844 + 0x38) | param_1;
  }
  return;
}



/* FUNCTION 080017dc FUN_080017dc SIZE 34 */

void FUN_080017dc(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x40) = *(uint *)(DAT_08001844 + 0x40) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x40) = *(uint *)(DAT_08001844 + 0x40) | param_1;
  }
  return;
}



/* FUNCTION 080017fe FUN_080017fe SIZE 34 */

void FUN_080017fe(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x44) = *(uint *)(DAT_08001844 + 0x44) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x44) = *(uint *)(DAT_08001844 + 0x44) | param_1;
  }
  return;
}



/* FUNCTION 08001820 FUN_08001820 SIZE 34 */

void FUN_08001820(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001844 + 0x10) = *(uint *)(DAT_08001844 + 0x10) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001844 + 0x10) = *(uint *)(DAT_08001844 + 0x10) | param_1;
  }
  return;
}



/* FUNCTION 08001aa0 FUN_08001aa0 SIZE 22 */

undefined4 FUN_08001aa0(int param_1)

{
  return *(undefined4 *)(DAT_08001bc0 + 0x10 + param_1);
}



/* FUNCTION 08001b62 FUN_08001b62 SIZE 34 */

void FUN_08001b62(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_08001bc0 + 0x38) = *(uint *)(DAT_08001bc0 + 0x38) & ~param_1;
  }
  else {
    *(uint *)(DAT_08001bc0 + 0x38) = *(uint *)(DAT_08001bc0 + 0x38) | param_1;
  }
  return;
}



/* FUNCTION 08001ba2 FUN_08001ba2 SIZE 22 */

bool FUN_08001ba2(uint param_1)

{
  return (*(uint *)(DAT_08001bc0 + 0x30) & param_1) != 0;
}



/* FUNCTION 08001bb8 FUN_08001bb8 SIZE 8 */

void FUN_08001bb8(undefined4 param_1)

{
  *(undefined4 *)(DAT_08001bc0 + 0x34) = param_1;
  return;
}



/* FUNCTION 08001c68 FUN_08001c68 SIZE 60 */

void FUN_08001c68(ushort *param_1,ushort *param_2)

{
  *param_1 = *param_1 & 0x3040 |
             *param_2 | param_2[1] | param_2[2] | param_2[3] | param_2[4] | param_2[5] | param_2[6]
             | param_2[7];
  param_1[0xe] = param_1[0xe] & 0xf7ff;
  param_1[8] = param_2[8];
  return;
}



/* FUNCTION 08001ca4 FUN_08001ca4 SIZE 350 */

void FUN_08001ca4(int param_1,ushort *param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  
  uVar3 = 2;
  uVar4 = 0;
  *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & 0xf040;
  *(undefined2 *)(param_1 + 0x20) = 2;
  uVar1 = *(ushort *)(param_1 + 0x1c);
  if (*(int *)(param_2 + 4) != 2) {
    if (param_2[2] == 0) {
      iVar6 = 1;
    }
    else {
      iVar6 = 2;
    }
    if ((*DAT_08001fc8 & 0x800000) != 0) {
      *DAT_08001fc8 = *DAT_08001fc8 & 0xff7fffff;
    }
    uVar3 = ((DAT_08001fcc / (DAT_08001fc8[-1] & 0x3f)) * ((DAT_08001fc8[0x1f] & 0x7fff) >> 6)) /
            ((DAT_08001fc8[0x1f] & 0x7fffffff) >> 0x1c);
    if (param_2[3] == 0x200) {
      uVar3 = ((uVar3 >> 8) * 10) / *(uint *)(param_2 + 4);
    }
    else {
      uVar3 = ((uVar3 / (uint)(iVar6 << 5)) * 10) / *(uint *)(param_2 + 4);
    }
    uVar3 = (uVar3 + 5 & 0xffff) / 10;
    uVar5 = uVar3 & 1;
    uVar3 = (uVar3 - uVar5 & 0x1ffff) >> 1;
    uVar4 = (ushort)(uVar5 << 8);
  }
  uVar2 = (ushort)uVar3;
  if ((uVar3 < 2) || (0xff < uVar3)) {
    uVar2 = 2;
    uVar4 = 0;
  }
  *(ushort *)(param_1 + 0x20) = param_2[3] | uVar4 | uVar2;
  *(ushort *)(param_1 + 0x1c) = param_2[2] | param_2[6] | param_2[1] | *param_2 | 0x800 | uVar1;
  return;
}



/* FUNCTION 08001e2e FUN_08001e2e SIZE 24 */

void FUN_08001e2e(ushort *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xffbf;
  }
  else {
    *param_1 = *param_1 | 0x40;
  }
  return;
}



/* FUNCTION 08001f2a FUN_08001f2a SIZE 6 */

undefined2 FUN_08001f2a(int param_1)

{
  return *(undefined2 *)(param_1 + 0xc);
}



/* FUNCTION 08001f30 FUN_08001f30 SIZE 4 */

void FUN_08001f30(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0xc) = param_2;
  return;
}



/* FUNCTION 08001f9e FUN_08001f9e SIZE 18 */

bool FUN_08001f9e(int param_1,ushort param_2)

{
  return (*(ushort *)(param_1 + 8) & param_2) != 0;
}



/* FUNCTION 08001fd6 FUN_08001fd6 SIZE 52 */

undefined4 FUN_08001fd6(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((((uint)*(ushort *)(param_1 + 8) & 1 << (param_2 & 0xf) & 0xffffU) == 0) ||
     (((uint)*(ushort *)(param_1 + 4) & 1 << ((int)param_2 >> 4 & 0xffU) & 0xffffU) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* FUNCTION 0800200a FUN_0800200a SIZE 20 */

void FUN_0800200a(int param_1,uint param_2)

{
  *(ushort *)(param_1 + 8) = ~(ushort)(1 << (param_2 & 0xf));
  return;
}



/* FUNCTION 0800202a FUN_0800202a SIZE 12 */

void FUN_0800202a(void)

{
  FUN_08001776(0x7f,1);
  return;
}



/* FUNCTION 08002036 FUN_08002036 SIZE 52 */

void FUN_08002036(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 local_10;
  uint3 local_c;
  undefined1 uStack_9;
  
  local_10 = param_3;
  _local_c = param_4;
  FUN_08001776(1);
  uVar1 = _local_c;
  local_10 = 0x200;
  _local_c = CONCAT31(stack0xfffffff5,2);
  uVar2 = _local_c;
  uStack_9 = SUB41(uVar1,3);
  local_c = (uint3)(ushort)uVar2;
  FUN_080012dc(DAT_0800237c,&local_10);
  local_10 = 0x400;
  FUN_080012dc(DAT_0800237c,&local_10);
  return;
}



/* FUNCTION 0800206a Boot_ProgramApplicationFromFile SIZE 490 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Reads creatorp.bin in chunks, erases/programs/verifies application flash */

void Boot_ProgramApplicationFromFile(void)

{
  int iVar1;
  uint uVar2;
  undefined4 local_1c;
  uint local_18;
  
  local_18 = 0;
  uVar2 = 0;
  local_1c = DAT_08002380;
  iVar1 = Boot_FS_Open(DAT_08002398,"1:/sys/creatorp.bin",1);
  if (iVar1 == 0) {
    if (*(uint *)(DAT_08002398 + 0xc) < 0xf0001) {
      Boot_DrawText_Candidate(0x32,0x121,"wait...",0xf800);
      *_DAT_0800239c = 0;
      FUN_08000a50();
      FUN_08000a7c(0x10,0);
      FUN_08000a7c(0x20,0);
      FUN_08000a7c(0x40,0);
      FUN_08000a7c(0x80,0);
      FUN_08000a7c(0x100,0);
      FUN_08000a7c(0x200,0);
      FUN_08000a7c(0x400,0);
      FUN_08000a7c(0x800,0);
      FUN_0800080c(0x20,2);
      FUN_0800080c(0x28,2);
      FUN_0800080c(0x30,2);
      FUN_0800080c(0x38,2);
      FUN_0800080c(0x40,2);
      FUN_0800080c(0x48,2);
      FUN_0800080c(0x50,2);
      FUN_0800080c(0x58,2);
      FUN_0800b9b0(DAT_080023b4,0x800);
      FUN_0800b9b0(_DAT_080023b8,0x800);
      do {
        Boot_FS_Read(DAT_08002398,_DAT_080023b8,0x800,&local_18);
        iVar1 = Boot_ProgramWordsAndVerify(&local_1c,_DAT_080023b8,(int)(local_18 & 0xffff) >> 2);
        if (iVar1 == 1) {
          Boot_DrawText_Candidate(5,0x121,"write error",0xffff);
          return;
        }
        if ((iVar1 != 0) && (iVar1 == 2)) {
          Boot_DrawText_Candidate(5,0x121,"write data error",0xffff);
          return;
        }
        FUN_0800b9b0(DAT_080023b4,0x800);
        FUN_0800b9b0(_DAT_080023b8,0x800);
        uVar2 = uVar2 + (local_18 & 0xffff);
        FUN_0800794e(0,0x121,(uVar2 * 0x1e0) / *(uint *)(DAT_08002398 + 0xc) & 0xffff,0x1e,0x7e0,
                     0x7e0,"");
      } while ((uVar2 < *(uint *)(DAT_08002398 + 0xc)) && (0x3ff < (ushort)local_18));
      if (uVar2 < *(uint *)(DAT_08002398 + 0xc)) {
        Boot_FS_Close(DAT_08002398);
        Boot_DrawText_Candidate(0xf0,0x121,"write file fail",0);
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      Boot_FS_Close(DAT_08002398);
      Boot_DrawText_Candidate(0xf0,0x121,"write file success",0);
    }
    else {
      *_DAT_0800239c = 1;
    }
  }
  else {
    *_DAT_0800239c = 1;
    Boot_DrawText_Candidate(5,0x121,"file error",0xffff);
  }
  return;
}



/* FUNCTION 08002254 FUN_08002254 SIZE 12 */

void FUN_08002254(void)

{
  int iVar1;
  
  for (iVar1 = DAT_08002400; iVar1 != 0; iVar1 = iVar1 + -1) {
  }
  return;
}



/* FUNCTION 08002260 FUN_08002260 SIZE 38 */

void FUN_08002260(void)

{
  int iVar1;
  undefined1 auStack_230 [552];
  
  iVar1 = Boot_FS_Open(auStack_230,"0:yahei24.xbf",1);
  if (iVar1 != 0) {
    FUN_080062a8(0,1,0x1000);
  }
  return;
}



/* FUNCTION 08002286 Boot_Main SIZE 244 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Mounts volumes, startup display, optional update, application handoff */

undefined4 Boot_Main(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  FUN_0800202a();
  FUN_08007f4c();
  FUN_08006c9e();
  FUN_08006c3e();
  FUN_08007630();
  for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
    iVar2 = FUN_080026fc(0);
    if (iVar2 == 0) {
      FUN_0800530e(0,_DAT_08002414);
      break;
    }
  }
  FUN_08007a1e(0x1e0,0x140,"0:start.bmp");
  iVar2 = 0;
  do {
    if (0x13 < iVar2) {
code_r0x080022fe:
      if (3 < iVar3) {
        Boot_DrawText_Candidate(10,0x14,"Bootloader V1.3 20201210",0x7e0);
        Boot_DrawText_Candidate(10,0x28,"Copyright 2020 by Flashforge.",0x7e0);
        Boot_DrawText_Candidate(0xa5,0x10d,"SPI FLASH Fail...",0x7e0);
      }
      Boot_DrawText_Candidate(0x1b8,0x121,&DAT_08002488,0x7e0);
      FUN_08007812(0);
      FUN_08002254();
      iVar3 = Boot_FS_Open(DAT_08002398,"1:/sys/creatorp.bin",1);
      if (iVar3 == 0) {
        FUN_08000774();
        FUN_08000bea(0xf3);
        Boot_ProgramApplicationFromFile();
        FUN_0800078e();
        Boot_JumpToApplication(DAT_08002380);
      }
      else {
        Boot_JumpToApplication(DAT_08002380);
      }
      return 0;
    }
    iVar1 = FUN_080026fc(1);
    if (iVar1 == 0) {
      FUN_0800530e(1,_DAT_08002424);
      goto code_r0x080022fe;
    }
    if (iVar2 == 4) {
      FUN_08002254();
      Boot_DrawText_Candidate(0xa5,0x121,"SD card Fail...",0x7e0);
    }
    iVar2 = iVar2 + 1;
  } while( true );
}



/* FUNCTION 08002490 FUN_08002490 SIZE 220 */

void FUN_08002490(void)

{
  uint *puVar1;
  uint *puVar2;
  int local_8;
  
  local_8 = 0;
  *DAT_08002674 = *DAT_08002674 | 0x10000;
  do {
    local_8 = local_8 + 1;
    if ((*DAT_08002674 & 0x20000) != 0) break;
  } while (local_8 != 0x500);
  if ((*DAT_08002674 & 0x20000) != 0) {
    DAT_08002674[0x10] = DAT_08002674[0x10] | 0x10000000;
    *DAT_08002678 = *DAT_08002678 | 0xc000;
    puVar2 = DAT_08002674;
    puVar1 = DAT_08002674 + 2;
    *puVar1 = DAT_08002674[2];
    *puVar1 = *puVar1 | 0x8000;
    *puVar1 = *puVar1 | 0x1400;
    puVar2[1] = DAT_0800267c;
    *puVar2 = *puVar2 | 0x1000000;
    do {
    } while ((*DAT_08002674 & 0x2000000) == 0);
    *DAT_08002680 = 0x705;
    puVar2 = DAT_08002674 + 2;
    *puVar2 = DAT_08002674[2] & 0xfffffffc;
    *puVar2 = *puVar2 | 2;
    do {
    } while ((DAT_08002674[2] & 0xc) != 8);
  }
  return;
}



/* FUNCTION 0800256c Boot_SystemInit SIZE 88 */

/* Clock and reset register configuration */

void Boot_SystemInit(void)

{
  uint *puVar1;
  
  *DAT_08002684 = *DAT_08002684 | 0xf00000;
  *DAT_08002674 = *DAT_08002674 | 1;
  DAT_08002674[2] = 0;
  puVar1 = DAT_08002674;
  *DAT_08002674 = *DAT_08002674 & DAT_08002688;
  puVar1[1] = DAT_0800268c;
  *puVar1 = *puVar1 & 0xfffbffff;
  DAT_08002674[3] = 0;
  FUN_08002490();
  DAT_08002684[-0x20] = 0x8000000;
  return;
}



/* FUNCTION 080025c4 FUN_080025c4 SIZE 174 */

void FUN_080025c4(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(DAT_08002674 + 8) & 0xc;
  if (uVar1 == 0) {
    *DAT_08002694 = DAT_08002690;
  }
  else if (uVar1 == 4) {
    *DAT_08002694 = DAT_08002698;
  }
  else if (uVar1 == 8) {
    uVar1 = *(uint *)(DAT_08002674 + 4) & 0x3f;
    if (*(int *)(DAT_08002674 + 4) << 9 < 0) {
      uVar1 = (DAT_08002698 / uVar1) * ((*(uint *)(DAT_08002674 + 4) & 0x7fff) >> 6);
    }
    else {
      uVar1 = (DAT_08002690 / uVar1) * ((*(uint *)(DAT_08002674 + 4) & 0x7fff) >> 6);
    }
    *DAT_08002694 = uVar1 / ((((*(uint *)(DAT_08002674 + 4) & 0x3ffff) >> 0x10) + 1) * 2);
  }
  else {
    *DAT_08002694 = DAT_08002690;
  }
  *DAT_08002694 =
       *DAT_08002694 >> *(sbyte *)(DAT_0800269c + ((*(uint *)(DAT_08002674 + 8) & 0xff) >> 4));
  return;
}



/* FUNCTION 080026a0 FUN_080026a0 SIZE 2 */

void FUN_080026a0(void)

{
  return;
}



/* FUNCTION 080026a2 thunk_FUN_080026a4 SIZE 2 */

void thunk_FUN_080026a4(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026a4 FUN_080026a4 SIZE 2 */

void FUN_080026a4(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026a6 thunk_FUN_080026a8 SIZE 2 */

void thunk_FUN_080026a8(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026a8 FUN_080026a8 SIZE 2 */

void FUN_080026a8(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026aa thunk_FUN_080026ac SIZE 2 */

void thunk_FUN_080026ac(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026ac FUN_080026ac SIZE 2 */

void FUN_080026ac(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026ae thunk_FUN_080026b0 SIZE 2 */

void thunk_FUN_080026b0(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026b0 FUN_080026b0 SIZE 2 */

void FUN_080026b0(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 080026b2 FUN_080026b2 SIZE 2 */

void FUN_080026b2(void)

{
  return;
}



/* FUNCTION 080026b4 FUN_080026b4 SIZE 2 */

void FUN_080026b4(void)

{
  return;
}



/* FUNCTION 080026b6 FUN_080026b6 SIZE 2 */

void FUN_080026b6(void)

{
  return;
}



/* FUNCTION 080026b8 FUN_080026b8 SIZE 10 */

void FUN_080026b8(void)

{
  FUN_0800b752(DAT_080026f4);
  return;
}



/* FUNCTION 080026c2 FUN_080026c2 SIZE 32 */

void FUN_080026c2(void)

{
  if (*(char *)(DAT_080026f4 + 10) != '\0') {
    *DAT_080026f8 = *DAT_080026f8 & 0xfffffff9;
    Boot_SystemInit();
    FUN_0800ab3e(DAT_080026f4);
  }
  return;
}



/* FUNCTION 080026e2 FUN_080026e2 SIZE 8 */

void FUN_080026e2(void)

{
  FUN_080042a0();
  return;
}



/* FUNCTION 080026ea FUN_080026ea SIZE 8 */

void FUN_080026ea(void)

{
  FUN_08004374();
  return;
}



/* FUNCTION 080026fc FUN_080026fc SIZE 76 */

undefined4 FUN_080026fc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 1;
  if (param_1 == 0) {
    FUN_08008988();
    iVar1 = FUN_08008a34();
    if (iVar1 == DAT_08002994) {
      uVar2 = 0;
    }
    else {
      uVar2 = 3;
    }
    *DAT_08002998 = 0x6000;
  }
  else if (param_1 == 1) {
    iVar1 = FUN_0800846e();
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 2;
    }
  }
  return uVar2;
}



/* FUNCTION 08002748 FUN_08002748 SIZE 42 */

undefined4 FUN_08002748(void)

{
  return 0;
}



/* FUNCTION 08002772 FUN_08002772 SIZE 208 */

undefined4 FUN_08002772(int param_1,int param_2,int param_3,uint param_4)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  bool bVar4;
  
  bVar2 = 0;
  uVar3 = 0;
  *DAT_0800299c = 1;
  if (param_1 == 0) {
    for (; 0 < (int)param_4; param_4 = param_4 - 1 & 0xff) {
      FUN_08008cba(param_2,param_3 << 9,0x200);
      param_3 = param_3 + 1;
      param_2 = param_2 + 0x200;
    }
    uVar3 = 0;
  }
  else if (param_1 == 1) {
    if (param_4 == 1) {
      cVar1 = FUN_080086c8(param_3,param_2);
    }
    else {
      cVar1 = FUN_08008706(param_3,param_2,param_4);
    }
    do {
      bVar4 = cVar1 == '\0';
      cVar1 = '\0';
      if (bVar4) break;
      FUN_0800846e();
      if (param_4 == 1) {
        cVar1 = FUN_080086c8(param_3,param_2);
      }
      else {
        cVar1 = FUN_08008706(param_3,param_2,param_4);
      }
      bVar2 = bVar2 + 1;
    } while (bVar2 < 5);
    if (cVar1 == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  *DAT_0800299c = 0;
  return uVar3;
}



/* FUNCTION 08002842 FUN_08002842 SIZE 202 */

undefined1 FUN_08002842(int param_1,int param_2,int param_3,uint param_4)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined1 uVar4;
  
  uVar4 = 0;
  bVar2 = 0;
  if (param_1 == 0) {
    for (; 0 < (int)param_4; param_4 = param_4 - 1 & 0xff) {
      FUN_08008de6(param_2,param_3 << 9,0x200);
      param_3 = param_3 + 1;
      param_2 = param_2 + 0x200;
    }
    uVar4 = 0;
  }
  else if (param_1 == 1) {
    if (param_4 == 1) {
      cVar1 = FUN_08008786(param_3,param_2);
    }
    else {
      cVar1 = FUN_08008856(param_3,param_2,param_4);
    }
    do {
      bVar3 = cVar1 == '\0';
      cVar1 = '\0';
      if (bVar3) break;
      FUN_0800846e();
      if (param_4 == 1) {
        cVar1 = FUN_08008786(param_3,param_2);
      }
      else {
        cVar1 = FUN_08008856(param_3,param_2,param_4);
      }
      bVar2 = bVar2 + 1;
    } while (bVar2 < 5);
    uVar4 = cVar1 != '\0';
  }
  else if ((param_1 != 4) && (param_1 != 5)) {
    uVar4 = 4;
  }
  return uVar4;
}



/* FUNCTION 0800290c FUN_0800290c SIZE 132 */

int FUN_0800290c(int param_1,int param_2,uint *param_3)

{
  if (param_1 == 0) {
    if (param_2 == 0) {
      param_1 = 0;
    }
    else if (param_2 == 1) {
      *param_3 = (uint)*DAT_08002998;
      param_1 = 0;
    }
    else if (param_2 == 2) {
      *(undefined2 *)param_3 = 0x200;
      param_1 = 0;
    }
    else if (param_2 == 3) {
      *(undefined2 *)param_3 = 8;
      param_1 = 0;
    }
    else {
      param_1 = 4;
    }
  }
  else if (param_1 == 1) {
    if (param_2 == 0) {
      param_1 = 0;
    }
    else if (param_2 == 1) {
      param_1 = 0;
    }
    else if (param_2 == 2) {
      *(undefined2 *)param_3 = 0x200;
      param_1 = 0;
    }
    else if (param_2 == 3) {
      *(undefined2 *)param_3 = 8;
      param_1 = 0;
    }
    else {
      param_1 = 4;
    }
  }
  return param_1;
}



/* FUNCTION 08002990 FUN_08002990 SIZE 4 */

undefined4 FUN_08002990(void)

{
  return DAT_080029a0;
}



/* FUNCTION 08002b8c FUN_08002b8c SIZE 130 */

void FUN_08002b8c(undefined4 param_1)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  FUN_080005fa(DAT_08002e00,0x1f400000);
  FUN_08000508(DAT_08002e00,0);
  FUN_08000350(DAT_08002e00);
  local_48 = 0x8000000;
  local_44 = DAT_08002e04;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0x400;
  local_2c = 0x1000;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0x30000;
  local_1c = 4;
  local_18 = 3;
  local_14 = 0x800000;
  local_10 = 0x200000;
  local_40 = param_1;
  FUN_08000494(DAT_08002e00,&local_48);
  FUN_08000622(DAT_08002e00,0x10,1);
  FUN_08000534(DAT_08002e00,0x20);
  FUN_08000508(DAT_08002e00,1);
  return;
}



/* FUNCTION 080042a0 FUN_080042a0 SIZE 164 */

undefined1 FUN_080042a0(void)

{
  int iVar1;
  
  iVar1 = FUN_08001ba2(0x100);
  if (iVar1 == 0) {
    iVar1 = FUN_08001ba2(2);
    if (iVar1 == 0) {
      iVar1 = FUN_08001ba2(8);
      if (iVar1 == 0) {
        iVar1 = FUN_08001ba2(0x20);
        if (iVar1 == 0) {
          iVar1 = FUN_08001ba2(0x10);
          if (iVar1 == 0) {
            iVar1 = FUN_08001ba2(0x200);
            if (iVar1 != 0) {
              FUN_08001bb8(0x200);
              *DAT_080043ac = 7;
            }
          }
          else {
            FUN_08001bb8(0x10);
            *DAT_080043ac = 5;
          }
        }
        else {
          FUN_08001bb8(0x20);
          *DAT_080043ac = 6;
        }
      }
      else {
        FUN_08001bb8(8);
        *DAT_080043ac = 4;
      }
    }
    else {
      FUN_08001bb8(2);
      *DAT_080043ac = 2;
    }
  }
  else {
    *DAT_080042d4 = 0;
    FUN_08001bb8(0x100);
    *DAT_080042d0 = 1;
  }
  FUN_08001b62(0xc33a,0);
  return *DAT_080043ac;
}



/* FUNCTION 08004374 FUN_08004374 SIZE 32 */

void FUN_08004374(void)

{
  if ((*DAT_080043b0 & 0x18000000) != 0) {
    *(undefined4 *)PTR_DAT_080043b4 = 1;
    FUN_080005fa(DAT_080043b0 + 0x16,0x18400000);
  }
  return;
}



/* FUNCTION 080043bc FUN_080043bc SIZE 26 */

void FUN_080043bc(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  bool bVar1;
  
  while (bVar1 = param_3 != 0, param_3 = param_3 + -1, bVar1) {
    *param_1 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  return;
}



/* FUNCTION 080043d6 FUN_080043d6 SIZE 20 */

void FUN_080043d6(undefined1 *param_1,undefined1 param_2,int param_3)

{
  bool bVar1;
  
  while (bVar1 = param_3 != 0, param_3 = param_3 + -1, bVar1) {
    *param_1 = param_2;
    param_1 = param_1 + 1;
  }
  return;
}



/* FUNCTION 080043ea FUN_080043ea SIZE 38 */

int FUN_080043ea(byte *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  
  do {
    bVar3 = param_3 == 0;
    param_3 = param_3 + -1;
    if (bVar3) {
      return 0;
    }
    bVar1 = *param_1;
    bVar2 = *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while ((uint)bVar1 - (uint)bVar2 == 0);
  return (uint)bVar1 - (uint)bVar2;
}



/* FUNCTION 08004410 FUN_08004410 SIZE 20 */

byte FUN_08004410(byte *param_1,uint param_2)

{
  for (; (*param_1 != 0 && (*param_1 != param_2)); param_1 = param_1 + 1) {
  }
  return *param_1;
}



/* FUNCTION 08004424 FUN_08004424 SIZE 82 */

undefined4 FUN_08004424(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 4) != '\0') {
    uVar2 = *(uint *)(param_1 + 0x30);
    iVar1 = FUN_08002842(*(undefined1 *)(param_1 + 1),param_1 + 0x34,uVar2,1);
    if (iVar1 != 0) {
      return 1;
    }
    *(undefined1 *)(param_1 + 4) = 0;
    if ((*(uint *)(param_1 + 0x24) <= uVar2) &&
       (uVar2 < (uint)(*(int *)(param_1 + 0x24) + *(int *)(param_1 + 0x1c)))) {
      for (uVar3 = (uint)*(byte *)(param_1 + 3); 1 < uVar3; uVar3 = uVar3 - 1) {
        uVar2 = uVar2 + *(int *)(param_1 + 0x1c);
        FUN_08002842(*(undefined1 *)(param_1 + 1),param_1 + 0x34,uVar2,1);
      }
    }
  }
  return 0;
}



/* FUNCTION 08004476 FUN_08004476 SIZE 50 */

undefined4 FUN_08004476(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x30) != param_2) {
    iVar1 = FUN_08004424(param_1);
    if (iVar1 != 0) {
      return 1;
    }
    iVar1 = FUN_08002772(*(undefined1 *)(param_1 + 1),param_1 + 0x34,param_2,1);
    if (iVar1 != 0) {
      return 1;
    }
    *(int *)(param_1 + 0x30) = param_2;
  }
  return 0;
}



/* FUNCTION 080044a8 FUN_080044a8 SIZE 200 */

int FUN_080044a8(char *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08004424(param_1);
  if (iVar1 == 0) {
    if ((*param_1 == '\x03') && (param_1[5] != '\0')) {
      param_1[0x30] = '\0';
      param_1[0x31] = '\0';
      param_1[0x32] = '\0';
      param_1[0x33] = '\0';
      FUN_080043d6(param_1 + 0x34,0,0x200);
      param_1[0x232] = 'U';
      param_1[0x233] = -0x56;
      param_1[0x34] = 'R';
      param_1[0x35] = 'R';
      param_1[0x36] = 'a';
      param_1[0x37] = 'A';
      param_1[0x218] = 'r';
      param_1[0x219] = 'r';
      param_1[0x21a] = 'A';
      param_1[0x21b] = 'a';
      param_1[0x21c] = param_1[0x10];
      param_1[0x21d] = (char)((ushort)*(undefined2 *)(param_1 + 0x10) >> 8);
      param_1[0x21e] = (char)((uint)*(undefined4 *)(param_1 + 0x10) >> 0x10);
      param_1[0x21f] = (char)((uint)*(undefined4 *)(param_1 + 0x10) >> 0x18);
      param_1[0x220] = param_1[0xc];
      param_1[0x221] = (char)((ushort)*(undefined2 *)(param_1 + 0xc) >> 8);
      param_1[0x222] = (char)((uint)*(undefined4 *)(param_1 + 0xc) >> 0x10);
      param_1[0x223] = (char)((uint)*(undefined4 *)(param_1 + 0xc) >> 0x18);
      FUN_08002842(param_1[1],param_1 + 0x34,*(undefined4 *)(param_1 + 0x14),1);
      param_1[5] = '\0';
    }
    iVar2 = FUN_0800290c(param_1[1],0);
    if (iVar2 != 0) {
      iVar1 = 1;
    }
  }
  return iVar1;
}



/* FUNCTION 08004570 FUN_08004570 SIZE 26 */

int FUN_08004570(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 - 2U < *(int *)(param_1 + 0x18) - 2U) {
    iVar1 = (param_2 - 2U) * (uint)*(byte *)(param_1 + 2) + *(int *)(param_1 + 0x2c);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}



/* FUNCTION 0800458a FUN_0800458a SIZE 228 */

uint FUN_0800458a(char *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  if ((param_2 < 2) || (*(uint *)(param_1 + 0x18) <= param_2)) {
    return 1;
  }
  cVar1 = *param_1;
  if (cVar1 == '\x01') {
    uVar4 = param_2 + (param_2 >> 1);
    iVar2 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (uVar4 >> 9));
    if (iVar2 == 0) {
      cVar1 = param_1[(uVar4 & 0x1ff) + 0x34];
      iVar2 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (uVar4 + 1 >> 9));
      if (iVar2 == 0) {
        if ((param_2 & 1) == 0) {
          return CONCAT11(param_1[(uVar4 + 1 & 0x1ff) + 0x34],cVar1) & 0xfff;
        }
        return (uint)(ushort)(CONCAT11(param_1[(uVar4 + 1 & 0x1ff) + 0x34],cVar1) >> 4);
      }
    }
  }
  else if (cVar1 == '\x02') {
    iVar2 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (param_2 >> 8));
    if (iVar2 == 0) {
      return (uint)*(ushort *)(param_1 + (param_2 & 0xff) * 2 + 0x34);
    }
  }
  else if ((cVar1 == '\x03') &&
          (iVar2 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (param_2 >> 7)), iVar2 == 0)) {
    pbVar3 = (byte *)(param_1 + (param_2 & 0x7f) * 4 + 0x34);
    return (pbVar3[3] & 0xf) << 0x18 | (uint)pbVar3[2] << 0x10 | (uint)pbVar3[1] << 8 |
           (uint)*pbVar3;
  }
  return 0xffffffff;
}



/* FUNCTION 0800466e FUN_0800466e SIZE 308 */

int FUN_0800466e(char *param_1,uint param_2,uint param_3)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  
  if ((param_2 < 2) || (*(uint *)(param_1 + 0x18) <= param_2)) {
    iVar5 = 2;
  }
  else {
    cVar1 = *param_1;
    bVar2 = (byte)(param_3 >> 8);
    if (cVar1 == '\x01') {
      uVar6 = param_2 + (param_2 >> 1);
      iVar5 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (uVar6 >> 9));
      if (iVar5 == 0) {
        if ((param_2 & 1) == 0) {
          uVar3 = param_3;
        }
        else {
          uVar3 = (byte)param_1[(uVar6 & 0x1ff) + 0x34] & 0xf | (param_3 & 0xff) << 4;
        }
        param_1[(uVar6 & 0x1ff) + 0x34] = (byte)uVar3;
        param_1[4] = '\x01';
        iVar5 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (uVar6 + 1 >> 9));
        if (iVar5 == 0) {
          if ((param_2 & 1) == 0) {
            bVar2 = param_1[(uVar6 + 1 & 0x1ff) + 0x34] & 0xf0U | bVar2 & 0xf;
          }
          else {
            bVar2 = (byte)((param_3 & 0xfff) >> 4);
          }
          param_1[(uVar6 + 1 & 0x1ff) + 0x34] = bVar2;
        }
      }
    }
    else if (cVar1 == '\x02') {
      iVar5 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (param_2 >> 8));
      if (iVar5 == 0) {
        param_1[(param_2 & 0xff) * 2 + 0x34] = (char)param_3;
        (param_1 + (param_2 & 0xff) * 2 + 0x34)[1] = bVar2;
      }
    }
    else if (cVar1 == '\x03') {
      iVar5 = FUN_08004476(param_1,*(int *)(param_1 + 0x24) + (param_2 >> 7));
      if (iVar5 == 0) {
        pcVar4 = param_1 + (param_2 & 0x7f) * 4 + 0x34;
        *pcVar4 = (char)param_3;
        pcVar4[1] = bVar2;
        pcVar4[2] = (char)(param_3 >> 0x10);
        pcVar4[3] = (byte)(param_3 >> 0x18) | pcVar4[3] & 0xf0U;
      }
    }
    else {
      iVar5 = 2;
    }
    param_1[4] = '\x01';
  }
  return iVar5;
}



/* FUNCTION 080047a4 FUN_080047a4 SIZE 104 */

int FUN_080047a4(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((1 < param_2) && (param_2 < *(uint *)(param_1 + 0x18))) {
    while( true ) {
      if (*(uint *)(param_1 + 0x18) <= param_2) {
        return 0;
      }
      uVar1 = FUN_0800458a(param_1,param_2);
      if (uVar1 == 0) {
        return 0;
      }
      if (uVar1 == 1) break;
      if (uVar1 == 0xffffffff) {
        return 1;
      }
      iVar2 = FUN_0800466e(param_1,param_2,0);
      if (iVar2 != 0) {
        return iVar2;
      }
      if (*(int *)(param_1 + 0x10) != -1) {
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
        *(undefined1 *)(param_1 + 5) = 1;
      }
      param_2 = uVar1;
    }
  }
  return 2;
}



/* FUNCTION 0800480c FUN_0800480c SIZE 202 */

uint FUN_0800480c(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_2 == 0) {
    uVar4 = *(uint *)(param_1 + 0xc);
    if ((uVar4 == 0) || (*(uint *)(param_1 + 0x18) <= uVar4)) {
      uVar4 = 1;
    }
  }
  else {
    uVar4 = FUN_0800458a(param_1,param_2);
    if (uVar4 < 2) {
      return 1;
    }
    if (uVar4 < *(uint *)(param_1 + 0x18)) {
      return uVar4;
    }
    uVar4 = param_2;
  }
  uVar3 = uVar4;
  while( true ) {
    uVar3 = uVar3 + 1;
    if ((*(uint *)(param_1 + 0x18) <= uVar3) && (uVar3 = 2, uVar4 < 2)) {
      return 0;
    }
    uVar1 = FUN_0800458a(param_1,uVar3);
    if (uVar1 == 0) {
      iVar2 = FUN_0800466e(param_1,uVar3,0xfffffff);
      if ((iVar2 == 0) && (param_2 != 0)) {
        iVar2 = FUN_0800466e(param_1,param_2,uVar3);
      }
      if (iVar2 == 0) {
        *(uint *)(param_1 + 0xc) = uVar3;
        if (*(int *)(param_1 + 0x10) != -1) {
          *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
          *(undefined1 *)(param_1 + 5) = 1;
        }
      }
      else if (iVar2 == 1) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = 1;
      }
      return uVar3;
    }
    if ((uVar1 == 0xffffffff) || (uVar1 == 1)) break;
    if (uVar3 == uVar4) {
      return 0;
    }
  }
  return uVar1;
}



/* FUNCTION 080048d6 FUN_080048d6 SIZE 50 */

int FUN_080048d6(int *param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  piVar1 = (int *)param_1[9];
  uVar3 = (param_2 >> 9) / (uint)*(byte *)(*param_1 + 2);
  while( true ) {
    uVar2 = piVar1[1];
    piVar1 = piVar1 + 2;
    if (uVar2 == 0) {
      return 0;
    }
    if (uVar3 < uVar2) break;
    uVar3 = uVar3 - uVar2;
  }
  return *piVar1 + uVar3;
}



/* FUNCTION 08004908 FUN_08004908 SIZE 156 */

undefined4 FUN_08004908(int *param_1,uint param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  *(short *)((int)param_1 + 6) = (short)param_2;
  uVar4 = param_1[2];
  if ((uVar4 == 1) || (*(uint *)(*param_1 + 0x18) <= uVar4)) {
    uVar2 = 2;
  }
  else {
    if ((uVar4 == 0) && (*(char *)*param_1 == '\x03')) {
      uVar4 = *(uint *)(*param_1 + 0x28);
    }
    if (uVar4 == 0) {
      param_1[3] = 0;
      if ((int)(uint)*(ushort *)(*param_1 + 8) <= (int)param_2) {
        return 2;
      }
      param_1[4] = *(int *)(*param_1 + 0x28) + (param_2 >> 4);
    }
    else {
      bVar1 = *(byte *)(*param_1 + 2);
      for (; (int)((uint)bVar1 * 0x10) <= (int)param_2;
          param_2 = param_2 + (uint)bVar1 * -0x10 & 0xffff) {
        uVar4 = FUN_0800458a(*param_1,uVar4);
        if (uVar4 == 0xffffffff) {
          return 1;
        }
        if ((uVar4 < 2) || (*(uint *)(*param_1 + 0x18) <= uVar4)) {
          return 2;
        }
      }
      param_1[3] = uVar4;
      iVar3 = FUN_08004570(*param_1,uVar4);
      param_1[4] = iVar3 + (param_2 >> 4);
    }
    param_1[5] = *param_1 + 0x34 + (param_2 & 0xf) * 0x20;
    uVar2 = 0;
  }
  return uVar2;
}



/* FUNCTION 080049a4 FUN_080049a4 SIZE 276 */

undefined4 FUN_080049a4(int *param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = *(short *)((int)param_1 + 6) + 1;
  uVar5 = (uint)uVar1;
  if ((uVar5 == 0) || (param_1[4] == 0)) {
    return 4;
  }
  if ((uVar1 & 0xf) == 0) {
    param_1[4] = param_1[4] + 1;
    if (param_1[3] == 0) {
      if (*(ushort *)(*param_1 + 8) <= uVar5) {
        return 4;
      }
    }
    else if ((ushort)(*(byte *)(*param_1 + 2) - 1 & uVar1 >> 4) == 0) {
      uVar2 = FUN_0800458a(*param_1,param_1[3]);
      if (uVar2 < 2) {
        return 2;
      }
      if (uVar2 == 0xffffffff) {
        return 1;
      }
      if (*(uint *)(*param_1 + 0x18) <= uVar2) {
        if (param_2 == 0) {
          return 4;
        }
        uVar2 = FUN_0800480c(*param_1,param_1[3]);
        if (uVar2 == 0) {
          return 7;
        }
        if (uVar2 == 1) {
          return 2;
        }
        if (uVar2 == 0xffffffff) {
          return 1;
        }
        iVar3 = FUN_08004424(*param_1);
        if (iVar3 != 0) {
          return 1;
        }
        FUN_080043d6(*param_1 + 0x34,0,0x200);
        uVar4 = FUN_08004570(*param_1,uVar2);
        *(undefined4 *)(*param_1 + 0x30) = uVar4;
        for (uVar6 = 0; uVar6 < *(byte *)(*param_1 + 2); uVar6 = uVar6 + 1 & 0xff) {
          *(undefined1 *)(*param_1 + 4) = 1;
          iVar3 = FUN_08004424(*param_1);
          if (iVar3 != 0) {
            return 1;
          }
          *(int *)(*param_1 + 0x30) = *(int *)(*param_1 + 0x30) + 1;
        }
        *(uint *)(*param_1 + 0x30) = *(int *)(*param_1 + 0x30) - uVar6;
      }
      param_1[3] = uVar2;
      iVar3 = FUN_08004570(*param_1,uVar2);
      param_1[4] = iVar3;
    }
  }
  *(ushort *)((int)param_1 + 6) = uVar1;
  param_1[5] = *param_1 + 0x34 + (uVar5 & 0xf) * 0x20;
  return 0;
}



/* FUNCTION 08004ab8 FUN_08004ab8 SIZE 86 */

int FUN_08004ab8(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08004908(param_1,0);
  if (iVar1 == 0) {
    iVar2 = 0;
    do {
      iVar1 = FUN_08004476(*param_1,param_1[4]);
      if (iVar1 != 0) {
        return iVar1;
      }
      if ((*(char *)param_1[5] == -0x1b) || (*(char *)param_1[5] == '\0')) {
        iVar2 = iVar2 + 1;
        if (iVar2 == param_2) {
          return 0;
        }
      }
      else {
        iVar2 = 0;
      }
      iVar1 = FUN_080049a4(param_1,1);
    } while (iVar1 == 0);
  }
  return iVar1;
}



/* FUNCTION 08004b0e FUN_08004b0e SIZE 32 */

uint FUN_08004b0e(char *param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(param_2 + 0x1a);
  if (*param_1 == '\x03') {
    uVar1 = CONCAT22(*(undefined2 *)(param_2 + 0x14),*(ushort *)(param_2 + 0x1a));
  }
  return uVar1;
}



/* FUNCTION 08004b2e FUN_08004b2e SIZE 16 */

void FUN_08004b2e(int param_1,undefined4 param_2)

{
  *(char *)(param_1 + 0x1a) = (char)param_2;
  *(char *)(param_1 + 0x1b) = (char)((uint)param_2 >> 8);
  *(char *)(param_1 + 0x14) = (char)((uint)param_2 >> 0x10);
  *(char *)(param_1 + 0x15) = (char)((uint)param_2 >> 0x18);
  return;
}



/* FUNCTION 08004b3e FUN_08004b3e SIZE 92 */

int FUN_08004b3e(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = FUN_08004908(param_1,0);
  if (iVar1 == 0) {
    while (iVar1 = FUN_08004476(*param_1,param_1[4]), iVar1 == 0) {
      pcVar3 = (char *)param_1[5];
      if (*pcVar3 == '\0') {
        iVar1 = 4;
        break;
      }
      if ((((pcVar3[0xb] & 8U) == 0) && (iVar2 = FUN_080043ea(pcVar3,param_1[6],0xb), iVar2 == 0))
         || (iVar1 = FUN_080049a4(param_1,0), iVar1 != 0)) break;
    }
  }
  return iVar1;
}



/* FUNCTION 08004b9a FUN_08004b9a SIZE 110 */

int FUN_08004b9a(undefined4 *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  
  iVar2 = 4;
  while( true ) {
    if ((param_1[4] == 0) || (iVar2 = FUN_08004476(*param_1,param_1[4]), iVar2 != 0))
    goto code_r0x08004bfc;
    cVar1 = *(char *)param_1[5];
    if (cVar1 == '\0') break;
    bVar3 = ((char *)param_1[5])[0xb] & 0x3f;
    if (((((cVar1 != -0x1b) && (cVar1 != '.')) && (bVar3 != 0xf)) && ((bVar3 == 8) == param_2)) ||
       (iVar2 = FUN_080049a4(param_1,0), iVar2 != 0)) goto code_r0x08004bfc;
  }
  iVar2 = 4;
code_r0x08004bfc:
  if (iVar2 != 0) {
    param_1[4] = 0;
  }
  return iVar2;
}



/* FUNCTION 08004c08 FUN_08004c08 SIZE 58 */

int FUN_08004c08(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_08004ab8(param_1,1);
  if ((iVar1 == 0) && (iVar1 = FUN_08004476(*param_1,param_1[4]), iVar1 == 0)) {
    FUN_080043d6(param_1[5],0,0x20);
    FUN_080043bc(param_1[5],param_1[6],0xb);
    *(undefined1 *)(*param_1 + 4) = 1;
  }
  return iVar1;
}



/* FUNCTION 08004c42 FUN_08004c42 SIZE 44 */

int FUN_08004c42(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_08004908(param_1,*(undefined2 *)((int)param_1 + 6));
  if ((iVar1 == 0) && (iVar1 = FUN_08004476(*param_1,param_1[4]), iVar1 == 0)) {
    *(undefined1 *)param_1[5] = 0xe5;
    *(undefined1 *)(*param_1 + 4) = 1;
  }
  return iVar1;
}



/* FUNCTION 08004c6e FUN_08004c6e SIZE 266 */

undefined4 FUN_08004c6e(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  
  for (pcVar7 = (char *)*param_2; (*pcVar7 == '/' || (*pcVar7 == '\\')); pcVar7 = pcVar7 + 1) {
  }
  pcVar6 = *(char **)(param_1 + 0x18);
  FUN_080043d6(pcVar6,0x20,0xb,param_4,param_1,param_2);
  uVar5 = 0;
  uVar8 = 8;
  uVar9 = 0;
  iVar10 = 0;
  while( true ) {
    while( true ) {
      iVar11 = iVar10 + 1;
      uVar4 = (uint)(byte)pcVar7[iVar10];
      if (((uVar4 < 0x21) || (uVar4 == 0x2f)) || (uVar4 == 0x5c)) {
        *param_2 = pcVar7 + iVar11;
        if (uVar4 < 0x21) {
          bVar3 = 4;
        }
        else {
          bVar3 = 0;
        }
        if (uVar9 == 0) {
          uVar1 = 6;
        }
        else {
          if (*pcVar6 == -0x1b) {
            *pcVar6 = '\x05';
          }
          if (uVar8 == 8) {
            uVar5 = (uVar5 & 0x3f) << 2;
          }
          if ((uVar5 & 3) == 1) {
            bVar3 = bVar3 | 0x10;
          }
          if ((uVar5 & 0xc) == 4) {
            bVar3 = bVar3 | 8;
          }
          pcVar6[0xb] = bVar3;
          uVar1 = 0;
        }
        return uVar1;
      }
      iVar10 = iVar11;
      if ((uVar4 != 0x2e) && (uVar9 < uVar8)) break;
      if ((uVar8 != 8) || (uVar4 != 0x2e)) {
        return 6;
      }
      uVar8 = 0xb;
      uVar5 = (uVar5 & 0x3f) << 2;
      uVar9 = 8;
    }
    if (0x7f < uVar4) {
      uVar5 = uVar5 | 3;
      uVar4 = (uint)*(byte *)(DAT_080050c8 + (uVar4 - 0x80));
    }
    cVar2 = (char)uVar4;
    iVar11 = FUN_08004410(&DAT_080050cc,uVar4);
    if (iVar11 != 0) break;
    if ((uVar4 < 0x41) || (0x5a < uVar4)) {
      if ((0x60 < uVar4) && (uVar4 < 0x7b)) {
        uVar5 = uVar5 | 1;
        cVar2 = cVar2 + -0x20;
      }
    }
    else {
      uVar5 = uVar5 | 2;
    }
    pcVar6[uVar9] = cVar2;
    uVar9 = uVar9 + 1;
  }
  return 6;
}



/* FUNCTION 08004d78 FUN_08004d78 SIZE 152 */

void FUN_08004d78(int param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  char cVar4;
  
  pcVar3 = (char *)((int)param_2 + 9);
  if (*(int *)(param_1 + 0x10) != 0) {
    iVar1 = *(int *)(param_1 + 0x14);
    for (uVar2 = 0; (uVar2 < 8 && (cVar4 = *(char *)(iVar1 + uVar2), cVar4 != ' '));
        uVar2 = uVar2 + 1) {
      if (cVar4 == '\x05') {
        cVar4 = -0x1b;
      }
      *pcVar3 = cVar4;
      pcVar3 = pcVar3 + 1;
    }
    if (*(char *)(iVar1 + 8) != ' ') {
      *pcVar3 = '.';
      for (uVar2 = 8; (pcVar3 = pcVar3 + 1, uVar2 < 0xb && (*(char *)(iVar1 + uVar2) != ' '));
          uVar2 = uVar2 + 1) {
        *pcVar3 = *(char *)(iVar1 + uVar2);
      }
    }
    *(undefined1 *)(param_2 + 2) = *(undefined1 *)(iVar1 + 0xb);
    *param_2 = (uint)*(byte *)(iVar1 + 0x1f) << 0x18 | (uint)*(byte *)(iVar1 + 0x1e) << 0x10 |
               (uint)*(byte *)(iVar1 + 0x1d) << 8 | (uint)*(byte *)(iVar1 + 0x1c);
    *(undefined2 *)(param_2 + 1) = *(undefined2 *)(iVar1 + 0x18);
    *(undefined2 *)((int)param_2 + 6) = *(undefined2 *)(iVar1 + 0x16);
  }
  *pcVar3 = '\0';
  return;
}



/* FUNCTION 08004e10 FUN_08004e10 SIZE 146 */

int FUN_08004e10(undefined4 *param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  byte *local_1c;
  
  if ((*param_2 == 0x2f) || (local_1c = param_2, *param_2 == 0x5c)) {
    local_1c = param_2 + 1;
  }
  param_1[2] = 0;
  if (*local_1c < 0x20) {
    iVar1 = FUN_08004908(param_1,0,param_3,param_4,param_1);
    param_1[5] = 0;
  }
  else {
    while (iVar1 = FUN_08004c6e(param_1,&local_1c), iVar1 == 0) {
      iVar1 = FUN_08004b3e(param_1);
      if (iVar1 != 0) {
        if (iVar1 != 4) {
          return iVar1;
        }
        if ((*(byte *)(param_1[6] + 0xb) & 4) == 0) {
          return 5;
        }
        return 4;
      }
      if ((*(byte *)(param_1[6] + 0xb) & 4) != 0) {
        return 0;
      }
      if ((*(byte *)(param_1[5] + 0xb) & 0x10) == 0) {
        return 5;
      }
      uVar2 = FUN_08004b0e(*param_1,param_1[5]);
      param_1[2] = uVar2;
    }
  }
  return iVar1;
}



/* FUNCTION 08004ea2 FUN_08004ea2 SIZE 138 */

undefined4 FUN_08004ea2(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_08002772(*(undefined1 *)(param_1 + 1),param_1 + 0x34,param_2,1);
  if (iVar1 == 0) {
    if (*(short *)(param_1 + 0x232) == -0x55ab) {
      if (((uint)*(byte *)(param_1 + 0x6c) << 0x10 | (uint)*(byte *)(param_1 + 0x6b) << 8 |
          (uint)*(byte *)(param_1 + 0x6a)) == DAT_080050dc) {
        uVar2 = 0;
      }
      else if (((uint)*(byte *)(param_1 + 0x88) << 0x10 | (uint)*(byte *)(param_1 + 0x87) << 8 |
               (uint)*(byte *)(param_1 + 0x86)) == DAT_080050dc) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 2;
    }
  }
  else {
    uVar2 = 3;
  }
  return uVar2;
}



/* FUNCTION 08004f2c FUN_08004f2c SIZE 910 */

/* WARNING: Removing unreachable block (ram,0x08004ff0) */

undefined4 FUN_08004f2c(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  int local_44;
  uint local_38;
  uint local_34;
  
  pbVar3 = (byte *)*param_1;
  local_34 = *pbVar3 - 0x30;
  if ((local_34 < 10) && (pbVar3[1] == 0x3a)) {
    *param_1 = pbVar3 + 2;
  }
  else {
    local_34 = 0;
  }
  *param_2 = 0;
  if (local_34 < 2) {
    pcVar10 = *(char **)(DAT_080050e0 + local_34 * 4);
    if (pcVar10 == (char *)0x0) {
      uVar4 = 0xc;
    }
    else {
      *param_2 = pcVar10;
      if ((*pcVar10 == '\0') || (uVar5 = FUN_08002748(pcVar10[1]), (uVar5 & 1) != 0)) {
        *pcVar10 = '\0';
        pcVar10[1] = (char)local_34;
        uVar5 = FUN_080026fc(pcVar10[1]);
        if ((uVar5 & 1) == 0) {
          if ((param_3 == 0) || ((uVar5 & 4) == 0)) {
            uVar5 = 0;
            iVar6 = FUN_08004ea2(pcVar10,0);
            if ((iVar6 == 1) && (pcVar10[0x1f6] != '\0')) {
              uVar5 = (uint)(byte)pcVar10[0x1fd] << 0x18 | (uint)(byte)pcVar10[0x1fc] << 0x10 |
                      (uint)(byte)pcVar10[0x1fb] << 8 | (uint)(byte)pcVar10[0x1fa];
              iVar6 = FUN_08004ea2(pcVar10,uVar5);
            }
            if (iVar6 == 3) {
              uVar4 = 1;
            }
            else if (iVar6 == 0) {
              if (*(short *)(pcVar10 + 0x3f) == 0x200) {
                uVar13 = (uint)*(ushort *)(pcVar10 + 0x4a);
                if (uVar13 == 0) {
                  uVar13 = (uint)(byte)pcVar10[0x5b] << 0x18 | (uint)(byte)pcVar10[0x5a] << 0x10 |
                           (uint)(byte)pcVar10[0x59] << 8 | (uint)(byte)pcVar10[0x58];
                }
                *(uint *)(pcVar10 + 0x1c) = uVar13;
                uVar12 = (uint)(byte)pcVar10[0x44];
                pcVar10[3] = pcVar10[0x44];
                if ((uVar12 == 1) || (uVar12 == 2)) {
                  bVar1 = pcVar10[0x41];
                  pcVar10[2] = bVar1;
                  if ((bVar1 == 0) || ((bVar1 - 1 & bVar1) != 0)) {
                    uVar4 = 0xd;
                  }
                  else {
                    *(undefined2 *)(pcVar10 + 8) = *(undefined2 *)(pcVar10 + 0x45);
                    if ((pcVar10[8] & 0xfU) == 0) {
                      local_38 = (uint)*(ushort *)(pcVar10 + 0x47);
                      if (local_38 == 0) {
                        local_38 = (uint)(byte)pcVar10[0x57] << 0x18 |
                                   (uint)(byte)pcVar10[0x56] << 0x10 |
                                   (uint)(byte)pcVar10[0x55] << 8 | (uint)(byte)pcVar10[0x54];
                      }
                      uVar7 = (uint)*(ushort *)(pcVar10 + 0x42);
                      if (uVar7 == 0) {
                        uVar4 = 0xd;
                      }
                      else {
                        uVar8 = uVar7 + uVar13 * uVar12 + (uint)(*(ushort *)(pcVar10 + 8) >> 4);
                        if (local_38 < uVar8) {
                          uVar4 = 0xd;
                        }
                        else {
                          uVar9 = (local_38 - uVar8) / (uint)(byte)pcVar10[2];
                          if (uVar9 == 0) {
                            uVar4 = 0xd;
                          }
                          else {
                            cVar11 = '\x01';
                            if (0xff5 < uVar9) {
                              cVar11 = '\x02';
                            }
                            if (0xfff5 < uVar9) {
                              cVar11 = '\x03';
                            }
                            *(uint *)(pcVar10 + 0x18) = uVar9 + 2;
                            *(uint *)(pcVar10 + 0x20) = uVar5;
                            *(uint *)(pcVar10 + 0x24) = uVar7 + uVar5;
                            *(uint *)(pcVar10 + 0x2c) = uVar8 + uVar5;
                            if (cVar11 == '\x03') {
                              if (*(short *)(pcVar10 + 8) != 0) {
                                return 0xd;
                              }
                              *(uint *)(pcVar10 + 0x28) =
                                   (uint)(byte)pcVar10[99] << 0x18 |
                                   (uint)(byte)pcVar10[0x62] << 0x10 |
                                   (uint)(byte)pcVar10[0x61] << 8 | (uint)(byte)pcVar10[0x60];
                              local_44 = *(int *)(pcVar10 + 0x18) << 2;
                            }
                            else {
                              if (*(short *)(pcVar10 + 8) == 0) {
                                return 0xd;
                              }
                              *(uint *)(pcVar10 + 0x28) = *(int *)(pcVar10 + 0x24) + uVar13 * uVar12
                              ;
                              if (cVar11 == '\x02') {
                                local_44 = *(int *)(pcVar10 + 0x18) << 1;
                              }
                              else {
                                local_44 = ((byte)pcVar10[0x18] & 1) +
                                           ((uint)(*(int *)(pcVar10 + 0x18) * 3) >> 1);
                              }
                            }
                            if (*(uint *)(pcVar10 + 0x1c) < local_44 + 0x1ffU >> 9) {
                              uVar4 = 0xd;
                            }
                            else {
                              pcVar10[0x10] = -1;
                              pcVar10[0x11] = -1;
                              pcVar10[0x12] = -1;
                              pcVar10[0x13] = -1;
                              pcVar10[0xc] = '\0';
                              pcVar10[0xd] = '\0';
                              pcVar10[0xe] = '\0';
                              pcVar10[0xf] = '\0';
                              if (cVar11 == '\x03') {
                                pcVar10[5] = '\0';
                                *(uint *)(pcVar10 + 0x14) = *(ushort *)(pcVar10 + 100) + uVar5;
                                iVar6 = FUN_08002772(pcVar10[1],pcVar10 + 0x34,
                                                     *(undefined4 *)(pcVar10 + 0x14),1);
                                if ((((iVar6 == 0) && (*(short *)(pcVar10 + 0x232) == -0x55ab)) &&
                                    (((uint)(byte)pcVar10[0x37] << 0x18 |
                                      (uint)(byte)pcVar10[0x36] << 0x10 |
                                      (uint)(byte)pcVar10[0x35] << 8 | (uint)(byte)pcVar10[0x34]) ==
                                     DAT_08005650)) &&
                                   (((uint)(byte)pcVar10[0x21b] << 0x18 |
                                     (uint)(byte)pcVar10[0x21a] << 0x10 |
                                     (uint)(byte)pcVar10[0x219] << 8 | (uint)(byte)pcVar10[0x218])
                                    == DAT_08005654)) {
                                  *(uint *)(pcVar10 + 0xc) =
                                       (uint)(byte)pcVar10[0x223] << 0x18 |
                                       (uint)(byte)pcVar10[0x222] << 0x10 |
                                       (uint)(byte)pcVar10[0x221] << 8 | (uint)(byte)pcVar10[0x220];
                                  *(uint *)(pcVar10 + 0x10) =
                                       (uint)(byte)pcVar10[0x21f] << 0x18 |
                                       (uint)(byte)pcVar10[0x21e] << 0x10 |
                                       (uint)(byte)pcVar10[0x21d] << 8 | (uint)(byte)pcVar10[0x21c];
                                }
                              }
                              *pcVar10 = cVar11;
                              sVar2 = *DAT_08005658;
                              *DAT_08005658 = sVar2 + 1;
                              *(short *)(pcVar10 + 6) = sVar2 + 1;
                              uVar4 = 0;
                              pcVar10[0x30] = '\0';
                              pcVar10[0x31] = '\0';
                              pcVar10[0x32] = '\0';
                              pcVar10[0x33] = '\0';
                              pcVar10[4] = '\0';
                            }
                          }
                        }
                      }
                    }
                    else {
                      uVar4 = 0xd;
                    }
                  }
                }
                else {
                  uVar4 = 0xd;
                }
              }
              else {
                uVar4 = 0xd;
              }
            }
            else {
              uVar4 = 0xd;
            }
          }
          else {
            uVar4 = 10;
          }
        }
        else {
          uVar4 = 3;
        }
      }
      else if ((param_3 == 0) || ((uVar5 & 4) == 0)) {
        uVar4 = 0;
      }
      else {
        uVar4 = 10;
      }
    }
  }
  else {
    uVar4 = 0xb;
  }
  return uVar4;
}



/* FUNCTION 080052d8 FUN_080052d8 SIZE 54 */

undefined4 FUN_080052d8(int *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if ((((param_1 == (int *)0x0) || (*param_1 == 0)) || (*(char *)*param_1 == '\0')) ||
     (*(short *)(*param_1 + 6) != (short)param_1[1])) {
    uVar1 = 9;
  }
  else {
    uVar2 = FUN_08002748(*(undefined1 *)(*param_1 + 1));
    if ((uVar2 & 1) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 3;
    }
  }
  return uVar1;
}



/* FUNCTION 0800530e FUN_0800530e SIZE 38 */

undefined4 FUN_0800530e(int param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if (param_1 < 2) {
    puVar2 = *(undefined1 **)(DAT_0800565c + param_1 * 4);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 0;
    }
    if (param_2 != (undefined1 *)0x0) {
      *param_2 = 0;
    }
    *(undefined1 **)(DAT_0800565c + param_1 * 4) = param_2;
    uVar1 = 0;
  }
  else {
    uVar1 = 0xb;
  }
  return uVar1;
}



/* FUNCTION 08005334 Boot_FS_Open SIZE 352 */

/* File object, path and mode parameters */

int Boot_FS_Open(int *param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  undefined1 auStack_50 [12];
  int local_44 [5];
  int local_30;
  undefined1 *local_2c;
  int *piStack_28;
  undefined4 local_24;
  uint uStack_20;
  
  if (param_1 == (int *)0x0) {
    iVar1 = 9;
  }
  else {
    *param_1 = 0;
    uVar6 = param_3 & 0x1f;
    piStack_28 = param_1;
    local_24 = param_2;
    uStack_20 = param_3;
    iVar1 = FUN_08004f2c(&local_24,local_44,param_3 & 0x1e);
    if (iVar1 == 0) {
      local_2c = auStack_50;
      iVar1 = FUN_08004e10(local_44,local_24);
      if ((iVar1 == 0) && (local_30 == 0)) {
        iVar1 = 6;
      }
      iVar4 = local_30;
      if ((param_3 & 0x1c) == 0) {
        if (iVar1 == 0) {
          if ((*(byte *)(local_30 + 0xb) & 0x10) == 0) {
            if (((param_3 & 2) != 0) && ((*(byte *)(local_30 + 0xb) & 1) != 0)) {
              iVar1 = 7;
            }
          }
          else {
            iVar1 = 4;
          }
        }
      }
      else {
        if (iVar1 == 0) {
          if ((*(byte *)(local_30 + 0xb) & 0x11) == 0) {
            if ((param_3 & 4) != 0) {
              iVar1 = 8;
            }
          }
          else {
            iVar1 = 7;
          }
        }
        else {
          if (iVar1 == 4) {
            iVar1 = FUN_08004c08(local_44);
          }
          uVar6 = uVar6 | 8;
          iVar4 = local_30;
        }
        if ((iVar1 == 0) && ((uVar6 & 8) != 0)) {
          uVar2 = FUN_08002990();
          *(char *)(iVar4 + 0xe) = (char)uVar2;
          *(char *)(iVar4 + 0xf) = (char)((uint)uVar2 >> 8);
          *(char *)(iVar4 + 0x10) = (char)((uint)uVar2 >> 0x10);
          *(char *)(iVar4 + 0x11) = (char)((uint)uVar2 >> 0x18);
          *(undefined1 *)(iVar4 + 0xb) = 0;
          *(undefined1 *)(iVar4 + 0x1c) = 0;
          *(undefined1 *)(iVar4 + 0x1d) = 0;
          *(undefined1 *)(iVar4 + 0x1e) = 0;
          *(undefined1 *)(iVar4 + 0x1f) = 0;
          iVar3 = FUN_08004b0e(local_44[0],iVar4);
          FUN_08004b2e(iVar4,0);
          *(undefined1 *)(local_44[0] + 4) = 1;
          if (iVar3 != 0) {
            uVar2 = *(undefined4 *)(local_44[0] + 0x30);
            iVar1 = FUN_080047a4(local_44[0],iVar3);
            if (iVar1 == 0) {
              *(int *)(local_44[0] + 0xc) = iVar3 + -1;
              iVar1 = FUN_08004476(local_44[0],uVar2);
            }
          }
        }
      }
      bVar5 = (byte)uVar6;
      if (iVar1 == 0) {
        if ((uVar6 & 8) != 0) {
          bVar5 = bVar5 | 0x20;
        }
        param_1[7] = *(int *)(local_44[0] + 0x30);
        param_1[8] = iVar4;
      }
      if (iVar1 == 0) {
        *(byte *)((int)param_1 + 6) = bVar5;
        iVar3 = FUN_08004b0e(local_44[0],iVar4);
        param_1[4] = iVar3;
        param_1[3] = (uint)*(byte *)(iVar4 + 0x1f) << 0x18 | (uint)*(byte *)(iVar4 + 0x1e) << 0x10 |
                     (uint)*(byte *)(iVar4 + 0x1d) << 8 | (uint)*(byte *)(iVar4 + 0x1c);
        param_1[2] = 0;
        param_1[6] = 0;
        param_1[9] = 0;
        *param_1 = local_44[0];
        *(undefined2 *)(param_1 + 1) = *(undefined2 *)(local_44[0] + 6);
      }
    }
  }
  return iVar1;
}



/* FUNCTION 08005494 Boot_FS_Read SIZE 476 */

/* File object, buffer, length and bytes-read pointer */

int Boot_FS_Read(int *param_1,int param_2,uint param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint local_3c;
  
  *param_4 = 0;
  iVar1 = FUN_080052d8(param_1);
  if (iVar1 == 0) {
    if ((*(byte *)((int)param_1 + 6) & 0x80) == 0) {
      if ((*(byte *)((int)param_1 + 6) & 1) == 0) {
        iVar1 = 7;
      }
      else {
        if ((uint)(param_1[3] - param_1[2]) < param_3) {
          param_3 = param_1[3] - param_1[2];
        }
        for (; param_3 != 0; param_3 = param_3 - uVar3) {
          if ((*(ushort *)(param_1 + 2) & 0x1ff) == 0) {
            uVar4 = *(byte *)(*param_1 + 2) - 1 & (uint)param_1[2] >> 9 & 0xff;
            if (uVar4 == 0) {
              if (param_1[2] == 0) {
                local_3c = param_1[4];
              }
              else if (param_1[9] == 0) {
                local_3c = FUN_0800458a(*param_1,param_1[5]);
              }
              else {
                local_3c = FUN_080048d6(param_1,param_1[2]);
              }
              if (local_3c < 2) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 2;
              }
              if (local_3c == 0xffffffff) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 1;
              }
              param_1[5] = local_3c;
            }
            iVar1 = FUN_08004570(*param_1,param_1[5]);
            if (iVar1 == 0) {
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
              return 2;
            }
            iVar1 = iVar1 + uVar4;
            uVar3 = param_3 >> 9;
            if (uVar3 == 0) {
              if (param_1[6] != iVar1) {
                if ((*(byte *)((int)param_1 + 6) & 0x40) != 0) {
                  iVar2 = FUN_08002842(*(undefined1 *)(*param_1 + 1),param_1 + 10,param_1[6],1);
                  if (iVar2 != 0) {
                    *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                    return 1;
                  }
                  *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
                }
                iVar2 = FUN_08002772(*(undefined1 *)(*param_1 + 1),param_1 + 10,iVar1,1);
                if (iVar2 != 0) {
                  *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                  return 1;
                }
              }
              param_1[6] = iVar1;
              goto LAB_0800562a;
            }
            if ((uint)*(byte *)(*param_1 + 2) < uVar4 + uVar3) {
              uVar3 = *(byte *)(*param_1 + 2) - uVar4;
            }
            iVar2 = FUN_08002772(*(undefined1 *)(*param_1 + 1),param_2,iVar1,uVar3 & 0xff);
            if (iVar2 != 0) {
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
              return 1;
            }
            if (((*(byte *)((int)param_1 + 6) & 0x40) != 0) && ((uint)(param_1[6] - iVar1) < uVar3))
            {
              FUN_080043bc(param_2 + (param_1[6] - iVar1) * 0x200,param_1 + 10,0x200);
            }
            uVar3 = uVar3 << 9;
          }
          else {
LAB_0800562a:
            uVar3 = 0x200 - (*(ushort *)(param_1 + 2) & 0x1ff);
            if (param_3 < uVar3) {
              uVar3 = param_3;
            }
            FUN_080043bc(param_2,(int)param_1 + (*(ushort *)(param_1 + 2) & 0x1ff) + 0x28,uVar3);
          }
          param_2 = param_2 + uVar3;
          param_1[2] = param_1[2] + uVar3;
          *param_4 = *param_4 + uVar3;
        }
        iVar1 = 0;
      }
    }
    else {
      iVar1 = 2;
    }
  }
  return iVar1;
}



/* FUNCTION 08005680 FUN_08005680 SIZE 542 */

int FUN_08005680(int *param_1,int param_2,uint param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int local_3c;
  
  *param_4 = 0;
  iVar1 = FUN_080052d8(param_1);
  if (iVar1 == 0) {
    if ((*(byte *)((int)param_1 + 6) & 0x80) == 0) {
      if ((*(byte *)((int)param_1 + 6) & 2) == 0) {
        iVar1 = 7;
      }
      else {
        local_3c = param_2;
        if (param_1[3] + param_3 < (uint)param_1[3]) {
          param_3 = 0;
        }
        for (; param_3 != 0; param_3 = param_3 - uVar3) {
          if ((*(ushort *)(param_1 + 2) & 0x1ff) == 0) {
            uVar4 = *(byte *)(*param_1 + 2) - 1 & (uint)param_1[2] >> 9 & 0xff;
            if (uVar4 == 0) {
              if (param_1[2] == 0) {
                iVar1 = param_1[4];
                if (iVar1 == 0) {
                  iVar1 = FUN_0800480c(*param_1,0);
                  param_1[4] = iVar1;
                }
              }
              else if (param_1[9] == 0) {
                iVar1 = FUN_0800480c(*param_1,param_1[5]);
              }
              else {
                iVar1 = FUN_080048d6(param_1,param_1[2]);
              }
              if (iVar1 == 0) break;
              if (iVar1 == 1) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 2;
              }
              if (iVar1 == -1) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 1;
              }
              param_1[5] = iVar1;
            }
            if ((*(byte *)((int)param_1 + 6) & 0x40) != 0) {
              iVar1 = FUN_08002842(*(undefined1 *)(*param_1 + 1),param_1 + 10,param_1[6],1);
              if (iVar1 != 0) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 1;
              }
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
            }
            iVar1 = FUN_08004570(*param_1,param_1[5]);
            if (iVar1 == 0) {
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
              return 2;
            }
            iVar1 = iVar1 + uVar4;
            uVar3 = param_3 >> 9;
            if (uVar3 == 0) {
              if (((param_1[6] != iVar1) && ((uint)param_1[2] < (uint)param_1[3])) &&
                 (iVar2 = FUN_08002772(*(undefined1 *)(*param_1 + 1),param_1 + 10,iVar1,1),
                 iVar2 != 0)) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                return 1;
              }
              param_1[6] = iVar1;
              goto LAB_08005838;
            }
            if ((uint)*(byte *)(*param_1 + 2) < uVar4 + uVar3) {
              uVar3 = *(byte *)(*param_1 + 2) - uVar4;
            }
            iVar2 = FUN_08002842(*(undefined1 *)(*param_1 + 1),local_3c,iVar1,uVar3 & 0xff);
            if (iVar2 != 0) {
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
              return 1;
            }
            if ((uint)(param_1[6] - iVar1) < uVar3) {
              FUN_080043bc(param_1 + 10,local_3c + (param_1[6] - iVar1) * 0x200,0x200);
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
            }
            uVar3 = uVar3 << 9;
          }
          else {
LAB_08005838:
            uVar3 = 0x200 - (*(ushort *)(param_1 + 2) & 0x1ff);
            if (param_3 < uVar3) {
              uVar3 = param_3;
            }
            FUN_080043bc((int)param_1 + (*(ushort *)(param_1 + 2) & 0x1ff) + 0x28,local_3c,uVar3);
            *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x40;
          }
          local_3c = local_3c + uVar3;
          param_1[2] = param_1[2] + uVar3;
          *param_4 = *param_4 + uVar3;
        }
        if ((uint)param_1[3] < (uint)param_1[2]) {
          param_1[3] = param_1[2];
        }
        *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x20;
        iVar1 = 0;
      }
    }
    else {
      iVar1 = 2;
    }
  }
  return iVar1;
}



/* FUNCTION 0800589e FUN_0800589e SIZE 176 */

int FUN_0800589e(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_080052d8(param_1);
  if ((iVar1 == 0) && ((*(byte *)((int)param_1 + 6) & 0x20) != 0)) {
    if ((*(byte *)((int)param_1 + 6) & 0x40) != 0) {
      iVar1 = FUN_08002842(*(undefined1 *)(*param_1 + 1),param_1 + 10,param_1[6],1);
      if (iVar1 != 0) {
        return 1;
      }
      *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
    }
    iVar1 = FUN_08004476(*param_1,param_1[7]);
    if (iVar1 == 0) {
      iVar1 = param_1[8];
      *(byte *)(iVar1 + 0xb) = *(byte *)(iVar1 + 0xb) | 0x20;
      *(char *)(iVar1 + 0x1c) = (char)param_1[3];
      *(char *)(iVar1 + 0x1d) = (char)((uint)param_1[3] >> 8);
      *(char *)(iVar1 + 0x1e) = (char)((uint)param_1[3] >> 0x10);
      *(char *)(iVar1 + 0x1f) = (char)((uint)param_1[3] >> 0x18);
      FUN_08004b2e(iVar1,param_1[4]);
      uVar2 = FUN_08002990();
      *(char *)(iVar1 + 0x16) = (char)uVar2;
      *(char *)(iVar1 + 0x17) = (char)((uint)uVar2 >> 8);
      *(char *)(iVar1 + 0x18) = (char)((uint)uVar2 >> 0x10);
      *(char *)(iVar1 + 0x19) = (char)((uint)uVar2 >> 0x18);
      *(undefined1 *)(iVar1 + 0x12) = 0;
      *(undefined1 *)(iVar1 + 0x13) = 0;
      *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xdf;
      *(undefined1 *)(*param_1 + 4) = 1;
      iVar1 = FUN_080044a8(*param_1);
    }
  }
  return iVar1;
}



/* FUNCTION 0800594e Boot_FS_Close SIZE 22 */

/* Closes update file */

int Boot_FS_Close(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = FUN_0800589e(param_1);
  if (iVar1 == 0) {
    *param_1 = 0;
  }
  return iVar1;
}



/* FUNCTION 08005964 FUN_08005964 SIZE 732 */

undefined8 FUN_08005964(int *param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int local_28;
  
  uVar10 = param_2;
  local_28 = FUN_080052d8(param_1);
  if (local_28 == 0) {
    if ((*(byte *)((int)param_1 + 6) & 0x80) == 0) {
      if (param_1[9] == 0) {
        if (((uint)param_1[3] < param_2) && ((*(byte *)((int)param_1 + 6) & 2) == 0)) {
          param_2 = param_1[3];
        }
        iVar3 = param_1[2];
        iVar2 = 0;
        param_1[2] = 0;
        if (param_2 != 0) {
          bVar1 = *(byte *)(*param_1 + 2);
          uVar4 = (uint)bVar1 * 0x200;
          if ((iVar3 == 0) || ((param_2 - 1) / uVar4 < (iVar3 - 1U) / uVar4)) {
            uVar7 = param_1[4];
            if (uVar7 == 0) {
              uVar7 = FUN_0800480c(*param_1,0);
              if (uVar7 == 1) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 2;
                goto LAB_0800597a;
              }
              if (uVar7 == 0xffffffff) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 1;
                goto LAB_0800597a;
              }
              param_1[4] = uVar7;
            }
            param_1[5] = uVar7;
          }
          else {
            param_1[2] = iVar3 - 1U & ~(uVar4 - 1);
            param_2 = param_2 - param_1[2];
            uVar7 = param_1[5];
          }
          if (uVar7 != 0) {
            for (; uVar4 < param_2; param_2 = param_2 + (uint)bVar1 * -0x200) {
              if ((*(byte *)((int)param_1 + 6) & 2) == 0) {
                uVar7 = FUN_0800458a(*param_1,uVar7);
              }
              else {
                uVar7 = FUN_0800480c(*param_1,uVar7);
                if (uVar7 == 0) {
                  param_2 = uVar4;
                  break;
                }
              }
              if (uVar7 == 0xffffffff) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 1;
                goto LAB_0800597a;
              }
              if ((uVar7 < 2) || (*(uint *)(*param_1 + 0x18) <= uVar7)) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 2;
                goto LAB_0800597a;
              }
              param_1[5] = uVar7;
              param_1[2] = param_1[2] + uVar4;
            }
            param_1[2] = param_1[2] + param_2;
            if ((param_2 & 0x1ff) != 0) {
              iVar2 = FUN_08004570(*param_1,uVar7);
              if (iVar2 == 0) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 2;
                goto LAB_0800597a;
              }
              iVar2 = iVar2 + (param_2 >> 9);
            }
          }
        }
        if (((*(ushort *)(param_1 + 2) & 0x1ff) != 0) && (param_1[6] != iVar2)) {
          if ((*(byte *)((int)param_1 + 6) & 0x40) != 0) {
            iVar3 = FUN_08002842(*(undefined1 *)(*param_1 + 1),param_1 + 10,param_1[6],1,uVar10,
                                 param_3);
            if (iVar3 != 0) {
              *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
              local_28 = 1;
              goto LAB_0800597a;
            }
            *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
          }
          iVar3 = FUN_08002772(*(undefined1 *)(*param_1 + 1),param_1 + 10,iVar2,1);
          if (iVar3 != 0) {
            *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
            local_28 = 1;
            goto LAB_0800597a;
          }
          param_1[6] = iVar2;
        }
        if ((uint)param_1[3] < (uint)param_1[2]) {
          param_1[3] = param_1[2];
          *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x20;
        }
      }
      else if (param_2 == 0xffffffff) {
        puVar6 = (uint *)param_1[9] + 1;
        uVar8 = *(uint *)param_1[9];
        uVar7 = 2;
        uVar4 = param_1[4];
        if (uVar4 != 0) {
          do {
            uVar9 = 0;
            uVar7 = uVar7 + 2;
            uVar10 = uVar4;
            do {
              uVar9 = uVar9 + 1;
              uVar11 = uVar4;
              uVar4 = FUN_0800458a(*param_1,uVar4);
              if (uVar4 < 2) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 2;
                goto LAB_0800597a;
              }
              if (uVar4 == 0xffffffff) {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 1;
                goto LAB_0800597a;
              }
            } while (uVar4 == uVar11 + 1);
            if (uVar7 <= uVar8) {
              puVar5 = puVar6 + 1;
              *puVar6 = uVar9;
              puVar6 = puVar6 + 2;
              *puVar5 = uVar10;
            }
          } while (uVar4 < *(uint *)(*param_1 + 0x18));
        }
        *(uint *)param_1[9] = uVar7;
        if (uVar8 < uVar7) {
          local_28 = 0x11;
        }
        else {
          *puVar6 = 0;
        }
      }
      else {
        if ((uint)param_1[3] < param_2) {
          param_2 = param_1[3];
        }
        param_1[2] = param_2;
        if (param_2 != 0) {
          iVar2 = FUN_080048d6(param_1,param_2 - 1);
          param_1[5] = iVar2;
          iVar2 = FUN_08004570(*param_1,param_1[5]);
          if (iVar2 == 0) {
            *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
            local_28 = 2;
          }
          else {
            iVar2 = iVar2 + (*(byte *)(*param_1 + 2) - 1 & param_2 - 1 >> 9);
            if (((*(ushort *)(param_1 + 2) & 0x1ff) != 0) && (param_1[6] != iVar2)) {
              if ((*(byte *)((int)param_1 + 6) & 0x40) != 0) {
                iVar3 = FUN_08002842(*(undefined1 *)(*param_1 + 1),param_1 + 10,param_1[6],1,uVar10,
                                     param_3);
                if (iVar3 != 0) {
                  *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                  local_28 = 1;
                  goto LAB_0800597a;
                }
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) & 0xbf;
              }
              iVar3 = FUN_08002772(*(undefined1 *)(*param_1 + 1),param_1 + 10,iVar2,1);
              if (iVar3 == 0) {
                param_1[6] = iVar2;
              }
              else {
                *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
                local_28 = 1;
              }
            }
          }
        }
      }
    }
    else {
      local_28 = 2;
    }
  }
LAB_0800597a:
  return CONCAT44(uVar10,local_28);
}



/* FUNCTION 08005c40 FUN_08005c40 SIZE 112 */

int FUN_08005c40(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_24 [12];
  int *piStack_18;
  undefined4 local_14;
  
  if (param_1 == (int *)0x0) {
    iVar1 = 9;
  }
  else {
    piStack_18 = param_1;
    local_14 = param_2;
    iVar1 = FUN_08004f2c(&local_14,param_1,0);
    iVar3 = *param_1;
    if (iVar1 == 0) {
      param_1[6] = (int)auStack_24;
      iVar1 = FUN_08004e10(param_1,local_14);
      if (iVar1 == 0) {
        if (param_1[5] != 0) {
          if ((*(byte *)(param_1[5] + 0xb) & 0x10) == 0) {
            iVar1 = 5;
          }
          else {
            iVar2 = FUN_08004b0e(iVar3,param_1[5]);
            param_1[2] = iVar2;
          }
        }
        if (iVar1 == 0) {
          *(undefined2 *)(param_1 + 1) = *(undefined2 *)(iVar3 + 6);
          iVar1 = FUN_08004908(param_1,0);
        }
      }
      if (iVar1 == 4) {
        iVar1 = 5;
      }
      if (iVar1 != 0) {
        *param_1 = 0;
      }
    }
    else {
      *param_1 = 0;
    }
  }
  return iVar1;
}



/* FUNCTION 08005cb0 FUN_08005cb0 SIZE 88 */

undefined8 FUN_08005cb0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  iStack_20 = param_2;
  uStack_1c = param_3;
  uStack_18 = param_4;
  iVar1 = FUN_080052d8(param_1);
  if (iVar1 == 0) {
    if (param_2 == 0) {
      iVar1 = FUN_08004908(param_1,0);
    }
    else {
      *(int **)(param_1 + 0x18) = &iStack_20;
      iVar1 = FUN_08004b9a(param_1,0);
      if (iVar1 == 4) {
        *(undefined4 *)(param_1 + 0x10) = 0;
        iVar1 = 0;
      }
      if (iVar1 == 0) {
        FUN_08004d78(param_1,param_2);
        iVar1 = FUN_080049a4(param_1,0);
        if (iVar1 == 4) {
          *(undefined4 *)(param_1 + 0x10) = 0;
          iVar1 = 0;
        }
      }
    }
  }
  return CONCAT44(iStack_20,iVar1);
}



/* FUNCTION 08005d42 FUN_08005d42 SIZE 260 */

int FUN_08005d42(undefined4 param_1,int *param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  short *psVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_38;
  int local_34;
  undefined4 uStack_30;
  int *piStack_2c;
  undefined4 *local_28;
  
  uStack_30 = param_1;
  piStack_2c = param_2;
  local_28 = param_3;
  local_34 = FUN_08004f2c(&uStack_30,param_3,0);
  pcVar3 = (char *)*local_28;
  if (local_34 == 0) {
    if (*(int *)(pcVar3 + 0x18) - 2U < *(uint *)(pcVar3 + 0x10)) {
      cVar1 = *pcVar3;
      iVar5 = 0;
      if (cVar1 == '\x01') {
        uVar6 = 2;
        do {
          iVar2 = FUN_0800458a(pcVar3,uVar6);
          if (iVar2 == -1) {
            local_34 = 1;
            break;
          }
          if (iVar2 == 1) {
            local_34 = 2;
            break;
          }
          if (iVar2 == 0) {
            iVar5 = iVar5 + 1;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(uint *)(pcVar3 + 0x18));
      }
      else {
        iVar2 = *(int *)(pcVar3 + 0x18);
        local_38 = *(int *)(pcVar3 + 0x24);
        iVar7 = 0;
        psVar4 = (short *)0x0;
        do {
          if (iVar7 == 0) {
            local_34 = FUN_08004476(pcVar3,local_38);
            if (local_34 != 0) break;
            psVar4 = (short *)(pcVar3 + 0x34);
            iVar7 = 0x200;
            local_38 = local_38 + 1;
          }
          if (cVar1 == '\x02') {
            if (*psVar4 == 0) {
              iVar5 = iVar5 + 1;
            }
            psVar4 = psVar4 + 1;
            iVar7 = iVar7 + -2;
          }
          else {
            if ((((*(byte *)((int)psVar4 + 3) & 0xf) == 0 && (char)psVar4[1] == '\0') &&
                *(char *)((int)psVar4 + 1) == '\0') && (char)*psVar4 == '\0') {
              iVar5 = iVar5 + 1;
            }
            psVar4 = psVar4 + 2;
            iVar7 = iVar7 + -4;
          }
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      *(int *)(pcVar3 + 0x10) = iVar5;
      if (cVar1 == '\x03') {
        pcVar3[5] = '\x01';
      }
      *param_2 = iVar5;
    }
    else {
      *param_2 = *(int *)(pcVar3 + 0x10);
    }
  }
  return local_34;
}



/* FUNCTION 08005e46 FUN_08005e46 SIZE 154 */

uint FUN_08005e46(int *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_080052d8(param_1);
  if (uVar1 == 0) {
    if ((*(byte *)((int)param_1 + 6) & 0x80) == 0) {
      if ((*(byte *)((int)param_1 + 6) & 2) == 0) {
        uVar1 = 7;
      }
    }
    else {
      uVar1 = 2;
    }
  }
  if (uVar1 == 0) {
    if ((uint)param_1[2] < (uint)param_1[3]) {
      param_1[3] = param_1[2];
      *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x20;
      if (param_1[2] == 0) {
        uVar1 = FUN_080047a4(*param_1,param_1[4]);
        param_1[4] = 0;
      }
      else {
        uVar2 = FUN_0800458a(*param_1,param_1[5]);
        uVar1 = (uint)(uVar2 == 0xffffffff);
        if (uVar2 == 1) {
          uVar1 = 2;
        }
        if (((uVar1 == 0) && (uVar2 < *(uint *)(*param_1 + 0x18))) &&
           (uVar1 = FUN_0800466e(*param_1,param_1[5],0xfffffff), uVar1 == 0)) {
          uVar1 = FUN_080047a4(*param_1,uVar2);
        }
      }
    }
    if (uVar1 != 0) {
      *(byte *)((int)param_1 + 6) = *(byte *)((int)param_1 + 6) | 0x80;
    }
  }
  return uVar1;
}



/* FUNCTION 08005ee0 FUN_08005ee0 SIZE 170 */

int FUN_08005ee0(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 auStack_58 [12];
  undefined1 auStack_4c [8];
  uint local_44;
  undefined4 local_30 [5];
  int local_1c;
  undefined1 *local_18;
  undefined4 local_14;
  
  local_14 = param_1;
  iVar1 = FUN_08004f2c(&local_14,local_30,1);
  if (iVar1 == 0) {
    local_18 = auStack_58;
    iVar1 = FUN_08004e10(local_30,local_14);
    if (iVar1 == 0) {
      if (local_1c == 0) {
        iVar1 = 6;
      }
      else if ((*(byte *)(local_1c + 0xb) & 1) != 0) {
        iVar1 = 7;
      }
      uVar2 = FUN_08004b0e(local_30[0],local_1c);
      if ((iVar1 == 0) && ((*(byte *)(local_1c + 0xb) & 0x10) != 0)) {
        if (uVar2 < 2) {
          iVar1 = 2;
        }
        else {
          FUN_080043bc(auStack_4c,local_30,0x1c);
          local_44 = uVar2;
          iVar1 = FUN_08004908(auStack_4c,2);
          if (iVar1 == 0) {
            iVar1 = FUN_08004b9a(auStack_4c,0);
            if (iVar1 == 0) {
              iVar1 = 7;
            }
            if (iVar1 == 4) {
              iVar1 = 0;
            }
          }
        }
      }
      if ((iVar1 == 0) && (iVar1 = FUN_08004c42(local_30), iVar1 == 0)) {
        if (uVar2 != 0) {
          iVar1 = FUN_080047a4(local_30[0],uVar2);
        }
        if (iVar1 == 0) {
          iVar1 = FUN_080044a8(local_30[0]);
        }
      }
    }
  }
  return iVar1;
}



/* FUNCTION 08005f8a FUN_08005f8a SIZE 352 */

int FUN_08005f8a(undefined4 param_1)

{
  char cVar3;
  char cVar2;
  char cVar1;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  char cVar10;
  bool bVar11;
  undefined1 auStack_4c [12];
  char *local_40 [2];
  int local_38;
  int local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  
  local_24 = param_1;
  uVar5 = FUN_08002990();
  iVar6 = FUN_08004f2c(&local_24,local_40,1);
  bVar11 = iVar6 == 0;
  do {
    if (!bVar11) {
      return iVar6;
    }
    local_28 = auStack_4c;
    iVar6 = FUN_08004e10(local_40,local_24);
    if (iVar6 == 0) {
      iVar6 = 8;
    }
    bVar11 = iVar6 == 4;
  } while (!bVar11);
  iVar6 = FUN_0800480c(local_40[0],0);
  iVar9 = 0;
  if (iVar6 == 0) {
    iVar9 = 7;
  }
  if (iVar6 == 1) {
    iVar9 = 2;
  }
  if (iVar6 == -1) {
    iVar9 = 1;
  }
  if (iVar9 == 0) {
    iVar9 = FUN_08004424(local_40[0]);
  }
  cVar1 = (char)((uint)uVar5 >> 8);
  cVar2 = (char)((uint)uVar5 >> 0x10);
  cVar3 = (char)((uint)uVar5 >> 0x18);
  if (iVar9 == 0) {
    iVar7 = FUN_08004570(local_40[0],iVar6);
    pcVar4 = local_40[0];
    pcVar8 = local_40[0] + 0x34;
    FUN_080043d6(pcVar8,0,0x200);
    FUN_080043d6(pcVar8,0x20,0xb);
    *pcVar8 = '.';
    pcVar4[0x3f] = '\x10';
    pcVar4[0x4a] = (char)uVar5;
    pcVar4[0x4b] = cVar1;
    pcVar4[0x4c] = cVar2;
    pcVar4[0x4d] = cVar3;
    FUN_08004b2e(pcVar8,iVar6);
    FUN_080043bc(pcVar4 + 0x54,pcVar8,0x20);
    pcVar4[0x55] = '.';
    if ((*local_40[0] == '\x03') && (*(int *)(local_40[0] + 0x28) == local_38)) {
      local_38 = 0;
    }
    FUN_08004b2e(pcVar4 + 0x54,local_38);
    for (cVar10 = local_40[0][2]; cVar10 != '\0'; cVar10 = cVar10 + -1) {
      *(int *)(local_40[0] + 0x30) = iVar7;
      iVar7 = iVar7 + 1;
      local_40[0][4] = '\x01';
      iVar9 = FUN_08004424(local_40[0]);
      if (iVar9 != 0) break;
      FUN_080043d6(pcVar8,0,0x200);
    }
  }
  if (iVar9 == 0) {
    iVar9 = FUN_08004c08(local_40);
  }
  if (iVar9 == 0) {
    *(undefined1 *)(local_2c + 0xb) = 0x10;
    *(char *)(local_2c + 0x16) = (char)uVar5;
    *(char *)(local_2c + 0x17) = cVar1;
    *(char *)(local_2c + 0x18) = cVar2;
    *(char *)(local_2c + 0x19) = cVar3;
    FUN_08004b2e(local_2c,iVar6);
    local_40[0][4] = '\x01';
    iVar9 = FUN_080044a8(local_40[0]);
  }
  else {
    FUN_080047a4(local_40[0],iVar6);
  }
  return iVar9;
}



/* FUNCTION 080060ea FUN_080060ea SIZE 84 */

int FUN_080060ea(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  undefined1 auStack_48 [12];
  int local_3c [5];
  int local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  local_20 = param_1;
  uStack_1c = param_2;
  uStack_18 = param_3;
  iVar2 = FUN_08004f2c(&local_20,local_3c,1);
  if (iVar2 == 0) {
    local_24 = auStack_48;
    iVar2 = FUN_08004e10(local_3c,local_20);
    if (iVar2 == 0) {
      if (local_28 == 0) {
        iVar2 = 6;
      }
      else {
        bVar1 = (byte)param_3 & 0x27;
        *(byte *)(local_28 + 0xb) = (byte)param_2 & bVar1 | *(byte *)(local_28 + 0xb) & ~bVar1;
        *(undefined1 *)(local_3c[0] + 4) = 1;
        iVar2 = FUN_080044a8(local_3c[0]);
      }
    }
  }
  return iVar2;
}



/* FUNCTION 0800613e FUN_0800613e SIZE 86 */

int FUN_0800613e(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_40 [12];
  int local_34 [5];
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  int iStack_14;
  
  local_18 = param_1;
  iStack_14 = param_2;
  iVar1 = FUN_08004f2c(&local_18,local_34,1);
  if (iVar1 == 0) {
    local_1c = auStack_40;
    iVar1 = FUN_08004e10(local_34,local_18);
    if (iVar1 == 0) {
      if (local_20 == 0) {
        iVar1 = 6;
      }
      else {
        *(undefined1 *)(local_20 + 0x16) = *(undefined1 *)(param_2 + 6);
        *(char *)(local_20 + 0x17) = (char)((ushort)*(undefined2 *)(param_2 + 6) >> 8);
        *(undefined1 *)(local_20 + 0x18) = *(undefined1 *)(param_2 + 4);
        *(char *)(local_20 + 0x19) = (char)((ushort)*(undefined2 *)(param_2 + 4) >> 8);
        *(undefined1 *)(local_34[0] + 4) = 1;
        iVar1 = FUN_080044a8(local_34[0]);
      }
    }
  }
  return iVar1;
}



/* FUNCTION 08006194 FUN_08006194 SIZE 276 */

int FUN_08006194(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_7c [12];
  byte local_70 [2];
  undefined1 auStack_6e [22];
  char *local_58 [2];
  int local_50;
  int local_44;
  char *local_3c [2];
  int local_34;
  int local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  local_20 = param_1;
  uStack_1c = param_2;
  iVar1 = FUN_08004f2c(&local_20,local_3c,1);
  if (iVar1 == 0) {
    local_58[0] = local_3c[0];
    local_24 = auStack_7c;
    iVar1 = FUN_08004e10(local_3c,local_20);
    if (iVar1 == 0) {
      if (local_28 == 0) {
        iVar1 = 4;
      }
      else {
        FUN_080043bc(local_70,local_28 + 0xb,0x15);
        FUN_080043bc(local_58,local_3c,0x1c);
        iVar1 = FUN_08004e10(local_58,param_2);
        if (iVar1 == 0) {
          iVar1 = 8;
        }
        if ((iVar1 == 4) && (iVar1 = FUN_08004c08(local_58), iVar1 == 0)) {
          FUN_080043bc(local_44 + 0xd,auStack_6e,0x13);
          *(byte *)(local_44 + 0xb) = local_70[0] | 0x20;
          local_3c[0][4] = '\x01';
          if ((local_34 != local_50) && ((*(byte *)(local_44 + 0xb) & 0x10) != 0)) {
            uVar2 = FUN_08004b0e(local_3c[0],local_44);
            iVar1 = FUN_08004570(local_3c[0],uVar2);
            if (iVar1 == 0) {
              iVar1 = 2;
            }
            else {
              iVar1 = FUN_08004476(local_3c[0],iVar1);
              if ((iVar1 == 0) && (local_3c[0][0x55] == '.')) {
                if ((*local_3c[0] == '\x03') && (local_50 == *(int *)(local_3c[0] + 0x28))) {
                  local_50 = 0;
                }
                FUN_08004b2e(local_3c[0] + 0x54,local_50);
                local_3c[0][4] = '\x01';
              }
            }
          }
          if ((iVar1 == 0) && (iVar1 = FUN_08004c42(local_3c), iVar1 == 0)) {
            iVar1 = FUN_080044a8(local_3c[0]);
          }
        }
      }
    }
  }
  return iVar1;
}



/* FUNCTION 080062a8 FUN_080062a8 SIZE 1518 */

undefined4 FUN_080062a8(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  bool bVar4;
  undefined1 uVar9;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined1 *puVar10;
  uint uVar11;
  int iVar12;
  undefined1 *puVar13;
  uint local_64;
  int local_60;
  uint local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_38;
  uint local_34;
  int local_30;
  int local_2c;
  uint uStack_28;
  
  if (param_1 < 2) {
    if (param_2 < 2) {
      if ((param_3 - 1 & param_3) == 0) {
        puVar13 = *(undefined1 **)(DAT_080066d0 + param_1 * 4);
        if (puVar13 == (undefined1 *)0x0) {
          uVar5 = 0xc;
        }
        else {
          *puVar13 = 0;
          local_40 = 0;
          local_3c = param_1;
          local_30 = param_1;
          local_2c = param_2;
          uStack_28 = param_3;
          uVar6 = FUN_080026fc(param_1);
          if ((uVar6 & 1) == 0) {
            if ((uVar6 & 4) == 0) {
              iVar7 = FUN_0800290c(local_3c,1,&local_5c);
              if ((iVar7 == 0) && (0x7f < local_5c)) {
                if (local_2c == 0) {
                  iVar7 = 0x3f;
                }
                else {
                  iVar7 = 0;
                }
                local_5c = local_5c - iVar7;
                if (param_3 == 0) {
                  local_44 = local_5c / 2000;
                  iVar12 = 0;
                  while (local_44 < *(ushort *)(DAT_080066d4 + iVar12 * 2)) {
                    iVar12 = iVar12 + 1;
                  }
                  param_3 = (uint)*(ushort *)(DAT_080066d8 + iVar12 * 2);
                }
                param_3 = param_3 >> 9;
                if (param_3 == 0) {
                  param_3 = 1;
                }
                if (0x80 < param_3) {
                  param_3 = 0x80;
                }
                uVar6 = local_5c / param_3;
                iVar12 = 1;
                if (0xff5 < uVar6) {
                  iVar12 = 2;
                }
                if (0xfff5 < uVar6) {
                  iVar12 = 3;
                }
                if (iVar12 == 3) {
                  uVar6 = uVar6 * 4 + 0x207;
                  local_60 = 0x20;
                  local_64 = 0;
                }
                else {
                  if (iVar12 == 1) {
                    iVar8 = (uVar6 * 3 + 1 >> 1) + 3;
                  }
                  else {
                    iVar8 = uVar6 * 2 + 4;
                  }
                  uVar6 = iVar8 + 0x1ff;
                  local_60 = 1;
                  local_64 = 0x20;
                }
                uVar6 = uVar6 >> 9;
                local_50 = local_60 + iVar7;
                local_54 = local_50 + uVar6;
                local_58 = local_54 + local_64;
                if (local_5c < (local_58 + param_3) - iVar7) {
                  uVar5 = 0xe;
                }
                else {
                  iVar8 = FUN_0800290c(local_3c,3,&local_48);
                  if (((iVar8 != 0) || (local_48 == 0)) || (0x8000 < local_48)) {
                    local_48 = 1;
                  }
                  local_48 = ((local_58 + local_48) - 1 & ~(local_48 - 1)) - local_58;
                  if (iVar12 == 3) {
                    local_60 = local_60 + local_48;
                    local_50 = local_50 + local_48;
                  }
                  else {
                    uVar6 = uVar6 + local_48;
                  }
                  uVar11 = (((local_5c - local_60) - uVar6) - local_64) / param_3;
                  if (((iVar12 == 2) && (uVar11 < 0xff6)) || ((iVar12 == 3 && (uVar11 < 0xfff6)))) {
                    uVar5 = 0xe;
                  }
                  else {
                    if (iVar12 == 1) {
                      local_38 = 1;
                    }
                    else if (iVar12 == 2) {
                      if (local_5c < 0x10000) {
                        local_38 = 4;
                      }
                      else {
                        local_38 = 6;
                      }
                    }
                    else {
                      local_38 = 0xc;
                    }
                    if (local_2c == 0) {
                      FUN_080043d6(puVar13 + 0x34,0,0x200);
                      puVar13[499] = 1;
                      puVar13[500] = 1;
                      puVar13[0x1f5] = 0;
                      puVar13[0x1f6] = (char)local_38;
                      puVar13[0x1f7] = 0xfe;
                      local_48 = (local_5c + iVar7) / 0x3ec1;
                      puVar13[0x1f8] = (byte)(local_48 >> 2) | 0x3f;
                      puVar13[0x1f9] = (char)local_48;
                      puVar13[0x1fa] = 0x3f;
                      puVar13[0x1fb] = 0;
                      puVar13[0x1fc] = 0;
                      puVar13[0x1fd] = 0;
                      puVar13[0x1fe] = (char)local_5c;
                      puVar13[0x1ff] = (char)(local_5c >> 8);
                      puVar13[0x200] = (char)(local_5c >> 0x10);
                      puVar13[0x201] = (char)(local_5c >> 0x18);
                      puVar13[0x232] = 0x55;
                      puVar13[0x233] = 0xaa;
                      iVar8 = FUN_08002842(local_3c,puVar13 + 0x34,0,1);
                      if (iVar8 != 0) {
                        return 1;
                      }
                      local_34 = 0xf8;
                    }
                    else {
                      local_34 = 0xf0;
                    }
                    puVar10 = puVar13 + 0x34;
                    FUN_080043d6(puVar10,0,0x200);
                    FUN_080043bc(puVar10,&DAT_080066dc,0xb);
                    puVar13[0x3f] = 0;
                    puVar13[0x40] = 2;
                    puVar13[0x41] = (char)param_3;
                    puVar13[0x42] = (char)local_60;
                    puVar13[0x43] = (char)((uint)local_60 >> 8);
                    puVar13[0x44] = 1;
                    if (iVar12 == 3) {
                      uVar9 = 0;
                    }
                    else {
                      uVar9 = 2;
                    }
                    puVar13[0x45] = 0;
                    puVar13[0x46] = uVar9;
                    uVar9 = (undefined1)(local_5c >> 8);
                    if (local_5c < 0x10000) {
                      puVar13[0x47] = (char)local_5c;
                      puVar13[0x48] = uVar9;
                    }
                    else {
                      puVar13[0x54] = (char)local_5c;
                      puVar13[0x55] = uVar9;
                      puVar13[0x56] = (char)(local_5c >> 0x10);
                      puVar13[0x57] = (char)(local_5c >> 0x18);
                    }
                    puVar13[0x49] = (char)local_34;
                    puVar13[0x4c] = 0x3f;
                    puVar13[0x4d] = 0;
                    puVar13[0x4e] = 0xff;
                    puVar13[0x4f] = 0;
                    puVar13[0x50] = (char)iVar7;
                    puVar13[0x51] = 0;
                    puVar13[0x52] = 0;
                    puVar13[0x53] = 0;
                    local_48 = FUN_08002990();
                    uVar9 = (undefined1)(uVar6 >> 8);
                    uVar2 = (undefined1)(local_48 >> 8);
                    uVar3 = (undefined1)(local_48 >> 0x10);
                    uVar1 = (undefined1)(local_48 >> 0x18);
                    if (iVar12 == 3) {
                      puVar13[0x77] = (char)local_48;
                      puVar13[0x78] = uVar2;
                      puVar13[0x79] = uVar3;
                      puVar13[0x7a] = uVar1;
                      puVar13[0x58] = (char)uVar6;
                      puVar13[0x59] = uVar9;
                      puVar13[0x5a] = (char)(uVar6 >> 0x10);
                      puVar13[0x5b] = (char)(uVar6 >> 0x18);
                      puVar13[0x60] = 2;
                      puVar13[0x61] = 0;
                      puVar13[0x62] = 0;
                      puVar13[99] = 0;
                      puVar13[100] = 1;
                      puVar13[0x65] = 0;
                      puVar13[0x66] = 6;
                      puVar13[0x67] = 0;
                      puVar13[0x74] = 0x80;
                      puVar13[0x76] = 0x29;
                      FUN_080043bc(puVar13 + 0x7b,"NO NAME    FAT32   ",0x13);
                    }
                    else {
                      puVar13[0x5b] = (char)local_48;
                      puVar13[0x5c] = uVar2;
                      puVar13[0x5d] = uVar3;
                      puVar13[0x5e] = uVar1;
                      puVar13[0x4a] = (char)uVar6;
                      puVar13[0x4b] = uVar9;
                      puVar13[0x58] = 0x80;
                      puVar13[0x5a] = 0x29;
                      FUN_080043bc(puVar13 + 0x5f,"NO NAME    FAT     ",0x13);
                    }
                    puVar13[0x232] = 0x55;
                    puVar13[0x233] = 0xaa;
                    iVar8 = FUN_08002842(local_3c,puVar10,iVar7,1);
                    if (iVar8 == 0) {
                      if (iVar12 == 3) {
                        FUN_08002842(local_3c,puVar10,iVar7 + 6,1);
                      }
                      local_4c = local_50;
                      bVar4 = false;
                      while (!bVar4) {
                        FUN_080043d6(puVar10,0,0x200);
                        iVar8 = local_4c;
                        if (iVar12 == 3) {
                          local_48 = local_34 | 0xffffff00;
                          *puVar10 = (char)local_34;
                          puVar13[0x35] = (char)(local_48 >> 8);
                          puVar13[0x36] = (char)(local_48 >> 0x10);
                          puVar13[0x37] = (char)(local_48 >> 0x18);
                          puVar13[0x38] = 0xff;
                          puVar13[0x39] = 0xff;
                          puVar13[0x3a] = 0xff;
                          puVar13[0x3b] = 0xff;
                          puVar13[0x3c] = 0xff;
                          puVar13[0x3d] = 0xff;
                          puVar13[0x3e] = 0xff;
                          puVar13[0x3f] = 0xf;
                        }
                        else {
                          if (iVar12 == 1) {
                            local_48 = DAT_08006b48;
                          }
                          else {
                            local_48 = 0xffffff00;
                          }
                          local_48 = local_48 | local_34;
                          *puVar10 = (char)local_48;
                          puVar13[0x35] = (char)(local_48 >> 8);
                          puVar13[0x36] = (char)(local_48 >> 0x10);
                          puVar13[0x37] = (char)(local_48 >> 0x18);
                        }
                        local_4c = local_4c + 1;
                        iVar8 = FUN_08002842(local_3c,puVar10,iVar8,1);
                        if (iVar8 != 0) {
                          return 1;
                        }
                        FUN_080043d6(puVar10,0,0x200);
                        for (local_48 = 1; iVar8 = local_4c, local_48 < uVar6;
                            local_48 = local_48 + 1) {
                          local_4c = local_4c + 1;
                          iVar8 = FUN_08002842(local_3c,puVar10,iVar8,1);
                          if (iVar8 != 0) {
                            return 1;
                          }
                        }
                        bVar4 = true;
                      }
                      if (iVar12 == 3) {
                        local_64 = param_3;
                      }
                      do {
                        iVar8 = local_4c;
                        local_4c = local_4c + 1;
                        iVar8 = FUN_08002842(local_3c,puVar10,iVar8,1);
                        if (iVar8 != 0) {
                          return 1;
                        }
                        local_64 = local_64 - 1;
                      } while (local_64 != 0);
                      if (iVar12 == 3) {
                        *puVar10 = 0x52;
                        puVar13[0x35] = 0x52;
                        puVar13[0x36] = 0x61;
                        puVar13[0x37] = 0x41;
                        puVar13[0x218] = 0x72;
                        puVar13[0x219] = 0x72;
                        puVar13[0x21a] = 0x41;
                        puVar13[0x21b] = 0x61;
                        puVar13[0x21c] = (char)(uVar11 - 1);
                        puVar13[0x21d] = (char)(uVar11 - 1 >> 8);
                        puVar13[0x21e] = (char)(uVar11 - 1 >> 0x10);
                        puVar13[0x21f] = (char)(uVar11 - 1 >> 0x18);
                        puVar13[0x220] = 2;
                        puVar13[0x221] = 0;
                        puVar13[0x222] = 0;
                        puVar13[0x223] = 0;
                        puVar13[0x232] = 0x55;
                        puVar13[0x233] = 0xaa;
                        FUN_08002842(local_3c,puVar10,iVar7 + 1,1);
                        FUN_08002842(local_3c,puVar10,iVar7 + 7,1);
                      }
                      iVar7 = FUN_0800290c(local_3c,0);
                      if (iVar7 == 0) {
                        uVar5 = 0;
                      }
                      else {
                        uVar5 = 1;
                      }
                    }
                    else {
                      uVar5 = 1;
                    }
                  }
                }
              }
              else {
                uVar5 = 1;
              }
            }
            else {
              uVar5 = 10;
            }
          }
          else {
            uVar5 = 3;
          }
        }
      }
      else {
        uVar5 = 0x13;
      }
    }
    else {
      uVar5 = 0x13;
    }
  }
  else {
    uVar5 = 0xb;
  }
  return uVar5;
}



/* FUNCTION 080068d6 FUN_080068d6 SIZE 78 */

char * FUN_080068d6(char *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  int local_28;
  undefined4 local_24;
  
  iVar1 = 0;
  pcVar3 = param_1;
  local_28 = param_3;
  local_24 = param_4;
  do {
    if ((param_2 + -1 <= iVar1) || (Boot_FS_Read(param_3,&local_24,1,&local_28), local_28 != 1))
    break;
    pcVar2 = pcVar3 + 1;
    *pcVar3 = (char)local_24;
    iVar1 = iVar1 + 1;
    pcVar3 = pcVar2;
  } while ((char)local_24 != '\n');
  *pcVar3 = '\0';
  if (iVar1 == 0) {
    param_1 = (char *)0x0;
  }
  return param_1;
}



/* FUNCTION 08006924 FUN_08006924 SIZE 38 */

undefined4 FUN_08006924(undefined1 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  undefined1 local_18;
  undefined3 uStack_17;
  int local_14;
  
  _local_18 = CONCAT31((int3)((uint)param_3 >> 8),param_1);
  local_14 = param_4;
  FUN_08005680(param_2,&local_18,1,&local_14);
  uVar1 = 1;
  if (local_14 != 1) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



/* FUNCTION 08006c30 FUN_08006c30 SIZE 14 */

uint FUN_08006c30(uint param_1)

{
  if ((int)param_1 < 0) {
    param_1 = (uint)(short)-(short)param_1;
  }
  return param_1 & 0xffff;
}



/* FUNCTION 08006c3e FUN_08006c3e SIZE 96 */

void FUN_08006c3e(void)

{
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  FUN_080017ba(1);
  local_5c = 0xf;
  local_58 = 0xf;
  local_54 = 5;
  local_50 = 0xf;
  local_4c = 0xf;
  local_48 = 0xf;
  local_44 = 0x10000000;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0x10;
  local_30 = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0x1000;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = &local_5c;
  local_8 = local_c;
  FUN_08000c2e(&local_40);
  FUN_08000d86(0,1);
  return;
}



/* FUNCTION 08006c9e FUN_08006c9e SIZE 358 */

void FUN_08006c9e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = param_3;
  local_c = param_4;
  FUN_08001776(0x5a,1);
  FUN_080013f2(DAT_080070a8,0,0xc);
  FUN_080013f2(DAT_080070a8,1,0xc);
  FUN_080013f2(DAT_080070a8,4,0xc);
  FUN_080013f2(DAT_080070a8,5,0xc);
  FUN_080013f2(DAT_080070a8,7,0xc);
  FUN_080013f2(DAT_080070a8,8,0xc);
  FUN_080013f2(DAT_080070a8,9,0xc);
  FUN_080013f2(DAT_080070a8,10,0xc);
  FUN_080013f2(DAT_080070a8,0xb,0xc);
  FUN_080013f2(DAT_080070a8,0xe,0xc);
  FUN_080013f2(DAT_080070a8,0xf,0xc);
  local_10 = 0xcfb3;
  local_c._0_3_ = 0x202;
  FUN_080012dc(DAT_080070a8,&local_10);
  FUN_080013f2(DAT_080070ac,7,0xc);
  FUN_080013f2(DAT_080070ac,8,0xc);
  FUN_080013f2(DAT_080070ac,9,0xc);
  FUN_080013f2(DAT_080070ac,10,0xc);
  FUN_080013f2(DAT_080070ac,0xb,0xc);
  FUN_080013f2(DAT_080070ac,0xc);
  FUN_080013f2(DAT_080070ac,0xd,0xc);
  FUN_080013f2(DAT_080070ac,0xe,0xc);
  FUN_080013f2(DAT_080070ac,0xf,0xc);
  local_10 = 0xff80;
  local_c = (uint)local_c._3_1_ << 0x18;
  local_c._0_2_ = 0x202;
  FUN_080012dc(DAT_080070ac,&local_10);
  local_10 = 0x800;
  local_c._2_2_ = local_c._2_2_ & 0xff00;
  local_c._0_2_ = 0x201;
  FUN_080012dc(DAT_080070b0,&local_10);
  local_10 = 0x2000;
  local_c._2_2_ = local_c._2_2_ & 0xff00;
  local_c = CONCAT22(local_c._2_2_,0x201);
  FUN_080012dc(DAT_080070a8,&local_10);
  FUN_080013d8(DAT_080070b0,0x800);
  FUN_080013d4(DAT_080070a8,0x2000);
  return;
}



/* FUNCTION 08006e12 FUN_08006e12 SIZE 10 */

undefined2 FUN_08006e12(void)

{
  return *DAT_080070b4;
}



/* FUNCTION 08006e1c FUN_08006e1c SIZE 8 */

undefined2 FUN_08006e1c(void)

{
  return *DAT_080070b4;
}



/* FUNCTION 08006e24 thunk_FUN_08006e38 SIZE 2 */

void thunk_FUN_08006e38(uint param_1)

{
  ushort uVar1;
  
  for (; 0 < (int)param_1; param_1 = param_1 - 1 & 0xffff) {
    for (uVar1 = 0; uVar1 < 500; uVar1 = uVar1 + 1) {
    }
  }
  return;
}



/* FUNCTION 08006e38 FUN_08006e38 SIZE 24 */

void FUN_08006e38(uint param_1)

{
  ushort uVar1;
  
  for (; 0 < (int)param_1; param_1 = param_1 - 1 & 0xffff) {
    for (uVar1 = 0; uVar1 < 500; uVar1 = uVar1 + 1) {
    }
  }
  return;
}



/* FUNCTION 08006e3e FUN_08006e3e SIZE 124 */

undefined4 FUN_08006e3e(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  FUN_080013d8(DAT_080070a8,0x2000);
  thunk_FUN_08006e38(10000);
  FUN_080013d4(DAT_080070a8,0x2000);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0xda);
  FUN_08006e1c();
  iVar1 = FUN_08006e1c();
  FUN_0800bb3e(0xdb);
  FUN_08006e1c();
  iVar2 = FUN_08006e1c();
  FUN_0800bb3e(0xdc);
  FUN_08006e1c();
  iVar3 = FUN_08006e1c();
  if (((iVar1 == 0x40) && (iVar2 == 0)) && (iVar3 == 0)) {
    uVar4 = 0x4802;
  }
  else if (((iVar1 == 0x54) && (iVar2 == 0x80)) && (iVar3 == 0x66)) {
    uVar4 = 0x9488;
  }
  else {
    uVar4 = 0x4802;
  }
  return uVar4;
}



/* FUNCTION 08006eba FUN_08006eba SIZE 1152 */

void FUN_08006eba(void)

{
  uint uVar1;
  
  FUN_080013d4(DAT_080070a8,0x2000);
  thunk_FUN_08006e38(1000);
  FUN_080013d8(DAT_080070a8,0x2000);
  thunk_FUN_08006e38(10000);
  FUN_080013d4(DAT_080070a8,0x2000);
  thunk_FUN_08006e38(1000);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(0x48);
  FUN_0800bb48(2);
  FUN_0800bb48(1);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x80);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(0x48);
  FUN_0800bb48(2);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x90);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(2);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x93);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(0x20);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0x51);
  FUN_0800bb48(0xf0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0x53);
  FUN_0800bb48(0x24);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0xb1);
  FUN_0800bb3e(0xc5);
  FUN_0800bb48(0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0xb0);
  FUN_0800bb3e(0xc4);
  FUN_0800bb48(2);
  FUN_0800bb48(8);
  FUN_0800bb48(5);
  FUN_0800bb48(0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x90);
  FUN_0800bb3e(0xc0);
  FUN_0800bb48(0);
  FUN_0800bb48(0xf);
  FUN_0800bb48(0);
  FUN_0800bb48(0x15);
  FUN_0800bb48(0);
  FUN_0800bb48(0x17);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x82);
  FUN_0800bb3e(0xc5);
  FUN_0800bb48(1);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x90);
  FUN_0800bb3e(0xc5);
  FUN_0800bb48(0x47);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xd8);
  FUN_0800bb48(0x58);
  FUN_0800bb48(0x58);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xd9);
  FUN_0800bb48(0xb0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x91);
  FUN_0800bb3e(0xb3);
  FUN_0800bb48(0xc0);
  FUN_0800bb48(0x25);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x81);
  FUN_0800bb3e(0xc1);
  FUN_0800bb48(0x77);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xe1);
  FUN_0800bb48(0);
  FUN_0800bb48(5);
  FUN_0800bb48(9);
  FUN_0800bb48(4);
  FUN_0800bb48(2);
  FUN_0800bb48(0xb);
  FUN_0800bb48(10);
  FUN_0800bb48(9);
  FUN_0800bb48(5);
  FUN_0800bb48(8);
  FUN_0800bb48(0x10);
  FUN_0800bb48(5);
  FUN_0800bb48(6);
  FUN_0800bb48(0x11);
  FUN_0800bb48(9);
  FUN_0800bb48(1);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xe2);
  FUN_0800bb48(0);
  FUN_0800bb48(5);
  FUN_0800bb48(9);
  FUN_0800bb48(4);
  FUN_0800bb48(2);
  FUN_0800bb48(0xb);
  FUN_0800bb48(10);
  FUN_0800bb48(9);
  FUN_0800bb48(5);
  FUN_0800bb48(8);
  FUN_0800bb48(0x10);
  FUN_0800bb48(5);
  FUN_0800bb48(6);
  FUN_0800bb48(0x11);
  FUN_0800bb48(9);
  FUN_0800bb48(1);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0x80);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(0);
  FUN_0800bb48(0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0);
  FUN_0800bb48(0);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0xff);
  FUN_0800bb48(0xff);
  FUN_0800bb48(0xff);
  FUN_0800bb48(0xff);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x36);
  FUN_0800bb48(0x60);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x3a);
  FUN_0800bb48(5);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x2b);
  FUN_0800bb48(0);
  FUN_0800bb48(0);
  FUN_0800bb48(1);
  FUN_0800bb48(0x3f);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x2a);
  FUN_0800bb48(0);
  FUN_0800bb48(0);
  FUN_0800bb48(1);
  FUN_0800bb48(0xdf);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x11);
  thunk_FUN_08006e38(30000);
  FUN_0800bb3e(0x29);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x2c);
  thunk_FUN_08006e38(500);
  for (uVar1 = 0; uVar1 < 0x25800; uVar1 = uVar1 + 1) {
    FUN_0800bb48(0xffff);
  }
  FUN_080013d4(DAT_08007724,0x800);
  return;
}



/* FUNCTION 0800734a FUN_0800734a SIZE 102 */

void FUN_0800734a(uint param_1,uint param_2,int param_3,int param_4)

{
  FUN_0800bb3e(0x2a);
  FUN_0800bb48((int)param_1 >> 8);
  FUN_0800bb48(param_1 & 0xff);
  FUN_0800bb48(((param_1 + param_3) - 1 & 0xffffff) >> 8);
  FUN_0800bb48((param_1 + param_3) - 1 & 0xff);
  FUN_0800bb3e(0x2b);
  FUN_0800bb48((int)param_2 >> 8);
  FUN_0800bb48(param_2 & 0xff);
  FUN_0800bb48(((param_2 + param_4) - 1 & 0xffffff) >> 8);
  FUN_0800bb48((param_2 + param_4) - 1 & 0xff);
  FUN_0800bb3e(0x2c);
  return;
}



/* FUNCTION 080073b0 FUN_080073b0 SIZE 126 */

void FUN_080073b0(uint param_1,uint param_2,uint param_3,uint param_4,undefined2 param_5)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;
  
  if ((int)param_1 < (int)param_3) {
    uVar3 = param_1;
  }
  else {
    uVar3 = param_3;
  }
  if ((int)param_2 < (int)param_4) {
    uVar4 = param_2;
  }
  else {
    uVar4 = param_4;
  }
  sVar1 = FUN_08006c30((int)(short)((short)param_3 - (short)param_1));
  sVar2 = FUN_08006c30((int)(short)((short)param_4 - (short)param_2));
  FUN_0800734a(uVar3 & 0xffff,uVar4 & 0xffff,sVar1 + 1U,sVar2 + 1U);
  for (uVar5 = 0; uVar5 < (ushort)(sVar2 + 1U); uVar5 = uVar5 + 1) {
    for (uVar6 = 0; uVar6 < (ushort)(sVar1 + 1U); uVar6 = uVar6 + 1) {
      *DAT_08007728 = param_5;
    }
  }
  return;
}



/* FUNCTION 0800742e FUN_0800742e SIZE 514 */

void FUN_0800742e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_080013d8(DAT_0800772c,0x2000,param_3,param_4,param_4);
  thunk_FUN_08006e38(10000);
  FUN_080013d4(DAT_0800772c,0x2000);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0x11);
  thunk_FUN_08006e38(500);
  FUN_0800bb3e(0xe0);
  FUN_0800bb48(0);
  FUN_0800bb48(0xe);
  FUN_0800bb48(0x15);
  FUN_0800bb48(6);
  FUN_0800bb48(0x13);
  FUN_0800bb48(9);
  FUN_0800bb48(0x3a);
  FUN_0800bb48(0xac);
  FUN_0800bb48(0x4f);
  FUN_0800bb48(5);
  FUN_0800bb48(0xd);
  FUN_0800bb48(0xb);
  FUN_0800bb48(0x33);
  FUN_0800bb48(0x3b);
  FUN_0800bb48(0xf);
  FUN_0800bb3e(0xe1);
  FUN_0800bb48(0);
  FUN_0800bb48(0xe);
  FUN_0800bb48(0x16);
  FUN_0800bb48(5);
  FUN_0800bb48(0x13);
  FUN_0800bb48(8);
  FUN_0800bb48(0x3b);
  FUN_0800bb48(0x9a);
  FUN_0800bb48(0x50);
  FUN_0800bb48(10);
  FUN_0800bb48(0x13);
  FUN_0800bb48(0xf);
  FUN_0800bb48(0x31);
  FUN_0800bb48(0x36);
  FUN_0800bb48(0xf);
  FUN_0800bb3e(0xc0);
  FUN_0800bb48(0x10);
  FUN_0800bb48(0x10);
  FUN_0800bb3e(0xc1);
  FUN_0800bb48(0x44);
  FUN_0800bb3e(0xc5);
  FUN_0800bb48(0);
  FUN_0800bb48(0x10);
  FUN_0800bb48(0x80);
  FUN_0800bb3e(0x36);
  FUN_0800bb48(0x68);
  FUN_0800bb3e(0x3a);
  FUN_0800bb48(0x55);
  FUN_0800bb3e(0x21);
  FUN_0800bb3e(0xb0);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xb1);
  FUN_0800bb48(0xb0);
  FUN_0800bb3e(0xb4);
  FUN_0800bb48(2);
  FUN_0800bb3e(0xb6);
  FUN_0800bb48(2);
  FUN_0800bb48(0x22);
  FUN_0800bb3e(0xb7);
  FUN_0800bb48(0xc6);
  FUN_0800bb3e(0xbe);
  FUN_0800bb48(0);
  FUN_0800bb48(4);
  FUN_0800bb3e(0xe9);
  FUN_0800bb48(0);
  FUN_0800bb3e(0xf7);
  FUN_0800bb48(0xa9);
  FUN_0800bb48(0x51);
  FUN_0800bb48(0x2c);
  FUN_0800bb48(0x82);
  FUN_0800bb3e(0x11);
  thunk_FUN_08006e38(0x4b0);
  FUN_0800bb3e(0x21);
  FUN_0800bb3e(0x29);
  FUN_080013d4(DAT_08007724,0x800);
  FUN_080073b0(0,0,0x1e0,0x140,0xffff);
  return;
}



/* FUNCTION 08007630 FUN_08007630 SIZE 46 */

void FUN_08007630(void)

{
  short *psVar1;
  short sVar2;
  
  sVar2 = FUN_08006e3e();
  psVar1 = DAT_08007730;
  *DAT_08007730 = sVar2;
  if (*psVar1 == -0x6b78) {
    FUN_0800742e();
  }
  else if (*DAT_08007730 == 0x4802) {
    FUN_08006eba();
  }
  return;
}



/* FUNCTION 0800765e FUN_0800765e SIZE 28 */

void FUN_0800765e(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0800734a(param_1,param_2,1);
  FUN_0800bb48(param_3);
  return;
}



/* FUNCTION 0800767a FUN_0800767a SIZE 26 */

uint FUN_0800767a(uint param_1)

{
  return (param_1 & 0x1f) << 0xb | param_1 & 0x7e0 | param_1 >> 0xb & 0xffff;
}



/* FUNCTION 08007694 FUN_08007694 SIZE 92 */

void FUN_08007694(uint param_1,uint param_2)

{
  FUN_0800bb3e(0x2a);
  FUN_0800bb48((int)param_1 >> 8);
  FUN_0800bb48(param_1 & 0xff);
  FUN_0800bb48((int)(param_1 + 1) >> 8);
  FUN_0800bb48(param_1 + 1 & 0xff);
  FUN_0800bb3e(0x2b);
  FUN_0800bb48((int)param_2 >> 8);
  FUN_0800bb48(param_2 & 0xff);
  FUN_0800bb48((int)(param_2 + 1) >> 8);
  FUN_0800bb48(param_2 + 1 & 0xff);
  FUN_0800bb3e(0x2e);
  FUN_08006e12();
  FUN_0800767a();
  return;
}



/* FUNCTION 080076f0 FUN_080076f0 SIZE 76 */

void FUN_080076f0(uint param_1,uint param_2,undefined2 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if ((int)param_2 < (int)param_1) {
    FUN_0800734a(param_2 & 0xffff,param_3,param_1 - param_2 & 0xffff,1);
  }
  else {
    FUN_0800734a(param_1 & 0xffff,param_3,param_2 - param_1 & 0xffff,1);
  }
  for (uVar2 = 0; iVar1 = FUN_08006c30((int)(short)((short)param_1 - (short)param_2)),
      (int)uVar2 <= iVar1; uVar2 = uVar2 + 1 & 0xffff) {
    FUN_0800bb48(param_4);
  }
  return;
}



/* FUNCTION 0800774e FUN_0800774e SIZE 76 */

void FUN_0800774e(uint param_1,uint param_2,undefined2 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  if ((int)param_2 < (int)param_1) {
    FUN_0800734a(param_3,param_2 & 0xffff,1,param_1 - param_2 & 0xffff);
  }
  else {
    FUN_0800734a(param_3,param_1 & 0xffff,1,param_2 - param_1 & 0xffff);
  }
  for (uVar2 = 0; iVar1 = FUN_08006c30((int)(short)((short)param_2 - (short)param_1)),
      (int)uVar2 <= iVar1; uVar2 = uVar2 + 1 & 0xffff) {
    FUN_0800bb48(param_4);
  }
  return;
}



/* FUNCTION 0800779a FUN_0800779a SIZE 38 */

void FUN_0800779a(undefined2 param_1)

{
  int iVar1;
  
  FUN_0800734a(0,0,0x1e0,0x140);
  for (iVar1 = 0x25800; iVar1 != 0; iVar1 = iVar1 + -1) {
    *DAT_08007b6c = param_1;
  }
  return;
}



/* FUNCTION 080077c0 FUN_080077c0 SIZE 82 */

void FUN_080077c0(short param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  ushort uVar2;
  byte bVar3;
  
  for (uVar1 = 0; uVar1 < 0x10; uVar1 = uVar1 + 1 & 0xff) {
    bVar3 = *(byte *)(DAT_08007b70 + (param_3 + -0x20) * 0x10 + uVar1);
    for (uVar2 = 0; uVar2 < 8; uVar2 = uVar2 + 1 & 0xff) {
      if ((bVar3 & 0x80) != 0) {
        FUN_0800765e(param_1 + uVar2,param_2 + uVar1 & 0xffff,param_4);
      }
      bVar3 = bVar3 << 1;
    }
  }
  return;
}



/* FUNCTION 08007812 FUN_08007812 SIZE 204 */

void FUN_08007812(int param_1)

{
  if (param_1 == 0) {
    FUN_0800bb3e(0x36);
    if (*DAT_08007b74 == 0x4802) {
      FUN_0800bb48(0x60);
    }
    else {
      FUN_0800bb48(0x68);
    }
    FUN_0800bb3e(0x2a);
    FUN_0800bb48(0);
    FUN_0800bb48(0);
    FUN_0800bb48(1);
    FUN_0800bb48(0xdf);
    FUN_0800bb3e(0x2b);
    FUN_0800bb48(0);
    FUN_0800bb48(0);
    FUN_0800bb48(1);
    FUN_0800bb48(0x3f);
  }
  else if (param_1 == 1) {
    FUN_0800bb3e(0x36);
    if (*DAT_08007b74 == 0x4802) {
      FUN_0800bb48(0x20);
    }
    else {
      FUN_0800bb48(0x28);
    }
    FUN_0800bb3e(0x2a);
    FUN_0800bb48(0);
    FUN_0800bb48(0);
    FUN_0800bb48(1);
    FUN_0800bb48(0xdf);
    FUN_0800bb3e(0x2b);
    FUN_0800bb48(0);
    FUN_0800bb48(0);
    FUN_0800bb48(1);
    FUN_0800bb48(0x3f);
  }
  return;
}



/* FUNCTION 080078de Boot_DrawText_Candidate SIZE 112 */

/* Coordinates, text and RGB565 color arguments */

void Boot_DrawText_Candidate(uint param_1,uint param_2,byte *param_3,undefined4 param_4)

{
  FUN_08007812(0);
  while (*param_3 != 0) {
    if (*param_3 < 0x80) {
      if (*param_3 == 10) {
        param_3 = param_3 + 1;
        param_2 = param_2 + 0x10 & 0xffff;
        param_1 = 0;
      }
      else if ((int)param_1 < 0x1d9) {
        FUN_080077c0(param_1,param_2,*param_3,param_4);
        param_3 = param_3 + 1;
        param_1 = param_1 + 8 & 0xffff;
      }
      else {
        param_2 = param_2 + 0x10 & 0xffff;
        FUN_080077c0(0,param_2,*param_3,param_4);
        param_3 = param_3 + 1;
        param_1 = 8;
      }
    }
    else {
      param_3 = param_3 + 1;
    }
  }
  return;
}



/* FUNCTION 0800794e FUN_0800794e SIZE 174 */

void FUN_0800794e(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,char *param_7)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  char *pcVar5;
  uint uVar6;
  
  uVar6 = 0;
  for (pcVar5 = param_7; *pcVar5 != '\0'; pcVar5 = pcVar5 + 1) {
    uVar6 = uVar6 + 8 & 0xffff;
  }
  FUN_080073b0(param_1,param_2,param_1 + param_3,param_2 + param_4,param_5);
  sVar2 = (short)param_1;
  sVar3 = (short)param_3;
  sVar1 = (short)param_2;
  FUN_080076f0((int)sVar2,(int)(short)(sVar2 + sVar3),(int)sVar1,0xffff);
  sVar4 = (short)param_4;
  FUN_080076f0((int)(short)(sVar2 + 1),(int)(short)(sVar2 + sVar3),(int)(short)(sVar1 + sVar4),
               0x8410);
  FUN_0800774e((int)sVar1,(int)(short)(sVar1 + sVar4),(int)sVar2,0xffff);
  FUN_0800774e((int)(short)(sVar1 + 1),(int)(short)(sVar1 + sVar4),(int)(short)(sVar2 + sVar3),
               0x8410);
  Boot_DrawText_Candidate
            (param_1 + (int)(param_3 - uVar6) / 2 & 0xffff,param_2 + (param_4 + -0x10) / 2 & 0xffff,
             param_7,param_6,param_3 - uVar6);
  return;
}



/* FUNCTION 080079fc FUN_080079fc SIZE 34 */

void FUN_080079fc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0800734a(param_1,param_2,param_3,param_4);
  FUN_0800bb3e(0x2c);
  return;
}



/* FUNCTION 08007a1e FUN_08007a1e SIZE 334 */

void FUN_08007a1e(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_84 [20];
  undefined1 auStack_70 [4];
  short local_6c [2];
  undefined1 auStack_68 [4];
  uint local_64;
  uint local_60;
  ushort local_5a;
  undefined1 auStack_40 [12];
  uint local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  
  uStack_30 = param_1;
  uStack_2c = param_2;
  local_28 = param_3;
  FUN_0800b844(auStack_84,&DAT_08007b78,param_3);
  FUN_0800530e(0,DAT_08007b7c);
  cVar2 = Boot_FS_Open(DAT_08007b80,auStack_84,1);
  *DAT_08007b84 = cVar2;
  if (*DAT_08007b74 == -0x6b7f) {
    FUN_08007812(0);
  }
  else if (*DAT_08007b74 == -0x6b78) {
    FUN_08007812(1);
  }
  else if (*DAT_08007b74 == 0x4802) {
    FUN_08007812(1);
  }
  if ((*DAT_08007b84 == '\0') &&
     (Boot_FS_Read(DAT_08007b80,local_6c,2,auStack_70), local_6c[0] == 0x4d42)) {
    Boot_FS_Read(DAT_08007b80,auStack_40,0xc,auStack_70);
    Boot_FS_Read(DAT_08007b80,auStack_68,0x28,auStack_70);
    iVar3 = local_64 * local_5a + 0x1f;
    iVar3 = ((int)(iVar3 + ((uint)(iVar3 >> 0x1f) >> 0x1b)) >> 5) * 4;
    if ((iVar3 < 0x5a1) && (0x17 < local_5a)) {
      FUN_080079fc(0,0,local_64 & 0xffff,local_60 & 0xffff);
      for (iVar5 = 0; iVar5 < (int)(local_60 + 1); iVar5 = iVar5 + 1) {
        for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
          Boot_FS_Read(DAT_08007b80,DAT_08007b88 + iVar4,1,auStack_70);
        }
        for (iVar4 = 0; iVar4 < (int)local_64; iVar4 = iVar4 + 1) {
          iVar1 = iVar4 * 3;
          local_34 = (uint)*(byte *)(DAT_08007b88 + iVar1);
          FUN_0800bb48(((int)(uint)*(byte *)(DAT_08007b88 + iVar1 + 2) >> 3) << 0xb |
                       ((int)(uint)*(byte *)(DAT_08007b88 + iVar1 + 1) >> 2) << 5 |
                       (int)local_34 >> 3);
        }
      }
      FUN_08007812(0);
      Boot_FS_Close(DAT_08007b80);
    }
  }
  return;
}



/* FUNCTION 08007b8c FUN_08007b8c SIZE 18 */

void FUN_08007b8c(undefined1 *param_1)

{
  undefined1 uVar1;
  
  uVar1 = *param_1;
  *param_1 = param_1[1];
  param_1[1] = param_1[2];
  param_1[2] = param_1[3];
  param_1[3] = uVar1;
  return;
}



/* FUNCTION 08007b9e FUN_08007b9e SIZE 26 */

void FUN_08007b9e(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  for (uVar1 = 0; (int)uVar1 < param_3; uVar1 = uVar1 + 1 & 0xff) {
    *(byte *)(param_1 + uVar1) = *(byte *)(param_1 + uVar1) ^ *(byte *)(param_2 + uVar1);
  }
  return;
}



/* FUNCTION 08007bb8 FUN_08007bb8 SIZE 34 */

void FUN_08007bb8(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  if (param_3 == 0) {
    iVar2 = DAT_08007eac;
  }
  else {
    iVar2 = DAT_08007ea8;
  }
  for (uVar1 = 0; (int)uVar1 < param_2; uVar1 = uVar1 + 1 & 0xff) {
    *(undefined1 *)(param_1 + uVar1) = *(undefined1 *)(iVar2 + (uint)*(byte *)(param_1 + uVar1));
  }
  return;
}



/* FUNCTION 08007bda FUN_08007bda SIZE 94 */

void FUN_08007bda(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_18;
  
  local_18 = param_4;
  for (uVar3 = 1; uVar3 < 4; uVar3 = uVar3 + 1 & 0xff) {
    for (uVar1 = 0; uVar1 < 4; uVar1 = uVar1 + 1 & 0xff) {
      *(undefined1 *)((int)&local_18 + uVar1) = *(undefined1 *)(param_1 + uVar1 * 4 + uVar3);
    }
    if (param_2 == 0) {
      uVar1 = uVar3;
    }
    else {
      uVar1 = 4 - uVar3;
    }
    for (uVar2 = 0; uVar2 < 4; uVar2 = uVar2 + 1 & 0xff) {
      iVar4 = uVar2 + (uVar1 & 0xff);
      *(undefined1 *)(param_1 + uVar2 * 4 + uVar3) =
           *(undefined1 *)((int)&local_18 + iVar4 + (iVar4 >> 2) * -4);
    }
  }
  return;
}



/* FUNCTION 08007c38 FUN_08007c38 SIZE 22 */

byte FUN_08007c38(byte param_1)

{
  if ((param_1 & 0x80) == 0) {
    param_1 = param_1 << 1;
  }
  else {
    param_1 = param_1 << 1 ^ 0x1b;
  }
  return param_1;
}



/* FUNCTION 08007c4e FUN_08007c4e SIZE 254 */

void FUN_08007c4e(byte *param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  undefined4 local_28;
  
  for (bVar6 = 0; bVar6 < 4; bVar6 = bVar6 + 1) {
    bVar5 = *param_1 ^ param_1[1] ^ param_1[2] ^ param_1[3];
    bVar1 = FUN_08007c38(*param_1 ^ param_1[1]);
    bVar1 = bVar1 ^ *param_1 ^ bVar5;
    bVar2 = FUN_08007c38(param_1[1] ^ param_1[2]);
    bVar2 = bVar2 ^ param_1[1] ^ bVar5;
    local_28._0_2_ = CONCAT11(bVar2,bVar1);
    bVar3 = FUN_08007c38(param_1[2] ^ param_1[3]);
    bVar3 = bVar3 ^ param_1[2] ^ bVar5;
    local_28._0_3_ = CONCAT12(bVar3,(undefined2)local_28);
    bVar4 = FUN_08007c38(param_1[3] ^ *param_1);
    bVar4 = bVar4 ^ param_1[3] ^ bVar5;
    local_28 = CONCAT13(bVar4,(undefined3)local_28);
    if (param_2 != 0) {
      FUN_08007c38(*param_1 ^ param_1[2]);
      uVar7 = FUN_08007c38();
      FUN_08007c38(param_1[1] ^ param_1[3]);
      uVar8 = FUN_08007c38();
      bVar5 = FUN_08007c38(uVar7 ^ uVar8);
      local_28._0_2_ = CONCAT11(bVar2 ^ bVar5 ^ (byte)uVar8,bVar1 ^ bVar5 ^ (byte)uVar7);
      local_28._0_3_ = CONCAT12(bVar3 ^ bVar5 ^ (byte)uVar7,(undefined2)local_28);
      local_28 = CONCAT13(bVar4 ^ bVar5 ^ (byte)uVar8,(undefined3)local_28);
    }
    *(undefined4 *)param_1 = local_28;
    param_1 = param_1 + 4;
  }
  return;
}



/* FUNCTION 08007d4c FUN_08007d4c SIZE 72 */

void FUN_08007d4c(undefined4 param_1)

{
  uint uVar1;
  
  FUN_08007b9e(param_1,DAT_08007eb0,0x10);
  for (uVar1 = 1; uVar1 < 0xb; uVar1 = uVar1 + 1 & 0xff) {
    FUN_08007bb8(param_1,0x10,0);
    FUN_08007bda(param_1,0);
    if (uVar1 != 10) {
      FUN_08007c4e(param_1,0);
    }
    FUN_08007b9e(param_1,uVar1 * 0x10 + DAT_08007eb0);
  }
  return;
}



/* FUNCTION 08007d94 FUN_08007d94 SIZE 78 */

void FUN_08007d94(undefined4 param_1)

{
  uint uVar1;
  
  FUN_08007b9e(param_1,DAT_08007eb0 + 0xa0,0x10);
  for (uVar1 = 10; uVar1 != 0; uVar1 = uVar1 - 1 & 0xff) {
    FUN_08007bda(param_1,1);
    FUN_08007bb8(param_1,0x10,1);
    FUN_08007b9e(param_1,(uVar1 - 1) * 0x10 + DAT_08007eb0,0x10);
    if (uVar1 != 1) {
      FUN_08007c4e(param_1,1);
    }
  }
  return;
}



/* FUNCTION 08007de2 FUN_08007de2 SIZE 114 */

void FUN_08007de2(undefined4 param_1)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint local_18;
  
  local_18 = DAT_08007eb4;
  FUN_0800b926(DAT_08007eb0,param_1,0x10);
  puVar3 = (undefined4 *)(DAT_08007eb0 + 0x10);
  for (uVar2 = 4; uVar2 < 0x2c; uVar2 = uVar2 + 1 & 0xff) {
    *puVar3 = puVar3[-1];
    if (uVar2 + ((int)uVar2 >> 2) * -4 == 0) {
      FUN_08007b8c(puVar3);
      FUN_08007bb8(puVar3,4,0);
      FUN_08007b9e(puVar3,&local_18,4);
      uVar1 = FUN_08007c38(local_18 & 0xff);
      local_18 = CONCAT31(local_18._1_3_,uVar1);
    }
    FUN_08007b9e(puVar3,puVar3 + -4,4);
    puVar3 = puVar3 + 1;
  }
  return;
}



/* FUNCTION 08007eb8 FUN_08007eb8 SIZE 48 */

void FUN_08007eb8(undefined4 param_1)

{
  int iVar1;
  
  do {
    iVar1 = FUN_08001f9e(DAT_080082bc,2);
  } while (iVar1 == 0);
  FUN_08001f30(DAT_080082bc,param_1);
  do {
    iVar1 = FUN_08001f9e(DAT_080082bc,1);
  } while (iVar1 == 0);
  FUN_08001f2a(DAT_080082bc);
  return;
}



/* FUNCTION 08007ee8 FUN_08007ee8 SIZE 100 */

void FUN_08007ee8(int param_1)

{
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  
  FUN_08001e2e(DAT_080082bc,0);
  local_1c = 0;
  local_1a = 0x104;
  local_18 = 0;
  local_16 = 2;
  local_14 = 1;
  local_12 = 0x200;
  local_e = 0;
  local_c = 7;
  if (param_1 == 0) {
    local_10 = 0x38;
  }
  else {
    local_10 = 0x20;
  }
  FUN_08001c68(DAT_080082bc,&local_1c);
  FUN_08001e2e(DAT_080082bc,1);
  return;
}



/* FUNCTION 08007f4c FUN_08007f4c SIZE 184 */

void FUN_08007f4c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = param_3;
  local_c = param_4;
  FUN_080017dc(0x4000);
  FUN_08001776(2,1);
  FUN_080013f2(DAT_080082c0,0xd,5);
  FUN_080013f2(DAT_080082c0,0xe,5);
  FUN_080013f2(DAT_080082c0,0xf,5);
  local_c = 0x1000202;
  local_10 = 0x2000;
  FUN_080012dc(DAT_080082c0,&local_10);
  local_10 = 0x8000;
  FUN_080012dc(DAT_080082c0,&local_10);
  local_10 = 0x4000;
  FUN_080012dc(DAT_080082c0,&local_10);
  local_10 = 0x1000;
  local_c = 0x201;
  FUN_080012dc(DAT_080082c0,&local_10);
  FUN_080013d4(DAT_080082c0,0x1000);
  FUN_080013d4(DAT_080082c0,0x1000);
  FUN_08007ee8(0);
  FUN_08001e2e(DAT_080082bc,1);
  return;
}



/* FUNCTION 08008004 FUN_08008004 SIZE 132 */

undefined4 FUN_08008004(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined4 uVar4;
  uint uVar5;
  
  FUN_080013d8(DAT_080082c0,0x1000);
  uVar3 = 0;
  do {
    if (1999 < uVar3) {
code_r0x0800803c:
      if (uVar3 == 2000) {
        FUN_080013d4(DAT_080082c0,0x1000);
        uVar4 = 1;
      }
      else {
        for (uVar5 = 0; (int)uVar5 < param_2; uVar5 = uVar5 + 1 & 0xffff) {
          uVar2 = FUN_08007eb8(0xff);
          *(undefined1 *)(param_1 + uVar5) = uVar2;
        }
        FUN_08007eb8(0xff);
        FUN_08007eb8(0xff);
        if (param_3 != 0) {
          FUN_080013d4(DAT_080082c0,0x1000);
          FUN_08007eb8(0xff);
        }
        uVar4 = 0;
      }
      return uVar4;
    }
    cVar1 = FUN_08007eb8(0xff);
    if (cVar1 == -2) {
      uVar3 = 0;
      goto code_r0x0800803c;
    }
    uVar3 = uVar3 + 1;
  } while( true );
}



/* FUNCTION 08008088 FUN_08008088 SIZE 132 */

uint FUN_08008088(uint param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  uint unaff_r5;
  
  FUN_08007eb8(0xff);
  FUN_08007eb8(0xff);
  FUN_080013d8(DAT_080082c0,0x1000);
  FUN_08007eb8(param_1 | 0x40);
  FUN_08007eb8(param_2 >> 0x18);
  FUN_08007eb8((param_2 & 0xffffff) >> 0x10);
  FUN_08007eb8((param_2 & 0xffff) >> 8);
  FUN_08007eb8(param_2 & 0xff);
  FUN_08007eb8(param_3);
  for (bVar2 = 0; bVar2 < 200; bVar2 = bVar2 + 1) {
    bVar1 = FUN_08007eb8(0xff);
    unaff_r5 = (uint)bVar1;
    if (unaff_r5 != 0xff) break;
  }
  FUN_080013d4(DAT_080082c0,0x1000);
  FUN_08007eb8(0xff);
  return unaff_r5;
}



/* FUNCTION 0800810c FUN_0800810c SIZE 740 */

char FUN_0800810c(byte *param_1)

{
  longlong lVar1;
  char cVar2;
  int iVar3;
  byte local_34;
  byte local_33;
  byte local_32;
  byte local_31;
  byte local_30;
  byte local_2f;
  byte local_2e;
  byte local_2d;
  byte local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  byte local_28;
  byte local_27;
  byte local_26;
  byte local_25;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  byte local_20;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  byte local_1c;
  byte local_1b;
  byte local_1a;
  byte local_19;
  byte local_18;
  byte local_17;
  byte local_16;
  byte local_15;
  
  cVar2 = FUN_08008088(9,0,0xff);
  if (cVar2 == '\0') {
    iVar3 = FUN_08008004(&local_24,0x10,1);
    if (iVar3 == 0) {
      cVar2 = FUN_08008088(10,0,0xff);
      if (cVar2 == '\0') {
        iVar3 = FUN_08008004(&local_34,0x10,1);
        if (iVar3 == 0) {
          *param_1 = local_24 >> 6;
          param_1[1] = (byte)((local_24 & 0x3f) >> 2);
          param_1[2] = local_24 & 3;
          param_1[3] = local_23;
          param_1[4] = local_22;
          param_1[5] = local_21;
          *(ushort *)(param_1 + 6) = (ushort)local_20 << 4;
          *(ushort *)(param_1 + 6) = *(ushort *)(param_1 + 6) | (ushort)(local_1f >> 4);
          param_1[8] = local_1f & 0xf;
          param_1[9] = local_1e >> 7;
          param_1[10] = (byte)((local_1e & 0x7f) >> 6);
          param_1[0xb] = (byte)((local_1e & 0x3f) >> 5);
          param_1[0xc] = (byte)((local_1e & 0x1f) >> 4);
          param_1[0xd] = 0;
          *(uint *)(param_1 + 0x10) = (local_1e & 3) << 10;
          *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | (uint)local_1d << 2;
          *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | (uint)(local_1c >> 6);
          param_1[0x14] = (byte)((local_1c & 0x3f) >> 3);
          param_1[0x15] = local_1c & 7;
          param_1[0x16] = local_1b >> 5;
          param_1[0x17] = (byte)((local_1b & 0x1f) >> 2);
          param_1[0x18] = (local_1b & 3) << 1;
          param_1[0x18] = param_1[0x18] | local_1a >> 7;
          param_1[0x19] = (byte)((local_1a & 0x7f) >> 2);
          param_1[0x1a] = (local_1a & 3) << 3;
          param_1[0x1a] = param_1[0x1a] | local_19 >> 5;
          param_1[0x1b] = local_19 & 0x1f;
          param_1[0x1c] = local_18 >> 7;
          param_1[0x1d] = (byte)((local_18 & 0x7f) >> 5);
          param_1[0x1e] = (byte)((local_18 & 0x1f) >> 2);
          param_1[0x1f] = (local_18 & 3) << 2;
          param_1[0x1f] = param_1[0x1f] | local_17 >> 6;
          param_1[0x20] = (byte)((local_17 & 0x3f) >> 5);
          param_1[0x21] = 0;
          param_1[0x22] = local_17 & 1;
          param_1[0x23] = local_16 >> 7;
          param_1[0x24] = (byte)((local_16 & 0x7f) >> 6);
          param_1[0x25] = (byte)((local_16 & 0x3f) >> 5);
          param_1[0x26] = (byte)((local_16 & 0x1f) >> 4);
          param_1[0x27] = (byte)((local_16 & 0xf) >> 2);
          param_1[0x28] = local_16 & 3;
          param_1[0x29] = local_15 >> 1;
          param_1[0x2a] = 1;
          if (param_1[0x56] == 4) {
            *(uint *)(param_1 + 0x10) = (uint)local_1c << 8;
            *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + (uint)local_1b;
          }
          lVar1 = ((ulonglong)*(uint *)(param_1 + 0x10) * 0x200 & 0xffffffff) * 0x400;
          *(int *)(param_1 + 0x48) = (int)lVar1;
          *(int *)(param_1 + 0x4c) =
               (int)((ulonglong)*(uint *)(param_1 + 0x10) * 0x200 >> 0x20) * 0x400 +
               (int)((ulonglong)lVar1 >> 0x20);
          param_1[0x50] = 0;
          param_1[0x51] = 2;
          param_1[0x52] = 0;
          param_1[0x53] = 0;
          param_1[0x2c] = local_34;
          *(ushort *)(param_1 + 0x2e) = (ushort)local_33 << 8;
          *(ushort *)(param_1 + 0x2e) = *(ushort *)(param_1 + 0x2e) | (ushort)local_32;
          *(uint *)(param_1 + 0x30) = (uint)local_31 << 0x18;
          *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | (uint)local_30 << 0x10;
          *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | (uint)local_2f << 8;
          *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | (uint)local_2e;
          param_1[0x34] = local_2d;
          param_1[0x35] = local_2c;
          *(uint *)(param_1 + 0x38) = (uint)local_2b << 0x18;
          *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | (uint)local_2a << 0x10;
          *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | (uint)local_29 << 8;
          *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | (uint)local_28;
          param_1[0x3c] = param_1[0x3c] | local_27 >> 4;
          *(ushort *)(param_1 + 0x3e) = (local_27 & 0xf) << 8;
          *(ushort *)(param_1 + 0x3e) = *(ushort *)(param_1 + 0x3e) | (ushort)local_26;
          param_1[0x40] = local_25 >> 1;
          param_1[0x41] = 1;
          cVar2 = '\0';
        }
        else {
          cVar2 = '\x02';
        }
      }
    }
    else {
      cVar2 = '\x01';
    }
  }
  return cVar2;
}



/* FUNCTION 080083fa FUN_080083fa SIZE 116 */

uint FUN_080083fa(uint param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  uint unaff_r5;
  
  FUN_08007eb8(0xff);
  FUN_08007eb8(0xff);
  FUN_080013d8(DAT_08008810,0x1000);
  FUN_08007eb8(param_1 | 0x40);
  FUN_08007eb8(param_2 >> 0x18);
  FUN_08007eb8((param_2 & 0xffffff) >> 0x10);
  FUN_08007eb8((param_2 & 0xffff) >> 8);
  FUN_08007eb8(param_2 & 0xff);
  FUN_08007eb8(param_3);
  bVar2 = 0;
  while( true ) {
    if (199 < bVar2) {
      return unaff_r5;
    }
    bVar1 = FUN_08007eb8(0xff);
    if (bVar1 != 0xff) break;
    bVar2 = bVar2 + 1;
    unaff_r5 = 0xff;
  }
  return (uint)bVar1;
}



/* FUNCTION 0800846e FUN_0800846e SIZE 602 */

char FUN_0800846e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  ushort uVar4;
  int iVar5;
  undefined2 uVar7;
  uint uVar6;
  
  FUN_080013d8(DAT_08008810,0x1000,param_3,param_4,0,0);
  for (uVar4 = 0; uVar4 < 0xf00; uVar4 = uVar4 + 1) {
  }
  for (uVar4 = 0; uVar4 < 800; uVar4 = uVar4 + 1) {
    FUN_08007eb8(0xff);
  }
  for (uVar4 = 0; uVar4 < 0x10; uVar4 = uVar4 + 1) {
    cVar1 = FUN_08008088(0,0,0x95);
    if (cVar1 == -0x41 || cVar1 == '\x01') {
      uVar4 = 0;
      break;
    }
  }
  if (uVar4 == 0x10) {
    return '\x01';
  }
  cVar1 = FUN_080083fa(8,0x1aa,0x87);
  if (cVar1 == '\x05') {
    *(undefined1 *)(DAT_08008814 + 0x56) = 1;
    FUN_080013d4(DAT_08008810,0x1000);
    FUN_08007eb8(0xff);
    for (uVar4 = 0; uVar4 < 0xfff; uVar4 = uVar4 + 1) {
      cVar1 = FUN_08008088(0x37,0);
      if (cVar1 != '\x01') {
        return cVar1;
      }
      cVar1 = FUN_08008088(0x29,0);
      if (cVar1 == '\0') {
        uVar4 = 0;
        break;
      }
    }
    if (uVar4 == 0xfff) {
      for (uVar4 = 0; uVar4 < 0xfff; uVar4 = uVar4 + 1) {
        cVar1 = FUN_08008088(1,0);
        if (cVar1 == '\0') {
          uVar4 = 0;
          break;
        }
      }
      if (uVar4 == 0xfff) {
        return '\x02';
      }
      *(undefined1 *)(DAT_08008814 + 0x56) = 0;
    }
    FUN_08007ee8(1);
    cVar1 = FUN_08008088(0x3b,0,1);
    if (cVar1 != '\0') {
      return cVar1;
    }
    cVar1 = FUN_08008088(0x10,0x200,0xff);
    if (cVar1 != '\0') {
      return cVar1;
    }
  }
  else if (cVar1 == '\x01') {
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    bVar2 = FUN_08007eb8(0xff);
    iVar5 = (uint)bVar2 << 0x10;
    uVar3 = FUN_08007eb8(0xff);
    uVar7 = (undefined2)(CONCAT13(uVar3,(int3)iVar5) >> 0x10);
    FUN_080013d4(DAT_08008810,0x1000);
    FUN_08007eb8(0xff);
    if (((char)uVar7 == '\x01') && ((char)((ushort)uVar7 >> 8) == -0x56)) {
      for (uVar4 = 0; uVar4 < 0xfff; uVar4 = uVar4 + 1) {
        cVar1 = FUN_08008088(0x37,0);
        if (cVar1 != '\x01') {
          return cVar1;
        }
        cVar1 = FUN_08008088(0x29,0x40000000,0);
        if (cVar1 == '\0') {
          uVar4 = 0;
          break;
        }
      }
      if (uVar4 == 0xfff) {
        return '\x03';
      }
      cVar1 = FUN_080083fa(0x3a,0);
      if (cVar1 != '\0') {
        return cVar1;
      }
      bVar2 = FUN_08007eb8(0xff);
      FUN_08007eb8(0xff);
      uVar4 = (ushort)bVar2;
      FUN_08007eb8(0xff);
      uVar6 = (uint)uVar4;
      FUN_08007eb8(0xff);
      uVar6 = uVar6 & 0xffffff;
      FUN_080013d4(DAT_08008810,0x1000);
      FUN_08007eb8(0xff);
      if ((uVar6 & 0x40) == 0) {
        *(undefined1 *)(DAT_08008814 + 0x56) = 2;
      }
      else {
        *(undefined1 *)(DAT_08008814 + 0x56) = 4;
      }
      FUN_08007ee8(1);
    }
  }
  FUN_0800810c(DAT_08008814);
  return '\0';
}



/* FUNCTION 080086c8 FUN_080086c8 SIZE 62 */

undefined1 FUN_080086c8(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  
  if (*(char *)(DAT_08008814 + 0x56) != '\x04') {
    param_1 = param_1 << 9;
  }
  cVar1 = FUN_08008088(0x11,param_1,0);
  if (cVar1 == '\0') {
    uVar2 = FUN_08008004(param_2,0x200);
    FUN_08008088(0xc,0);
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



/* FUNCTION 08008706 FUN_08008706 SIZE 128 */

undefined4 FUN_08008706(int param_1,int param_2,uint param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(DAT_08008814 + 0x56) != '\x04') {
    param_1 = param_1 << 9;
  }
  cVar1 = FUN_08008088(0x12,param_1,0);
  if (cVar1 == '\0') {
    for (uVar4 = 0; uVar4 < param_3; uVar4 = uVar4 + 1) {
      iVar3 = FUN_08008004(param_2 + uVar4 * 0x200,0x200,0);
      if (iVar3 != 0) {
        FUN_08008088(0xc,0);
        FUN_080013d4(DAT_08008810,0x1000);
        return 2;
      }
    }
    FUN_08008088(0xc,0);
    FUN_080013d4(DAT_08008810,0x1000);
    FUN_08007eb8(0xff);
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



/* FUNCTION 08008786 FUN_08008786 SIZE 200 */

undefined4 FUN_08008786(int param_1,undefined1 *param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  
  if (*(char *)(DAT_08008814 + 0x56) != '\x04') {
    param_1 = param_1 << 9;
  }
  cVar1 = FUN_08008088(0x18,param_1,0);
  if (cVar1 == '\0') {
    FUN_080013d8(DAT_08008810,0x1000);
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xfe);
    for (uVar3 = 0; uVar3 < 0x200; uVar3 = uVar3 + 1) {
      FUN_08007eb8(*param_2);
      param_2 = param_2 + 1;
    }
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    bVar2 = FUN_08007eb8(0xff);
    if ((bVar2 & 0x1f) == 5) {
      iVar6 = 0;
      do {
        iVar5 = FUN_08007eb8(0xff);
        if (iVar5 != 0) {
          FUN_080013d4(DAT_08008980,0x1000);
          FUN_08007eb8(0xff);
          return 0;
        }
        bVar7 = iVar6 != 0x40000;
        iVar6 = iVar6 + 1;
      } while (bVar7);
      FUN_080013d4(DAT_08008980,0x1000);
      uVar4 = 3;
    }
    else {
      FUN_080013d4(DAT_08008810,0x1000);
      uVar4 = 2;
    }
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}



/* FUNCTION 08008856 FUN_08008856 SIZE 296 */

undefined4 FUN_08008856(int param_1,undefined1 *param_2,uint param_3)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  
  if (*(char *)(DAT_08008984 + 0x56) != '\x04') {
    param_1 = param_1 << 9;
  }
  if (*(char *)(DAT_08008984 + 0x56) != '\0') {
    FUN_08008088(0x17,param_3,0);
  }
  cVar1 = FUN_08008088(0x19,param_1,0);
  if (cVar1 == '\0') {
    FUN_080013d8(DAT_08008980,0x1000);
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    FUN_08007eb8(0xff);
    for (uVar6 = 0; uVar6 < param_3; uVar6 = uVar6 + 1) {
      FUN_08007eb8(0xfc);
      for (uVar3 = 0; uVar3 < 0x200; uVar3 = uVar3 + 1) {
        FUN_08007eb8(*param_2);
        param_2 = param_2 + 1;
      }
      FUN_08007eb8(0xff);
      FUN_08007eb8(0xff);
      bVar2 = FUN_08007eb8(0xff);
      if ((bVar2 & 0x1f) != 5) {
        FUN_080013d4(DAT_08008980,0x1000);
        return 2;
      }
      iVar7 = 0;
      while (iVar5 = FUN_08007eb8(0xff), iVar5 != 0xff) {
        bVar8 = iVar7 == 0x40000;
        iVar7 = iVar7 + 1;
        if (bVar8) {
          FUN_080013d4(DAT_08008980,0x1000);
          return 3;
        }
      }
    }
    cVar1 = FUN_08007eb8(0xfd);
    if (cVar1 == '\0') {
      uVar4 = 4;
    }
    else {
      iVar7 = 0;
      do {
        iVar5 = FUN_08007eb8(0xff);
        if (iVar5 == 0xff) {
          FUN_080013d4(DAT_08008980,0x1000);
          FUN_08007eb8(0xff);
          return 0;
        }
        bVar8 = iVar7 != 0x40000;
        iVar7 = iVar7 + 1;
      } while (bVar8);
      FUN_080013d4(DAT_08008980,0x1000);
      uVar4 = 5;
    }
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}



/* FUNCTION 08008988 FUN_08008988 SIZE 16 */

void FUN_08008988(void)

{
  FUN_08008ea0();
  FUN_08008f52(0,1);
  return;
}



/* FUNCTION 08008998 FUN_08008998 SIZE 14 */

undefined1 FUN_08008998(undefined4 param_1)

{
  undefined1 uVar1;
  
  uVar1 = FUN_08008fa8(param_1);
  return uVar1;
}



/* FUNCTION 080089a6 FUN_080089a6 SIZE 10 */

void FUN_080089a6(void)

{
  FUN_08008998(0xff);
  return;
}



/* FUNCTION 080089b0 FUN_080089b0 SIZE 76 */

void FUN_080089b0(undefined1 *param_1,uint param_2,uint param_3)

{
  undefined1 uVar1;
  bool bVar2;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(3);
  FUN_08008998((param_2 & 0xffffff) >> 0x10);
  FUN_08008998((param_2 & 0xffff) >> 8);
  FUN_08008998(param_2 & 0xff);
  while( true ) {
    bVar2 = param_3 == 0;
    param_3 = param_3 - 1 & 0xffff;
    if (bVar2) break;
    uVar1 = FUN_08008998(0xff);
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  FUN_080013d4(DAT_08008d9c,0x10);
  return;
}



/* FUNCTION 080089fc FUN_080089fc SIZE 56 */

undefined4 FUN_080089fc(void)

{
  undefined4 uVar1;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(0xab);
  FUN_08008998(0xff);
  FUN_08008998(0xff);
  FUN_08008998(0xff);
  uVar1 = FUN_08008998(0xff);
  FUN_080013d4(DAT_08008d9c,0x10);
  return uVar1;
}



/* FUNCTION 08008a34 FUN_08008a34 SIZE 74 */

uint FUN_08008a34(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(0x9f);
  iVar1 = FUN_08008998(0xff);
  iVar2 = FUN_08008998(0xff);
  uVar3 = FUN_08008998(0xff);
  FUN_080013d4(DAT_08008d9c,0x10);
  return iVar1 << 0x10 | iVar2 << 8 | uVar3;
}



/* FUNCTION 08008a7e FUN_08008a7e SIZE 26 */

void FUN_08008a7e(void)

{
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(6);
  FUN_080013d4(DAT_08008d9c,0x10);
  return;
}



/* FUNCTION 08008a98 FUN_08008a98 SIZE 46 */

void FUN_08008a98(void)

{
  uint uVar1;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(5);
  do {
    uVar1 = FUN_08008998(0xff);
  } while ((uVar1 & 1) != 0);
  FUN_080013d4(DAT_08008d9c,0x10);
  return;
}



/* FUNCTION 08008ac6 FUN_08008ac6 SIZE 62 */

void FUN_08008ac6(uint param_1)

{
  FUN_08008a7e();
  FUN_08008a98();
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(0x20);
  FUN_08008998((param_1 & 0xffffff) >> 0x10);
  FUN_08008998((param_1 & 0xffff) >> 8);
  FUN_08008998(param_1 & 0xff);
  FUN_080013d4(DAT_08008d9c,0x10);
  FUN_08008a98();
  return;
}



/* FUNCTION 08008b04 FUN_08008b04 SIZE 92 */

void FUN_08008b04(undefined1 *param_1,uint param_2,uint param_3)

{
  bool bVar1;
  
  FUN_08008a7e();
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(2);
  FUN_08008998((param_2 & 0xffffff) >> 0x10);
  FUN_08008998((param_2 & 0xffff) >> 8);
  FUN_08008998(param_2 & 0xff);
  if (0x100 < (int)param_3) {
    param_3 = 0x100;
  }
  while (bVar1 = param_3 != 0, param_3 = param_3 - 1 & 0xffff, bVar1) {
    FUN_08008998(*param_1);
    param_1 = param_1 + 1;
  }
  FUN_080013d4(DAT_08008d9c,0x10);
  FUN_08008a98();
  return;
}



/* FUNCTION 08008c82 FUN_08008c82 SIZE 38 */

undefined4 FUN_08008c82(void)

{
  undefined4 uVar1;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(5);
  uVar1 = FUN_08008998(0xff);
  FUN_080013d4(DAT_08008d9c,0x10);
  return uVar1;
}



/* FUNCTION 08008ca8 FUN_08008ca8 SIZE 18 */

void FUN_08008ca8(void)

{
  uint uVar1;
  
  do {
    uVar1 = FUN_08008c82();
  } while ((uVar1 & 1) != 0);
  return;
}



/* FUNCTION 08008cba FUN_08008cba SIZE 78 */

void FUN_08008cba(int param_1,uint param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(3);
  FUN_08008998((param_2 & 0xffffff) >> 0x10);
  FUN_08008998((param_2 & 0xffff) >> 8);
  FUN_08008998(param_2 & 0xff);
  for (uVar2 = 0; (int)uVar2 < param_3; uVar2 = uVar2 + 1 & 0xffff) {
    uVar1 = FUN_08008998(0xff);
    *(undefined1 *)(param_1 + uVar2) = uVar1;
  }
  FUN_080013d4(DAT_08008d9c,0x10);
  return;
}



/* FUNCTION 08008d08 FUN_08008d08 SIZE 64 */

void FUN_08008d08(uint param_1)

{
  FUN_08008a7e();
  FUN_08008ca8();
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(0x20);
  FUN_08008998((param_1 & 0xfff) >> 4);
  FUN_08008998((param_1 & 0xf) << 4);
  FUN_08008998(0);
  FUN_080013d4(DAT_08008d9c,0x10);
  FUN_08008ca8();
  return;
}



/* FUNCTION 08008d48 FUN_08008d48 SIZE 84 */

void FUN_08008d48(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  FUN_08008a7e();
  FUN_080013d8(DAT_08008d9c,0x10);
  FUN_08008998(2);
  FUN_08008998((param_2 & 0xffffff) >> 0x10);
  FUN_08008998((param_2 & 0xffff) >> 8);
  FUN_08008998(param_2 & 0xff);
  for (uVar1 = 0; (int)uVar1 < param_3; uVar1 = uVar1 + 1 & 0xffff) {
    FUN_08008998(*(undefined1 *)(param_1 + uVar1));
  }
  FUN_080013d4(DAT_08008d9c,0x10);
  FUN_08008ca8();
  return;
}



/* FUNCTION 08008da0 FUN_08008da0 SIZE 70 */

void FUN_08008da0(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = 0x100 - (param_2 & 0xff);
  if ((int)param_3 <= (int)uVar1) {
    uVar1 = param_3;
  }
  while (FUN_08008d48(param_1,param_2,uVar1), param_3 != uVar1) {
    param_1 = param_1 + uVar1;
    param_2 = param_2 + uVar1;
    param_3 = param_3 - uVar1 & 0xffff;
    if (param_3 < 0x101) {
      uVar1 = param_3;
    }
    else {
      uVar1 = 0x100;
    }
  }
  return;
}



/* FUNCTION 08008de6 FUN_08008de6 SIZE 180 */

void FUN_08008de6(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = DAT_08008e9c;
  uVar4 = param_2 >> 0xc;
  uVar5 = param_2 & 0xfff;
  uVar2 = 0x1000 - uVar5;
  if ((int)param_3 <= (int)(0x1000 - uVar5)) {
    uVar2 = param_3;
  }
  while( true ) {
    FUN_08008cba(iVar1,uVar4 << 0xc,0x1000);
    for (uVar3 = 0; ((int)uVar3 < (int)uVar2 && (*(char *)(iVar1 + uVar5 + uVar3) == -1));
        uVar3 = uVar3 + 1 & 0xffff) {
    }
    if ((int)uVar3 < (int)uVar2) {
      FUN_08008d08(uVar4);
      for (uVar3 = 0; (int)uVar3 < (int)uVar2; uVar3 = uVar3 + 1 & 0xffff) {
        *(undefined1 *)(iVar1 + uVar3 + uVar5) = *(undefined1 *)(param_1 + uVar3);
      }
      FUN_08008da0(iVar1,uVar4 << 0xc,0x1000);
    }
    else {
      FUN_08008da0(param_1,param_2,uVar2);
    }
    if (param_3 == uVar2) break;
    uVar4 = uVar4 + 1;
    uVar5 = 0;
    param_1 = param_1 + uVar2;
    param_2 = param_2 + uVar2;
    param_3 = param_3 - uVar2 & 0xffff;
    if (param_3 < 0x1001) {
      uVar2 = param_3;
    }
    else {
      uVar2 = 0x1000;
    }
  }
  return;
}



/* FUNCTION 08008ea0 FUN_08008ea0 SIZE 178 */

void FUN_08008ea0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = param_3;
  local_c = param_4;
  FUN_080017fe(0x1000);
  FUN_08001776(1);
  FUN_08001200(DAT_080090f8);
  FUN_08001200(DAT_080090f8);
  FUN_08001200(DAT_080090f8);
  FUN_080013f2(DAT_080090f8,5);
  FUN_080013f2(DAT_080090f8,6,5);
  FUN_080013f2(DAT_080090f8,7,5);
  local_c = 0x2000202;
  local_10 = 0x20;
  FUN_080012dc(DAT_080090f8,&local_10);
  local_10 = 0x40;
  FUN_080012dc(DAT_080090f8,&local_10);
  local_10 = 0x80;
  FUN_080012dc(DAT_080090f8,&local_10);
  FUN_08001776(1);
  FUN_080013d4(DAT_080090f8,0x10);
  local_10 = 0x10;
  local_c = 0x1000201;
  FUN_080012dc(DAT_080090f8,&local_10);
  return;
}



/* FUNCTION 08008f52 FUN_08008f52 SIZE 86 */

void FUN_08008f52(undefined2 param_1,undefined2 param_2)

{
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  
  FUN_08001e2e(PTR_DAT_080090fc,0);
  local_20 = 0;
  local_1e = 0x104;
  local_1a = 2;
  local_16 = 0x200;
  local_14 = 0;
  local_12 = 0;
  local_10 = 7;
  local_1c = param_1;
  local_18 = param_2;
  FUN_08001c68(PTR_DAT_080090fc,&local_20);
  FUN_08001e2e(PTR_DAT_080090fc,1);
  return;
}



/* FUNCTION 08008fa8 FUN_08008fa8 SIZE 52 */

undefined2 FUN_08008fa8(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  do {
    iVar2 = FUN_08001f9e(PTR_DAT_080090fc,2);
  } while (iVar2 == 0);
  FUN_08001f30(PTR_DAT_080090fc,param_1);
  do {
    iVar2 = FUN_08001f9e(PTR_DAT_080090fc,1);
  } while (iVar2 == 0);
  uVar1 = FUN_08001f2a(PTR_DAT_080090fc);
  return uVar1;
}



/* FUNCTION 080090c2 FUN_080090c2 SIZE 52 */

undefined2 FUN_080090c2(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  do {
    iVar2 = FUN_08001f9e(DAT_08009104,2);
  } while (iVar2 == 0);
  FUN_08001f30(DAT_08009104,param_1);
  do {
    iVar2 = FUN_08001f9e(DAT_08009104,1);
  } while (iVar2 == 0);
  uVar1 = FUN_08001f2a(DAT_08009104);
  return uVar1;
}



/* FUNCTION 08009108 Boot_ProgramWordsAndVerify SIZE 78 */

/* Writes 32-bit words then compares flash readback */

undefined4 Boot_ProgramWordsAndVerify(uint *param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  while( true ) {
    if ((param_3 <= uVar2) || (DAT_0800917c < *param_1)) {
      return 0;
    }
    iVar1 = FUN_0800095e(*param_1,*(undefined4 *)(param_2 + uVar2 * 4));
    if (iVar1 != 8) {
      return 1;
    }
    if (*(int *)*param_1 != *(int *)(param_2 + uVar2 * 4)) break;
    *param_1 = *param_1 + 4;
    uVar2 = uVar2 + 1;
  }
  return 2;
}



/* FUNCTION 08009156 Boot_JumpToApplication SIZE 38 */

/* Checks MSP range, loads stack pointer and calls reset vector */

void Boot_JumpToApplication(uint *param_1)

{
  bool bVar1;
  
  if ((*param_1 & DAT_08009180) == 0x20000000) {
    *DAT_08009184 = param_1[1];
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setMainStackPointer(*param_1);
    }
    (*(code *)*DAT_08009184)();
  }
  return;
}



/* FUNCTION 08009188 FUN_08009188 SIZE 174 */

void FUN_08009188(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = param_3;
  local_c = param_4;
  FUN_08001776(1);
  local_10 = 0x1900;
  local_c = 0x302;
  FUN_080012dc(DAT_080092c0,&local_10);
  FUN_080013f2(DAT_080092c0,8,10);
  FUN_080013f2(DAT_080092c0,0xb,10);
  FUN_080013f2(DAT_080092c0,0xc,10);
  local_10 = 0x200;
  local_c = 0x10300;
  FUN_080012dc(DAT_080092c0,&local_10);
  local_10 = 0x400;
  local_c = CONCAT22(0x101,CONCAT11(3,(undefined1)local_c));
  FUN_080012dc(DAT_080092c0,&local_10);
  FUN_080013f2(DAT_080092c0,10);
  FUN_080017fe(0x4000);
  FUN_08001798(0x80,1);
  return;
}



/* FUNCTION 08009236 FUN_08009236 SIZE 44 */

void FUN_08009236(void)

{
  undefined4 in_r3;
  undefined4 local_10;
  
  local_10 = in_r3;
  FUN_08000270(0x600);
  local_10 = 0x1030143;
  FUN_0800027a(&local_10);
  return;
}



/* FUNCTION 08009262 FUN_08009262 SIZE 44 */

void FUN_08009262(void)

{
  undefined4 in_r3;
  undefined4 local_10;
  
  local_10 = in_r3;
  FUN_08000270(0x600);
  local_10 = 0x30143;
  FUN_0800027a(&local_10);
  return;
}



/* FUNCTION 0800928e FUN_0800928e SIZE 30 */

void FUN_0800928e(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    uVar1 = uVar1 + 1;
  } while (uVar1 <= (uint)(param_1 * 0x78) / 7);
  return;
}



/* FUNCTION 080092ac FUN_080092ac SIZE 18 */

void FUN_080092ac(int param_1)

{
  FUN_0800928e(param_1 * 1000);
  return;
}



/* FUNCTION 080092c4 FUN_080092c4 SIZE 6 */

longlong FUN_080092c4(uint param_1)

{
  return (ulonglong)param_1 << 0x20;
}



/* FUNCTION 080092ca FUN_080092ca SIZE 66 */

void FUN_080092ca(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  FUN_08009188(param_1);
  FUN_080092c4(param_1);
  *(undefined4 *)(param_1 + 0x5e4) = param_4;
  *(undefined4 *)(param_1 + 0x5e8) = param_5;
  *(undefined4 *)(param_1 + 0x5ec) = param_3;
  FUN_0800ad4a(param_1,param_2);
  (*(code *)**(undefined4 **)(param_1 + 0x5e8))();
  FUN_08009236(param_1);
  return;
}



/* FUNCTION 0800930c FUN_0800930c SIZE 84 */

undefined4 FUN_0800930c(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint local_10;
  undefined4 uStack_c;
  
  local_10 = param_3;
  uStack_c = param_4;
  FUN_08009cbe(param_1,&local_10);
  if ((local_10 & 0x1f) == 0) {
    FUN_08009a98(param_1,&local_10);
  }
  else if ((local_10 & 0x1f) == 1) {
    FUN_08009b0a(param_1,&local_10);
  }
  else if ((local_10 & 0x1f) == 2) {
    FUN_08009b56(param_1,&local_10);
  }
  else {
    FUN_0800af38(param_1,local_10 & 0x80);
  }
  return 0;
}



/* FUNCTION 08009360 FUN_08009360 SIZE 150 */

undefined4 FUN_08009360(int param_1,int param_2)

{
  undefined2 uVar1;
  
  if (param_2 == 0) {
    if (*(char *)(param_1 + 0x111) == '\x03') {
      if (*(uint *)(param_1 + 0x37c) < *(uint *)(param_1 + 0x390)) {
        *(int *)(param_1 + 0x390) = *(int *)(param_1 + 0x390) - *(int *)(param_1 + 0x37c);
        if (*(char *)(param_1 + 3) == '\x01') {
          *(int *)(param_1 + 0x380) = *(int *)(param_1 + 0x380) + *(int *)(param_1 + 0x37c);
        }
        if (*(uint *)(param_1 + 0x390) < *(uint *)(param_1 + 0x37c)) {
          uVar1 = (undefined2)*(undefined4 *)(param_1 + 0x390);
        }
        else {
          uVar1 = (undefined2)*(undefined4 *)(param_1 + 0x37c);
        }
        FUN_08009636(param_1,*(undefined4 *)(param_1 + 0x380),uVar1);
      }
      else {
        if ((*(int *)(*(int *)(param_1 + 0x5e4) + 0x10) != 0) &&
           (*(char *)(param_1 + 0x112) == '\x03')) {
          (**(code **)(*(int *)(param_1 + 0x5e4) + 0x10))(param_1);
        }
        FUN_08009654(param_1);
      }
    }
  }
  else if ((*(int *)(*(int *)(param_1 + 0x5e4) + 0x18) != 0) &&
          (*(char *)(param_1 + 0x112) == '\x03')) {
    (**(code **)(*(int *)(param_1 + 0x5e4) + 0x18))(param_1,param_2);
  }
  return 0;
}



/* FUNCTION 080093f6 FUN_080093f6 SIZE 14 */

undefined4 FUN_080093f6(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 4) = *DAT_080095b8;
  return 0;
}



/* FUNCTION 08009404 FUN_08009404 SIZE 208 */

undefined4 FUN_08009404(int param_1,int param_2)

{
  if (param_2 == 0) {
    if (*(char *)(param_1 + 0x111) == '\x02') {
      if (*(uint *)(param_1 + 0x124) < *(uint *)(param_1 + 0x138)) {
        *(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) - *(int *)(param_1 + 0x124);
        if (*(char *)(param_1 + 3) == '\x01') {
          *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + *(int *)(param_1 + 0x124);
        }
        FUN_080095ea(param_1,*(undefined4 *)(param_1 + 0x128),*(undefined2 *)(param_1 + 0x138));
      }
      else if (((*(uint *)(param_1 + 0x13c) ==
                 *(uint *)(param_1 + 0x124) *
                 (*(uint *)(param_1 + 0x13c) / *(uint *)(param_1 + 0x124))) &&
               (*(uint *)(param_1 + 0x124) <= *(uint *)(param_1 + 0x13c))) &&
              (*(uint *)(param_1 + 0x13c) < *(uint *)(param_1 + 0x140))) {
        FUN_080095ea(param_1,0);
        *(undefined4 *)(param_1 + 0x140) = 0;
      }
      else {
        if ((*(int *)(*(int *)(param_1 + 0x5e4) + 0xc) != 0) &&
           (*(char *)(param_1 + 0x112) == '\x03')) {
          (**(code **)(*(int *)(param_1 + 0x5e4) + 0xc))(param_1);
        }
        FUN_08009678(param_1);
      }
    }
    if (*(char *)(param_1 + 0x116) == '\x01') {
      FUN_080093f6(param_1);
      *(undefined1 *)(param_1 + 0x116) = 0;
    }
  }
  else if ((*(int *)(*(int *)(param_1 + 0x5e4) + 0x14) != 0) &&
          (*(char *)(param_1 + 0x112) == '\x03')) {
    (**(code **)(*(int *)(param_1 + 0x5e4) + 0x14))(param_1,param_2);
  }
  return 0;
}



/* FUNCTION 080094d4 FUN_080094d4 SIZE 50 */

undefined4 FUN_080094d4(int param_1)

{
  FUN_0800ade6(param_1,0,0x40);
  FUN_0800ade6(param_1,0x80,0x40,0);
  *(undefined1 *)(param_1 + 0x112) = 1;
  (**(code **)(*(int *)(param_1 + 0x5e8) + 4))(*(undefined1 *)(param_1 + 2));
  return 0;
}



/* FUNCTION 08009506 FUN_08009506 SIZE 30 */

undefined4 FUN_08009506(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x5e8) + 0x10))();
  *(undefined1 *)(param_1 + 0x112) = *(undefined1 *)(param_1 + 0x113);
  *(undefined1 *)(param_1 + 0x112) = 3;
  return 0;
}



/* FUNCTION 08009524 FUN_08009524 SIZE 32 */

undefined4 FUN_08009524(int param_1)

{
  *(undefined1 *)(param_1 + 0x113) = *(undefined1 *)(param_1 + 0x112);
  *(undefined1 *)(param_1 + 0x112) = 4;
  (**(code **)(*(int *)(param_1 + 0x5e8) + 0xc))();
  return 0;
}



/* FUNCTION 08009544 FUN_08009544 SIZE 26 */

undefined4 FUN_08009544(int param_1)

{
  if (*(int *)(*(int *)(param_1 + 0x5e4) + 0x1c) != 0) {
    (**(code **)(*(int *)(param_1 + 0x5e4) + 0x1c))(param_1);
  }
  return 0;
}



/* FUNCTION 0800955e FUN_0800955e SIZE 30 */

undefined4 FUN_0800955e(int param_1,undefined4 param_2)

{
  (*(code *)**(undefined4 **)(param_1 + 0x5e4))(param_1,param_2);
  (**(code **)(*(int *)(param_1 + 0x5e8) + 8))();
  return 0;
}



/* FUNCTION 0800957c FUN_0800957c SIZE 22 */

undefined4 FUN_0800957c(int param_1,undefined4 param_2)

{
  (**(code **)(*(int *)(param_1 + 0x5e4) + 4))(param_1,param_2);
  return 0;
}



/* FUNCTION 08009592 FUN_08009592 SIZE 18 */

undefined4 FUN_08009592(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x5e4) + 0x20))(param_1);
  return 0;
}



/* FUNCTION 080095a4 FUN_080095a4 SIZE 18 */

undefined4 FUN_080095a4(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x5e4) + 0x24))(param_1);
  return 0;
}



/* FUNCTION 080095bc FUN_080095bc SIZE 46 */

undefined4 FUN_080095bc(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x13c) = param_3;
  *(undefined4 *)(param_1 + 0x138) = param_3;
  *(undefined1 *)(param_1 + 0x111) = 2;
  FUN_0800aeea(param_1,0,param_2,param_3);
  return 0;
}



/* FUNCTION 080095ea FUN_080095ea SIZE 30 */

undefined4 FUN_080095ea(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0800aeea(param_1,0,param_2,param_3);
  return 0;
}



/* FUNCTION 08009608 FUN_08009608 SIZE 46 */

undefined4 FUN_08009608(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x394) = param_3;
  *(undefined4 *)(param_1 + 0x390) = param_3;
  *(undefined1 *)(param_1 + 0x111) = 3;
  FUN_0800ae98(param_1,0,param_2,param_3);
  return 0;
}



/* FUNCTION 08009636 FUN_08009636 SIZE 30 */

undefined4 FUN_08009636(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0800ae98(param_1,0,param_2,param_3);
  return 0;
}



/* FUNCTION 08009654 FUN_08009654 SIZE 36 */

undefined4 FUN_08009654(int param_1)

{
  *(undefined1 *)(param_1 + 0x111) = 4;
  FUN_0800aeea(param_1,0,0);
  FUN_0800aa72(param_1);
  return 0;
}



/* FUNCTION 08009678 FUN_08009678 SIZE 36 */

undefined4 FUN_08009678(int param_1)

{
  *(undefined1 *)(param_1 + 0x111) = 5;
  FUN_0800ae98(param_1,0,0);
  FUN_0800aa72(param_1);
  return 0;
}



/* FUNCTION 080096b0 FUN_080096b0 SIZE 30 */

void FUN_080096b0(undefined4 param_1)

{
  FUN_0800af38(param_1,0x80);
  FUN_0800af38(param_1,0);
  FUN_0800aa72(param_1);
  return;
}



/* FUNCTION 080096ce FUN_080096ce SIZE 72 */

void FUN_080096ce(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x112) == '\x02') || (*(char *)(param_1 + 0x112) == '\x03')) {
    if (*(short *)(param_2 + 2) == 1) {
      *(undefined4 *)(param_1 + 0x118) = 0;
      (**(code **)(*(int *)(param_1 + 0x5e4) + 8))(param_1,param_2);
      FUN_08009654(param_1);
    }
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return;
}



/* FUNCTION 08009716 FUN_08009716 SIZE 94 */

/* WARNING: Switch with 1 destination removed at 0x08009758 */

void FUN_08009716(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  
  if (*(short *)(param_2 + 2) == 1) {
    *(undefined4 *)(param_1 + 0x118) = 1;
    pcVar1 = *(code **)(*(int *)(param_1 + 0x5e4) + 8);
    (*pcVar1)(param_1,param_2,pcVar1,param_4,param_4);
    FUN_08009654(param_1);
  }
  else if ((*(short *)(param_2 + 2) == 2) && (*(char *)(param_2 + 4) == '\0')) {
    *DAT_08009b80 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4);
    *(undefined1 *)(param_1 + 0x116) = 1;
    FUN_08009654(param_1);
  }
  return;
}



/* FUNCTION 080097b6 FUN_080097b6 SIZE 74 */

void FUN_080097b6(int param_1,undefined4 param_2)

{
  uint *puVar1;
  
  puVar1 = DAT_08009b84;
  if ((*(char *)(param_1 + 0x112) == '\x02') || (*(char *)(param_1 + 0x112) == '\x03')) {
    *DAT_08009b84 = 1;
    if (*(int *)(param_1 + 0x118) != 0) {
      *puVar1 = *puVar1 | 2;
    }
    FUN_080095bc(param_1,DAT_08009b84,2);
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return;
}



/* FUNCTION 08009800 FUN_08009800 SIZE 78 */

void FUN_08009800(int param_1,int param_2)

{
  if (*(short *)(param_2 + 6) == 1) {
    if (*(char *)(param_1 + 0x112) == '\x02') {
      FUN_080095bc(param_1,DAT_08009b88,1);
    }
    else if (*(char *)(param_1 + 0x112) == '\x03') {
      FUN_080095bc(param_1,param_1 + 0x110,1);
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return;
}



/* FUNCTION 0800984e FUN_0800984e SIZE 204 */

void FUN_0800984e(int param_1,int param_2)

{
  byte *pbVar1;
  
  pbVar1 = DAT_08009b8c;
  *DAT_08009b8c = *(byte *)(param_2 + 2);
  if (*pbVar1 < 2) {
    if (*(char *)(param_1 + 0x112) == '\x02') {
      if (*DAT_08009b8c == 0) {
        FUN_08009654(param_1);
      }
      else {
        *(byte *)(param_1 + 0x110) = *DAT_08009b8c;
        *(undefined1 *)(param_1 + 0x112) = 3;
        FUN_0800955e(param_1,*DAT_08009b8c);
        FUN_08009654(param_1);
      }
    }
    else if (*(char *)(param_1 + 0x112) == '\x03') {
      if (*DAT_08009b8c == 0) {
        *(undefined1 *)(param_1 + 0x112) = 2;
        *(byte *)(param_1 + 0x110) = *DAT_08009b8c;
        FUN_0800957c(param_1,*DAT_08009b8c);
        FUN_08009654(param_1);
      }
      else if (*(byte *)(param_1 + 0x110) == *DAT_08009b8c) {
        FUN_08009654(param_1);
      }
      else {
        FUN_0800957c(param_1,*(undefined1 *)(param_1 + 0x110));
        *(byte *)(param_1 + 0x110) = *DAT_08009b8c;
        FUN_0800955e(param_1,*DAT_08009b8c);
        FUN_08009654(param_1);
      }
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return;
}



/* FUNCTION 0800991a FUN_0800991a SIZE 92 */

void FUN_0800991a(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  if ((*(short *)(param_2 + 4) == 0) && (*(short *)(param_2 + 6) == 0)) {
    bVar1 = *(byte *)(param_2 + 2);
    bVar2 = bVar1 & 0x7f;
    if (*(char *)(param_1 + 0x112) == '\x03') {
      FUN_080096b0(param_1,param_2);
    }
    else {
      *(byte *)(param_1 + 0x114) = bVar2;
      FUN_0800afec(param_1,bVar2);
      FUN_08009654(param_1);
      if ((bVar1 & 0x7f) == 0) {
        *(undefined1 *)(param_1 + 0x112) = 1;
      }
      else {
        *(undefined1 *)(param_1 + 0x112) = 2;
      }
    }
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return;
}



/* FUNCTION 08009976 FUN_08009976 SIZE 276 */

void FUN_08009976(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  uint local_18;
  
  local_18 = param_4;
  switch((int)(uint)*(ushort *)(param_2 + 2) >> 8) {
  default:
    FUN_080096b0(param_1,param_2);
    return;
  case 1:
    iVar1 = (*(code *)**(undefined4 **)(param_1 + 0x5ec))(*(undefined1 *)(param_1 + 2),&local_18);
    if ((*(short *)(param_2 + 6) == 0x40) || (*(char *)(param_1 + 0x112) == '\x01')) {
      local_18 = 8;
    }
    break;
  case 2:
    iVar1 = (**(code **)(*(int *)(param_1 + 0x5e4) + 0x28))(*(undefined1 *)(param_1 + 2),&local_18);
    *(undefined1 *)(iVar1 + 1) = 2;
    *(int *)(param_1 + 0x5f0) = iVar1;
    break;
  case 3:
    switch(*(undefined1 *)(param_2 + 2)) {
    case 0:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 4))(*(undefined1 *)(param_1 + 2),&local_18);
      break;
    case 1:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 8))(*(undefined1 *)(param_1 + 2),&local_18);
      break;
    case 2:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 0xc))(*(undefined1 *)(param_1 + 2),&local_18)
      ;
      break;
    case 3:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 0x10))
                        (*(undefined1 *)(param_1 + 2),&local_18);
      break;
    case 4:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 0x14))
                        (*(undefined1 *)(param_1 + 2),&local_18);
      break;
    case 5:
      iVar1 = (**(code **)(*(int *)(param_1 + 0x5ec) + 0x18))
                        (*(undefined1 *)(param_1 + 2),&local_18);
      break;
    default:
      FUN_080096b0(param_1,param_2);
      return;
    }
    break;
  case 6:
    FUN_080096b0(param_1,param_2);
    return;
  case 7:
    FUN_080096b0(param_1,param_2);
    return;
  }
  if (((ushort)local_18 != 0) && (*(short *)(param_2 + 6) != 0)) {
    if (*(ushort *)(param_2 + 6) <= (ushort)local_18) {
      local_18._0_2_ = *(ushort *)(param_2 + 6);
    }
    local_18 = (uint)(ushort)local_18;
    FUN_080095bc(param_1,iVar1,local_18);
  }
  return;
}



/* FUNCTION 08009a98 FUN_08009a98 SIZE 104 */

undefined4 FUN_08009a98(undefined4 param_1,int param_2)

{
  switch(*(undefined1 *)(param_2 + 1)) {
  case 0:
    FUN_080097b6(param_1,param_2);
    break;
  case 1:
    FUN_080096ce(param_1,param_2);
    break;
  default:
    FUN_080096b0(param_1,param_2);
    break;
  case 3:
    FUN_08009716(param_1,param_2);
    break;
  case 5:
    FUN_0800991a(param_1,param_2);
    break;
  case 6:
    FUN_08009976(param_1,param_2);
    break;
  case 8:
    FUN_08009800(param_1,param_2);
    break;
  case 9:
    FUN_0800984e(param_1,param_2);
  }
  return 0;
}



/* FUNCTION 08009b0a FUN_08009b0a SIZE 76 */

undefined4 FUN_08009b0a(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x112) == '\x03') {
    if (*(byte *)(param_2 + 4) < 2) {
      (**(code **)(*(int *)(param_1 + 0x5e4) + 8))(param_1,param_2);
      if (*(short *)(param_2 + 6) == 0) {
        FUN_08009654(param_1);
      }
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  else {
    FUN_080096b0(param_1,param_2);
  }
  return 0;
}



/* FUNCTION 08009b56 FUN_08009b56 SIZE 344 */

undefined4 FUN_08009b56(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_2 + 4);
  cVar1 = *(char *)(param_2 + 1);
  if (cVar1 == '\0') {
    if (*(char *)(param_1 + 0x112) == '\x02') {
      if ((uVar2 != 0) && (uVar2 != 0x80)) {
        FUN_0800af38(param_1,uVar2);
      }
    }
    else if (*(char *)(param_1 + 0x112) == '\x03') {
      if ((uVar2 & 0x80) == 0x80) {
        if (*(char *)(param_1 + (uVar2 & 0x7f) * 0x28 + 0x11e) == '\0') {
          *DAT_08009d6c = 0;
        }
        else {
          *DAT_08009d6c = 1;
        }
      }
      else if ((*(byte *)(param_2 + 4) & 0x80) == 0) {
        if (*(char *)(param_1 + uVar2 * 0x28 + 0x376) == '\0') {
          *DAT_08009d6c = 0;
        }
        else {
          *DAT_08009d6c = 1;
        }
      }
      FUN_080095bc(param_1,DAT_08009d6c,2);
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  else if (cVar1 == '\x01') {
    if (*(char *)(param_1 + 0x112) == '\x02') {
      if ((uVar2 != 0) && (uVar2 != 0x80)) {
        FUN_0800af38(param_1,uVar2);
      }
    }
    else if (*(char *)(param_1 + 0x112) == '\x03') {
      if (*(short *)(param_2 + 2) == 0) {
        if ((uVar2 != 0) && (uVar2 != 0x80)) {
          FUN_0800af80(param_1,uVar2);
          (**(code **)(*(int *)(param_1 + 0x5e4) + 8))(param_1,param_2);
        }
        FUN_08009654(param_1);
      }
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  else if (cVar1 == '\x03') {
    if (*(char *)(param_1 + 0x112) == '\x02') {
      if ((uVar2 != 0) && (uVar2 != 0x80)) {
        FUN_0800af38(param_1,uVar2);
      }
    }
    else if (*(char *)(param_1 + 0x112) == '\x03') {
      if (((*(short *)(param_2 + 2) == 0) && (uVar2 != 0)) && (uVar2 != 0x80)) {
        FUN_0800af38(param_1,uVar2);
      }
      (**(code **)(*(int *)(param_1 + 0x5e4) + 8))(param_1,param_2);
      FUN_08009654(param_1);
    }
    else {
      FUN_080096b0(param_1,param_2);
    }
  }
  return 0;
}



/* FUNCTION 08009cbe FUN_08009cbe SIZE 72 */

void FUN_08009cbe(int param_1,undefined1 *param_2)

{
  *param_2 = *(undefined1 *)(param_1 + 0x5cc);
  param_2[1] = *(undefined1 *)(param_1 + 0x5cd);
  *(undefined2 *)(param_2 + 2) = *(undefined2 *)(param_1 + 0x5ce);
  *(undefined2 *)(param_2 + 4) = *(undefined2 *)(param_1 + 0x5d0);
  *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x5d2);
  *(uint *)(param_1 + 0x140) = (uint)*(ushort *)(param_2 + 6);
  *(undefined1 *)(param_1 + 0x111) = 1;
  return;
}



/* FUNCTION 08009d06 FUN_08009d06 SIZE 20 */

char FUN_08009d06(char *param_1)

{
  char cVar1;
  
  cVar1 = '\0';
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    cVar1 = cVar1 + '\x01';
  }
  return cVar1;
}



/* FUNCTION 08009d1a FUN_08009d1a SIZE 82 */

void FUN_08009d1a(char *param_1,undefined1 *param_2,short *param_3)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_1 != (char *)0x0) {
    sVar1 = FUN_08009d06(param_1);
    *param_3 = sVar1 * 2 + 2;
    *param_2 = (char)*param_3;
    uVar2 = 2;
    param_2[1] = 3;
    for (; *param_1 != '\0'; param_1 = param_1 + 1) {
      uVar3 = uVar2 + 1 & 0xff;
      param_2[uVar2] = *param_1;
      uVar2 = uVar3 + 1 & 0xff;
      param_2[uVar3] = 0;
    }
  }
  return;
}



/* FUNCTION 08009d70 FUN_08009d70 SIZE 52 */

void FUN_08009d70(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 4) = 0xffffffff;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0xbfffffff;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x18) = 0x80000800;
  return;
}



/* FUNCTION 08009da4 FUN_08009da4 SIZE 108 */

undefined4 FUN_08009da4(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    FUN_0800928e(3);
    uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + 0x10);
    uVar2 = uVar2 + 1;
    if (DAT_0800a1a0 < uVar2) {
      return 0;
    }
  } while (-1 < (int)uVar1);
  uVar2 = 0;
  *(uint *)(*(int *)(param_1 + 0xc) + 0x10) = (uVar1 & 0xfffffffe) + 1;
  do {
    uVar2 = uVar2 + 1;
    if (DAT_0800a1a0 < uVar2) break;
  } while ((*(uint *)(*(int *)(param_1 + 0xc) + 0x10) & 1) != 0);
  FUN_0800928e(3);
  return 0;
}



/* FUNCTION 08009e10 FUN_08009e10 SIZE 64 */

undefined4 FUN_08009e10(int param_1,undefined4 *param_2,int param_3,int param_4)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (*(char *)(param_1 + 3) == '\0') {
    puVar2 = *(undefined4 **)(param_1 + 0xd0 + param_3 * 4);
    for (uVar1 = 0; uVar1 < (uint)((int)(param_4 + 3 + ((uint)(param_4 + 3 >> 0x1f) >> 0x1e)) >> 2);
        uVar1 = uVar1 + 1) {
      *puVar2 = *param_2;
      param_2 = param_2 + 1;
    }
  }
  return 0;
}



/* FUNCTION 08009e50 FUN_08009e50 SIZE 40 */

undefined4 * FUN_08009e50(int param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0xd0);
  for (uVar1 = 0; uVar1 < (uint)((int)(param_3 + 3 + ((uint)(param_3 + 3 >> 0x1f) >> 0x1e)) >> 2);
      uVar1 = uVar1 + 1) {
    *param_2 = *puVar2;
    param_2 = param_2 + 1;
  }
  return param_2;
}



/* FUNCTION 08009e78 FUN_08009e78 SIZE 204 */

undefined4 FUN_08009e78(byte *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  param_1[3] = 0;
  param_1[2] = 1;
  param_1[4] = 0x40;
  iVar1 = DAT_0800a1a4;
  param_1[5] = 0;
  if (param_2 == 1) {
    param_1[0xb] = 1;
    *param_1 = 8;
    param_1[1] = 4;
    param_1[6] = 0x40;
    param_1[7] = 1;
    param_1[8] = 2;
    iVar3 = 0x50000000;
  }
  else {
    iVar3 = 0;
    if (param_2 == 0) {
      param_1[0xb] = 0;
      *param_1 = 0xc;
      param_1[1] = 6;
      param_1[6] = 0;
      param_1[7] = 5;
      iVar3 = iVar1;
    }
  }
  *(int *)(param_1 + 0xc) = iVar3;
  *(int *)(param_1 + 0x10) = iVar3 + 0x800;
  for (uVar2 = 0; uVar2 < param_1[1]; uVar2 = uVar2 + 1) {
    *(uint *)(param_1 + uVar2 * 4 + 0x18) = iVar3 + 0x900 + uVar2 * 0x20;
    *(uint *)(param_1 + uVar2 * 4 + 0x54) = iVar3 + 0xb00 + uVar2 * 0x20;
  }
  *(int *)(param_1 + 0x14) = iVar3 + 0x400;
  *(int *)(param_1 + 0xcc) = iVar3 + 0x440;
  for (uVar2 = 0; uVar2 < *param_1; uVar2 = uVar2 + 1) {
    *(uint *)(param_1 + uVar2 * 4 + 0x90) = iVar3 + 0x500 + uVar2 * 0x20;
  }
  for (uVar2 = 0; uVar2 < *param_1; uVar2 = uVar2 + 1) {
    *(uint *)(param_1 + uVar2 * 4 + 0xd0) = iVar3 + 0x1000 + uVar2 * 0x1000;
  }
  *(int *)(param_1 + 0x10c) = iVar3 + 0xe00;
  return 0;
}



/* FUNCTION 08009f44 FUN_08009f44 SIZE 294 */

longlong FUN_08009f44(int param_1)

{
  uint uVar1;
  uint local_18;
  uint local_14;
  
  local_18 = 0;
  if (*(char *)(param_1 + 8) == '\x01') {
    uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + 0x38);
    local_14 = uVar1 & 0xfffeffff;
    if (*(char *)(param_1 + 9) != '\0') {
      local_14 = (uVar1 & 0xffeeffff) + 0x100000;
    }
    *(uint *)(*(int *)(param_1 + 0xc) + 0x38) = local_14;
    *(uint *)(*(int *)(param_1 + 0xc) + 0xc) = *(uint *)(*(int *)(param_1 + 0xc) + 0xc) & 0xffb5ffbf
    ;
    FUN_08009da4(param_1);
    if (*(char *)(param_1 + 3) == '\x01') {
      local_18 = 0x2a;
      *(undefined4 *)(*(int *)(param_1 + 0xc) + 8) = 0x2a;
    }
  }
  else {
    *(uint *)(*(int *)(param_1 + 0xc) + 0xc) =
         (*(uint *)(*(int *)(param_1 + 0xc) + 0xc) & 0xffffffbf) + 0x40;
    FUN_08009da4(param_1);
    local_14 = 0x2d0000;
    if (*(char *)(param_1 + 9) != '\0') {
      local_14 = 0x3d0000;
    }
    *(uint *)(*(int *)(param_1 + 0xc) + 0x38) = local_14;
    FUN_080092ac(0x14);
  }
  if (*(char *)(param_1 + 3) == '\x01') {
    local_18 = ((*(uint *)(*(int *)(param_1 + 0xc) + 8) & 0xffffffe1) + 10 & 0xffffffdf) + 0x20;
    *(uint *)(*(int *)(param_1 + 0xc) + 8) = local_18;
  }
  return (ulonglong)local_18 << 0x20;
}



/* FUNCTION 0800a06a FUN_0800a06a SIZE 34 */

undefined4 FUN_0800a06a(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0xc) + 8) = *(uint *)(*(int *)(param_1 + 0xc) + 8) | 1;
  return 0;
}



/* FUNCTION 0800a08c FUN_0800a08c SIZE 34 */

undefined4 FUN_0800a08c(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0xc) + 8) = *(uint *)(*(int *)(param_1 + 0xc) + 8) & 0xfffffffe;
  return 0;
}



/* FUNCTION 0800a0ae FUN_0800a0ae SIZE 80 */

undefined4 FUN_0800a0ae(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  *(uint *)(*(int *)(param_1 + 0xc) + 0x10) = (param_2 & 0x1f) << 6 | 0x20;
  do {
    uVar1 = uVar1 + 1;
    if (DAT_0800a1a0 < uVar1) break;
  } while (*(int *)(*(int *)(param_1 + 0xc) + 0x10) << 0x1a < 0);
  FUN_0800928e(3);
  return 0;
}



/* FUNCTION 0800a0fe FUN_0800a0fe SIZE 70 */

undefined4 FUN_0800a0fe(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x10) = 0x10;
  do {
    uVar1 = uVar1 + 1;
    if (DAT_0800a1a0 < uVar1) break;
  } while (*(int *)(*(int *)(param_1 + 0xc) + 0x10) << 0x1b < 0);
  FUN_0800928e(3);
  return 0;
}



/* FUNCTION 0800a144 FUN_0800a144 SIZE 78 */

undefined4 FUN_0800a144(int param_1,int param_2)

{
  uint local_18;
  
  local_18 = *(uint *)(*(int *)(param_1 + 0xc) + 0xc) & 0x9fffffff;
  if (param_2 == 1) {
    local_18 = local_18 + 0x20000000;
  }
  else if (param_2 == 0) {
    local_18 = local_18 + 0x40000000;
  }
  *(uint *)(*(int *)(param_1 + 0xc) + 0xc) = local_18;
  FUN_080092ac(0x32);
  return 0;
}



/* FUNCTION 0800a192 FUN_0800a192 SIZE 12 */

uint FUN_0800a192(int param_1)

{
  return *(uint *)(*(int *)(param_1 + 0xc) + 0x14) & 1;
}



/* FUNCTION 0800a1a8 FUN_0800a1a8 SIZE 22 */

bool FUN_0800a1a8(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0800a192(param_1);
  return iVar1 != 1;
}



/* FUNCTION 0800a1be FUN_0800a1be SIZE 20 */

bool FUN_0800a1be(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0800a192(param_1);
  return iVar1 == 1;
}



/* FUNCTION 0800a1d2 FUN_0800a1d2 SIZE 16 */

uint FUN_0800a1d2(int param_1)

{
  return *(uint *)(*(int *)(param_1 + 0xc) + 0x14) & *(uint *)(*(int *)(param_1 + 0xc) + 0x18);
}



/* FUNCTION 0800a1ea FUN_0800a1ea SIZE 24 */

void FUN_0800a1ea(int param_1,uint param_2)

{
  **(uint **)(param_1 + 0x10) = **(uint **)(param_1 + 0x10) & 0xfffffffc | param_2 & 3;
  return;
}



/* FUNCTION 0800a202 FUN_0800a202 SIZE 154 */

undefined4 FUN_0800a202(int param_1)

{
  int local_10;
  
  local_10 = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x18) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0xbfffffff;
  FUN_08009d70(param_1);
  if (*(char *)(param_1 + 3) == '\0') {
    local_10 = 0x10;
  }
  *(uint *)(*(int *)(param_1 + 0xc) + 0x18) =
       *(uint *)(*(int *)(param_1 + 0xc) + 0x18) & ~(local_10 + 0x3c3808U) | local_10 + 0x3c3808U;
  return 0;
}



/* FUNCTION 0800a29c FUN_0800a29c SIZE 526 */

undefined4 FUN_0800a29c(int param_1)

{
  uint uVar1;
  undefined4 local_2c;
  undefined4 local_14;
  
  **(undefined4 **)(param_1 + 0x10c) = 0;
  **(uint **)(param_1 + 0x10) = **(uint **)(param_1 + 0x10) & 0xffffe7ff;
  if (*(char *)(param_1 + 0xb) == '\x01') {
    FUN_0800a1ea(param_1,3);
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x24) = 0x80;
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x28) = 0x200080;
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x104) = 0x8000a0;
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x108) = 0x200120;
    *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x10c) = 0x140;
  }
  FUN_0800a0ae(param_1,0x10);
  FUN_0800a0fe(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x14) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x18) = 0xffffffff;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x1c) = 0;
  for (uVar1 = 0; uVar1 < *(byte *)(param_1 + 1); uVar1 = uVar1 + 1) {
    if (**(int **)(param_1 + 0x18 + uVar1 * 4) < 0) {
      local_14 = 0x48000000;
    }
    else {
      local_14 = 0;
    }
    **(undefined4 **)(param_1 + 0x18 + uVar1 * 4) = local_14;
    *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar1 * 4) + 0x10) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar1 * 4) + 8) = 0xff;
  }
  for (uVar1 = 0; uVar1 < *(byte *)(param_1 + 1); uVar1 = uVar1 + 1) {
    if (**(int **)(param_1 + 0x54 + uVar1 * 4) < 0) {
      local_2c = 0x48000000;
    }
    else {
      local_2c = 0;
    }
    **(undefined4 **)(param_1 + 0x54 + uVar1 * 4) = local_2c;
    *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar1 * 4) + 0x10) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar1 * 4) + 8) = 0xff;
  }
  *(uint *)(*(int *)(param_1 + 0x10) + 0x10) =
       *(uint *)(*(int *)(param_1 + 0x10) + 0x10) & 0xfffffeff | 0x100;
  if (*(char *)(param_1 + 3) == '\x01') {
    *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x30) = 0x810103;
  }
  FUN_0800a202(param_1);
  return 0;
}



/* FUNCTION 0800a4aa FUN_0800a4aa SIZE 52 */

undefined4 FUN_0800a4aa(int param_1)

{
  uint uVar1;
  
  uVar1 = (*(uint *)(*(int *)(param_1 + 0x10) + 8) & 7) >> 1;
  if (uVar1 == 0) {
    return 3;
  }
  if (uVar1 != 1) {
    if (uVar1 == 2) {
      return 1;
    }
    if (uVar1 != 3) {
      return 0;
    }
  }
  return 2;
}



/* FUNCTION 0800a4de FUN_0800a4de SIZE 106 */

undefined8 FUN_0800a4de(int param_1)

{
  uint uVar1;
  uint local_c;
  
  local_c = **(uint **)(param_1 + 0x18);
  uVar1 = (*(uint *)(*(int *)(param_1 + 0x10) + 8) & 7) >> 1;
  if ((uVar1 != 0) && (uVar1 != 1)) {
    if (uVar1 == 2) {
      local_c = (local_c & 0xfffff800) + 3;
      goto code_r0x0800a526;
    }
    if (uVar1 != 3) goto code_r0x0800a526;
  }
  local_c = local_c & 0xfffff800;
code_r0x0800a526:
  **(uint **)(param_1 + 0x18) = local_c;
  *(uint *)(*(int *)(param_1 + 0x10) + 4) =
       *(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffeff | 0x100;
  return 0x10000000000;
}



/* FUNCTION 0800a548 FUN_0800a548 SIZE 152 */

undefined4 FUN_0800a548(int param_1,byte *param_2)

{
  uint *puVar1;
  uint local_14;
  
  if (param_2[1] == 1) {
    puVar1 = *(uint **)(param_1 + 0x18 + (uint)*param_2 * 4);
    local_14 = 1 << *param_2 & 0xffff;
  }
  else {
    puVar1 = *(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
    local_14 = (1 << *param_2) << 0x10;
  }
  if (-1 < (int)(*puVar1 << 0x10)) {
    *puVar1 = ((*puVar1 & 0xec33f800 | *(ushort *)(param_2 + 8) & 0x7ff | (param_2[3] & 3) << 0x12 |
               (param_2[6] & 0xf) << 0x16) + 0x10000000 & 0xffff7fff) + 0x8000;
  }
  *(uint *)(*(int *)(param_1 + 0x10) + 0x1c) = *(uint *)(*(int *)(param_1 + 0x10) + 0x1c) | local_14
  ;
  return 0;
}



/* FUNCTION 0800a5e0 FUN_0800a5e0 SIZE 94 */

undefined4 FUN_0800a5e0(int param_1,byte *param_2)

{
  undefined4 *puVar1;
  uint local_14;
  
  if (param_2[1] == 1) {
    puVar1 = *(undefined4 **)(param_1 + 0x18 + (uint)*param_2 * 4);
    local_14 = 1 << *param_2 & 0xffff;
  }
  else {
    puVar1 = *(undefined4 **)(param_1 + 0x54 + (uint)*param_2 * 4);
    local_14 = (1 << *param_2) << 0x10;
  }
  *puVar1 = 0;
  *(uint *)(*(int *)(param_1 + 0x10) + 0x1c) =
       *(uint *)(*(int *)(param_1 + 0x10) + 0x1c) & ~local_14;
  return 0;
}



/* FUNCTION 0800a63e FUN_0800a63e SIZE 502 */

longlong FUN_0800a63e(int param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  byte *local_20;
  uint local_1c;
  uint local_18;
  
  local_20 = param_2;
  if (param_2[1] == 1) {
    local_18 = **(uint **)(param_1 + 0x18 + (uint)*param_2 * 4);
    uVar2 = *(uint *)(*(int *)(param_1 + 0x18 + (uint)*param_2 * 4) + 0x10);
    if (*(int *)(param_2 + 0x14) == 0) {
      local_1c = uVar2 & 0xe0000000 | 0x80000;
    }
    else {
      uVar1 = ((*(int *)(param_2 + 0x14) + -1 + *(uint *)(param_2 + 8)) / *(uint *)(param_2 + 8) &
              0x3ff) << 0x13;
      local_1c = uVar2 & 0xe0000000 | *(uint *)(param_2 + 0x14) & 0x7ffff | uVar1;
      if (param_2[3] == 1) {
        local_1c = (uVar2 & 0x80000000 | *(uint *)(param_2 + 0x14) & 0x7ffff | uVar1) + 0x20000000;
      }
    }
    *(uint *)(*(int *)(param_1 + 0x18 + (uint)*param_2 * 4) + 0x10) = local_1c;
    if (*(char *)(param_1 + 3) == '\x01') {
      *(undefined4 *)(*(int *)(param_1 + 0x18 + (uint)*param_2 * 4) + 0x14) =
           *(undefined4 *)(param_2 + 0x10);
    }
    else if ((param_2[3] != 1) && (*(int *)(param_2 + 0x14) != 0)) {
      *(uint *)(*(int *)(param_1 + 0x10) + 0x34) =
           *(uint *)(*(int *)(param_1 + 0x10) + 0x34) | 1 << *param_2;
    }
    if (param_2[3] == 1) {
      local_20 = *(byte **)(*(int *)(param_1 + 0x10) + 8);
      if ((int)local_20 << 0x17 < 0) {
        local_18 = (local_18 & 0xefffffff) + 0x10000000;
      }
      else {
        local_18 = (local_18 & 0xdfffffff) + 0x20000000;
      }
    }
    **(int **)(param_1 + 0x18 + (uint)*param_2 * 4) =
         ((local_18 & 0xfbffffff) + 0x4000000 & 0x7fffffff) + 0x80000000;
    if (param_2[3] == 1) {
      FUN_08009e10(param_1,*(undefined4 *)(param_2 + 0xc),*param_2,*(undefined2 *)(param_2 + 0x14));
    }
  }
  else {
    local_18 = **(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
    uVar2 = *(uint *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x10);
    if (*(int *)(param_2 + 0x14) == 0) {
      local_1c = uVar2 & 0xe0000000 | *(uint *)(param_2 + 8) & 0x7ffff | 0x80000;
    }
    else {
      uVar1 = (uint)(*(int *)(param_2 + 8) + -1 + *(int *)(param_2 + 0x14)) / *(uint *)(param_2 + 8)
              & 0x3ff;
      local_1c = uVar2 & 0xe0000000 | uVar1 << 0x13 | *(int *)(param_2 + 8) * uVar1 & 0x7ffff;
    }
    *(uint *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x10) = local_1c;
    if (*(char *)(param_1 + 3) == '\x01') {
      *(undefined4 *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x14) =
           *(undefined4 *)(param_2 + 0x10);
    }
    if (param_2[3] == 1) {
      if (param_2[5] == 0) {
        local_18 = (local_18 & 0xefffffff) + 0x10000000;
      }
      else {
        local_18 = (local_18 & 0xdfffffff) + 0x20000000;
      }
    }
    **(int **)(param_1 + 0x54 + (uint)*param_2 * 4) =
         ((local_18 & 0xfbffffff) + 0x4000000 & 0x7fffffff) + 0x80000000;
  }
  return ZEXT48(local_20) << 0x20;
}



/* FUNCTION 0800a834 FUN_0800a834 SIZE 342 */

longlong FUN_0800a834(int param_1,byte *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint local_20;
  
  if (param_2[1] == 1) {
    puVar1 = *(uint **)(param_1 + 0x18);
    uVar2 = *puVar1;
    local_20 = puVar1[4];
    if (*(int *)(param_2 + 0x14) == 0) {
      local_20 = local_20 & 0xffe7ff80;
    }
    else {
      if (*(uint *)(param_2 + 8) < *(uint *)(param_2 + 0x14)) {
        *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_2 + 8);
        local_20 = local_20 & 0xffffff80 | param_2[8] & 0x7f;
      }
      else {
        local_20 = local_20 & 0xffffff80 | param_2[0x14] & 0x7f;
      }
      local_20 = local_20 & 0xffe7ffff;
    }
    local_20 = local_20 + 0x80000;
    puVar1[4] = local_20;
    if (*(char *)(param_1 + 3) == '\x01') {
      *(undefined4 *)(*(int *)(param_1 + 0x18 + (uint)*param_2 * 4) + 0x14) =
           *(undefined4 *)(param_2 + 0x10);
    }
    *puVar1 = ((uVar2 & 0xfbffffff) + 0x4000000 & 0x7fffffff) + 0x80000000;
    if ((*(char *)(param_1 + 3) == '\0') && (*(int *)(param_2 + 0x14) != 0)) {
      *(uint *)(*(int *)(param_1 + 0x10) + 0x34) =
           *(uint *)(*(int *)(param_1 + 0x10) + 0x34) | 1 << *param_2;
    }
  }
  else {
    uVar2 = **(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
    uVar3 = *(uint *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x10);
    if (*(int *)(param_2 + 0x14) == 0) {
      local_20 = uVar3 & 0xffe7ff80 | param_2[8] & 0x7f;
    }
    else {
      *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_2 + 8);
      local_20 = uVar3 & 0xffe7ff80 | param_2[8] & 0x7f;
    }
    local_20 = local_20 + 0x80000;
    *(uint *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x10) = local_20;
    if (*(char *)(param_1 + 3) == '\x01') {
      *(undefined4 *)(*(int *)(param_1 + 0x54 + (uint)*param_2 * 4) + 0x14) =
           *(undefined4 *)(param_2 + 0x10);
    }
    **(int **)(param_1 + 0x54 + (uint)*param_2 * 4) =
         ((uVar2 & 0xfbffffff) + 0x4000000 & 0x7fffffff) + 0x80000000;
  }
  return (ulonglong)local_20 << 0x20;
}



/* FUNCTION 0800a98a FUN_0800a98a SIZE 100 */

undefined4 FUN_0800a98a(int param_1,byte *param_2)

{
  uint *puVar1;
  uint local_10;
  
  if (param_2[1] == 1) {
    puVar1 = *(uint **)(param_1 + 0x18 + (uint)*param_2 * 4);
    local_10 = *puVar1;
    if ((int)local_10 < 0) {
      local_10 = (local_10 & 0xbfffffff) + 0x40000000;
    }
    *puVar1 = (local_10 & 0xffdfffff) + 0x200000;
  }
  else {
    puVar1 = *(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
    *puVar1 = (*puVar1 & 0xffdfffff) + 0x200000;
  }
  return 0;
}



/* FUNCTION 0800a9ee FUN_0800a9ee SIZE 80 */

undefined4 FUN_0800a9ee(int param_1,byte *param_2)

{
  uint *puVar1;
  uint local_10;
  
  if (param_2[1] == 1) {
    puVar1 = *(uint **)(param_1 + 0x18 + (uint)*param_2 * 4);
  }
  else {
    puVar1 = *(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
  }
  local_10 = *puVar1 & 0xffdfffff;
  if ((param_2[3] == 3) || (param_2[3] == 2)) {
    local_10 = (*puVar1 & 0xefdfffff) + 0x10000000;
  }
  *puVar1 = local_10;
  return 0;
}



/* FUNCTION 0800aa3e FUN_0800aa3e SIZE 16 */

uint FUN_0800aa3e(int param_1)

{
  return (*(uint *)(*(int *)(param_1 + 0x10) + 0x18) & *(uint *)(*(int *)(param_1 + 0x10) + 0x1c))
         >> 0x10;
}



/* FUNCTION 0800aa4e FUN_0800aa4e SIZE 20 */

uint FUN_0800aa4e(int param_1,int param_2)

{
  return *(uint *)(*(int *)(param_1 + 0x54 + param_2 * 4) + 8) &
         *(uint *)(*(int *)(param_1 + 0x10) + 0x14);
}



/* FUNCTION 0800aa62 FUN_0800aa62 SIZE 16 */

uint FUN_0800aa62(int param_1)

{
  return *(uint *)(*(int *)(param_1 + 0x10) + 0x18) & *(uint *)(*(int *)(param_1 + 0x10) + 0x1c) &
         0xffff;
}



/* FUNCTION 0800aa72 FUN_0800aa72 SIZE 98 */

void FUN_0800aa72(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10) = 0xc0080018;
  if (*(char *)(param_1 + 3) == '\x01') {
    *(int *)(*(int *)(param_1 + 0x54) + 0x14) = param_1 + 0x5cc;
    **(undefined4 **)(param_1 + 0x54) = 0x80008000;
  }
  return;
}



/* FUNCTION 0800aad4 FUN_0800aad4 SIZE 106 */

void FUN_0800aad4(int param_1)

{
  if ((*(int *)(param_1 + 0x118) != 0) && ((*(uint *)(*(int *)(param_1 + 0x10) + 8) & 1) != 0)) {
    if (*(char *)(param_1 + 10) != '\0') {
      **(uint **)(param_1 + 0x10c) = *(uint *)(param_1 + 0x10c) & 0xfffffffc;
    }
    *(uint *)(*(int *)(param_1 + 0x10) + 4) = *(uint *)(*(int *)(param_1 + 0x10) + 4) | 1;
    FUN_080092ac(5);
    *(uint *)(*(int *)(param_1 + 0x10) + 4) = *(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffffe;
  }
  return;
}



/* FUNCTION 0800ab3e FUN_0800ab3e SIZE 54 */

void FUN_0800ab3e(int param_1)

{
  if ((*(char *)(param_1 + 10) != '\0') && ((*(uint *)(*(int *)(param_1 + 0x10) + 8) & 1) != 0)) {
    **(uint **)(param_1 + 0x10c) = *(uint *)(param_1 + 0x10c) & 0xfffffffc;
  }
  return;
}



/* FUNCTION 0800ab74 FUN_0800ab74 SIZE 82 */

void FUN_0800ab74(int param_1)

{
  uint uVar1;
  
  *(undefined1 *)(param_1 + 0x112) = 1;
  for (uVar1 = 0; uVar1 < *(byte *)(param_1 + 1); uVar1 = uVar1 + 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar1 * 4) + 8) = 0xff;
    *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar1 * 4) + 8) = 0xff;
  }
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x14) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x1c) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x18) = 0xffffffff;
  FUN_0800a0fe(param_1);
  FUN_0800a0ae(param_1,0x10);
  return;
}



/* FUNCTION 0800abc6 FUN_0800abc6 SIZE 106 */

undefined4 FUN_0800abc6(int param_1,byte *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2[1] == 1) {
    iVar2 = **(int **)(param_1 + 0x18 + (uint)*param_2 * 4);
    if (iVar2 << 10 < 0) {
      uVar1 = 0x10;
    }
    else if (iVar2 << 0xe < 0) {
      uVar1 = 0x20;
    }
    else {
      uVar1 = 0x30;
    }
  }
  else {
    iVar2 = **(int **)(param_1 + 0x54 + (uint)*param_2 * 4);
    if (iVar2 << 10 < 0) {
      uVar1 = 0x1000;
    }
    else if (iVar2 << 0xe < 0) {
      uVar1 = 0x2000;
    }
    else {
      uVar1 = 0x3000;
    }
  }
  return uVar1;
}



/* FUNCTION 0800ac30 FUN_0800ac30 SIZE 282 */

void FUN_0800ac30(int param_1,byte *param_2,int param_3)

{
  uint *puVar1;
  uint local_18;
  
  if (param_2[1] == 1) {
    puVar1 = *(uint **)(param_1 + 0x18 + (uint)*param_2 * 4);
    local_18 = *puVar1;
    if (param_3 == 0x10) {
      FUN_0800a98a(param_1,param_2);
      return;
    }
    if (param_3 == 0x20) {
      local_18 = (local_18 & 0xf7ffffff) + 0x8000000;
    }
    else if (param_3 == 0x30) {
      if ((int)(local_18 << 10) < 0) {
        param_2[5] = 0;
        FUN_0800a9ee(param_1,param_2);
        return;
      }
      local_18 = (((local_18 & 0xfbffffff) + 0x4000000 & 0xffff7fff) + 0x8000 & 0x7fffffff) +
                 0x80000000;
    }
    else if (param_3 == 0) {
      local_18 = local_18 & 0xffff7fff;
    }
  }
  else {
    puVar1 = *(uint **)(param_1 + 0x54 + (uint)*param_2 * 4);
    local_18 = *puVar1;
    if (param_3 == 0x1000) {
      local_18 = (local_18 & 0xffdfffff) + 0x200000;
    }
    else if (param_3 == 0x2000) {
      local_18 = (local_18 & 0xf7ffffff) + 0x8000000;
    }
    else if (param_3 == 0x3000) {
      if ((int)(local_18 << 10) < 0) {
        param_2[5] = 0;
        FUN_0800a9ee(param_1,param_2);
        return;
      }
      local_18 = (((local_18 & 0xfbffffff) + 0x4000000 & 0xffff7fff) + 0x8000 & 0x7fffffff) +
                 0x80000000;
    }
    else if (param_3 == 0) {
      local_18 = local_18 & 0xffff7fff;
    }
  }
  *puVar1 = local_18;
  return;
}



/* FUNCTION 0800ad4a FUN_0800ad4a SIZE 156 */

void FUN_0800ad4a(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  
  FUN_08009e78(param_1,param_2);
  *(undefined1 *)(param_1 + 0x112) = 1;
  *(undefined1 *)(param_1 + 0x114) = 0;
  for (uVar2 = 0; uVar2 < *(byte *)(param_1 + 1); uVar2 = uVar2 + 1) {
    puVar1 = (undefined1 *)(param_1 + 0x11c + uVar2 * 0x28);
    puVar1[1] = 1;
    *puVar1 = (char)uVar2;
    *(short *)(puVar1 + 6) = (short)uVar2;
    puVar1[3] = 0;
    *(undefined4 *)(puVar1 + 8) = 0x40;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    *(undefined4 *)(puVar1 + 0x14) = 0;
  }
  for (uVar2 = 0; uVar2 < *(byte *)(param_1 + 1); uVar2 = uVar2 + 1) {
    puVar1 = (undefined1 *)(param_1 + 0x374 + uVar2 * 0x28);
    puVar1[1] = 0;
    *puVar1 = (char)uVar2;
    *(short *)(puVar1 + 6) = (short)uVar2;
    puVar1[3] = 0;
    *(undefined4 *)(puVar1 + 8) = 0x40;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    *(undefined4 *)(puVar1 + 0x14) = 0;
  }
  FUN_0800a08c(param_1);
  FUN_08009f44(param_1);
  FUN_0800a144(param_1,0);
  FUN_0800a29c(param_1);
  FUN_0800a06a(param_1);
  return;
}



/* FUNCTION 0800ade6 FUN_0800ade6 SIZE 104 */

undefined4 FUN_0800ade6(int param_1,uint param_2,undefined4 param_3,int param_4)

{
  byte *pbVar1;
  
  if ((param_2 & 0x80) == 0x80) {
    pbVar1 = (byte *)(param_1 + 0x11c + (param_2 & 0x7f) * 0x28);
  }
  else {
    pbVar1 = (byte *)(param_1 + 0x374 + (param_2 & 0x7f) * 0x28);
  }
  *pbVar1 = (byte)param_2 & 0x7f;
  pbVar1[1] = (byte)((param_2 & 0x80) >> 7);
  *(undefined4 *)(pbVar1 + 8) = param_3;
  pbVar1[3] = (byte)param_4;
  if (pbVar1[1] != 0) {
    *(ushort *)(pbVar1 + 6) = (ushort)*pbVar1;
  }
  if (param_4 == 2) {
    pbVar1[4] = 0;
  }
  FUN_0800a548(param_1,pbVar1);
  return 0;
}



/* FUNCTION 0800ae4e FUN_0800ae4e SIZE 74 */

undefined4 FUN_0800ae4e(int param_1,uint param_2)

{
  byte *pbVar1;
  
  if ((param_2 & 0x80) == 0x80) {
    pbVar1 = (byte *)(param_1 + 0x11c + (param_2 & 0x7f) * 0x28);
  }
  else {
    pbVar1 = (byte *)(param_1 + 0x374 + (param_2 & 0x7f) * 0x28);
  }
  *pbVar1 = (byte)param_2 & 0x7f;
  pbVar1[1] = (byte)((param_2 & 0x80) >> 7);
  FUN_0800a5e0(param_1,pbVar1);
  return 0;
}



/* FUNCTION 0800ae98 FUN_0800ae98 SIZE 82 */

undefined4 FUN_0800ae98(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_1 + 0x374 + (param_2 & 0x7f) * 0x28);
  *(undefined4 *)(pbVar1 + 0xc) = param_3;
  *(undefined4 *)(pbVar1 + 0x14) = param_4;
  pbVar1[0x18] = 0;
  pbVar1[0x19] = 0;
  pbVar1[0x1a] = 0;
  pbVar1[0x1b] = 0;
  pbVar1[1] = 0;
  *pbVar1 = (byte)param_2 & 0x7f;
  if (*(char *)(param_1 + 3) == '\x01') {
    *(undefined4 *)(pbVar1 + 0x10) = param_3;
  }
  if (*pbVar1 == 0) {
    FUN_0800a834(param_1,pbVar1);
  }
  else {
    FUN_0800a63e(param_1,pbVar1);
  }
  return 0;
}



/* FUNCTION 0800aeea FUN_0800aeea SIZE 78 */

undefined4 FUN_0800aeea(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_1 + 0x11c + (param_2 & 0x7f) * 0x28);
  pbVar1[1] = 1;
  *pbVar1 = (byte)param_2 & 0x7f;
  *(undefined4 *)(pbVar1 + 0xc) = param_3;
  *(undefined4 *)(pbVar1 + 0x10) = param_3;
  pbVar1[0x18] = 0;
  pbVar1[0x19] = 0;
  pbVar1[0x1a] = 0;
  pbVar1[0x1b] = 0;
  *(undefined4 *)(pbVar1 + 0x14) = param_4;
  if (*pbVar1 == 0) {
    FUN_0800a834(param_1,pbVar1);
  }
  else {
    FUN_0800a63e(param_1,pbVar1);
  }
  return 0;
}



/* FUNCTION 0800af38 FUN_0800af38 SIZE 72 */

undefined4 FUN_0800af38(int param_1,uint param_2)

{
  byte *pbVar1;
  
  if ((param_2 & 0x80) == 0x80) {
    pbVar1 = (byte *)(param_1 + 0x11c + (param_2 & 0x7f) * 0x28);
  }
  else {
    pbVar1 = (byte *)(param_1 + 0x374 + param_2 * 0x28);
  }
  pbVar1[2] = 1;
  *pbVar1 = (byte)param_2 & 0x7f;
  pbVar1[1] = (byte)((param_2 & 0xff) >> 7);
  FUN_0800a98a(param_1,pbVar1);
  return 0;
}



/* FUNCTION 0800af80 FUN_0800af80 SIZE 72 */

undefined4 FUN_0800af80(int param_1,uint param_2)

{
  byte *pbVar1;
  
  if ((param_2 & 0x80) == 0x80) {
    pbVar1 = (byte *)(param_1 + 0x11c + (param_2 & 0x7f) * 0x28);
  }
  else {
    pbVar1 = (byte *)(param_1 + 0x374 + param_2 * 0x28);
  }
  pbVar1[2] = 0;
  *pbVar1 = (byte)param_2 & 0x7f;
  pbVar1[1] = (byte)((param_2 & 0xff) >> 7);
  FUN_0800a9ee(param_1,pbVar1);
  return 0;
}



/* FUNCTION 0800afc8 FUN_0800afc8 SIZE 36 */

undefined4 FUN_0800afc8(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x80) == 0x80) {
    FUN_0800a0ae(param_1,param_2 & 0x7f);
  }
  else {
    FUN_0800a0fe(param_1);
  }
  return 0;
}



/* FUNCTION 0800afec FUN_0800afec SIZE 28 */

void FUN_0800afec(int param_1,uint param_2)

{
  **(uint **)(param_1 + 0x10) = **(uint **)(param_1 + 0x10) | (param_2 & 0x7f) << 4;
  return;
}



/* FUNCTION 0800b008 FUN_0800b008 SIZE 32 */

void FUN_0800b008(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x10) + 4) = *(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffffd;
  FUN_080092ac(3);
  return;
}



/* FUNCTION 0800b028 FUN_0800b028 SIZE 34 */

void FUN_0800b028(int param_1)

{
  *(uint *)(*(int *)(param_1 + 0x10) + 4) =
       (*(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffffd) + 2;
  FUN_080092ac(3);
  return;
}



/* FUNCTION 0800b08a FUN_0800b08a SIZE 62 */

void FUN_0800b08a(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((param_2 & 0x80) == 0x80) {
    iVar1 = param_1 + 0x11c + (param_2 & 0x7f) * 0x28;
  }
  else {
    iVar1 = param_1 + 0x374 + param_2 * 0x28;
  }
  FUN_0800ac30(param_1,iVar1,param_3);
  return;
}



/* FUNCTION 0800b0c8 FUN_0800b0c8 SIZE 40 */

undefined4 FUN_0800b0c8(int param_1)

{
  (**(code **)(*DAT_0800b4cc + 0x20))(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x200000;
  return 1;
}



/* FUNCTION 0800b0f0 FUN_0800b0f0 SIZE 40 */

undefined4 FUN_0800b0f0(int param_1)

{
  (**(code **)(*DAT_0800b4cc + 0x1c))(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x100000;
  return 1;
}



/* FUNCTION 0800b118 FUN_0800b118 SIZE 102 */

undefined4 FUN_0800b118(int param_1)

{
  uint uVar1;
  int iVar2;
  int local_10;
  
  FUN_0800a4de(param_1);
  uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + 0xc);
  iVar2 = FUN_0800a4aa(param_1);
  if (iVar2 == 3) {
    *(undefined1 *)(param_1 + 2) = 0;
    *(undefined2 *)(param_1 + 4) = 0x200;
    local_10 = (uVar1 & 0xffffc3ff) + 0x2400;
  }
  else {
    *(undefined1 *)(param_1 + 2) = 1;
    *(undefined2 *)(param_1 + 4) = 0x40;
    local_10 = (uVar1 & 0xffffc3ff) + 0x1400;
  }
  *(int *)(*(int *)(param_1 + 0xc) + 0xc) = local_10;
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x2000;
  return 1;
}



/* FUNCTION 0800b17e FUN_0800b17e SIZE 254 */

undefined4 FUN_0800b17e(int param_1)

{
  uint uVar1;
  
  *(uint *)(*(int *)(param_1 + 0x10) + 4) = *(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffffe;
  FUN_0800a0ae(param_1,0);
  for (uVar1 = 0; uVar1 < *(byte *)(param_1 + 1); uVar1 = uVar1 + 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar1 * 4) + 8) = 0xff;
    *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar1 * 4) + 8) = 0xff;
  }
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x18) = 0xffffffff;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x1c) = 0x10001;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x14) = 0xb;
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10) = 0xb;
  **(uint **)(param_1 + 0x10) = **(uint **)(param_1 + 0x10) & 0xfffff80f;
  FUN_0800aa72(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x1000;
  (**(code **)(*DAT_0800b4cc + 0x10))(param_1);
  return 1;
}



/* FUNCTION 0800b27c FUN_0800b27c SIZE 168 */

undefined4 FUN_0800b27c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  *(uint *)(*(int *)(param_1 + 0xc) + 0x18) = *(uint *)(*(int *)(param_1 + 0xc) + 0x18) & 0xffffffef
  ;
  uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + 0x20);
  iVar2 = param_1 + 0x374 + (uVar1 & 0xf) * 0x28;
  switch((uVar1 & 0x1fffff) >> 0x11) {
  case 1:
    break;
  case 2:
    if ((uVar1 & 0x7fff) >> 4 != 0) {
      FUN_08009e50(param_1,*(undefined4 *)(iVar2 + 0xc),(uVar1 & 0x7fff) >> 4);
      *(uint *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + ((uVar1 & 0x7fff) >> 4);
      *(uint *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) + ((uVar1 & 0x7fff) >> 4);
    }
    break;
  case 3:
    break;
  case 4:
    break;
  case 6:
    FUN_08009e50(param_1,param_1 + 0x5cc,8);
    *(uint *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) + ((uVar1 & 0x7fff) >> 4);
  }
  *(uint *)(*(int *)(param_1 + 0xc) + 0x18) = *(uint *)(*(int *)(param_1 + 0xc) + 0x18) | 0x10;
  return 1;
}



/* FUNCTION 0800b32c FUN_0800b32c SIZE 38 */

undefined4 FUN_0800b32c(int param_1)

{
  (**(code **)(*DAT_0800b4cc + 0xc))(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 8;
  return 1;
}



/* FUNCTION 0800b352 FUN_0800b352 SIZE 158 */

undefined4 FUN_0800b352(int param_1)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = *(char *)(param_1 + 0x112);
  (**(code **)(*DAT_0800b4cc + 0x14))(param_1);
  uVar2 = *(uint *)(*(int *)(param_1 + 0x10) + 8);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x800;
  if ((((*(char *)(param_1 + 10) != '\0') && ((uVar2 & 1) != 0)) &&
      (*(char *)(param_1 + 0x115) == '\x01')) && (cVar1 == '\x03')) {
    **(uint **)(param_1 + 0x10c) = **(uint **)(param_1 + 0x10c) | 1;
    **(uint **)(param_1 + 0x10c) = **(uint **)(param_1 + 0x10c) | 3;
    *DAT_0800b4d0 = *DAT_0800b4d0 | 6;
  }
  return 1;
}



/* FUNCTION 0800b3f0 FUN_0800b3f0 SIZE 100 */

undefined8 FUN_0800b3f0(int param_1,uint param_2)

{
  uint local_18;
  
  local_18 = param_2;
  if (*(char *)(param_1 + 10) != '\0') {
    local_18 = *(uint *)(param_1 + 0x10c) & 0xfffffffc;
    **(uint **)(param_1 + 0x10c) = local_18;
  }
  *(uint *)(*(int *)(param_1 + 0x10) + 4) = *(uint *)(*(int *)(param_1 + 0x10) + 4) & 0xfffffffe;
  (**(code **)(*DAT_0800b4cc + 0x18))(param_1);
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 0x80000000;
  return CONCAT44(local_18,1);
}



/* FUNCTION 0800b454 FUN_0800b454 SIZE 146 */

undefined4 FUN_0800b454(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint local_20;
  
  iVar1 = param_1 + 0x11c + param_2 * 0x28;
  uVar2 = *(int *)(iVar1 + 0x14) - *(int *)(iVar1 + 0x18);
  if (*(uint *)(iVar1 + 8) < uVar2) {
    uVar2 = *(uint *)(iVar1 + 8);
  }
  local_20 = *(uint *)(*(int *)(param_1 + 0x18 + param_2 * 4) + 0x18);
  while (((uVar2 + 3 >> 2 < (local_20 & 0xffff) &&
          (*(uint *)(iVar1 + 0x18) < *(uint *)(iVar1 + 0x14))) && (*(int *)(iVar1 + 0x14) != 0))) {
    uVar2 = *(int *)(iVar1 + 0x14) - *(int *)(iVar1 + 0x18);
    if (*(uint *)(iVar1 + 8) < uVar2) {
      uVar2 = *(uint *)(iVar1 + 8);
    }
    FUN_08009e10(param_1,*(undefined4 *)(iVar1 + 0xc),param_2 & 0xff,uVar2 & 0xffff);
    *(uint *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + uVar2;
    *(uint *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + uVar2;
    local_20 = *(uint *)(*(int *)(param_1 + 0x18 + param_2 * 4) + 0x18);
  }
  return 1;
}



/* FUNCTION 0800b4ee FUN_0800b4ee SIZE 40 */

uint FUN_0800b4ee(int param_1,uint param_2)

{
  return *(uint *)(*(int *)(param_1 + 0x18 + param_2 * 4) + 8) &
         (*(uint *)(*(int *)(param_1 + 0x10) + 0x10) |
         (*(uint *)(*(int *)(param_1 + 0x10) + 0x34) >> (param_2 & 0xff) & 1) << 7);
}



/* FUNCTION 0800b516 FUN_0800b516 SIZE 320 */

undefined4 FUN_0800b516(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint local_18;
  
  uVar2 = 0;
  for (uVar1 = FUN_0800aa62(param_1); uVar1 != 0; uVar1 = uVar1 >> 1) {
    if ((uVar1 & 1) != 0) {
      local_18 = FUN_0800b4ee(param_1,uVar2 & 0xff);
      if ((local_18 & 1) != 0) {
        *(uint *)(*(int *)(param_1 + 0x10) + 0x34) =
             *(uint *)(*(int *)(param_1 + 0x10) + 0x34) & ~(1 << (uVar2 & 0xff));
        local_18 = 1;
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 1;
        (**(code **)(*DAT_0800b83c + 4))(param_1,uVar2 & 0xff);
        if (((*(char *)(param_1 + 3) == '\x01') && (uVar2 == 0)) &&
           (*(char *)(param_1 + 0x111) == '\x04')) {
          FUN_0800aa72(param_1);
        }
      }
      if ((int)(local_18 << 0x1c) < 0) {
        local_18 = 8;
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 8;
      }
      if ((int)(local_18 << 0x1b) < 0) {
        local_18 = 0x10;
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 0x10;
      }
      if ((int)(local_18 << 0x19) < 0) {
        local_18 = 0x40;
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 0x40;
      }
      if ((int)(local_18 << 0x1e) < 0) {
        local_18 = 2;
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 2;
      }
      if ((int)(local_18 << 0x18) < 0) {
        FUN_0800b454(param_1,uVar2);
        *(undefined4 *)(*(int *)(param_1 + 0x18 + uVar2 * 4) + 8) = 0x80;
      }
    }
    uVar2 = uVar2 + 1;
  }
  return 1;
}



/* FUNCTION 0800b656 FUN_0800b656 SIZE 252 */

undefined4 FUN_0800b656(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint local_14;
  
  uVar2 = 0;
  for (uVar1 = FUN_0800aa3e(param_1); uVar1 != 0; uVar1 = uVar1 >> 1) {
    if ((uVar1 & 1) != 0) {
      local_14 = FUN_0800aa4e(param_1,uVar2 & 0xff);
      if ((local_14 & 1) != 0) {
        local_14 = 1;
        *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar2 * 4) + 8) = 1;
        if (*(char *)(param_1 + 3) == '\x01') {
          *(uint *)(param_1 + uVar2 * 0x28 + 0x38c) =
               *(int *)(param_1 + uVar2 * 0x28 + 0x37c) -
               (*(uint *)(*(int *)(param_1 + 0x54 + uVar2 * 4) + 0x10) & 0x7ffff);
        }
        (**(code **)*DAT_0800b83c)(param_1,uVar2 & 0xff);
        if (((*(char *)(param_1 + 3) == '\x01') && (uVar2 == 0)) &&
           (*(char *)(param_1 + 0x111) == '\x05')) {
          FUN_0800aa72(param_1);
        }
      }
      if ((int)(local_14 << 0x1e) < 0) {
        local_14 = 2;
        *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar2 * 4) + 8) = 2;
      }
      if ((int)(local_14 << 0x1c) < 0) {
        (**(code **)(*DAT_0800b83c + 8))(param_1);
        *(undefined4 *)(*(int *)(param_1 + 0x54 + uVar2 * 4) + 8) = 8;
      }
    }
    uVar2 = uVar2 + 1;
  }
  return 1;
}



/* FUNCTION 0800b752 FUN_0800b752 SIZE 234 */

uint FUN_0800b752(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = FUN_0800a1a8(param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_0800a1d2(param_1);
    if (iVar1 == 0) {
      return 0;
    }
    if (iVar1 << 0xc < 0) {
      uVar3 = FUN_0800b656(param_1);
    }
    if (iVar1 << 0xd < 0) {
      uVar2 = FUN_0800b516(param_1);
      uVar3 = uVar3 | uVar2;
      *DAT_0800b840 = *DAT_0800b840 + 1;
    }
    if (iVar1 << 0x1e < 0) {
      *(undefined4 *)(*(int *)(param_1 + 0xc) + 0x14) = 2;
    }
    if (iVar1 < 0) {
      uVar2 = FUN_0800b3f0(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0x14 < 0) {
      uVar2 = FUN_0800b352(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0x1c < 0) {
      uVar2 = FUN_0800b32c(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0x1b < 0) {
      uVar2 = FUN_0800b27c(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0x13 < 0) {
      uVar2 = FUN_0800b17e(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0x12 < 0) {
      uVar2 = FUN_0800b118(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 0xb < 0) {
      uVar2 = FUN_0800b0f0(param_1);
      uVar3 = uVar3 | uVar2;
    }
    if (iVar1 << 10 < 0) {
      uVar2 = FUN_0800b0c8(param_1);
      uVar3 = uVar3 | uVar2;
    }
  }
  return uVar3;
}



/* FUNCTION 0800b844 FUN_0800b844 SIZE 34 */

void FUN_0800b844(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_20 = param_1;
  uStack_1c = param_4;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_0800ba0e(param_2,&local_20,&uStack_8,DAT_0800b868 + 0x800b850);
  FUN_0800ba34(0,&local_20);
  return;
}



/* FUNCTION 0800b86c FUN_0800b86c SIZE 104 */

undefined4 FUN_0800b86c(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = 0;
  do {
    param_1[8] = iVar1;
LAB_0800b878:
    iVar1 = (*(code *)param_1[3])(param_1);
    if (iVar1 == 0) {
LAB_0800b8ce:
      return param_1[8];
    }
    if (iVar1 == 0x25) {
      uVar3 = 0;
      iVar1 = (*(code *)param_1[3])(param_1);
      if (iVar1 == 0) goto LAB_0800b8ce;
      if (iVar1 - 0x41U < 0x1a) {
        iVar1 = iVar1 + 0x20;
        uVar3 = 0x800;
      }
      *param_1 = uVar3;
      iVar2 = FUN_080001fc(param_1,iVar1,param_2);
      if (iVar2 == 0) goto LAB_0800b884;
      if (iVar2 == 1) {
        param_2 = param_2 + 4;
      }
      else {
        param_2 = (param_2 + 7U & 0xfffffff8) + 8;
      }
      goto LAB_0800b878;
    }
LAB_0800b884:
    (*(code *)param_1[1])(iVar1,param_1[2]);
    iVar1 = param_1[8] + 1;
  } while( true );
}



/* FUNCTION 0800b8d4 FUN_0800b8d4 SIZE 82 */

byte * FUN_0800b8d4(byte *param_1,undefined1 *param_2,uint param_3)

{
  uint uVar1;
  undefined1 *puVar2;
  
  if (param_3 == 1) {
    uVar1 = 1;
  }
  else {
    if ((int)((uint)*param_1 << 0x1a) < 0) {
      param_3 = *(uint *)(param_1 + 0x1c);
    }
    for (uVar1 = 0; (uVar1 < param_3 && (param_2[uVar1] != '\0')); uVar1 = uVar1 + 1) {
    }
  }
  puVar2 = param_2 + uVar1;
  *(uint *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) - uVar1;
  *(uint *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + uVar1;
  for (; param_2 < puVar2; param_2 = param_2 + 1) {
    (**(code **)(param_1 + 4))(*param_2,*(undefined4 *)(param_1 + 8));
  }
  return param_1;
}



/* FUNCTION 0800b926 FUN_0800b926 SIZE 238 */

undefined8 FUN_0800b926(uint *param_1,uint *param_2,uint param_3,uint param_4)

{
  bool bVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  byte *pbVar5;
  byte bVar6;
  undefined2 uVar7;
  byte in_r12;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  
  puVar4 = param_2;
  if (3 < param_3) {
    uVar8 = (uint)param_1 & 3;
    puVar2 = param_1;
    uVar9 = uVar8;
    if (uVar8 != 0) {
      bVar6 = (byte)*param_2;
      puVar4 = (uint *)((int)param_2 + 1);
      if (uVar8 < 3) {
        puVar4 = (uint *)((int)param_2 + 2);
        uVar9 = (uint)*(byte *)((int)param_2 + 1);
      }
      *(byte *)param_1 = bVar6;
      param_2 = puVar4;
      if (uVar8 < 2) {
        param_2 = (uint *)((int)puVar4 + 1);
        bVar6 = (byte)*puVar4;
      }
      param_3 = (param_3 + uVar8) - 4;
      puVar4 = (uint *)((int)param_1 + 1);
      if (uVar8 < 3) {
        puVar4 = (uint *)((int)param_1 + 2);
        *(byte *)((int)param_1 + 1) = (byte)uVar9;
      }
      puVar2 = puVar4;
      if (uVar8 < 2) {
        puVar2 = (uint *)((int)puVar4 + 1);
        *(byte *)puVar4 = bVar6;
      }
    }
    param_4 = (uint)param_2 & 3;
    if (param_4 == 0) {
      uVar9 = 0;
      while (uVar8 = param_3 - 0x20, 0x1f < param_3) {
        uVar9 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        *puVar2 = *param_2;
        puVar2[1] = uVar9;
        puVar2[2] = uVar10;
        puVar2[3] = uVar11;
        uVar9 = param_2[4];
        uVar10 = param_2[5];
        uVar11 = param_2[6];
        uVar12 = param_2[7];
        param_2 = param_2 + 8;
        puVar2[4] = uVar9;
        puVar2[5] = uVar10;
        puVar2[6] = uVar11;
        puVar2[7] = uVar12;
        puVar2 = puVar2 + 8;
        param_3 = uVar8;
      }
      if ((uVar8 & 0x10) != 0) {
        uVar9 = *param_2;
        uVar10 = param_2[1];
        uVar11 = param_2[2];
        uVar12 = param_2[3];
        param_2 = param_2 + 4;
        *puVar2 = uVar9;
        puVar2[1] = uVar10;
        puVar2[2] = uVar11;
        puVar2[3] = uVar12;
        puVar2 = puVar2 + 4;
      }
      if ((int)(param_3 << 0x1c) < 0) {
        uVar9 = *param_2;
        uVar10 = param_2[1];
        param_2 = param_2 + 2;
        *puVar2 = uVar9;
        puVar2[1] = uVar10;
        puVar2 = puVar2 + 2;
      }
      puVar3 = puVar2;
      puVar4 = param_2;
      if ((uVar8 & 4) != 0) {
        puVar4 = param_2 + 1;
        uVar9 = *param_2;
        puVar3 = puVar2 + 1;
        *puVar2 = uVar9;
      }
      uVar7 = (undefined2)uVar9;
      if ((uVar8 & 3) == 0) {
        return CONCAT44(puVar4,puVar3);
      }
      bVar1 = (uVar8 & 2) != 0;
      param_3 = param_3 << 0x1f;
      bVar13 = (int)param_3 < 0;
      puVar2 = puVar4;
      if (bVar1) {
        puVar2 = (uint *)((int)puVar4 + 2);
        uVar7 = (undefined2)*puVar4;
      }
      puVar4 = puVar2;
      if (bVar13) {
        puVar4 = (uint *)((int)puVar2 + 1);
        param_3 = (uint)(byte)*puVar2;
      }
      puVar2 = puVar3;
      if (bVar1) {
        puVar2 = (uint *)((int)puVar3 + 2);
        *(undefined2 *)puVar3 = uVar7;
      }
      puVar3 = puVar2;
      if (bVar13) {
        puVar3 = (uint *)((int)puVar2 + 1);
        *(byte *)puVar2 = (byte)param_3;
      }
      return CONCAT44(puVar4,puVar3);
    }
    while( true ) {
      in_r12 = (byte)uVar9;
      if (param_3 < 8) break;
      puVar4 = param_2 + 1;
      param_4 = *param_2;
      param_2 = param_2 + 2;
      uVar9 = *puVar4;
      *puVar2 = param_4;
      puVar2[1] = uVar9;
      puVar2 = puVar2 + 2;
      param_3 = param_3 - 8;
    }
    param_3 = param_3 - 4;
    param_1 = puVar2;
    puVar4 = param_2;
    if (-1 < (int)param_3) {
      puVar4 = param_2 + 1;
      param_4 = *param_2;
      param_1 = puVar2 + 1;
      *puVar2 = param_4;
    }
  }
  bVar6 = (byte)param_4;
  bVar1 = (param_3 & 2) != 0;
  param_3 = param_3 << 0x1f;
  bVar13 = (int)param_3 < 0;
  if (bVar1) {
    pbVar5 = (byte *)((int)puVar4 + 1);
    bVar6 = (byte)*puVar4;
    puVar4 = (uint *)((int)puVar4 + 2);
    in_r12 = *pbVar5;
  }
  puVar2 = puVar4;
  if (bVar13) {
    puVar2 = (uint *)((int)puVar4 + 1);
    param_3 = (uint)(byte)*puVar4;
  }
  if (bVar1) {
    pbVar5 = (byte *)((int)param_1 + 1);
    *(byte *)param_1 = bVar6;
    param_1 = (uint *)((int)param_1 + 2);
    *pbVar5 = in_r12;
  }
  puVar4 = param_1;
  if (bVar13) {
    puVar4 = (uint *)((int)param_1 + 1);
    *(byte *)param_1 = (byte)param_3;
  }
  return CONCAT44(puVar2,puVar4);
}



/* FUNCTION 0800b9b0 FUN_0800b9b0 SIZE 78 */

undefined4 * FUN_0800b9b0(undefined4 *param_1,uint param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  bool bVar4;
  
  bVar4 = 0x1f < param_2;
  param_2 = param_2 - 0x20;
  do {
    if (bVar4) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      param_1[6] = 0;
      param_1[7] = 0;
      param_1 = param_1 + 8;
      bVar4 = 0x1f < param_2;
      param_2 = param_2 - 0x20;
    }
  } while (bVar4);
  if ((param_2 & 0x10) != 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1 = param_1 + 4;
  }
  if ((int)(param_2 << 0x1c) < 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1 = param_1 + 2;
  }
  uVar3 = param_2 << 0x1e;
  puVar2 = param_1;
  if ((param_2 & 4) != 0) {
    puVar2 = param_1 + 1;
    *param_1 = 0;
  }
  if (uVar3 == 0) {
    return puVar2;
  }
  puVar1 = puVar2;
  if ((int)uVar3 < 0) {
    puVar1 = (undefined4 *)((int)puVar2 + 2);
    *(undefined2 *)puVar2 = 0;
  }
  puVar2 = puVar1;
  if ((uVar3 & 0x40000000) != 0) {
    puVar2 = (undefined4 *)((int)puVar1 + 1);
    *(undefined1 *)puVar1 = 0;
  }
  return puVar2;
}



/* FUNCTION 0800ba0e FUN_0800ba0e SIZE 32 */

void FUN_0800ba0e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_40 [4];
  undefined4 local_3c;
  undefined4 uStack_38;
  int local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_2c = 0;
  local_34 = DAT_0800ba30 + 0x800ba20;
  local_3c = param_4;
  uStack_38 = param_2;
  uStack_30 = param_1;
  FUN_0800b86c(auStack_40,param_3);
  return;
}



/* FUNCTION 0800ba34 FUN_0800ba34 SIZE 10 */

void FUN_0800ba34(undefined1 param_1,undefined4 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)*param_2;
  *puVar1 = param_1;
  *param_2 = puVar1 + 1;
  return;
}



/* FUNCTION 0800bad0 FUN_0800bad0 SIZE 4 */

undefined4 FUN_0800bad0(void)

{
  return DAT_0800bad4;
}



/* FUNCTION 0800bad8 FUN_0800bad8 SIZE 74 */

void FUN_0800bad8(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 unaff_lr;
  uint *puVar3;
  
  uVar1 = FUN_0800bad0();
  *(undefined4 *)((uVar1 & 0xfffffff8) + 0x5c) = unaff_lr;
  puVar3 = (uint *)((uVar1 & 0xfffffff8) + 0x58);
  *puVar3 = uVar1;
  FUN_0800024c();
  puVar2 = (undefined4 *)*puVar3;
  *puVar2 = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[5] = 0;
  puVar2[6] = 0;
  puVar2[7] = 0;
  puVar2[8] = 0;
  puVar2[9] = 0;
  puVar2[10] = 0;
  puVar2[0xb] = 0;
  puVar2[0xc] = 0;
  puVar2[0xd] = 0;
  puVar2[0xe] = 0;
  puVar2[0xf] = 0;
  return;
}



/* FUNCTION 0800bb22 FUN_0800bb22 SIZE 14 */

void FUN_0800bb22(undefined4 param_1)

{
  FUN_08000224(param_1);
  software_bkpt(0xab);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 0800bb30 FUN_0800bb30 SIZE 8 */

void FUN_0800bb30(void)

{
  software_bkpt(0xab);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



/* FUNCTION 0800bb3e FUN_0800bb3e SIZE 8 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800bb3e(undefined2 param_1)

{
  _DAT_60000000 = param_1;
  return;
}



/* FUNCTION 0800bb48 FUN_0800bb48 SIZE 6 */

void FUN_0800bb48(undefined2 param_1)

{
  *DAT_0800bb50 = param_1;
  return;
}



/* FUNCTION 0800bb54 FUN_0800bb54 SIZE 10 */

undefined4 FUN_0800bb54(void)

{
  return 0x3000000;
}


