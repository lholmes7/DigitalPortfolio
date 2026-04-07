;MASM.asm
;Landon Holmes

Include Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode:dword

.data

sum Dword ?

.code
main PROC
If (ebx <= ecx)
{
eax = 5;
edx = 6;
}
    invoke ExitProcess, 0

main ENDP
END main