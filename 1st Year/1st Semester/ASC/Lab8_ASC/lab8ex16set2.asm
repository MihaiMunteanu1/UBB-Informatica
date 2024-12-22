bits 32

global start        

extern exit,fopen,fread,fclose,printf   
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fread msvcrt.dll    
import printf msvcrt.dll  
                          
segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100
    sir resb 100    
    lungime_sir dd 0
    
    format_afisareY db "y= %d ", 0
    format_afisareZ db "z= %d ", 0
	
;16.Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de litere 'y' si 'z' si sa se afiseze aceaste valori. Numele fisierului text este definit in segmentul de date.
segment code use32 class=code
    start:
        ;FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
       
        cmp eax,0
        je final
        mov [descriptor_fisier],eax
        
        ;int fread(void * str, int size, int count, FILE * stream)
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir],eax
        
        mov esi,sir
        mov ecx,[lungime_sir]
        cld
        jecxz sfarsit_loop
        mov ebx,0
        mov edx,0
        repeta:
            lodsb
            cmp al,'y'
            je adaugay
            
            cmp al,'z'
            je adaugaz
            
            jmp salt
            
            adaugay:
            inc ebx
            jmp salt
            adaugaz:
            inc edx

            salt:
        loop repeta
        
        sfarsit_loop:
        ;pusha sa pot face cu edx dupa
        ;AFISARE
        push edx
        push dword format_afisareZ
        call[printf]
        add esp,4*2
        ;popa
        push ebx
        push dword format_afisareY
        call[printf]
        add esp,4*2

        ; int fclose(FILE * descriptor)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
   
    final:
        push dword 0      
        call [exit]  