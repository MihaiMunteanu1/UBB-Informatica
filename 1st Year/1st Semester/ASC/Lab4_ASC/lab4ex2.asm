bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dw 0001001000110100b ;0001 0010 0011 0100 b
    b dw 0101011001111000b ;0101 0110 0111 1000 b
    c dd 0                 ;xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
                           ;0101 0110 0111 1000 1001 0001 0100 0011
                           ; 5     6   7     8    9    1   4     3
               
; Se dau cuvintele A si B. Se cere dublucuvantul C:
; bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
; bitii 4-8 ai lui C coincid cu bitii 0-4 ai lui A
; bitii 9-15 ai lui C coincid cu bitii 6-12 ai lui A
; bitii 16-31 ai lui C coincid cu bitii lui B
segment code use32 class=code
    start:
        mov ebx,0
        
        mov ax,[b]
        and ax,0000000111100000b ;biti 5-8 a lui b
        
        mov cl,5
        ror ax,cl
        or bx,ax 
        ;--------
        
        mov ax,[a]
        and ax,0000000000011111b  ;biti 0-4 a lui a
        
        mov cl,4  ; sa punem in biti 4-8 a lui c
        rol ax,cl
        or bx,ax
        ;-------------
        
        mov ax,[a]
        and ax,0001111111000000b ;biti 6-12 a lui a
        
        mov cl,3
        rol ax,cl
        or bx,ax
        
        mov cx,[b]   ;16-31 a lui b
        
        push cx
        push bx
        pop ebx
        
        mov [c],ebx
        
        
        push    dword 0      
        call    [exit]      
