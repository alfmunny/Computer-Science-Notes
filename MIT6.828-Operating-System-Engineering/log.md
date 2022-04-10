# MIT 6.828: Operation System Engineering

Category: OS
Content: Course 🖥
Created time: Feb 1, 2021 1:40 AM
Status: Inbox
Tags: C
URL: https://github.com/alfmunny/MIT6.828-Operation-System-Engineering

# Log

- 2020.02.27
    - Start the course.
    - Found an interesting posts about the new course information of 6.S081. [https://conanhujinming.github.io/post/mit_6_828_together/](https://conanhujinming.github.io/post/mit_6_828_together/)
    - Watch the lecture 1 video [introduction](https://www.youtube.com/watch?v=L6YqHxYHa7A&feature=youtu.be&ab_channel=DavidMorejon).
        - run xv6.
        - show some examples: [https://pdos.csail.mit.edu/6.828/2020/lec/l-overview/](https://pdos.csail.mit.edu/6.828/2020/lec/l-overview/)
            - copy, open, grep, fork, echo, exec, forkexec, redirect
            - file descriptor 0 and 1
    - Prepare the tool chain and environment.
        - There is a bug when executing `make qemu`

            ```bash
            dyld: Library not loaded: /usr/local/opt/isl/lib/libisl.22.dylib
            ```

            Solution:

            ```bash
            install_name_tool -change '/usr/local/opt/isl/lib/libisl.22.dylib' /usr/local/opt/isl/lib/libisl.dylib /usr/local/Cellar/riscv-gnu-toolchain/master/libexec/gcc/riscv64-unknown-elf/10.2.0/cc1
            ```

-