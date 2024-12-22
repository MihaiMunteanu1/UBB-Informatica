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
    nume_fisier db "ex11.txt",0
    descriptor_fisier dd 0
    mod_acces db "w",0
    text resb 100
    format db "%s",0
    formatprint db "%s ",0
segment code use32 class=code
    start:
        ;fopen
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fisier],eax
        cmp eax, 0
        je final
        while_read:
            push dword text
            push dword format
            call [scanf]
            add esp,4*2

            mov al,[text]
            mov bl,'$'
            cmp al,bl
            jz close
       
            push dword text
            push dword formatprint
            push dword [descriptor_fisier]
            call [fprintf]
            add esp,4*3 
            
            jmp while_read
            
        close:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
    final:
        push    dword 0      
        call    [exit]      
