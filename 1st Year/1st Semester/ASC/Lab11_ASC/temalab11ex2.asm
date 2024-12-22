bits 32 

global start        
extern transformare
extern exit,scanf,printf
import scanf msvcrt.dll  
import printf msvcrt.dll        
import exit msvcrt.dll  
%include "modul11ex2.asm"
 

segment data use32 class=data
    sir times 100 dd 0
    sir_memorie times 100 dd 0
    mesaj db "Dati sirul: ",0
    format db "%s",0
    
;Se cere sa se citeasca de la tastatura un sir de numere, date in baza 10 ca numere cu semn (se citeste de la tastatura un sir de caractere si in memorie trebuie stocat un sir de numere).
segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add esp,4*1
        
        push dword sir
        push dword format
        call [scanf]
        add esp,4*2
        
        mov esi,sir
        mov edi,sir_memorie
        call transformare
        
        ;mov [sir_memorie],edi
        
        push    dword 0      
        call    [exit]    
        
    ; transformare:
        ; cld
        ; mov ecx,100
        ; repeta:
            ; lodsb
            ; cmp al,0
            ; je sfarsit
            ; sub al,'0'
            ; stosb
            ; jmp repeta
        ; sfarsit:
        ; ret        
