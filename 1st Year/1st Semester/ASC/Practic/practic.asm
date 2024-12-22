bits 32 

global start

extern exit               
import exit msvcrt.dll    
                         
extern fopen, fread, fprintf, fclose,fscanf,printf,scanf
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class=data
    minim dd 1000
    numar dd 0
    nume_fisier db 0
    mesaj1 db 'numele fisier: ',0
    format db '%s',0
    format2 db '%d',0
    mod_acces db 'r',0
    descriptor_fisier dd 0
    mesaj2 db 'Minim pozitii impare: %d',0
segment code use32 class=code
    start:
        push dword mesaj1
        call [printf]
        add esp,4
        
        push dword nume_fisier
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        mov esi,1
        cld
        while_citeste:
            push dword numar
            push dword format2
            push dword [descriptor_fisier]
            call [fscanf]
            add esp,4*3
            
            ; cmp eax,-1
            ; jz final
            ; mov eax,[numar]
            
            mov eax,[numar]
            mov ebx,0
            cmp eax,ebx
            jz final
            
            test esi,01h
            jz salt
            mov ebx,[minim]
            cmp eax,ebx
            jl modifica
            jmp salt
            modifica:
            mov [minim],eax   
            salt:
            inc esi
        jmp while_citeste
        
    final:
        push dword [minim]
        push dword mesaj2
        call [printf]
        add esp,4*2
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
    
        push    dword 0      
        call    [exit]       
