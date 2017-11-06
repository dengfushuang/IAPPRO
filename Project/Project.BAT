SET PATH=D:\Keil\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\Library\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\sam-ba 2.9;D:\VSCODE\Microsoft VS Code\bin;D:\Mingw\bin
SET CPU_TYPE=LPC1778
SET CPU_VENDOR=NXP
SET UV2_TARGET=Project
SET CPU_CLOCK=0x00B71B00
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\debug_frmwrk.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_crc.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_pinsel.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_uart.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_clkpwr.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_iap.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_systick.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lpc177x_8x_gpio.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_lpc17xx._ia"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\core_cm3.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_lpc177x_8x.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\cmd_process.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\IAPBOOT.lnp"
"D:\Keil\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\IAPBOOT.axf" --i32combined --output ".\Objects\IAPBOOT.hex"
