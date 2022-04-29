ifdef VIDEO_LIB_PATH
	CUR_DIR=$(VIDEO_LIB_PATH)
else
	CUR_DIR=$(PWD)
endif

CFG_PARAMS_DIR=${CUR_DIR}/cfg_params
EXCTL_DEV_DIR=${CUR_DIR}/exctl_dev
I2C_DIR=${CUR_DIR}/i2c
ISP_2K_DIR=${CUR_DIR}/isp_2k
ISP_2K_CORE_DIR=${ISP_2K_DIR}/core
ISP_2K_DS_DIR=${ISP_2K_DIR}/ds
ISP_2K_FBC_DIR=${ISP_2K_DIR}/fbc
ISP_2K_FBD_DIR=${ISP_2K_DIR}/fbd
ISP_2K_REMAP_DIR=${ISP_2K_DIR}/remap
ISP_2K_TABLE_DIR=${ISP_2K_DIR}/table
ISP_2K_WRAP_DIR=${ISP_2K_DIR}/wrap
ISP_3D_DIR=${CUR_DIR}/isp_3d
ISP_3D_CORE_DIR=${ISP_3D_DIR}/core
ISP_3D_WRAP_DIR=${ISP_3D_DIR}/wrap
ISP_FBC_DIR=${CUR_DIR}/isp_fbc
ISP_FBC_WRAP_DIR=${ISP_FBC_DIR}/wrap
ISP_FBC_CORE_DIR=${ISP_FBC_DIR}/core
MIPI_DIR=${CUR_DIR}/mipi
MIPI_CSI_DIR=${MIPI_DIR}/csi
MIPI_DSI_DIR=${MIPI_DIR}/dsi
MIPI_PHY_DIR=${MIPI_DIR}/phy
SENSOR_DIR=${CUR_DIR}/sensor
VI_DIR=${CUR_DIR}/vi
VI_WRAP_DIR=${VI_DIR}/wrap
VI_PIPE_DIR=${VI_DIR}/pipe
VO_DIR=${CUR_DIR}/vo
VO_CORE_DIR=${VO_DIR}/core
VO_REMAP_DIR=${VO_DIR}/remap
VO_TABLE_DIR=${VO_DIR}/table
BT1120_DIR=${CUR_DIR}/bt1120
MAIN_DIR=${CUR_DIR}

INC_DIR= -I${I2C_DIR} \
         -I${MAIN_DIR}

SRC = ${wildcard  ${EXCTL_DEV_DIR}/*.c} \
      ${wildcard  ${I2C_DIR}/*.c} \
      ${wildcard  ${ISP_2K_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_CORE_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_DS_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_FBC_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_FBD_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_TABLE_DIR}/*.c} \
      ${wildcard  ${ISP_2K_WRAP_DIR}/*.c} \
	  ${wildcard  ${ISP_2K_REMAP_DIR}/*.c} \
	  ${wildcard  ${ISP_3D_DIR}/*.c} \
	  ${wildcard  ${ISP_3D_CORE_DIR}/*.c} \
	  ${wildcard  ${ISP_3D_WRAP_DIR}/*.c} \
	  ${wildcard  ${ISP_FBC_DIR}/*.c} \
	  ${wildcard  ${ISP_FBC_WRAP_DIR}/*.c} \
	  ${wildcard  ${ISP_FBC_CORE_DIR}/*.c} \
      ${wildcard  ${MIPI_DIR}/*.c} \
	  ${wildcard  ${MIPI_CSI_DIR}/*.c} \
	  ${wildcard  ${MIPI_DSI_DIR}/*.c} \
	  ${wildcard  ${MIPI_PHY_DIR}/*.c} \
      ${wildcard  ${SENSOR_DIR}/*.c} \
      ${wildcard  ${VI_DIR}/*.c} \
	  ${wildcard  ${VI_WRAP_DIR}/*.c} \
	  ${wildcard  ${VI_PIPE_DIR}/*.c} \
      ${wildcard  ${VO_DIR}/*.c} \
      ${wildcard  ${VO_CORE_DIR}/*.c} \
      ${wildcard  ${VO_REMAP_DIR}/*.c} \
      ${wildcard  ${VO_TABLE_DIR}/*.c} \
      ${wildcard  ${BT1120_DIR}/*.c} \
      ${wildcard  ${CFG_PARAMS_DIR}/*.c} \
      ${wildcard  ${MAIN_DIR}/*.c}

OBJ = ${patsubst %.c, %.o, ${SRC}}

TARGET=libvideo.so


CROSS_COMPILE=riscv64-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

CCFLAGS=-g -Wall ${INC_DIR} -L ./ -O2

${TARGET}: ${OBJ}
	${LD} ${OBJ} -shared  -o $@
	@echo "Compile done."


#${OBJ}:${SRC}
#   $(CC) ${CCFLAGS} -c $? 

$(OBJ):%.o:%.c
	@echo "Compiling $< ==> $@"
	${CC} ${CCFLAGS} -c -fpic $< -o $@


clean:
	@rm -f ${OBJ}
	@echo "Clean object files done."

	@rm -f *~
	@echo "Clean tempreator files done."

	@rm -f ${TARGET}
	@echo "Clean target files done."

	@echo "Clean done."


