bits 32 

global start        

extern exit ,printf
import printf msvcrt.dll              
import exit msvcrt.dll   

segment data use32 class=data
    sir dq 1110111b,100000000h,0ABCD0002E7FCh,5
    len equ ($-sir)/8
    rez times len dd 0
    format_afisare db '%x ',0
    format_afisare2 db '%d',0
    format_afisare3 db ' ',0
    grad db 0
    contor db 0
    copie dd 0
    verif db 0
segment code use32 class=code
    start:
        mov esi,sir
        mov edi,rez
        cld
        mov ecx,len
        repeta:
            lodsd
            mov dword[copie],eax
            mov byte[grad],0
            mov byte[contor],0
            push ecx
            mov ecx,32
            clc
            repeta2:
                rcl eax,1
                mov bl,0
                adc bl,bl
                cmp bl,1
                jne next
                add byte[contor],1
                cmp byte[contor],3
                je next2
                jmp continua
                next2:
                add byte[grad],1
                mov byte[contor],0
                next: 
                mov byte[contor],0
                continua:
            loop repeta2
            pop ecx
            cmp byte[grad],2
            jb cont2
            mov eax,dword[copie]
            stosd
            push ecx
            push eax
            push dword format_afisare
            call [printf]
            add esp,4*2
            pop ecx
            cont2:
            add esi,4
        loop repeta
        mov esi,rez
        mov ecx,len
        cld
        repeta3:
            push ecx
            push dword format_afisare3
            call [printf]
            add esp,4
            pop ecx
            lodsd
            push ecx
            mov ecx,32
            mov byte[verif],0
            repeta4:
                rcl eax,1
                mov bl,0
                adc bl,bl
                cmp bl,1
                je pas1
                jmp salt3
                pas1:
                    cmp byte[verif],0
                    je pas2
                    jmp salt2
                    pas2:
                    mov byte[verif],1
                    salt2:
                    push eax
                    push ecx
                    push 1
                    push dword format_afisare2
                    call [printf]
                    add esp,4*2
                    pop ecx
                    pop eax
                    jmp continua2
                salt3:
                cmp byte[verif],0
                je salt4
                push eax
                push ecx
                push 0
                push dword format_afisare2
                call [printf]
                add esp,4*2
                pop ecx
                pop eax
                salt4:
                continua2:
            loop repeta4
            pop ecx
        loop repeta3
        final:
        push    dword 0      
        call    [exit]      
