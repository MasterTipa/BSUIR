.model small
.stack 100h
.data
    input_text db 10,13,"Enter a Number :",10,13,'$'
    error db 10,13,"incorrect number$"
    msg_and db 10,13,"AND:$"
    msg_or db 10,13,"OR:$"
    msg_xor db 10,13,"XOR:$"
    msg_not1 db 10,13,"NOT1:$"
    msg_not2 db 10,13,"NOT2:$"
    msg_number db 10,13,"Your Number:$"
    max_zn db 5,"32767"
    buff dw 7,8 Dup(?)
    Number1 dw ? 
    Number2 dw ?
    sign1 dw ?
    sign2 dw ?
    ans dw 7 dup (?),'$' 
.code     
_xor_proc proc          ; NEAR=TINY SMALL COMPACT , else (FAR)
     xor si,si
    xor di,di
    xor bx,bx
    xor ax,ax
    xor dx,dx
     ret
_xor_proc endp
_inverse_ proc
    cmp di,0
    je _set_one
    mov di,0
    jmp _ret_end
    _set_one:
    mov di,1
    _ret_end:
    ret
_inverse_ endp   
_input_number proc
    
    mov dx, offset input_text
    mov ah, 0x9
    int 0x21  
    mov dx, offset buff				
    mov ah, 0x0A
    int 21h
    xor di,di
    xor bx,bx
    xor ax,ax
    ;mov cx,offset max_zn
    mov si,offset buff+2
    cmp byte ptr [si],'-'
    jne _first_step
    mov di,1
    inc si
    cmp byte ptr[si],'0'
    je _exit_zero 
        _first_step:
            cmp byte ptr[si], 0dh
            je _exit_int
            cmp byte ptr[si], ' '
            je _exit_error
            cmp byte ptr[si], '0'
            jl _exit_error          ;если меньше (or l)
            cmp byte ptr[si], '9'
            jg _exit_error          ;если больше (or a)
            mov bl, 10
            mul bx                  ; * (IMUL)
            jc _exit_error          ;есть переполнение (OF=1)
            cmp dx,0
            jnz _exit_error
            mov bl, byte ptr [si]
            sub bl, '0'             ; - (SBB)
            add ax, bx              ; + (ADC)
            jc _exit_error
            cmp ax,8000h
            ja _exit_error
            inc si
            jmp _first_step
        
        _exit_error:
            mov dx,offset error
            mov ax,0x0900
            int 21h  
            jmp _exit_without_output:
        _exit_zero:
            mov di,0
            jmp _ret    
        _exit_int:
            cmp di,1
            jne _exit_check
            neg ax                  ;dop code
            jmp _ret
        _exit_check:
            or ax,ax
            js _exit_error  
        _ret:                    
            
            ret
_input_number endp
_clean_ans proc
        mov cx,6
        xor di,di
        inc di              ;+1
        mov [ans+di],'0'
        _loop_cleaning:
        ;lea dx,ans
        mov [ans+di],'$'
        inc di              ;+1
        loop _loop_cleaning
        ret
_clean_ans endp    
_output_number proc
    push ax
    cmp di,0 
    je positive
    neg ax    
    positive:
    mov bx,10
    mov cx,0
    mov [ans],'0'
    
    _loop:
        mov dx,0
        div bx          ;/ (IDIV)
        cmp ax,0    
        je dxing
        add dx,'0'
        push dx
        inc cx
        jmp _loop
    
    dxing:
        cmp dx,0
        je stringing
        add dx,'0'
        push dx
        inc cx
        jmp stringing    
    
    stringing:
        cmp cx,0
        je return
        lea dx,ans
        cmp di,0
        je _loop_this
        dec di
        mov [ans+di],'-'
        inc di
  
    _loop_this:
        pop ax 
        mov [ans+di],ax
        inc di
        loop _loop_this
    return:
        pop ax
        mov dl, 10;
        mov ah, 0x02;
        int 0x21
        mov dl, 13;
        mov ah, 0x02;
        int 0x21
        mov dx, offset ans
        mov ah, 0x09
        int 0x21
        ret    
    
_output_number endp     
 
_start:
    mov ax, @data
    mov ds, ax
    
call _input_number
    mov Number1, ax
    mov sign1,di   
    mov dx,offset msg_number
    mov ah,0x9
    int 0x21
    mov ax,Number1
    mov di,sign1
call _output_number
call _clean_ans    
call _input_number
    mov Number2, ax
    mov sign2,di
    mov dx,offset msg_number
    mov ah,0x9
    int 0x21
    mov ax,Number2
    mov di,sign2
call _output_number                
call _clean_ans   
_logical_byte_operation_AND:
    mov dx, offset msg_and
    mov ah, 0x9
    int 0x21
call _xor_proc    
    mov bx,Number1
    mov dx,Number2
    AND dx,bx
    mov ax,dx
    mov dx,sign1
    mov di,sign2
    AND di,dx
    call _output_number
    call _clean_ans
_logical_byte_operation_OR:
    mov dx, offset msg_or
    mov ah, 0x9
    int 0x21
    call _xor_proc
    mov bx,Number1
    mov dx,Number2
    OR dx,bx
    mov ax,dx
    mov dx,sign1
    mov di,sign2
    OR di,dx
    call _output_number
    call _clean_ans  
_logical_byte_operation_XOR:
    mov dx, offset msg_xor
    mov ah, 0x9
    int 0x21
    call _xor_proc
    mov bx,Number1
    mov dx,Number2
    XOR dx,bx
    mov ax,dx
    mov dx,sign1
    mov di,sign2
    XOR di,dx
    call _output_number
    call _clean_ans    
_logical_byte_operation_NOT1:
    mov dx, offset msg_not1
    mov ah, 0x9
    int 0x21
    call _xor_proc
    mov bx,Number1
    NOT bx
    mov ax,bx
    mov di,sign1
   ;NOT di
    call _inverse_
    call _output_number
    call _clean_ans
_logical_byte_operation_NOT2:
    mov dx, offset msg_not2
    mov ah, 0x9
    int 0x21
    call _xor_proc
    mov dx,Number2
    NOT dx
    mov ax,dx
    mov di,sign2
    ;NOT di 
    call _inverse_
    call _output_number
   
   ;   0000 0011 1100 1001  969
   ;   0000 0010 1011 1000  696
   ;A  0000 0010 1000 1000 +
   ;O  0000 0011 1111 1001 +
   ;X  0000 0001 0111 0001 +
   ;N1 1111 1100 0011 0110 +
   ;N2 1111 1101 0100 0111 +
   ;
_exit:
    mov ah, 0x4c
    int 0x21    

_exit_without_output:
    mov ah, 0x4c
    int 0x21

end _start