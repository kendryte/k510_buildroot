#!/bin/sh

BOARD_DIR="$(dirname $0)"
GENIMAGE_CFG_SD="${BOARD_DIR}/genimage-sdcard.cfg"
GENIMAGE_CFG_EMMC="${BOARD_DIR}/genimage-emmc.cfg"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"

rm -rf "${GENIMAGE_TMP}"

echo "post-image script"
echo "post-image.sh is called from $PWD"

KERNEL_BUILD_DIR="${BUILD_DIR}/linux-custom"

riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/k510.dts ${BINARIES_DIR}/k510.dts.tmp

${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510.dtb ${BINARIES_DIR}/k510.dts.tmp

which python3


/usr/bin/python3 ${BOARD_DIR}/app_shaaes.py ${BINARIES_DIR}/u-boot.bin ${BINARIES_DIR}/u-boot_burn.bin

genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_CFG_SD}"

rm -rf "${GENIMAGE_TMP}"

genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_CFG_EMMC}"

exit $?
