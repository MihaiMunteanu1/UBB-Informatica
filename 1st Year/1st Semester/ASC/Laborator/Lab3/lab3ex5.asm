bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a db 9
    b dw 2
    c db 6
    d dd 4
    x dq 5    
;(a*b+2)/(a+7-c)+d+x;  a,c-byte; b-word; d-doubleword; x-qword fara semn
;=B
segment code use32 class=code
    start:
        ;a+7-c
        mov al,[a]
        add al,7
        sub al,[c]
        
        mov cl,al ;cl=a+7-c
        
        ;a*b+2
        mov al,[a]
        mov ah,0 
        mul word[b] ;dx:ax=a*b
        add ax,2
        
        ;(a*b+2)/(a+7-c)
        div cl
        
        ;+d+x
        push dx
        push ax
        pop eax
        
        add eax,[d]
        mov edx,0
        
        add eax,[x]
        add edx,[x+4]
        
        
        push    dword 0      
        call    [exit]      
