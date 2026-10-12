1-
dissasemble main

2-
chmod 777 debugger0_b
dissasemble run
break *mian+59
print/d $eax

3-
chmod 777 debugger0_c
disassemble main
break *main+22
x/4xb $rbp-0x4

4-
chmod 777 debugger0_b
disassemble main
dissasemble func1
print 0x3269


