bits 32

global start

extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    sir dd 1234A678h,12345678h,1AC3B47Dh,0FEDC9876h
    len equ ($-sir)/4
    max db 0
    suma db 0
    format_afisare db '%x ',0
    format_afisare2 db '%d ',0
segment code use32 class=code
    start:
        mov esi,sir
        cld
        mov ecx,len
        jecxz final
        repeta:
            push ecx
            mov ecx,4
            mov byte[max],0
            repeta2:
                lodsb
                cmp al,byte[max]
                jbe salt
                mov byte[max],al
                salt:
            loop repeta2
            mov eax,0
            mov al,byte[max]
            push eax
            push dword format_afisare
            call [printf]
            add esp,4*2
            mov al,byte[max]
            add byte[suma],al
            pop ecx
        loop repeta
        movsx eax,byte[suma]
        
        push eax
        push dword format_afisare2
        call [printf]
        add esp,4*2
        final:
        push dword 0
        call [exit]