bits 32

global start        


extern exit, printf, scanf       
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll     
                          
segment data use32 class=data
	n1 dd 0     
    n2 dd 0
	message1 db "n1=", 0  
    message2 db "n2=", 0
	format  db "%d", 0  
    rezultat db "Media este %x,rest %d",0
;16.Sa se citeasca de la tastatura doua numere a si b (in baza 10). Sa se calculeze si sa se afiseze media lor aritmetica in baza 16.
segment code use32 class=code
    start:
       
        push dword message1 
        call [printf]      
        add esp, 4*1      
        
        push dword n1  
         push dword format
        call [scanf]       
        add esp, 4 * 2    
            
        push dword message2
        call [printf]
        add esp, 4*1
        
        push dword n2
         push dword format
        call [scanf]
        add esp,4*2
        
        ; mov eax,0
        ; mov edx,0
        ; mov eax,[n1]
        ; mov ebx,[n2]
        ; div ebx
        mov eax,[n1]
        add eax,[n2]
        cdq
        mov ebx,2
        idiv ebx

        push edx
        push eax
        push dword rezultat
        call [printf]
        add esp,4*3
   
     
        push dword 0      
        call [exit]  