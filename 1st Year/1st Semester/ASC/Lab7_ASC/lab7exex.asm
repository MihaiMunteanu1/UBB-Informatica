bits 32 

global start        

extern exit               
import exit msvcrt.dll   

segment data use32 class=data
    sir dd 4, 7, 1, 5, 2, 9, 2
    len equ ($-sir)/4
    dest resd len
;Sortam sirul
segment code use32 class=code
    start:
        mov ecx,len
        mov edi,dest
        
        repeta1:
            mov eax, -1 ; punem o val max cu care sa comparam: FF..
            
            push edi
            push ecx  ;punem pe stiva ca sa mai facem un loop si sa nu le afectam
            mov ecx, len
            mov edi, sir ;l-am pus in edi ca sa putem compara cu scasd
            
            repeta2:
                scasd ;compara eax cu elementul curent
                jb continua
                mov eax, [edi-4] ;pun in eax numarul cu care am comparat inainte
                                 ; edi-4 pentru ca scasd adauga +4 la edi
                mov ebx, edi     ;retinem pozitia ca sa nu-l mai comparam pe viitor cu el
                sub ebx, 4
                
                continua:
            loop repeta2
            
            pop ecx
            pop edi;scoatem valoriile initiale
            
            stosd;valoarea minima din eax o punem in edi ->destinatie
            mov dword[ebx], -1 ;pune -1 pe pozitia elementului minim care l-am pus in edi
            
        loop repeta1

        push    dword 0      
        call    [exit]      
