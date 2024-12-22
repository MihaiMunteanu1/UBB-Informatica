bits 32

global start        

extern exit, printf, scanf               
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll 

section data use32 class=data
    a resb 100
    format db "%d",0
    rezultat db "cel mai mare numar: %d",10,0
    
section code use32 class=code
    start:
        mov ebx,0
        cat_timp:
            push dword a
            push dword format
            call [scanf]
            add esp,4*2
        
            mov al,[a]
            cmp al,0
            je continua2
            
            mov eax,[a]
            cmp eax,ebx
            jg modifica
            jmp salt
            modifica:
            mov ebx,eax
                
            salt:
            jmp cat_timp
            
        continua2:
        push ebx
        push dword rezultat
        call [printf]
        add esp,4*2
        
        push   dword 0      
        call   [exit]  