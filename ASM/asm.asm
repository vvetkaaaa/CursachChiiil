.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO :DWORD

Date PROTO 
Time PROTO 
OutputStr PROTO :DWORD
OutputStrNoLine PROTO :DWORD
OutputInt PROTO :DWORD
OutputIntNoLine PROTO :DWORD

.stack 4096

.CONST
	overflownum BYTE "Выход за пределы значения", 0
	neguint BYTE "Отрицательное число", 0
	L1 BYTE "x and y arent equals", 0
	L2 BYTE "x and y are equals", 0
	L3 DWORD 3
	L4 DWORD 2
	L5 DWORD 5
	L6 BYTE "two num are equals", 0
	L7 BYTE "two num arent equals", 0
	L8 DWORD 14
	L9 BYTE "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", 0

.data
	count DWORD 0
	more_res DWORD 0
	equals_res DWORD ?
	main_data DWORD ?
	main_time DWORD ?
	main_a DWORD 0
	main_b DWORD 0
	main_x DWORD 0
	main_y DWORD 0
	main_eq DWORD ?
	main_noeq DWORD ?
	main_eight DWORD 0
	main_resmore DWORD 0
	main_output DWORD ?
	main_tyu DWORD ?

.code

more PROC more_a : DWORD, more_b : DWORD
	mov eax, more_a
	cmp eax, more_b
	ja m0
	jb m1
	je m1
m0:
	push more_a
	pop more_res
	jmp e0
m1:
	push more_b
	pop more_res
e0:
	push more_res
	jmp local0
local0:
	pop eax
	ret
OutAsm:
	push 0
	call ExitProcess
OVERFLOW:
	push offset overflownum
	call OutputStr
	push 0
	call ExitProcess
NEGNUM:
	push offset neguint
	call OutputStr
	push 0
	call ExitProcess
more ENDP

equals PROC equals_x : DWORD, equals_y : DWORD
	mov eax, equals_x
	cmp eax, equals_y
	jne m2
	je m3
	je m3
m2:
	push offset L1
	pop equals_res
	jmp e1
m3:
	push offset L2
	pop equals_res
e1:
	push equals_res
	jmp local1
local1:
	pop eax
	ret
OutAsm:
	push 0
	call ExitProcess
OVERFLOW:
	push offset overflownum
	call OutputStr
	push 0
	call ExitProcess
NEGNUM:
	push offset neguint
	call OutputStr
	push 0
	call ExitProcess
equals ENDP

main PROC
	call Date
	push eax
	pop main_data
	push main_data
	call OutputStr
	call Time
	push eax
	pop main_time
	push main_time
	call OutputStr
	push L3
	pop main_a
	push L4
	pop main_b
	push L5
	pop main_x
	push L5
	pop main_y
	push offset L6
	pop main_eq
	push offset L7
	pop main_noeq
	mov eax, main_x
	cmp eax, main_y
	je m4
	jne m5
	je m5
m4:
	push main_eq
	call OutputStr
	jmp e2
m5:
	push main_noeq
	call OutputStr
e2:
	push L8
	pop main_eight
	push main_eight
	call OutputInt
	push main_a
	push main_b
	pop edx
	pop edx
	push main_b
	push main_a
	call more
	push eax
	pop main_resmore
	push main_x
	push main_y
	pop edx
	pop edx
	push main_y
	push main_x
	call equals
	push eax
	pop main_output
	push main_x
	call OutputInt
	push offset L9
	pop main_tyu
	push main_resmore
	call OutputInt
	push main_output
	call OutputStr
OutAsm:
	push 0
	call ExitProcess
OVERFLOW:
	push offset overflownum
	call OutputStr
	push 0
	call ExitProcess
NEGNUM:
	push offset neguint
	call OutputStr
	push 0
	call ExitProcess
main ENDP
end main