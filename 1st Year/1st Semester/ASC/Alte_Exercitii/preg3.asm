bits 32

global start

extern exit,scanf
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    sir_numere times 3 dd 0
    sir_octeti times 3 db 0
    n dd 0
    format_citire db '%d',0
    numar dd 0
    suma db 0
    
segment code use32 class=code
start:
    push dword n
    push dword format_citire
    call [scanf]
    add esp,4*2
    
    cld
    mov ecx,[n]
    jecxz final
    mov esi,sir_numere
    mov edi,sir_octeti
    repeta:
        push ecx
        push dword numar
        push dword format_citire
        call [scanf]
        add esp,4*2
        pop ecx
        mov eax,[numar]
        mov [esi],eax
        add esi,4
        
        mov byte[suma],0
        repeta_suma:
            cmp eax,0
            je final_suma
            mov edx,0
            mov ebx,10
            div ebx
            test dl,1
            jnz sari
            add [suma],dl
            sari:
            jmp repeta_suma
        final_suma:
        mov al,[suma]
        mov [edi],al
        inc edi
    loop repeta
    
    final:
    push dword 0
    call [exit]
    
 
