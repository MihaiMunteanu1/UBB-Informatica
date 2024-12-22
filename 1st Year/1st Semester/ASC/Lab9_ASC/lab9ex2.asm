bits 32 

global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100

    sir resb 100
    lungime_sir dd 0
    cifra_max db -1
    
    format_afisare db "%d  ", 0
    zece equ 10

; our code starts here
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp EAX, 0
        je final
        
        mov [descriptor_fisier], EAX
        
        ; int fread(void * str, int size, int count, FILE * stream)
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir], EAX
        
        mov esi, sir
        mov ecx, [lungime_sir]
        cld
        jecxz iesireBucla
        
        mov eax,0
        
        bucla:
            push eax
            lodsb
            mov bl,al
            
            pop eax
            
            cmp al,' '
            je afisareNumar
            
            mul dword[zece]
            add al,bl
                        
            final_bucla:
            loop bucla
            
        afisareNumar:
        push EAX
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        jecxz iesireBucla
        jmp final_bucla
        iesireBucla:
        
        ; int printf(const char * format, variabila_1);
        ; GRESIT: push dword [cifra_max]
        
        mov EAX, 0
        mov AL, [cifra_max]
        
        push EAX
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        ; int fclose(FILE * descriptor)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        
        final:
        ; exit(0)
        push    dword 0      
        call    [exit]       
        