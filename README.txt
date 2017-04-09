Q: Why we need to install kernel-package
A: Bởi vì tại đây chúng ta có rất nhiều phiên bản hat nhân (kernel) để cho chúng ta lựa chọn sao cho phù hợp
với cấu hình phân cứng của máy ảo hay máy thật của bạn.

Q: Why we have to use another kernel source from the server such as http://www.kernel.org,
can we compile the original kernel (the local kernel on the running OS) directly
A: Được, bạn có thể biên dịch hạt nhân gốc (the original kernel) trong tệp của OS đang sử dụng, vì hật nhân mặc định
được vận chuyển với Debian xử lý hầu hết các cấu hình. Ngoài ra, Debian thường cung cấp một số hạt nhân thay
thế, bạn cần kiểm tra trước hạt nhân này tương thích tốt với cấu hình phần cứng của bạn, tuy nhiên những lợi
ích cụ thể biên dịch từ hạt nhân (kernel) mới từ server là để:
- Xử lý các nhu cầu phần cứng đặc biệt, hoặc xung đột phần cứng với hạt nhân được cung cấp trước
- Sử dụng các tùy chọn sử dụng hạt nhân mà không được hỗ trợ trong các hạt nhân được cung cấp trước (chẳng hạn như hỗ trợ bộ nhớ cao)
- Tối ưu hóa hạt nhân bằng cách loại bỏ các trình điều khiển vô ích để tăng tốc độ khởi động
- Tạo ra một monolithic thay vì một hạt nhân đã được modularized
- Chạy một cập nhật hạt nhân hoặc dành cho nhà phát triển

3.5 Configuration
* Kernel configuration *

$ cp /boot/config -4.x.x-generic ˜/kernelbuild/[kernel directory]/.config

*  To edit configure file through terminal interface, we must install libncurses5 − dev package first *

$ sudo apt-get install libncurses5-dev

$ make nconfig // or make menuconfig

To change kernel version, go to General setup option, Access to the line \(-ARCH) Local version - append
to kernel release". Then enter a dot \." followed by your MSSV. For example:

.1513656

* During compiling, you can encounter the error caused by missing openssl packages. You need to
install these packages by running the following command: *

$ sudo apt-get install openssl libssl-dev

QUESTION: What is the meaning of other parts, i.e. i386, procmem, and sys_procmem?:
A: 
- [Number]: Tất cả các syscalls được xác định bởi một số duy nhất. Để gọi một syscall, 
chúng ta nói với kernel để gọi syscall theo số của nó chứ không phải bằng tên của nó.
- i386 : [ABI] : Application Binary Interface - là interface giữa hai chương trình modules, một trong số
đó thường là thư viện hoặc hệ điều hành, ở mức mã máy phổ biến là x64, x32, i386
- procmem : [name] : đây là tên của syscall
- sys_procmem : [entry point] : Điểm truy cập, là tên của hàm để gọi để xử lý syscall. Quy ước đặt tên cho
hàm này là tên của syscall có tiền tố với sys_. Ví dụ, điểm truy nhập của syscall đọc là sys_read.

QUESTION: What is the meaning of each line above?
A: {
	struct proc_segs; // đối số proc_segs kiểu struct
	asmlinkage long sys_procmem( int pid, struct proc_segs * info); 
/** hàm sử lý syscall kiểu trả về long 
* asmlinkage là một tag được định nghĩa (#define) với một số gcc biên dịch cho trình trình
* biên dịch biết rằng hàm không mong chờ tìm thấy tất cả đối số trong thanh ghi (registers) một cách tối ưu
* phổ biến. Nhưng chỉ trên stack của CPU. systemcall tiếp nhận đối số number đầu tiên, và cho phép 4 đối số
* đưuọc truyền vào hệ thống thực, các đối số này nằm trên stack. tất cả systemcall đánh dấu bởi asmlinkage tag
* nên chúng nhìn stack để tìm đối số, Nó cũng được sử dụng để cho phép gọi một hàm từ assembly files.		
	*/
										
}
Similarly, add the following line to the end of syscall_64.tbl if you use the OS - 64bit:
[number] x32 procmem sys_procmem , we can find file syscall_64.tbl in arch/x86/entry/syscalls


4 Compiling Linux Kernel

- Build the configured kernel
* run "make" to complie the kernel and create vmlinuz. but "$ make" takes long time to run, we can use tag
"-j np", where np is the number of processes you run this command.
->Or
vmlinuz is \the kernel". Specifically, it is the kernel image that will be uncompressed and loaded into
memory by GRUB or whatever other boot loader you use. Then build the loadable kernel modules.

