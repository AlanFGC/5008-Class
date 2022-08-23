# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
  
.globl main

main:
            # (1) What are we setting up here?
            # Ans:
  pushq %rbp      # here we are pushing 8 bytes into the stack, the %rbp is the frame pointer.
  movq  %rsp, %rbp  # we are moving 8 bytes from %rsp register which keeps track of stack position to the %rbp register. 
                    # these lines are usually setting up the stack to run the program

              # (2) What is going on here
              # Ans:
  movq $1, %rax     # it is moving and 8 byte piece of data $1 to the register %rax, according to me this $1 variable represents a value.
                    # by convention %rax is where you store the return value or send a value to a function.
  movq $1, %rdi     # here it is doing the same but moving it to the %rdi register, %rdi is usually used to pass parameter value to a function.
  leaq .hello.str,%rsi  # we are loading the effective address of the source into the destination %rsi. .hello.str looks like a variable of string type.


          # (3) What is syscall? We did not talk about this
          # in class.
          # Ans: syscall is how the code communicates with the operating system. In this case its probably trying to execute 'a display to the terminal command'
          #
  syscall     # Which syscall is being run?
          # Ans: in this case we are passing an address to the %rsi which is used as the first(1) argument of x86_64 architecture. In the previous lines we pass 1
          # to the rax register which is invoking the write function. Syscall one accepts a char* as the first argument to write onto the terminal.

          # (4) What would another option be instead of 
          # using a syscall to achieve this?
          # Ans: there are ways to do this without using the syscall that asks the OS kernel to perform this, we can write or own code that interacts with 
          # stdout (standard Output). This manual approach would need information to be sent to stdout so that it can be displayed in the terminal. 

  movq  $60, %rax   # (5) We are again setting up another syscall
  movq  $0, %rdi    # What command is it?
              # Ans:  the value 60 is the exit call of the program. We are ending the program here.
  syscall

  popq %rbp     # (Note we do not really need
              # this command here after the syscall)

.hello.str:
  .string "Hello World!\n"
  .size .hello.str,13   # (6) Why is there a 13 here?
                # Ans:  13 is the size of the string
