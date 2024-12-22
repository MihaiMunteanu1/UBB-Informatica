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
    nume_fisier db 'ex24.txt',0
    descriptor_fisier dd 0
    format db '%s',0
    mod_acces db 'w',0
    text db 'ab2cv jda 6vx. g67s',0
    len equ $-text
    text_nou times (len+1) db 0
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        mov esi,text
        mov edi,text_nou
        mov ecx,len
        jecxz final
        cld
        repeta:
            lodsb
            cmp al,'0'
            jl skip
            cmp al,'9'
            jg skip
            mov al,'C'
          
            skip:
            stosb
        loop repeta
        
        ;pt ex 25;
        ; repeta:
            ; lodsb
            ; cmp al,' '
            ; je modifica
            ; jmp skip
            ; modifica:
            ; mov al,'S'          
            ; skip:
            ; stosb
        ; loop repeta
        
        push dword text_nou
        push dword format
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
