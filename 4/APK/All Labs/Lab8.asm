.286
.model tiny
.code
org 100h
program:
jmp set_resident

old_keyboard_interrupt_handler dd 0
old_timer_interrupt_handler dd 0
old_int10h_interrupt_handler dd 0

save_screen_flag db 0

video_buff equ 0B800h
screen_attribute db 3bh
screen_symbol db ' '
screen_buffer dw 2000 dup(0)
screen_size equ 4000
screen_row_size equ 80

save_interval dw 0
save_interval_str db 5 dup(0)
time_counter dw 0

symbols_overflow_flag db 0
no_symbol_flag db 0
invalid_symbol_flag db 0

time_counter_overflow_msg db "Delay too big", 10, 13, '$'

no_symbol_msg db "No argument founded", 10, 13, '$'

invalid_argument_msg db "Invalid argument", 10, 13, '$'

keyboard_interrupt_handler proc far
    pusha
    push es
    push ds
    push cs
    pop ds

    pushf
    call dword ptr cs:old_keyboard_interrupt_handler

    cli

    xor ax, ax
    mov ah, 11h
    int 16h
    jz empty_keyboard_buffer

    cmp al, 1Bh
    jne empty_keyboard_buffer


    mov ds, word ptr cs:old_keyboard_interrupt_handler + 2
    mov dx, word ptr cs:old_keyboard_interrupt_handler
    mov al, 09h
    mov ah, 25h
    int 21h

    mov ds, word ptr cs:old_int10h_interrupt_handler + 2
    mov dx, word ptr cs:old_int10h_interrupt_handler
    mov al, 10h
    mov ah, 25h
    int 21h

    mov ds, word ptr cs:old_timer_interrupt_handler + 2
    mov dx, word ptr cs:old_timer_interrupt_handler
    mov al, 1ch
    mov ah, 25h
    int 21h
    
    push cs
    pop ds

    empty_keyboard_buffer:

    sti

    cmp byte ptr cs:[save_screen_flag], 0
    jne stop_save_screen
    jmp exit_keyboard_interrupt_handler

    stop_save_screen:
        call restore_screen
        mov byte ptr cs:[save_screen_flag], 0
        jmp exit_keyboard_interrupt_handler

    exit_keyboard_interrupt_handler:
    mov word ptr cs:[time_counter], 0
    ;mov al, byte ptr[screen_attribute]
    ;inc al
    ;mov byte ptr[screen_attribute], al
    pop ds
    pop es
    popa
    iret
keyboard_interrupt_handler endp

int10h_interrupt_handler proc far
    pusha
    push es
    push ds
    push cs
    pop ds

    pushf
    call cs:old_int10h_interrupt_handler

    pop ds
    pop es
    popa

    cmp ax, 8899h
    je swap
    jmp _exit_int10h
    swap:
        xchg al, ah
    _exit_int10h:
    iret
int10h_interrupt_handler endp
    
timer_interrupt_handler proc far
    push ds
    push cs
    pop ds

    pushf
    call dword ptr cs:old_timer_interrupt_handler

    pusha

    xor ax, ax
    mov ax, word ptr cs:[time_counter]
    inc ax
    mov word ptr cs:[time_counter], ax
    cmp ax, word ptr cs:[save_interval]

    jb exit_time_interrupt_handler

    cmp byte ptr cs:[save_screen_flag], 0
    jne exit_time_interrupt_handler

    mov word ptr cs:[time_counter], 0
    mov byte ptr cs:[save_screen_flag], 1
    call save_screen
    call render_sleep_picture


    exit_time_interrupt_handler:
    
    popa
    pop ds
    iret
timer_interrupt_handler endp

save_screen proc
    pusha
    push es
    push video_buff
    pop es
    xor di, di
    xor ax, ax
    save_screen_loop:
        mov ax, word ptr es:[di]
        mov word ptr cs:[screen_buffer + di], ax
        add di, 2
        cmp di, screen_size
        jl save_screen_loop
    pop es
    popa
    ret
save_screen endp

restore_screen proc
    pusha
    push es
    push video_buff
    pop es
    xor di, di
    xor ax, ax
    restore_screen_loop:
        mov ax, word ptr [screen_buffer + di]
        mov word ptr es:[di], ax
        add di, 2
        cmp di, screen_size
        jl restore_screen_loop
    pop es
    popa
    ret
restore_screen endp

