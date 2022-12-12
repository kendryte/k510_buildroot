#!/bin/sh


export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib
if ! cat /proc/partitions  | grep mmcblk0p[1-9] > /dev/null  ; then
	echo "emmc first use "
	(parted  /dev/mmcblk0  mklabel msdos;emmcsize=$(parted /dev/mmcblk0 print free | grep Free  | awk '{print $2}');\
	parted  -a minimal /dev/mmcblk0 mkpart  primary 1049kB  2097kB; \
	parted  -a minimal /dev/mmcblk0 mkpart primary  2098kB  33.6MB;\
	parted  -a minimal /dev/mmcblk0 mkpart  primary  33.6MB  570MB;\
	parted  -a minimal /dev/mmcblk0 mkpart  primary  570MB   ${emmcsize}; \
	yes |  mkfs.vfat /dev/mmcblk0p2; \
	yes |  mkfs.ext2 /dev/mmcblk0p3; \
	yes |  mkfs.vfat /dev/mmcblk0p4;) > /dev/null 2>&1
fi



if [ -f /first_run_flag_file ];then
	#set -x	
	bootddev=$(cat /proc/cmdline  | sed  -n  "s#root=\(\/dev\/mmcblk[0-9]\).*#\1#p" )
	if [ -n  "${bootddev}"  ];then
		rootpart=$(cat /proc/cmdline  | sed  -n  "s/root=\/dev\/mmcblk[0-9]\p\([0-9]\).*/\1/p" )
		datapart=$(($rootpart+1))
		
		if $( cat /proc/partitions | grep  ${bootddev:5}p${datapart} > /dev/null ) ;then
			echo "${bootddev}p${datapart} /root/data  auto" >>/etc/fstab
			echo "${bootddev}p${datapart}  exist"
			rm -f 	/first_run_flag_file; 
		else	#不存在分区			
			parted ${bootddev}  rm $datapart  2>/dev/null
			( parted    ${bootddev} print free  |  awk   \
					"function partsd(start, end){a=\" parted  -a minimal  ${bootddev}  mkpart  primary fat32 \"  start \" \" end  \" ;\";print(a); system(a);}\
					function mkfspart(part){dp=\"${bootddev}p\" part; fs_cmd=\"/sbin/mkfs.vfat \" dp; print(fs_cmd);system(fs_cmd);}\
					function add_fstab(part){dp=\"${bootddev}p\" part;cmd=\"echo \" dp    \" /root/data  auto >>/etc/fstab\"; print(cmd);system(cmd);}\
					function mount_part(part){dp=\"${bootddev}p\" part;cmd=\"mount \"  dp    \" /root/data  \"; print(cmd);system(cmd);}\
					BEGIN {i=0; s[i]=0;e[i]=0;}\
					/Free Space/  { i++; print \$1,\$2; s[i]=\$1;e[i]=\$2;} \
					END {partsd(  s[i],  e[i]); mkfspart($datapart);add_fstab($datapart); mount_part($datapart);}"	; 
				rm -f 	/first_run_flag_file; ) >/dev/null 2>&1
		fi	
		
	fi
	#set +x
fi

echo /sbin/mdev > /proc/sys/kernel/hotplug
mdev -s
mkdir -p /dev/shm
mount -a

#产生coredump文件，coredump文件在/root/data/coredump/目录下面
[ -d /root/data/coredump  ] || mkdir -p /root/data/coredump
echo "|/etc/core_dump_gzip.sh %e %s %p" > /proc/sys/kernel/core_pattern
ulimit -c unlimited 

export hostname0=
export mnt_path0=
export hostname1=
export mnt_path1=
export auto=




#

dmesg > dmesg_boot.log
echo $(grep Machine /dmesg_boot.log| sed 's/^.*canaan //g') > platform.log
linux_ver=`uname -r`

if [ -d /lib/modules/$linux_ver/ ]; then
		depmod -a
        while read module
        do
                if [ "$auto" == "1" ]; then
                        module_name=`basename $module .ko`
                        rmmod $module_name
                fi
				
                #insmod /lib/modules/$linux_ver/$module
				module_name=`basename $module .ko`
				modprobe $module_name


        done</lib/modules/$linux_ver/modules.order
fi

#change SHELL default version
#if [ -f /bin/bash ]; then
#        ln -sf /bin/bash /bin/sh
#fi

if [ "$auto" != "1" ]; then
        exit 1
fi

#for i in $drvs
#do
#drv=$(dmesg | grep "$i")
#if [ "$?" == "1" ]; then
#	echo "$i NOT exist"
#	exit
#fi
#done

#exit

test -z $hostname1
if [ "$?" == "1" ]; then
	echo "mount hastname1 = $hostname1"
	mount -t nfs -o nolock,rsize=1024,wsize=1024 $hostname1:$mnt_path1 mnt
else
	echo "mount hastname0 = $hostname0"
	mount -t nfs -o nolock,rsize=1024,wsize=1024 $hostname0:$mnt_path0 mnt
fi

if [ "$?" != "0" ]; then
	echo "mount mnt fail"
	exit 1
fi
lsmod 2>&1 | tee mnt/log/lsmod.log
cp dmesg_boot.log mnt/log/
mount /dev/mmcblk0p1 /tmp
if [ "$?" != "0" ]; then
	echo "mount tmp fail"
	exit 1
fi

cd
cd mnt
dmesg > log/dmesg_run.log
sh test_drivers.sh

