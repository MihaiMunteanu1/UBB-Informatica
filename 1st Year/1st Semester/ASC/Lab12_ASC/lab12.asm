bits 32

global _convert_to_dec

segment data public data use32

    adresa_sir_char dd 0
    is_negative db 0
    
segment code public code use32
    _convert_to_dec:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        mov [adresa_sir_char], eax
        mov esi, [adresa_sir_char]
        
        mov eax, 0
        mov ecx, -1
        
        cmp byte [esi], '-'
        jne char_to_dec
        inc byte [is_negative]
        inc esi
        
        char_to_dec:
            cmp byte [esi], 0
            jz end_conversion
            
            mov edx, 10
            mul edx
            
            mov edx, 0
            mov dl, [esi]
            inc esi
            sub edx, '0'
            
            add eax, edx
        loop char_to_dec
        end_conversion:
        
        cmp byte [is_negative], 0
        jz end_function
        mov edx, eax
        mov eax, 0
        sub eax, edx
        
        end_function:
            mov esp, ebp
            pop ebp
            ret