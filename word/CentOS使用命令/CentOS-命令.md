# **CentOS**命令 记录 #
梁志军 home-pc CentOS 虚拟机 root账号密码：root123456

## 常用 ##
1. 查看centos上安装了多少个软件  
	rpm -qa | wc -l
2. 查看安装了的软件包  
	rpm -qa | sort
3. 字符界面切换到图形界面  
	startx
4. 图形界面切换到字符界面  
	init 3
5. 添加用户  
	adduser ***userName***
6. 更改用户密码  
	passwd ***userName***
7. 添加文件可写权限  
	chmod -v u+w /etc/sudoers
8. 收回sudoers文件可写权限  
	chmod -v u-w /etc/sudoers
9. 检查是否安装  
	yum list installed | grep glibc  
	或者  
	rpm -qa | grep glibc  
	其中 glibc 是要检查的内容，
10. 重启网络服务  
	systemctl restart network.service  
11. 查看某个库是否安装  
	rpm -qa | grep gdb
12. 启动vsftpd服务相关  
	systemctl start vsftpd.service   或   systemct start vsftpd  
	systemctl stop vsftpd.service   或   systemct stop vsftpd  
	systemctl restart vsftpd.service   或   systemct restart vsftpd  	
13. 查看可以登录系统的用户  
	cat /etc/passwd | grep -v /sbin/nologin | cut -d : -f 1
14. 普通用户修改文件的账户名称  
	必须切换到root用户  
	chown -R 账户名称  文件或目录  
15. 普通用户修改文件的账户名称以及用户组名称  
	chown -R 账户名称：用户组名称  文件或目录
16. windows上传文件到CentOS  
	首先安装 yum install lrzsz -y  
	只能使用xshell  
	rz			windows上传文件到CentOS  
	sz file	 	CentOS 文件下载到windows上  
17. 主机名相关  
	查看主机名   		hostname  
	临时修改主机名   	hostname XXX
	永久修改主机名	hostnamectl set-hostname XXX
18. gdb调试生成core文件  
 	前置条件：编译时需要加 -g 选项使程序生成调试信息: gcc -g core_test.c -o core_test  
	1） core文件开关  
	- ulimit -c 查看core开关，如果为0表示关闭，不会生成core文件；  
	- ulimit -c [filesize] 设置core文件大小，当最小设置为4之后才会生成core文件；  
	- 使用 ulimit -c unlimited 设置core文件大小为不限制，这是常用的做法；  
	- 如果需要开机就执行，则需要将这句命令写到 /etc/profile 等文件  
	
	2）core文件命名和保存路径
	- 可以通过 /proc/sys/kernel/core_pattern 设置 core 文件名和保存路径，方法如下：  
		echo "/corefile/core-%e-%p-%t" > /proc/sys/kernel/core_pattern

    命名的参数列表：  
    %p - insert pid into filename 添加pid  
    %u - insert current uid into filename 添加当前uid  
    %g - insert current gid into filename 添加当前gid  
    %s - insert signal that caused the coredump into the filename 添加导致产生core的信号  
    %t - insert UNIX time that the coredump occurred into filename 添加core文件生成时的unix时间  
    %h - insert hostname where the coredump happened into filename 添加主机名  
    %e - insert coredumping executable name into filename 添加命令名。  

	3）调试core文件  
	- 方法①: gdb [exec file] [core file] 然后执行bt看堆栈信息：  
	- 方法②:gdb -c [core file],然后 file [exec file],最后再使用 bt 查看错误位置：  
19. 设置vi相关内容  
	在~/.vimrc文件中添加以下内容  
	- 显示行号  set nu  
	- 设置Tab 键跳过的空格数 set tabstop=4  
		
20. 挂载/卸载 移动硬盘  
	fdisk -l  
	注意：新硬盘需要分区  
	
	挂载 mount /dev/sdc2 /home/liangzhijun/udisk  
	卸载 umount /home/liangzhijun/udisk  

