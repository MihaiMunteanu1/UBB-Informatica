bits 32 

global start

extern exit               
import exit msvcrt.dll    
                         
extern fopen, fread, fprintf, fclose,fscanf
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
segment data use32 class=data
    file_name db 'ex27.txt', 0
    mod_access db 'a+', 0
    file_descriptor dd 0

    numar db 0
    format db '%d',0
    minim db 0
segment code use32 class=code
    start:
        push dword mod_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        cmp eax, 0
        je final
        mov [file_descriptor], eax
        
        mov ebx,0
        cat_timp:
            push dword numar
            push dword format
            push dword [file_descriptor]
            call [fscanf]
            add esp,4*3
            
            mov al,[numar]
            mov bl,0
            cmp al,bl
            jz final
            
            mov bl,[minim]
            cmp al,bl
            jg modifica
            jmp salt
            modifica:
            mov [minim],al
            salt:
            jmp cat_timp
    final:
        push dword [minim]
        push dword format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3
  
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

        push    dword 0      
        call    [exit]       