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
    nume_fisier db 'ex17.txt',0
    format db '%d',0
    format_scriere db "%d ",0
    numar resb 100
    descriptor_fisier dd 0
    mod_acces db "w",0
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        while_citeste:
            push dword numar
            push dword format
            call [scanf]
            add esp,4*2
            
            mov al,[numar]
            cmp al,0
            je final
            mov bl,7
            div bl
            cmp ah,0
            je scriere
            jmp continua
            scriere:
            push dword [numar]
            push dword format_scriere
            push dword [descriptor_fisier]
            call [fprintf]
            add esp,4*3
            continua:
            jmp while_citeste
        
        final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
