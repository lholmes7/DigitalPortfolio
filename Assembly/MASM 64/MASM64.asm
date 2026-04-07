;MASM64.asm
;Landon Holmes

option casemap:none

.data
arr DWORD 10, 20, 30, 40, 50, 60   ; 6 elements (even number)
count DWORD 6                       ; number of elements

.code
main PROC
    xor ecx, ecx        ; ECX = index (in elements, not bytes)

pair_loop:
    cmp ecx, count
    jge loop_end        ; stop if we reach the end

    ; swap arr[ecx] with arr[ecx+1]
    mov eax, DWORD PTR arr[ecx*4]       ; load arr[i] into EAX
    mov edx, DWORD PTR arr[(ecx+1)*4]   ; load arr[i+1] into EDX

    mov DWORD PTR arr[ecx*4], edx       ; arr[i] = arr[i+1]
    mov DWORD PTR arr[(ecx+1)*4], eax   ; arr[i+1] = arr[i]

    add ecx, 2          ; move to next pair
    jmp pair_loop

loop_end:
    invoke ExitProcess, 0
main ENDP
END main