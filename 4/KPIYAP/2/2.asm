;17. заменить все числа на слово <number>, с последующим их удалением.
.model small
.stack 100h
.data
    start_msg db "Enter a string:",10,13,'$'
    word_number db "<number>"
    string  db 201                          ;,200,200,200
            db ?
            db 201 dup (?)
.code
 get_length proc 
    pop ax
    pop bx
    sub ax, bx
    push ax
    ret
 get_length endp
 
 left_shift_with_insert macro count, str, word  ;//8, string, <number>
        pop dx                                  ;//достаём конец слова
        push di                                 ;//сохраняем конец слова
        push si                                 ;//сохраняем пробел
        mov si, dx                              ;//помещаем конец слова в si
        xor ax, ax
        mov al, byte ptr [str + 1]              ;//Прямая?(ptr)              
        mov di, offset str + 2                  ;//относительная косвенная?
        add di, ax                              ;//Сумма
        inc di                                  ;//Увеличение на 1 (смещение вправо)
        shift_loop:
            dec di                              ;//Уменьшение на 1 (смещение влево)
            mov al, byte ptr ds:[di]            ;//Прямая?(ptr) Косвенная (ds:[di])?
            mov byte ptr ds:[di+8], al 
            cmp di, si
            je  _insert_word
            jmp shift_loop
        _insert_word:
            mov di, offset word
            xor cx, cx
            mov cx, 8                           ;//Непосредственная
            _insert_word_loop:
                mov al, [di]                    ;//Косвенная(индексная)
                mov [si], al
                inc di
                inc si
            loop _insert_word_loop
                
                mov si, dx
                xor ax, ax
                mov al, byte ptr [str + 1]              
                mov di, offset str + 2                            
                add di, ax
                add di,8                              
                add si,8
                inc di
                xor cx,cx
    _loop_this:
                dec di
                cmp di, si  
                jne _loop_this
                inc cx
                mov ah, ' '
                mov al, [di]
                cmp ah,al
                je _exit_shift
                mov ah, '$'
                mov al, [di]
                cmp ah,al
                je _exit_shift
                
            _swap_to_end:    
                mov al, byte ptr ds:[di+1]  
                mov byte ptr ds:[di], al 
                inc di
                mov ah, '$'
                mov al, [di]
                cmp ah,al
                jne _swap_to_end
                jmp _loop_this
                
            jmp _exit_shift
         _exit_shift:
            pop si
            pop di                                     
  endm
            
            
_start:
    mov ax, @data
    mov ds, ax
    
_start_msg:								;//Вывод стартового сообщения
    mov dx, offset start_msg
    mov ah, 0x9
    int 0x21
    mov dx, offset string				;//Ввод строки
    mov ah, 0x0A
    int 21h
   
_check_string_length:
   xor ah, ah
   xor si, si
   mov si, offset string + 1	
   mov al, byte ptr[si]
   cmp al, 201							;//Проверка на 200символов
   jae _exit_without_output
   cmp al, 0							;//Проверка на 0 символов
   je _exit_without_output
   jmp _replace_enter
    
_replace_enter:
    xor si, si
    mov si, offset string + 1
    xor ch, ch
    mov cl, [si]
    inc cx
    add si,cx                           ;//увеличиваем счётчик на длину string+2
    mov al, '$'
    mov [si], al                        ;//Добавляем символ в конец 
    
_prepare_for_searching_words:
    mov di, offset string + 2
    xor ax, ax
    mov al, 32                          ;//указываем пробел
    xor cx, cx
    mov cl, byte ptr[string + 1]        ;//передаём ссылку на начало строки
    inc cx                              
    jmp _find_word                      ;// al = ' ', cl=&string

_inc_dest_index:
    mov di, si                         ;//первый символ
    inc di
    xor ax, ax
    mov ah, '$'
    mov al, [di]                        ;//сравниваем с концом строки
    inc di
    pop cx
    cmp ah, al
    je _exit
    jmp _find_word    

_find_word:
    push di                         ;//загоняем в стек di = string+2
    jmp _start_searching_word       ;// ss = {di=string+2}

_start_searching_word:
    mov ah, [di]                    ;//передаём первый символ из di в ah, при этом al=' '
    inc di
    cmp al, ah
    je _check_is_number             ;//нашли пробел
    loop _start_searching_word      
    jmp _check_is_number            ;//конец строки
        
       
_check_is_number_last:
    dec di
    mov si, di
    pop di
    push cx
    xor dx, dx
    mov dx, di
    dec di
    xor ax, ax
    cmp di, si
    je _inc_dest_index
    jmp _start_cheking_last
    
_start_cheking_last:
    cmp di, si
    je _out_founded_word
    inc di
    mov ah, "0"
    mov al, [di]
    cmp al, ah
    jl _exit
    mov ah, "9"
    cmp al, ah
    jg _exit
    jmp _start_cheking_last
       
_check_is_number:                   
    dec cx                      
    sub di, 2                   ;//разность
    mov si, di                  ;//положение первого сивола
    pop di                      
    push cx                     
    xor dx, dx
    mov dx, di                  ;//запоминаем положение символа
    dec di
    xor ax, ax
    cmp di, si
    je _inc_dest_index
    jmp _start_cheking

_start_cheking:
    cmp di, si                  ;//si = ' ',di = string  
    je _insert_word_number
    inc di
    mov ah, "0"
    mov al, [di]
    cmp al, ah
    jl _inc_dest_index
    mov ah, "9"
    cmp al, ah
    jg _inc_dest_index
    jmp _start_cheking
    
_insert_word_number:            
    push dx                     ;//в стек отправляем конец слова (числа)
    left_shift_with_insert 8, string, word_number
    dec cx
    sub si, cx
    add di, 8
    add si, 8
    xor ax, ax
    mov al, byte ptr[string+1]
    add al, 8 
    sub al, ch
    mov byte ptr[string+1], al
    jmp _inc_dest_index    
    
    
    
_out_founded_word:
    mov di, dx
    dec di
    xor dx, dx
    jmp _print_word
_print_word:
    inc di
    mov dl, [di]
    mov ah, 0x2
    int 0x21
    cmp si, di
    jne _print_word
    je _inc_dest_index
    
_exit_without_output:
    mov ah, 0x4c
    int 0x21
    
_exit:
    mov dl, 10;
    mov ah, 0x02;
    int 0x21
    mov dl, 13;
    mov ah, 0x02;
    int 0x21
    mov dx, offset string + 2
    mov ah, 0x09
    int 0x21
    ;mov dx, offset string + 257
    ;mov ah, 0x09
    ;int 0x21
    ;mov dx, offset string + 512
    ;mov ah, 0x09
    ;int 0x21
    mov ah, 0x4c
    int 0x21    
end _start