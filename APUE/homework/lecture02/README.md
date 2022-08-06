# File Descriptors Warmup Exercise

Write a small program that:

prints the value of the STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO constants
prints the value of the file descriptors referenced via the stdin, stdout, and stderr streams
open(2)s a file, then prints the value of the resulting file descriptor
fopen(3)s a file, then prints the value of the file descriptor referenced via that stream
What happens when you open the same file multiple times with or without closing it again in between?

Try opening the same file twice, then writing different data to each file descriptor (via write(2)) - what happens?

Open an existing file that contains some data - perform alternate read(2) and write(2)s on that file descriptor. What does that tell you about the position in the file as you perform these operations? How would you go about replacing a specific word in a file?

Even for this warmup exercise, remember to ensure that your code complies with our requirements 

## Notes to questions

What happens when you open the same file multiple times with or without closing it again in between?

> It opens successfully, and with another file descriptor 

Try opening the same file twice, then writing different data to each file descriptor (via write(2)) - what happens?

> If they are opened with "O_RDWR", the second write will overwrite the first one's content. 
> If the second one is opend with "O_RDWR | O_APPEND", the content will be appended to the end of the file.

Open an existing file that contains some data - perform alternate read(2) and write(2)s on that file descriptor. What does that tell you about the position in the file as you perform these operations? 

> Read will move the current position of the file. Write will continue from this position after read.

How would you go about replacing a specific word in a file?
> We can read util we encounter the word, and rewind the position and write. But if the replaced word is longer as the original word, the next word can be overwritten.

