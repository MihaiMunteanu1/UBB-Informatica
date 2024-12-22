bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a db 101
    b db 2
    c dw 5
    e dd 4
    x dq 101    
;(100+a+b*c)/(a-100)+e+x/a; a,b-byte; c-word; e-doubleword; x-qword fara semn
;201+10+4+1=216=D8
segment code use32 class=code
    start:
        ;a-100
        mov al,[a]
        sub al,100
        mov cl,al
        
        ;(100+a+b*c)
        mov al,[b]
        mov ah,0
        mul word[c] ;dx:ax=b*c
        mov bl,[a]
        mov bh,0
        add ax,bx
        
        mov bl,100
        mov bh,0
        
        add ax,bx
        
        ;(100+a+b*c)/(a-100)
        div cl
        
        ;+e
        push dx
        push ax
        pop eax
        add eax,[e]
        
        ;x/a
        push eax
        mov eax,[x]
        mov edx,[x+4]
        mov ebx,0
        mov bl,[a] 
        div ebx
        
        mov ebx,0
        pop ebx
        
        add eax,ebx ;edx:eax=(100+a+b*c)/(a-100)+e+x/a
        
        push    dword 0      
        call    [exit]      
