; Print hello world
push hello_world
push 13
push 0
syscall

; Exit with code 0
push 0
push 1
syscall

; Define strings
hello_world:
	bytes "Hello World!\n"