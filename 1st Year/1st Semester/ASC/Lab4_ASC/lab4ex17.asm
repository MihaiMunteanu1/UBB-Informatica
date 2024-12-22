bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dw 0001001000110100b ;0001 0010 0011 0100 b
    b db 01111000b         ;          0111 1000 b
    c dd 0                 ;xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
                           ;1101 1110 0100 1000 1100 0000 0100 1111
                           ; D    E    4    8    C     0    4   F
                           
                           ;DE69C04F
                                      
; bitii 0-3 ai lui C au valoarea 1
; bitii 4-7 ai lui C coincid cu bitii 0-3 ai lui A
; bitii 8-13 ai lui C au valoarea 0
; bitii 14-23 ai lui C coincid cu bitii 4-13 ai lui A
; bitii 24-29 ai lui C coincid cu bitii 2-7 ai lui B
; bitii 30-31 au valoarea 1
segment code use32 class=code
    start:
        mov ebx,0 ;aici vom calcula rezultatul
        
        ; bitii 0-3 ai lui C au valoarea 1
        mov bl,1111b
        
        ; bitii 4-7 ai lui C coincid cu bitii 0-3 ai lui A
        mov ax,[a]
        and ax,0000000000001111b
        
        mov cl,4
        rol ax,cl
        or bx,ax
        
        ; bitii 8-13 ai lui C au valoarea 0
        mov bh,0 ; bitii 8-11
        ;din mov ebx,0  bitii 12-13 is zero
        
        ; bitii 14-23 ai lui C coincid cu bitii 4-13 ai lui A
        mov eax,0
        mov ax,[a]
        and eax,00000000000000000011111111110000b
        
        mov cl,10
        rol eax,cl
        or ebx,eax
        
        ; bitii 24-29 ai lui C coincid cu bitii 2-7 ai lui B

        mov eax,0
        mov al,[b]
        and eax,00000000000000000000000011111100b
        
        mov cl,22
        rol eax,cl
        or ebx,eax
        
        ; bitii 30-31 au valoarea 1
        or ebx,11000000000000000000000000000000b
        
        mov [c],ebx
        
        
        push    dword 0      
        call    [exit]      
