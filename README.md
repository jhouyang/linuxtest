
1. fork 会继承mutex, rwlock, condition; 不会继承记录锁，信号量。
2. 进程退出时：内核会自动给记录锁解锁，但是信号量却并不会。
3. fcntl F_SETLKW/F_SETLCK/F_GETLCK是一种建议锁，就是说如果进程绕过他们直接访问文件也是可以的。


信号量的数量有限制，进程最多256，信号量最大值32767
