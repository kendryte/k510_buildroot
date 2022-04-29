#!/bin/sh

BOARD_DIR="$(dirname $0)"
GENIMAGE_SD_CFG="${BOARD_DIR}/genimage-sdcard.cfg"
GENIMAGE_SD_TMP="${BUILD_DIR}/genimage-sd.tmp"
GENIMAGE_EMMC_CFG="${BOARD_DIR}/genimage-emmc.cfg"
GENIMAGE_EMMC_TMP="${BUILD_DIR}/genimage-emmc.tmp"


rm -rf "${GENIMAGE_SD_TMP}"
rm -rf "${GENIMAGE_EMMC_TMP}"

if [ -f "${BOARD_DIR}/../../../k510_evb_lp3_v1_1_defconfig/local.mk" ]
then
        OVERRIDE_LINUX="$(cat ${BOARD_DIR}/../../../k510_evb_lp3_v1_1_defconfig/local.mk | grep LINUX)"

        OVERRIDE_UBOOT="$(cat ${BOARD_DIR}/../../../k510_evb_lp3_v1_1_defconfig/local.mk | grep UBOOT)"
fi;


if [ -z "$OVERRIDE_LINUX" ]
then
        KERNEL_VERSION="$(cat ${O}/.config | grep BR2_LINUX_KERNEL_VERSION | awk -F "=" '{print $2}' | sed 's/\"//g')"
        KERNEL_BUILD_DIR="${BUILD_DIR}/linux-$KERNEL_VERSION"
else
        KERNEL_VERSION="custom"
        KERNEL_BUILD_DIR="${BUILD_DIR}/linux-custom"
fi;

if [ -z "$OVERRIDE_UBOOT" ]
then
        UBOOT_VERSION="$(cat ${O}/.config | grep BR2_TARGET_UBOOT_VERSIONBR2_TARGET_UBOOT_VERSION | awk -F "=" '{print $2}' | sed 's/\"//g')"
        UBOOT_BUILD_DIR="${BUILD_DIR}/uboot-$UBOOT_VERSION"
else
        UBOOT_BUILD_DIR="${BUILD_DIR}/uboot-custom"
fi;

#riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/k510_evb_lp3_v1_1_sdcard.dts ${BINARIES_DIR}/k510_evb_lp3_v1_1_sdcard.dts.tmp

#${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510.dtb ${BINARIES_DIR}/k510_evb_lp3_v1_1_sdcard.dts.tmp

#riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/k510_evb_lp3_v1_1_nfsroot.dts ${BINARIES_DIR}/k510_evb_lp3_v1_1_nfsroot.dts.tmp

#${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510_nfsroot.dtb ${BINARIES_DIR}/k510_evb_lp3_v1_1_nfsroot.dts.tmp

riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/canaan/k510_evb_lp3_v1_1.dts ${BINARIES_DIR}/k510_evb_lp3_v1_1.dts.tmp

${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510.dtb ${BINARIES_DIR}/k510_evb_lp3_v1_1.dts.tmp

#riscv64-linux-cpp -nostdinc -I ${KERNEL_BUILD_DIR}/include -I ${KERNEL_BUILD_DIR}/arch  -undef -x assembler-with-cpp ${KERNEL_BUILD_DIR}/arch/riscv/boot/dts/canaan/k510_evb_lp3_v1_1_nfsroot.dts ${BINARIES_DIR}/k510_evb_lp3_v1_1_nfsroot.dts.tmp

#${KERNEL_BUILD_DIR}/scripts/dtc/dtc -I dts -o ${BINARIES_DIR}/k510_nfsroot.dtb ${BINARIES_DIR}/k510_evb_lp3_v1_1_nfsroot.dts.tmp

${UBOOT_BUILD_DIR}/tools/mkenvimage -s 0x2000 -o ${BINARIES_DIR}/uboot-sd.env ${BOARD_DIR}/uboot-sdcard.env
${UBOOT_BUILD_DIR}/tools/mkenvimage -s 0x2000 -o ${BINARIES_DIR}/uboot-emmc.env ${BOARD_DIR}/uboot-emmc.env
${UBOOT_BUILD_DIR}/tools/mkenvimage -s 0x2000 -o ${BINARIES_DIR}/uboot-nfs.env ${BOARD_DIR}/uboot-nfs.env

/usr/bin/python3 ${BOARD_DIR}/app_shaaes.py ${BINARIES_DIR}/u-boot.bin ${BINARIES_DIR}/u-boot_burn.bin

genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_SD_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_SD_CFG}"

genimage                           \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_EMMC_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_EMMC_CFG}"

exit $?
