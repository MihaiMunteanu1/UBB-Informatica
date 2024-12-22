bits 32 

global start        

extern exit,printf,scanf               
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll 

segment data use32 class=data
    a dd 0
    format db "%x",0
    mesaj1 db "a= ",0
    mesaj2 db "b= ",0
    rezultat db "rezultat= %d",10,0
    rezultat2 db "rezultat= -%d",10,0
    
segment code use32 class=code
    start:
        push dword mesaj1
        call [printf]
        add esp,4
        
        push dword a
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword[a]
        push dword rezultat
        call [printf]
        add esp,4*2
        
        mov al,[a]
        mov bl,80h
        cmp al,bl
        jge afis2
        jmp afis1
        
        afis2:
        mov ebx,0
        mov bl,255
        sub bl,al
        push ebx
        push dword rezultat2
        call [printf]
        add esp,4*2
        jmp final
        
        afis1:
        mov eax,[a]
        push eax
        push dword rezultat
        call [printf]
        add esp,4*2
        final:
        push   dword 0      
        call   [exit]     