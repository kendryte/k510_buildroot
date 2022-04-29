#!/bin/bash
#set -ex
set -e
BOARD_DIR="$(cd "$(dirname "$0")";pwd)"
BRW_ROOT="$(cd {BOARD_DIR}/../../..;pwd)"
BUILD_DIR=${BRW_ROOT}/${CONF}/build
BINARIES_DIR=${BRW_ROOT}/${CONF}/images
TARGET_DIR=${BRW_ROOT}/${CONF}/target

GENIMAGE_SD_CFG="${BOARD_DIR}/genimage-sdcard_debian.cfg"
GENIMAGE_SD_TMP="${BUILD_DIR}/genimage-sd.tmp"

KERNEL_BUILD_DIR="${BUILD_DIR}/linux-$1"


if [ -f "${BRW_ROOT}/${CONF}/local.mk" ]
then
	OVERRIDE_LINUX="$(cat ${BRW_ROOT}/${CONF}/local.mk | grep LINUX)"
fi;


if [ -z "$OVERRIDE_LINUX" ]
then
	KERNEL_VERSION="$(cat ${BRW_ROOT}/${CONF}/.config | grep BR2_LINUX_KERNEL_VERSION | awk -F "=" '{print $2}' | sed 's/\"//g')"
	KERNEL_BUILD_DIR="${BUILD_DIR}/linux-$KERNEL_VERSION"
else
	KERNEL_VERSION="custom"
	KERNEL_BUILD_DIR="${BUILD_DIR}/linux-custom"
fi;


${BRW_ROOT}/${CONF}/host/bin/riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/canaan/k510_crb_lp3_debian_v0_1.dts ${BINARIES_DIR}/k510_crb_lp3_debian_v0_1.dts.tmp
${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510.dtb ${BINARIES_DIR}/k510_crb_lp3_debian_v0_1.dts.tmp


rm -rf  "${BINARIES_DIR}/debian"  "${BINARIES_DIR}/debian.ext2"
fakeroot tar -xf ${BOARD_DIR}/debian.tar.gz   -C "${BINARIES_DIR}"
fakeroot cp "${TARGET_DIR}/app/nncase_demo"   "${BINARIES_DIR}/debian/app/" -r
fakeroot cp "${TARGET_DIR}/etc/uboot_dsi_logo.gbr.bmp.argb"   "${BINARIES_DIR}/debian/etc/" -r
fakeroot cp ${TARGET_DIR}/usr/lib/libopencv_core.so.4.5  "${BINARIES_DIR}/debian/usr/lib/riscv64-linux-gnu/"
fakeroot cp ${TARGET_DIR}/usr/lib/libopencv_imgcodecs.so.4.5  "${BINARIES_DIR}/debian/usr/lib/riscv64-linux-gnu/"
fakeroot cp ${TARGET_DIR}/usr/lib/libopencv_imgproc.so.4.5  "${BINARIES_DIR}/debian/usr/lib/riscv64-linux-gnu/"
fakeroot cp ${TARGET_DIR}/lib64/lp64d/libvideo.so  "${BINARIES_DIR}/debian/usr/lib/riscv64-linux-gnu/"
#fakeroot cp ${TARGET_DIR}/usr/lib/libopencv  "${BINARIES_DIR}/debian/usr/lib/riscv64-linux-gnu/"

fakeroot mkfs.ext2 -d "${BINARIES_DIR}/debian"  -r 1 -N 0 -m 5 -L "" -O ^64bit   "${BINARIES_DIR}/debian.ext2"  3G
rm -rf  debian.ext2 "${BINARIES_DIR}/debian"  ${BINARIES_DIR}/k510_crb_lp3_debian_v0_1.dts.tmp

rm -rf "${GENIMAGE_SD_TMP}"  

${BRW_ROOT}/${CONF}/host/bin/genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_SD_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_SD_CFG}"

mv  ${BINARIES_DIR}/k510.dtb    ${BINARIES_DIR}/k510_debian.dtb 	 
rm -rf "${GENIMAGE_SD_TMP}"  
