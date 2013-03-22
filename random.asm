;sycall parameter order: rdi,rsi,rdx,rcx,r10,r11
;additional parameters are passed on the stack

extern atoi
extern printf

%define STDIN 0
%define STDOUT 1

%define READ 0
%define WRITE 1
%define TIME 201

%define NL 0Ah

; Linear Congruence constants
%define a 05DEECE66Dh
%define c 0Bh

%define BUF_LEN 80

section .data

title		db "Linear Congruence Pseudo Random Number Generator",NL,NL,0
enter_min	db "Enter a minimum value for the random numbers ",0
enter_max 	db "Enter a maximum value for the random numbers ",0
enter_count 	db "How many random numbers? ",0
num_str 	db "%d ",0
endl		db NL,0

section .bss

buf resb BUF_LEN
min resb BUF_LEN
max resb BUF_LEN
count resb BUF_LEN

section .text

global main
main:

mov rax,title			; Print title
call WriteString

mov rax,enter_min		; Prompt minimum
call WriteString
mov rax,endl
call WriteString
call ReadInt
mov [min],rax

mov rax,enter_max		; Prompt maximum
call WriteString
mov rax,endl
call WriteString
call ReadInt
mov [max],rax

mov rax,enter_count		; Prompt count
call WriteString
mov rax,endl
call WriteString
call ReadInt
mov [count],rax

mov r10,[min]			; swap [min] and [max] if [min] > [max]
mov r11,[max]
cmp r10,r11
jl .LinearCongruence
mov [min],r11
mov [max],r10

.LinearCongruence:
call LinearCongruence		; Generate random numbers

mov rax,0			; Return 0
ret

;-------------------------------------------------------------------------------
LinearCongruence:
; Prints 'count' random numbers between 'min' and 'max' using the drand48 Linear
; Congruence formula.
;-------------------------------------------------------------------------------
	push rax
	push rbx
	push rcx
	push rdx
	push r10
	push r11

	mov rax,TIME		; Use seconds since the Unix Epoch for random seed
	syscall
	mov rcx,[count]		; Prepare to loop [count] times
	cmp rcx,0		; if count == 0, return to prevent "infinite" loop
	je .end

	.loop:
		; Xsub(n+1) = (aXsub(n) + c)mod m   n>= 0
		mov r10,a;	; a = 05DEECE66Dh
		mul r10
		add rax,c	; c = 0Bh
		mov r11,rax	; Store random value
		mov rdx,0	; Clear dividend upper bits. rax contains lower bits we're interested in.

		; num_low_to_high = (r % (hi - low + 1)) + low
		mov rbx,[max]	
		sub rbx,[min]
		add rbx,1
		div rbx 	; rdx:rax = dividend, rax = quotient, rbx = divisor, remainder = rdx 
		add rdx,[min]
		mov rax,rdx
		push r11
		push rcx	; Registers are volatile. Store count before calling this procedure.
		call WriteInt	; Print random number between min and max
		pop rcx
		pop r11
		mov rax,r11	; Restore random value
	loop .loop		; Do while count-- > 0

	mov rax,endl		; Print newline
	call WriteString

	.end:
	pop r11
	pop r10
	pop rdx
	pop rcx
	pop rbx
	pop rax
	ret

;-------------------------------------------------------------------------------
ReadInt:
; Reads a string from STDIN and parses the integer
; Returns:	RAX = integer read (0 if no integer found)
;-------------------------------------------------------------------------------
	push rdi

	call ReadString
	mov rdi,buf
	call atoi

	pop rdi
	ret

;-------------------------------------------------------------------------------
ReadString:
; Reads a string from STDIN
; Returns:	buf = string read
;-------------------------------------------------------------------------------
	push rax
	push rdi
	push rsi
	push rdx

	mov rax,READ
	mov rdi,STDIN
	mov rsi,buf
	mov rdx,BUF_LEN
	syscall

	pop rdx
	pop rsi
	pop rdi
	pop rax
	ret

;-------------------------------------------------------------------------------
WriteInt:
; Writes an integer to STDOUT
; Receives:	RAX = Integer to be printed
;-------------------------------------------------------------------------------
	push rdi
	push rsi

	mov rsi,rax
	mov rdi,num_str
	mov rax,0
	call printf

	pop rsi
	pop rdi
	ret

;-------------------------------------------------------------------------------
WriteString:
; Writes a string to STDOUT
; Receives:	RAX = string to be printed
;-------------------------------------------------------------------------------
	;mov rsi,rax
	;mov rdx,rdi
	;mov rax,WRITE
	;mov rdi,STDOUT
	;syscall
	push rdi

	mov rdi,rax
	mov rax,0
	call printf

	pop rdi
	ret

