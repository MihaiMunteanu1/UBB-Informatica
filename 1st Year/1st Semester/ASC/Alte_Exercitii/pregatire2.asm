bits 32 

global start        

extern exit,fopen,fread,fclose,fprintf,printf,scanf               
import exit msvcrt.dll  
import printf msvcrt.dll 
import scanf msvcrt.dll 
import fopen msvcrt.dll  
import fread msvcrt.dll 
import fclose msvcrt.dll 
import fprintf msvcrt.dll 

segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier dd 0
    vocale db 'a','e','i','o','u','A','E','I','O','U',0
    lenv equ $-vocale
    
    dimensiune dd 1
    count dd 100
    sir resb 100    
    lungime_sir dd 0
    
    format_afisare db "%d", 0

segment code use32 class=code
    start:
        ;fopen
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        ;fread
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp,4*4
        
        mov [lungime_sir],eax
        
        mov esi,sir
        mov ecx,[lungime_sir]
        cld 
        jecxz final
        mov ebx,0
        repeta:
            lodsb
            push ecx
            mov ecx,lenv
            mov edi,vocale
            repeta2:
                scasb
                je continua
            loop repeta2
            inc ebx
            continua:
            pop ecx
        loop repeta
        
        push ebx
        push dword format_afisare
        call [printf]
        add esp,4*2
        
        ;fclose
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
    final:
        push    dword 0      
        call    [exit]      
