bits 32 

global start        

extern exit               
import exit msvcrt.dll    
;a byte
;b word
;c double_word
;d quad_word
segment data use32 class=data
    a db 9
    b dw 2
    c dd 1
    d dq 4

; (a+b+d)-(a-c-d)+(b-c) fara semn =15-4+1=12=C
segment code use32 class=code
    start:    
        ;a-c-d
        mov eax,0
        mov al,[a]
        sub eax,[c]
        mov edx,0
        mov ebx,[d]
        mov ecx,[d+4]
        sub eax,ebx
        sub edx,ecx
        
        mov ebx,eax
        mov ecx,edx
        
        ;a+b+d
        mov eax,0
        mov al,[a]
        add ax,[b]
        mov edx,0
        add eax,[d]
        add edx,[d+4]
        
        ;(a+b+d)-(a-c-d)
        sub eax,ebx
        sub edx,ecx
        
        mov ebx,eax
        mov ecx,edx        
        ;b-c
        mov eax,0
        mov ax,[b]
        sub eax,[c]
        
        ;(a+b+d)-(a-c-d)+(b-c)
        
        add eax,ebx
        
        
        
        push    dword 0      
        call    [exit]      
