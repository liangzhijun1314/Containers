#Linux 下 Git命令使用

## GIT 命令
1. 克隆  
	git clone http://10.70.57.104/cboxpc/cbox_pc.git  

2. 查看分支  
	git branch -a  

3. 切换分支  
	git checkout -b 分支名  origin/分支名  

4. 拉取最新代码  
	git pull  

5. 所有已修改的文件还原  
	git reset —-hard  

6. 代码还原到某个版本  
	git reset --hard HEAD  
	说明： HEAD表示当前版本，上一个版本就是HEAD^,上上个HEAD^^,更多个时HEAD~100  

7. 所有非git上的文件及目录均删除  
	git clean -xfd  
8. 查看状态  
	git  status  

9. 文件还原  
	git checkout fileName  

10. 文件提交  
说明：提交文件时，需要执行以下三条指令  
	- git add fileName	   #增加文件  
	- git commit -m “log”  #提交日志  
	- git push			   #提交  

11. 显示日志  
	git log  

12. 只显示一个日志  
	git log --pretty=oneline  

13. 查看git项目地址  
	git remote -v	(注意：必须在项目的路径下输入，cmd里也可以)  

# windows TortoiseGit 图形界面使用#

1. 代码回退  

	- show log  
	- 右键某个版本，点Reset **  to this  
	- 单选Hard:Reset working tree and index(discard add local changes)  ->ok  
		直到 success  
	- 可以pull 一下到最新版本，也可以向下继续回退代码  
2. 查看项目git 地址 
	- 在项目下 TortoiseGit->Settings  Git->Remote->origin
