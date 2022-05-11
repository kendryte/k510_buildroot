# 贡献指南

首先感谢您参与本开源项目，在您提交issue和pull request之前请认真阅读本指南

在提交pull request时一定要关联相应的issue，如果没有相应issue，请先创建issue</br>
关于pull request关联issue，GitHub支持自动和手动关联，具体操作请参考[Link PR to issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue)

issue和pull request填写时都支持Markdown，关于GitHub的Markdown语法和扩展请参考[GitHub Flavored Markdown](https://docs.github.com/en/get-started/writing-on-github)

## 提交issue

1. 打开issue界面 https://github.com/kendryte/k510_buildroot/issues
2. 查看issue列表中是否已经存在相似issue，如果没有请点击`New issue`按钮
3. 根据您的问题类型，选择不同的issue模板
4. 填写必须项后(带红色\*标记)，点击`Submit new issue`按钮完成提交

## 提交pull request

1. Fork本仓库到您的github
2. Clone仓库到您本地
3. 您可以基于`main`或`dev`分支创建新分支并添加更改`git checkout -b newbranch -l main|dev`
4. 提交您的更改到您的github
5. 进入您的github仓库点击`Pull request`按钮后点击`New pull request`按钮
6. 选择`base repository`为`kendryte/k510_buildroot`，选择`base`为`dev`，选择`head repository`为`yourname/k510_buildroot`，选择`compare`为`newbranch`
7. 根据pull request模板要求填写您的描述
8. 点击`Create pull request`完成提交

> 如果您对以上流程还有不清楚的地方请参考[GitHub PR Flow](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests)

## 生成linux和uboot补丁包

k510_buildroot中linux和uboot使用的是补丁包方式

如果需要修改kernel代码，请在kernel补丁目录`package\patches\linux`新增补丁文件</br>
如果需要修改uboot代码，请在uboot补丁目录`package\patches\uboot`新增补丁文件

制作补丁时请提前做好代码修改备份，下面以k510_crb_lp3_v1_2_defconfig的linux补丁为例
```shell
cd k510_crb_lp3_v1_2_defconfig
make linux-dirclean
make linux-patch
cd build/linux-4.17
git init .
git add -f .
git commit -a -m "init"
#修改代码，比如 rm -rf README MAINTAINERS
git commit -m "delete README MAINTAINERS" README MAINTAINERS
git format-patch --no-renames -1
#生成补丁文件，执行完后可以看到类似 0001-delete-README-MAINTAINERS.patch 文件
```
把 0001-delete-README-MAINTAINERS.patch 重命名成一个比较大的名字比如 00100--delete-README-MAINTAINERS.patch 后，放到kernel补丁目录`package\patches\linux`，因为按从小到大的顺序打入补丁，请保证新加入的补丁名字最大

然后按照pull request流程提交补丁文件
