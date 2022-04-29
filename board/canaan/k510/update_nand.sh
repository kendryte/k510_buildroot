#!/bin/sh

#echo $*
#function usage()
#{
#	cat <<EOF 
#	param error!!
#	usage is:
#	$0 uppackage tmp_path 	
#EOF
#}
#package=$1
#temp=$2
#[ $# -ge 2 ]  || { usage; exit; }
#tar -xvf ${package}  -C "${temp}" || { echo "${package} decompress  error !"; exit; }

#set -x


mtd_u1="/dev/mtd$(cat /proc/mtd | sed -n -e "/uboot-1/s/mtd\([0-9]*\).*/\1/p")"
mtd_u2="/dev/mtd$(cat /proc/mtd | sed -n -e "/uboot-2/s/mtd\([0-9]*\).*/\1/p")"
mtd_u3="/dev/mtd$(cat /proc/mtd | sed -n -e "/uboot-3/s/mtd\([0-9]*\).*/\1/p")"
mtd_e="/dev/mtd$(cat /proc/mtd | sed -n -e "/env/s/mtd\([0-9]*\).*/\1/p")"
mtd_d="/dev/mtd$(cat /proc/mtd | sed -n -e "/dtb/s/mtd\([0-9]*\).*/\1/p")"
mtd_k="/dev/mtd$(cat /proc/mtd | sed -n -e "/kernel/s/mtd\([0-9]*\).*/\1/p")"
mtd_r="/dev/mtd$(cat /proc/mtd | sed -n -e "/rootfs/s/mtd\([0-9]*\).*/\1/p")"
f_u="./u-boot_burn.bin"
f_e="./uboot-nand.env"
f_d="./k510.dtb"
f_k="./bootm-bbl.img"
f_r="./rootfs.ubi"

set -x
[ -f "$f_u" ] && { flash_erase "${mtd_u1}" 0 0 && time nandwrite -m  -p "${mtd_u1}" "$f_u"; }
[ -f "$f_u" ] && { flash_erase "${mtd_u2}" 0 0 && time nandwrite -m  -p "${mtd_u2}" "$f_u"; }
[ -f "$f_u" ] && { flash_erase "${mtd_u3}" 0 0 && time nandwrite -m  -p "${mtd_u3}" "$f_u"; }


[ -f "$f_e" ] && { flash_erase "${mtd_e}" 0 0 && time nandwrite -m  -p "${mtd_e}" "$f_e"; }
[ -f "$f_d" ] && { flash_erase "${mtd_d}" 0 0 && time nandwrite -m  -p "${mtd_d}" "$f_d"; }
[ -f "$f_k" ] && { flash_erase "${mtd_k}" 0 0 && time nandwrite -m  -p "${mtd_k}" "$f_k"; }
[ -f "$f_r" ] && { flash_erase "${mtd_r}" 0 0 && time nandwrite -m  -p "${mtd_r}" "$f_r"; }

#ubiattach  -p /dev/mtd7
#mount -t ubifs ubi0_0 /mnt




