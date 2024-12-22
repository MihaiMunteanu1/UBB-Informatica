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
    lit_mici db 'abcdefghijklmnopqrstvuwxyz',0
    lenl equ $-lit_mici
    
    dimensiune dd 1
    count dd 100
    sir resb 100    
    lungime_sir dd 0
    
    format_afisare db "litera: %c, cu frecventa: %d", 0

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
        
        mov esi,lit_mici
        mov ecx,lenl
        jecxz final
        cld
        mov ebx,0
        mov edx,0
        repeta:
            lodsb
            push ecx
            mov ecx,[lungime_sir]
            mov edi,sir
            mov bl,0
            repeta2:
                scasb
                je adauga
                jmp salt
                adauga:
                inc bl
                salt:
            loop repeta2
            cmp bl,dl
            jg modifica
            jmp continua
            modifica:
            mov dl,bl
            mov dh,al
            continua:
            pop ecx
        loop repeta
        
        mov eax,0
        mov al,dl
        mov ebx,0
        mov bl,dh
        
        push eax
        push ebx
        push dword format_afisare
        call [printf]
        add esp,4*3
        
        ;fclose
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
    final:
        push    dword 0      
        call    [exit]      
