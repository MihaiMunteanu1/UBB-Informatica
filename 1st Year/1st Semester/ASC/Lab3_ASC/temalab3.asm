bits 32 

global start        


extern exit               
import exit msvcrt.dll    
                          
segment data use32 class=data
    a db 1
    b dw 2
    c dd 3
    d dq 4

    
segment code use32 class=code
    start:
        
        mov al,[a]
        
        push    dword 0      
        call    [exit]       
