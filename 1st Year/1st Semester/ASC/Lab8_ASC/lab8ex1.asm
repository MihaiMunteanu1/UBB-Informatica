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
    rezultat db "Produsul este %d",0
;1.Sa se citeasca de la tastatura doua numere (in baza 10) si sa se calculeze produsul lor. Rezultatul inmultirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date).
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
        
        mov eax,0
        mov eax,[n1]
        imul dword[n2]
        
        push eax
        push dword rezultat
        call [printf]
        add esp,4*2
   
     
        push dword 0      
        call [exit]       