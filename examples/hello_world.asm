; Print hello world
push 27
push 12
push 0
syscall

; Exit with code 0
push 0
push 1
syscall

; Define strings
	bytes "Hello World!"