21. 卸载opendssh
	yum remove openssh 
	
22. 关闭防火墙 
	systemctl stop firewalld.service 

23. disabled selinux
	selinux也需要disable，运行命令getenforce，若不是Disabled，执行下面的步骤：
    编辑配置文件：sudo vi /etc/sysconfig/selinux 
    把SELINUX的值改为disabled：SELINUX=disabled 
    重启系统：sudo init 6 

24. 配置共享文件夹 
	https://blog.csdn.net/qq_29495141/article/details/88787515 
	
## 问题 ##
一、   tar解压出错tar: Child returned status 1  
	tar 参数解析:  
解压:  
-z 用gzip来压缩/解压缩文件，加上该选项后可以将档案文件进行压缩，但还原时也一定要使用该选项进行解压缩。  
-x 从档案文件中释放文件。  
-v 详细报告tar处理的文件信息。如无此选项，tar不报告文件信息。  
-f 使用档案文件或设备，这个选项通常是必选的。f参数必须放在最末尾。  
压缩:  
-c 建立一个压缩文件的参数指令(create 的意思)。  
-j 是否同时具有 bzip2 的属性？亦即是否需要用 bzip2 压缩？  
-z 是否同时具有 gzip 的属性？亦即是否需要用 gzip 压缩？  


[root]#tar zxvf gdb-8.3.tar.gz  
	gzip: stdin: not in gzip format  
	tar: Child returned status 1  
	tar: Error is not recoverable: exiting now  
改为(去掉z即可完成解压)  
[root]#tar xvf gdb-8.3.tar.gz  
  
二、解决CentOS 编译gdb时出错  
make install 后提示：  
make[5]: *** [gdb.info] Error 127  
make[5]: Leaving directory `/root/gdb-8.3/gdb/doc'

make[4]: *** [subdir_do] Error 1  
make[4]: Leaving directory `/root/gdb-8.3/gdb'  

make[3]: *** [install-only] Error 2  
make[3]: Leaving directory `/root/gdb-8.3/gdb'  

make[2]: *** [install] Error 2  
make[2]: Leaving directory `/root/gdb-8.3/gdb'  

make[1]: *** [install-gdb] Error 2  
make[1]: Leaving directory `/root/gdb-8.3'  
make: *** [install] Error 2  

解决方法：
yum install texinfo  
重新make instal  
  
三、win10/CentOS7双系统，其中Win10启动项丢失的解决办法  

 通过 grub2-mkconfig -o /boot/grub2/grub.cfg 重新生成grub.cfg后检测到windows  
 或者在/boot/grub2/grub.cfg里添加  

	menuentry 'Windows Recovery Environment (loader) (on /dev/sda1)' --class windows --class os $menuentry_id_option 'osprober-chain-4B89F2        D196E5C422' {  
		insmod part_msdos  
		insmod ntfs  
		set root='hd0,msdos1'  
		if [ x$feature_platform_search_hint = xy ]; then  
			search --no-floppy --fs-uuid --set=root --hint-bios=hd0,msdos1 --hint-efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1 --hint='hd        0,msdos1'  4B89F2D196E5C422  
		else  
			search --no-floppy --fs-uuid --set=root 4B89F2D196E5C422  
		fi  
		parttool ${root} hidden-  
		drivemap -s (hd0) ${root}  
		chainloader +1  
	}  

四、不能启动图形界面的原因  
	由于一开始出现不能启动图形界面的问题为了解决该问题，  

	通过		yum groupremove "GNOME Desktop" 删除gnome  
	重新安装   yum -y groups install "GNOME Desktop"
			  systemctl set-default graphical.target
			  reboot
	多出一个CentOS的启动项，但是该启动项也不能启动图形界面  

由于yum源安装的都是最新版本，之前的图形是xorg,最新的是wayland，所以无法启动图形界面  
