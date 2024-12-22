bits 32 

global start        

extern exit               
import exit msvcrt.dll    
;a byte
;b word
;c double_word
;d quad_word
segment data use32 class=data
    a db 4
    b dw 3
    c dd 2
    d dq 1
  
; (a-b-c)+(d-b-c)-(a-d) cu semn -1+-4-3=-8
segment code use32 class=code
    start:
        ;(a-b-c)
        mov al,[a]
        cbw
        sub ax,[b]
        cwde
        sbb eax,[c]
        
        push eax
        
        ;d-b-c
        mov ebx,[d]
        mov ecx,[d+4]
        
        mov ax,[b]
        cwde
        cdq
        
        sub ebx,eax
        sbb ecx,edx
        
        mov eax,[c]
        cdq
        
        sub ebx,eax
        sbb ecx,edx
        
        ;(a-b-c)+(d-b-c)
        pop eax
        cdq
        add eax,ebx
        adc edx,ecx
        
        mov ebx,eax
        mov ecx,edx
        
        ;(a-d)
        mov al,[a]
        cbw
        cwde
        cdq
        sub eax,[d]
        sbb edx,[d+4]
        
        ;(a-b-c)+(d-b-c)-(a-d)
        sub ebx,eax
        sbb ecx,edx
        
        mov eax,ebx
        mov edx,ecx
        
        push    dword 0      
        call    [exit]      
