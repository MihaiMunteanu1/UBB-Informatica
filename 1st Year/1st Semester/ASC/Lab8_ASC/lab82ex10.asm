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
    format db "%s",0
    nume_fisier resb 30
    text resb 120
    mesaj db "Numele fisierului: ",0
    mesaj2 db "Text: ",0
    
    mod_acces db "w",0
    descriptor_fisier dd 0

segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add esp,4
        
        push dword nume_fisier
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword mesaj2
        call [printf]
        add esp,4
        
        push dword text
        push dword format
        call [scanf]
        add esp,4*2
        
        ;fopen
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fisier],eax
        cmp eax, 0
        je final
        
        push dword text
        push dword format
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
    final:
        push    dword 0      
        call    [exit]      
