bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a db 40
    b db 2
    c dw 20
    e dd -4
    x dq 50    
;(100+a+b*c)/(a-100)+e+x/a; a,b-byte; c-word; e-doubleword; x-qword cu semn
;-6.rest 10(A)
segment code use32 class=code
    start:
        ;a-100
        mov al,[a]
        sub al,100
        mov cl,al
        
        ;(100+a+b*c)
        mov al,[b]
        mov ah,0
        imul word[c] ;dx:ax=b*c
        mov bl,[a]
        mov bh,0
        adc ax,bx
        
        mov bl,100
        mov bh,0
        
        adc ax,bx
        
        ;(100+a+b*c)/(a-100)
        idiv cl
        
        ;+e
        push dx
        push ax
        pop eax
        adc eax,[e]
        
        ;x/a
        push eax
        mov eax,[x]
        mov edx,[x+4]
        mov ebx,0
        mov bl,[a] 
        idiv ebx
        
        mov ebx,0
        pop ebx
        
        adc eax,ebx ;edx:eax=(100+a+b*c)/(a-100)+e+x/a
        
        push    dword 0      
        call    [exit]      
