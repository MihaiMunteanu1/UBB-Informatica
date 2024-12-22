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
    nume_fisier db 'ex30.txt',0
    descriptor_fisier dd 0
    format db '%s',0
    format_afisare db '%s',10,0
    mod_acces db 'w',0
    
    cuvant resb 100

segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        mov [descriptor_fisier],eax
        cmp eax,0
        je final
        
        
        while_citeste:
            push dword cuvant
            push dword format
            call [scanf]
            add esp,4*2
            
            mov al,[cuvant]
            mov bl,'$'
            cmp al,bl
            jz final
            
            mov esi,cuvant
            cld
            repeta:
                lodsb
                cmp al,0
                jz continua
                cmp al,'0'
                jl skip
                cmp al,'9'
                jg skip
                
                push dword cuvant
                push dword format_afisare
                push dword [descriptor_fisier]
                call [fprintf]
                add esp,4*3
                jmp continua
                
                skip:
                jmp repeta
        
            continua:
        jmp while_citeste
        
        
        final:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      
        call    [exit]      
