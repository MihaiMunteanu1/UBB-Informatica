bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
      a dw 2
      b db -3
      c dd -4 
      x dq 5

    
;25. (a*a+b+x)/(b+b)+c*c   a-word; b-byte; c-doubleword; x-qword  cu semn
;15
segment code use32 class=code
    start:      
        mov ax,[a]
        imul word[a] ;dx:ax=a*a
        
        ;adunam cu qword si trebuie sa facem dx:ax in eax
        
        push dx
        push ax
        pop ebx ;ebx=a*a=4
        
        mov al,[b]
        cbw ;ax=b
        cwde ;eax=b
        
        add eax,ebx ;eax=a*a+b=1
        cdq
        
        mov ebx,[x]
        mov ecx,[x+4] ;edx:ebx=x=5
        
        clc
        add eax,ebx
        adc edx,ecx
        push eax ;edx:eax-stiva=(a*a+b+x)=6
       
         
        mov al,[b]
        add al,[b]
        cbw ;AL->AX
        cwde ;AX->EAX
        
        mov ebx,eax
        pop eax 
        idiv ebx ;(a*a+b+x)/(b+b)
        
        cdq ;urmeaza sa adunam qword edx:eax=(a*a+b+x)/(b+b)
        
        mov ebx,eax
        mov ecx,edx ;ecx:ebx=edx:eax=(a*a+b+x)/(b+b)
        
        mov eax,[c]
        imul dword[c]
        
        clc
        add eax,ebx
        add edx,ecx ;edx:eax=(a*a+b+x)/(b+b)+c*c
        
        
        
        push    dword 0      
        call    [exit]      
