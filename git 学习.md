# git 学习

## 创建版本库

#### 1.初始化

使用`git init`命令。

#### 2.添加文件

添加文件到Git仓库，分两步：

1. 使用命令`git add <file>`，注意，可反复多次使用，添加多个文件；
2. 使用命令`git commit -m <message>`，完成。

### 工作区状态

- 要随时掌握工作区的状态，使用`git status`命令。
- 如果`git status`告诉你有文件被修改过，用`git diff`可以查看修改内容。

## 版本回退

- `HEAD`指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令`git reset --hard commit_id`。

- ```
  $ git reset --hard HEAD^  上一个版本就是HEAD^
  ```

- 穿梭前，用`git log`可以查看提交历史，以便确定要回退到哪个版本。

- 要重返未来，用`git reflog`查看命令历史，以便确定要回到未来的哪个版本。

### 暂存区

使用 git add 将文件放入暂存区

![image-20220727165717806](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220727165717806.png)

`git add`命令实际上就是把要提交的所有修改放到暂存区（Stage），然后，执行`git commit`就可以一次性把暂存区的所有修改提交到分支。



一旦提交后，如果你又没有对工作区做任何修改，那么工作区就是“干净”的：

![image-20220727170131786](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220727170131786.png)

### 撤销

命令`git checkout -- readme.txt`意思就是，把`readme.txt`文件在工作区的修改全部撤销，这里有两种情况：

一种是`readme.txt`自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；

一种是`readme.txt`已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。

注意

`git checkout -- file`命令中的`--`很重要，没有`--`，就变成了“切换到另一个分支”的命令

#### 将暂存区的修改撤销

用命令`git reset HEAD <file>`可以把暂存区的修改撤销掉（unstage），重新放回工作区

`git reset`命令既可以回退版本，也可以把暂存区的修改回退到工作区。当我们用`HEAD`时，表示最新的版本。

### 小结

场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令`git checkout -- file`。

场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令`git reset HEAD <file>`，就回到了场景1，第二步按场景1操作。

场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，参考[版本回退](https://www.liaoxuefeng.com/wiki/896043488029600/897013573512192)一节，不过前提是没有推送到远程库。

### 删除文件

工作区

```
$ rm test.txt
```

确实要从版本库中删除该文件，那就用命令`git rm`删掉，并且`git commit`

```
$ git rm test.txt
$ git commit -m "remove test.txt"
```

如果暂存区还有，就可以恢复

```
 git checkout -- test.txt
```

### 创建远程仓库

youremail@example.com成你自己的邮件地址，然后一路回车，使用默认值即可

```
$ ssh-keygen -t rsa -C "youremail@example.com"
```

第2步：登陆GitHub，打开“Account settings”，“SSH Keys”页面

点“Add Key”，你就应该看到已经添加的Key：

### 添加远程库

1.登陆GitHub，然后，在右上角找到“Create a new repo”按钮，创建一个新的仓库



2.在Repository name填入`learngit`，其他保持默认设置，点击“Create repository”按钮，就成功地创建了一个新的Git仓库



3.我们根据GitHub的提示，在本地的`learngit`仓库下运行命令：

```
$ git remote add origin git@github.com:michaelliao/learngit.git
```

把上面的`michaelliao`替换成你自己的GitHub账户名

把本地库的内容推送到远程，用`git push`命令，实际上是把当前分支`master`推送到远程。

由于远程库是空的，我们第一次推送`master`分支时，加上了`-u`参数，Git不但会把本地的`master`分支内容推送的远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来，在以后的推送或者拉取时就可以简化命令。

#### 提交

从现在起，只要本地作了提交，就可以通过命令：

```
$ git push origin master
```

把本地`master`分支的最新修改推送至GitHub，现在，你就拥有了真正的分布式版本库！

### 删除远程库

如果添加的时候地址写错了，或者就是想删除远程库，可以用`git remote rm <name>`命令。使用前，建议先用`git remote -v`查看远程库信息：

```
$ git remote -v
origin  git@github.com:michaelliao/learn-git.git (fetch)
origin  git@github.com:michaelliao/learn-git.git (push)
```

然后，根据名字删除，比如删除`origin`：

```
$ git remote rm origin
```

### 小结

要关联一个远程库，使用命令`git remote add origin git@server-name:path/repo-name.git`；

关联一个远程库时必须给远程库指定一个名字，`origin`是默认习惯命名；

关联后，使用命令`git push -u origin master`第一次推送master分支的所有内容；

此后，每次本地提交后，只要有必要，就可以使用命令`git push origin master`推送最新修改；
