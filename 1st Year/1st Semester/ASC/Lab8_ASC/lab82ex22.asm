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
    nume_fisier db 'ex22.txt',0
    descriptor_fisier dd 0
    format db '%d',10,0
    mod_acces db 'w',0
    numar dw 1234
    cifra dd 0
    
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        mov eax,[numar]
        repeta:  
            mov edx,0
            mov ecx,10
            div ecx
            mov [cifra],edx
            cmp dword[cifra],0
            je final
            push eax
            push dword [cifra]
            push dword format
            push dword [descriptor_fisier]
            call [fprintf]
            add esp,4*3
            pop eax
            
            jmp repeta
        
        final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
