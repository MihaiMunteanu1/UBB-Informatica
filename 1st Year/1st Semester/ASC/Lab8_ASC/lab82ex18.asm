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
    nume_fisier db 'ex18.txt',0
    descriptor_fisier dd 0
    mod_acces db "r",0
    format db 'cuvinte: %d',0
    text resb 100
    dimensiune dd 1
    count dd 100
    lungime_sir db 0
    
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword text
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir],eax
        
        mov esi,text
        mov ecx,[lungime_sir]
        cld
        jecxz final
        mov ebx,0
        repeta:
            lodsb
            cmp al,' '
            je cuvant
            jmp continua
            cuvant:
            inc ebx
            continua:
        loop repeta
        
        inc ebx

        push ebx
        push dword format
        call [printf]
        add esp,4*2
        
        final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
