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
    b dw 1
    c dd 3
    d dq -4
; (d+d-c)-(c+c-a)+(c+a)=4 cu semn 
segment code use32 class=code
    start:
        ;(c+c-a)
        mov al,[a]        
        cbw
        cwde
        mov ebx,eax
        mov eax,[c]
        add eax,eax
        sbb eax,ebx
        push eax
        
        ;d+d-c
        mov eax,[c]
        cdq               
        mov ecx,edx
        mov ebx,eax  ;ECX:EBX=c pentru a putea fi scazut din qw
        
        mov eax,[d]
        mov edx,[d+4]
        
        add eax,eax
        adc edx,edx
        
        sub eax,ebx
        sbb edx,ecx
        
        ;(d+d-c)-(c+c-a)
        mov ebx,eax
        mov ecx,edx
        pop eax
        cdq
        sub ebx,eax
        sbb ecx,edx
        
        ;c+a
        mov al,[a]
        cbw
        cwde
        add eax,[c]
        cdq
        
        ;(d+d-c)-(c+c-a)+(c+a)
        
        add eax,ebx
        adc edx,ecx
        
        
        push    dword 0      
        call    [exit]      