QUESTION: What is the meaning of these two stages, namely \make" and \make modules"?

A: {}

Installing the new kernel
$ sudo make modules_install
or
$ sudo make -j 4 modules_install
Then install the kernel itself:
$ sudo make install
or
$ sudo make -j 4 install
$ sudo reboot
done


5 - when add a systemcall funtions make sure that you add a line at the end of Makefile In the
folder arch/x86/kernel file for compiling the system call. (maybe at line if(x86))

obj-y += sys_name.o #name of syscall object file 

***HERE IS INFORMATION OF A PROCESS USE /PROC/$pPID/MAPS***
 /proc/[pid]/maps
              A file containing the currently mapped memory regions and
              their access permissions.  See mmap(2) for some further
              information about memory mappings.

              Permission to access this file is governed by a ptrace access
              mode PTRACE_MODE_READ_FSCREDS check; see ptrace(2).

              The format of the file is:

       address           perms offset  dev   inode       pathname
       00400000-00452000 r-xp 00000000 08:02 173521      /usr/bin/dbus-daemon
       00651000-00652000 r--p 00051000 08:02 173521      /usr/bin/dbus-daemon
       00652000-00655000 rw-p 00052000 08:02 173521      /usr/bin/dbus-daemon
       00e03000-00e24000 rw-p 00000000 00:00 0           [heap]
       00e24000-011f7000 rw-p 00000000 00:00 0           [heap]
       ...
       35b1800000-35b1820000 r-xp 00000000 08:02 135522  /usr/lib64/ld-2.15.so
       35b1a1f000-35b1a20000 r--p 0001f000 08:02 135522  /usr/lib64/ld-2.15.so
       35b1a20000-35b1a21000 rw-p 00020000 08:02 135522  /usr/lib64/ld-2.15.so
       35b1a21000-35b1a22000 rw-p 00000000 00:00 0
       35b1c00000-35b1dac000 r-xp 00000000 08:02 135870  /usr/lib64/libc-2.15.so
       35b1dac000-35b1fac000 ---p 001ac000 08:02 135870  /usr/lib64/libc-2.15.so
       35b1fac000-35b1fb0000 r--p 001ac000 08:02 135870  /usr/lib64/libc-2.15.so
       35b1fb0000-35b1fb2000 rw-p 001b0000 08:02 135870  /usr/lib64/libc-2.15.so
       ...
       f2c6ff8c000-7f2c7078c000 rw-p 00000000 00:00 0    [stack:986]
       ...
       7fffb2c0d000-7fffb2c2e000 rw-p 00000000 00:00 0   [stack]
       7fffb2d48000-7fffb2d49000 r-xp 00000000 00:00 0   [vdso]

              The address field is the address space in the process that the
              mapping occupies.  The perms field is a set of permissions:

                   r = read
                   w = write
                   x = execute
                   s = shared
                   p = private (copy on write)

              The offset field is the offset into the file/whatever; dev is
              the device (major:minor); inode is the inode on that device.
              0 indicates that no inode is associated with the memory
              region, as would be the case with BSS (uninitialized data).

              The pathname field will usually be the file that is backing
              the mapping.  For ELF files, you can easily coordinate with
              the offset field by looking at the Offset field in the ELF
              program headers (readelf -l).

              There are additional helpful pseudo-paths:

                   [stack]
                          The initial process's (also known as the main
                          thread's) stack.

                   [stack:<tid>] (since Linux 3.4)
                          A thread's stack (where the <tid> is a thread ID).
                          It corresponds to the /proc/[pid]/task/[tid]/
                          path.

                   [vdso] The virtual dynamically linked shared object.  See
                          vdso(7).

                   [heap] The process's heap.

              If the pathname field is blank, this is an anonymous mapping
              as obtained via mmap(2).  There is no easy way to coordinate
              this back to a process's source, short of running it through
              gdb(1), strace(1), or similar.

              Under Linux 2.0, there is no field giving pathname.


5.1
QUESTION: Why we have to re-define proc segs struct while we have already defined it inside the kernel?


https://shanetully.com/2014/04/adding-a-syscall-to-linux-3-14/
https://www.gnu.org/prep/standards/html_node/Writing-C.html
http://www.tldp.org/LDP/lkmpg/2.6/html/index.html
http://duartes.org/gustavo/blog/post/how-the-kernel-manages-your-memory/
https://medium.com/@ssreehari/implementing-a-system-call-in-linux-kernel-4-7-1-6f98250a8c38

http://www.informit.com/articles/article.aspx?p=368650
http://www.informit.com/articles/article.aspx?p=370047
 