render_sleep_picture proc
    pusha
    push es
    push video_buff
    pop es
    xor di, di
    mov al, byte ptr cs:[screen_symbol]
    mov ah, byte ptr cs:[screen_attribute]
    render_sleep_picture_loop:
        mov word ptr es:[di], ax
        add di, 2
        cmp di, screen_size
        jl render_sleep_picture_loop
    pop es
    popa
    ret
render_sleep_picture endp


;input: si - source string
;       di - place to hold digit
;output: in di   
atoi proc
    pusha
    xor bx, bx
    xor ax, ax
    start_converting:
        cmp byte ptr cs:[si], '0'
        jb _exit_atoi
        cmp byte ptr cs:[si], '9'
        jg _exit_atoi
        mov bl, 10
        mul bx 
        mov bl, byte ptr cs:[si]
        sub bl, '0'
        add ax, bx
        inc si
        jmp start_converting
    _exit_atoi:
    mov word ptr cs:[di], ax
    popa
    ret
atoi endp  

parse_command_line proc
    pusha
    xor ax, ax
    xor bx, bx
    mov bl, byte ptr es:[80h]
    cmp bl, 1
    jbe _exit_parse_command_line_no_symbol
    cmp bl, 4
    jg _exit_parse_command_line_symbol_overflow
    mov si, 82h
    mov di, offset save_interval_str
    parse_count:
        mov al, byte ptr es:[si]
        cmp al, ' '
        je end_parse_count
        cmp al, 0dh
        je end_parse_count
        cmp al, '0'
        jl _invalid_value
        cmp al, '9'
        jg _invalid_value
        mov byte ptr[di], al
        inc si
        inc di
        jmp parse_count
    end_parse_count:
        mov byte ptr[di], '$'
        jmp _exit_parse_command_line
    _exit_parse_command_line_no_symbol:
        mov byte ptr[no_symbol_flag], 1
        jmp _exit_parse_command_line
    _exit_parse_command_line_symbol_overflow:
        mov byte ptr[symbols_overflow_flag], 1
        jmp _exit_parse_command_line
     _invalid_value:
        mov byte ptr[invalid_symbol_flag], 1
        jmp _exit_parse_command_line
    _exit_parse_command_line:
        popa
        ret
parse_command_line endp

;input: ax - secs
;ouput: ax - ticks
convert_sec_to_ticks proc
    xor bx, bx
    mov bx, 182
    mul bx
    mov bx, 10
    div bx
    ret
convert_sec_to_ticks endp


set_resident:
    mov ax, 8899h
    int 10h
    cmp ax, 9988h
    je _exit
    jmp installer
    _exit:
        mov ax, 4c00h
        int 21h

    copy_counter_overflow:
        xor dx, dx
        mov ah, 09h
        mov dx, offset cs:time_counter_overflow_msg
        int 21h
        jmp _exit
    
    error_no_symbol:
        xor dx, dx
        mov ah, 09h
        mov dx, offset cs:no_symbol_msg
        int 21h
        jmp _exit

    invalid_argument:
        xor dx, dx
        mov ah, 09h
        mov dx, offset cs:invalid_argument_msg
        int 21h
        jmp _exit

    installer:
    call parse_command_line

    cmp byte ptr cs:[no_symbol_flag], 1
    je error_no_symbol

    cmp byte ptr cs:[symbols_overflow_flag], 1
    je copy_counter_overflow

    cmp byte ptr cs:[invalid_symbol_flag], 1
    je invalid_argument

    mov si, offset cs:save_interval_str
    mov di, offset cs:save_interval
    call atoi
    mov ax, word ptr cs:[save_interval]
    call convert_sec_to_ticks
    mov word ptr cs:[save_interval], ax

    cli

    mov al, 10h
    mov ah, 35h
    int 21h

    mov word ptr cs:old_int10h_interrupt_handler, bx
    mov word ptr cs:old_int10h_interrupt_handler + 2, es

    mov dx, offset int10h_interrupt_handler
    mov al, 10h
    mov ah, 25h
    int 21h

    mov al, 1ch
    mov ah, 35h
    int 21h

    mov word ptr cs:old_timer_interrupt_handler, bx
    mov word ptr cs:old_timer_interrupt_handler + 2, es

    mov dx, offset cs:timer_interrupt_handler
    mov al, 1ch
    mov ah, 25h
    int 21h


    mov al, 09h
    mov ah, 35h
    int 21h

    mov word ptr cs:old_keyboard_interrupt_handler, bx
    mov word ptr cs:old_keyboard_interrupt_handler + 2, es

    mov dx, offset cs:keyboard_interrupt_handler
    mov al, 09h
    mov ah, 25h
    int 21h


    sti

    mov dx, offset set_resident
    int 27h

end program
