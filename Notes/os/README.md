# OS

## Coroutine

[A working example][./coroutine.cc]

Readings:

- [Fibers](https://graphitemaster.github.io/fibers/)
    - Preemptive Scheduling and Cooperative Scheduling
    - The Problem with Multi-Threading
        - The problem with thread pools
            - Locality of reference: local valusneed their lifetime's extended for an undefined amount of time, because job isn't going to be executed immediately.
            - Starvation causes deadlock

        - N:1 means N fibers to 1 thread
        - M:N means M fibers to N thread

- [协程原理解析](https://zhuanlan.zhihu.com/p/52061886)
- [C 的 coroutine 库](https://blog.codingnow.com/2012/07/c_coroutine.html)
- [coroutine code](https://github.com/cloudwu/coroutine)




