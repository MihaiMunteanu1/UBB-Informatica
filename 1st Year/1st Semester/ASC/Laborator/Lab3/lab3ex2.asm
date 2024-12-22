bits 32 

global start        

extern exit               
import exit msvcrt.dll    
;a byte
;b word
;c double_word
;d quad_word
segment data use32 class=data
    a db 10
    b dw 2
    c dd 3
    d dq 4

; (a+c)-(d+b) fara semn
;7
segment code use32 class=code
    start:
        ;d+b
        mov eax,[d]
        mov edx,[d+4]
        mov ebx,0
        mov bx,[b]
        add eax,ebx
        
        mov ebx,eax
        mov ecx,edx
        
        
        ;a+c    
        mov eax,0
        mov al,[a]
        add eax,[c]
        mov edx,0
        
        
        ;(a+c)-(d+b)
        sub eax,ebx
        sub edx,ecx
        
        
        push    dword 0      
        call    [exit]      
