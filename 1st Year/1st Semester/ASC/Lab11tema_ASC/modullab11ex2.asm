bits 32 
 
global transformare
%ifndef  _MODULLAB11EX2_ASM_ 
%define  _MODULLAB11EX2_ASM_ 
segment code use32 class=code
    transformare:
        cld
        mov ebx,0
        repeta:
            mov eax,0
            lodsb
            cmp al,0
            je sfarsit
            sub al,'0'
            mov cl,10
            mul cl
            mov bx,ax
            add bl,al
            jmp repeta  
        sfarsit:
        mov eax,ebx
        stosd
        ret  
    
%endif
    
