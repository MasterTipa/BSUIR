.286
.model tiny
.code
org 100h
jmp start
begin:
    handle_error proc
        pusha
        mov word ptr[error_code], ax
        mov si, offset error_code_string
        call itoa
        popa
        ret
    handle_error endp

    output_error proc
        pusha
        xor dx, dx
        mov ah, 09h
        mov dx, offset error_message
        int 21h
        mov ah, 09h
        mov dx, offset error_code_string
        int 21h
        mov ah, 09h
        mov dx, offset move_cursor
        int 21h
        popa
        ret
    output_error endp

     strlen proc
        push si
        xor ax, ax
        xor cx, cx
        strlen_loop:
            mov al, byte ptr[si]
            cmp al, 0
            je _exit_strlen
            inc si
            inc cx
            jmp strlen_loop

        _exit_strlen:
            pop si
            ret
    strlen endp

    ;input: ax - digit to convert
    ;       si - buffer to hold digit
    ;output: in buffer si - symbol representation of digit
    itoa proc
        pusha
        ;xor si, si
	    ;xor ax, ax
	    xor bx, bx
        ;mov di, offset error_code_string
        ;mov bx, ax
        ;call strlen
        ;mov ax, bx
        ;sub cx, 2
        ;add si, cx
        ;mov ax, word ptr[error_code]
        mov di, si
        _outer_loop_:
           mov bx, 10
	       xor dx, dx
           div bx
           add dx, '0'
           mov bl, byte ptr[si]
           inc si
           mov byte ptr[si], bl
           dec si
           mov byte ptr[si], dl
           inc si
           cmp ax, 0
           je _ret_itoa
           jmp _outer_loop_
        _ret_itoa:
            mov byte ptr[si], '$'       
        	popa
        	ret
    itoa endp

    ;input: si - source string
    ;       di - place to hold digit
    ;output: in di   
    atoi proc
        pusha
        xor bx, bx
        xor ax, ax
        start_converting:
            cmp byte ptr[si], '0'
            jb _exit_atoi
            cmp byte ptr[si], '9'
            jg _exit_atoi
            mov bl, 10
            mul bx 
            mov bl, byte ptr [si]
            sub bl, '0'
            add ax, bx
            inc si
            jmp start_converting
        _exit_atoi:
        mov word ptr[di], ax
        popa
        ret
    atoi endp    
    
    write_symbol proc
        pusha
        xor ah, ah
        mov al, bl
        mov si, offset digit
        call itoa
        xor dx, dx
        mov ah, 09h
        mov dx, offset digit
        int 21h
        ;xor dx, dx
        ;mov dl, al
        ;mov ah, 02h
        ;int 21h
        xor dx, dx
        mov dl, 10
        mov ah, 02h
        int 21h
        mov dl, 13
        mov ah, 02h
        int 21h
        popa
        ret
    write_symbol endp

    parse_command_line proc
        pusha
        xor ax, ax
        xor bx, bx

        mov bl, byte ptr es:[80h]
        ;call write_symbol
        cmp bl, 1
        jbe _exit_parse_command_line

        cmp bl, 4
        jg _exit_parse_command_line

        mov si, 82h
        mov di, offset count_of_copies
        ;add di, bx
        parse_count:
            mov al, byte ptr es:[si]
            ;call write_symbol
            cmp al, ' '
            je end_parse_count
            cmp al, 0dh
            je end_parse_count

            mov byte ptr[di], al
            inc si
            inc di
            jmp parse_count

        end_parse_count:
            mov byte ptr[di], '$'
            jmp _exit_parse_command_line

        _exit_parse_command_line:
            popa
            ret
    parse_command_line endp


    print_number proc
        pusha
        xor dx, dx
        mov ah, 09h
        mov dx, offset number_message
        int 21h
        mov ah, 09h
        mov dx, offset count_of_copies
        int 21h
        mov ah, 09h
        mov dx, offset move_cursor
        int 21h
        popa
        ret
    print_number endp


    set_cmd_param proc
        pusha
        mov si, offset count_of_copies
        call strlen
        sub cx, 2
        mov byte ptr[commandline], cl
        mov di, offset count_of_copies
        mov si, 2
        xor ax, ax
        xor bx, bx

        set_cmd_param_loop:
            mov al, byte ptr[di]
            cmp al, '$'
            je _exit_set_param
            mov bl, byte ptr[commandline+si]
            inc si
            mov byte ptr[commandline+si], bl
            dec si
            mov byte ptr[commandline+si], al
            inc si
            inc di
            ;cmp si, 1
            ;je _exit_set_param
            jmp set_cmd_param_loop

        _exit_set_param:
        popa
        ret
    set_cmd_param endp


start:

    call parse_command_line
    mov si, offset count_of_copies
    mov di, offset copy_counter
    call atoi
    
    call print_number
    
    cmp word ptr[copy_counter], 0
    je _exit

    ;call print_number

    xor cx, cx
    xor dx, dx


    mov ax, 4a00h
    ;mov bx, ((code_segment_length/16) + 1) + 256/16 + ((data_segment_size/16) + 1) + 256/16
    mov bx, ((code_segment_length/16)+1) + 256/16
    int 21h
    jc _error

    cmp word ptr[copy_counter], 0
    je _exit

    ;call print_number
    mov ax, word ptr[copy_counter]
    dec ax
    mov word ptr[copy_counter], ax
    mov si, offset count_of_copies
    call itoa
    call set_cmd_param


    mov ax, 4b00h
    lea dx, program_path
    lea bx, exec_param_block
    ;mov word ptr[buff_ss], ss
    ;mov word ptr[buff_sp], sp
    int 21h
    ;mov ss, word ptr[buff_ss]
    ;mov sp, word ptr[buff_sp]
    jc _error
    jmp _exit
    
    _error:
        call handle_error
        call output_error
    
    _exit:
        xor dx, dx
        mov ah, 09h
        mov dx, offset shit_msg
        int 21h
        mov ax, 4c00h
        int 21h
    ;int 20h
    

    program_path db "c:/to_run/lab7.exe", 0
    exec_param_block dw 0
    cmd_of dw offset commandline, 0
    fcb1 dw 005ch, 0
    fcb2 dw 006ch, 0

    commandline db 4
                db " ", 0dh
    commandline_text db 122 dup(?)

    epb_length dw $-exec_param_block

    copy_counter dw 0

    count_of_copies db 3 dup('$'), '$', 0

    digit db 6 dup('$'), 0

    shit_msg db "Lel, it's happend cuz you dummy$"

    error_code dw 0
    error_code_string db 6 dup('$'), 0
    error_message db "Error occurred. Error code : ", '$'
    move_cursor db 10, 13, '$'

    number_message db "Number of copy : ", '$', 0

    buff_ss dw 0
    buff_sp dw 0


    data_segment_size = $ - program_path
    code_segment_length = $ - begin
end start
end begin