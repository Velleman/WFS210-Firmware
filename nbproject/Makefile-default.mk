#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Source_Files/usb/usb_device.c Source_Files/usb/usb_function_cdc.c Source_Files/usb/usb_hal_dspic33e.c Source_Files/WFS210/autorange.c Source_Files/WFS210/buffer.c Source_Files/WFS210/calibration.c Source_Files/WFS210/checksum.c Source_Files/WFS210/low_voltage.c Source_Files/WFS210/parser.c Source_Files/WFS210/wfs210.c Source_Files/WFS210/wfs210_rx.c Source_Files/WFS210/wfs210_scope.c Source_Files/WFS210/wfs210_setting.c Source_Files/WFS210/wfs210_tx.c Source_Files/WFS210/wfs210_usb.c Source_Files/WFS210/wifi.c Source_Files/WFS210/wifi_cmd_reply_parser.c Source_Files/main.c Source_Files/usb_descriptors.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source_Files/usb/usb_device.o ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o ${OBJECTDIR}/Source_Files/WFS210/autorange.o ${OBJECTDIR}/Source_Files/WFS210/buffer.o ${OBJECTDIR}/Source_Files/WFS210/calibration.o ${OBJECTDIR}/Source_Files/WFS210/checksum.o ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o ${OBJECTDIR}/Source_Files/WFS210/parser.o ${OBJECTDIR}/Source_Files/WFS210/wfs210.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o ${OBJECTDIR}/Source_Files/WFS210/wifi.o ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o ${OBJECTDIR}/Source_Files/main.o ${OBJECTDIR}/Source_Files/usb_descriptors.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source_Files/usb/usb_device.o.d ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d ${OBJECTDIR}/Source_Files/WFS210/autorange.o.d ${OBJECTDIR}/Source_Files/WFS210/buffer.o.d ${OBJECTDIR}/Source_Files/WFS210/calibration.o.d ${OBJECTDIR}/Source_Files/WFS210/checksum.o.d ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d ${OBJECTDIR}/Source_Files/WFS210/parser.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d ${OBJECTDIR}/Source_Files/WFS210/wifi.o.d ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d ${OBJECTDIR}/Source_Files/main.o.d ${OBJECTDIR}/Source_Files/usb_descriptors.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source_Files/usb/usb_device.o ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o ${OBJECTDIR}/Source_Files/WFS210/autorange.o ${OBJECTDIR}/Source_Files/WFS210/buffer.o ${OBJECTDIR}/Source_Files/WFS210/calibration.o ${OBJECTDIR}/Source_Files/WFS210/checksum.o ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o ${OBJECTDIR}/Source_Files/WFS210/parser.o ${OBJECTDIR}/Source_Files/WFS210/wfs210.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o ${OBJECTDIR}/Source_Files/WFS210/wifi.o ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o ${OBJECTDIR}/Source_Files/main.o ${OBJECTDIR}/Source_Files/usb_descriptors.o

# Source Files
SOURCEFILES=Source_Files/usb/usb_device.c Source_Files/usb/usb_function_cdc.c Source_Files/usb/usb_hal_dspic33e.c Source_Files/WFS210/autorange.c Source_Files/WFS210/buffer.c Source_Files/WFS210/calibration.c Source_Files/WFS210/checksum.c Source_Files/WFS210/low_voltage.c Source_Files/WFS210/parser.c Source_Files/WFS210/wfs210.c Source_Files/WFS210/wfs210_rx.c Source_Files/WFS210/wfs210_scope.c Source_Files/WFS210/wfs210_setting.c Source_Files/WFS210/wfs210_tx.c Source_Files/WFS210/wfs210_usb.c Source_Files/WFS210/wifi.c Source_Files/WFS210/wifi_cmd_reply_parser.c Source_Files/main.c Source_Files/usb_descriptors.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU806
MP_LINKER_FILE_OPTION=,--script="linker\p33EP256MU806.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source_Files/usb/usb_device.o: Source_Files/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_device.c  -o ${OBJECTDIR}/Source_Files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o: Source_Files/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_function_cdc.c  -o ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o: Source_Files/usb/usb_hal_dspic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_hal_dspic33e.c  -o ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/autorange.o: Source_Files/WFS210/autorange.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/autorange.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/autorange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/autorange.c  -o ${OBJECTDIR}/Source_Files/WFS210/autorange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/autorange.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/autorange.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/buffer.o: Source_Files/WFS210/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/buffer.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/buffer.c  -o ${OBJECTDIR}/Source_Files/WFS210/buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/calibration.o: Source_Files/WFS210/calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/calibration.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/calibration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/calibration.c  -o ${OBJECTDIR}/Source_Files/WFS210/calibration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/calibration.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/calibration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/checksum.o: Source_Files/WFS210/checksum.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/checksum.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/checksum.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/checksum.c  -o ${OBJECTDIR}/Source_Files/WFS210/checksum.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/checksum.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/checksum.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/low_voltage.o: Source_Files/WFS210/low_voltage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/low_voltage.c  -o ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/parser.o: Source_Files/WFS210/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/parser.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/parser.c  -o ${OBJECTDIR}/Source_Files/WFS210/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/parser.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210.o: Source_Files/WFS210/wfs210.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o: Source_Files/WFS210/wfs210_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_rx.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o: Source_Files/WFS210/wfs210_scope.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_scope.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o: Source_Files/WFS210/wfs210_setting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_setting.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o: Source_Files/WFS210/wfs210_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_tx.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o: Source_Files/WFS210/wfs210_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_usb.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wifi.o: Source_Files/WFS210/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wifi.c  -o ${OBJECTDIR}/Source_Files/WFS210/wifi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wifi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wifi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o: Source_Files/WFS210/wifi_cmd_reply_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wifi_cmd_reply_parser.c  -o ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/main.o: Source_Files/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files" 
	@${RM} ${OBJECTDIR}/Source_Files/main.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/main.c  -o ${OBJECTDIR}/Source_Files/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb_descriptors.o: Source_Files/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files" 
	@${RM} ${OBJECTDIR}/Source_Files/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb_descriptors.c  -o ${OBJECTDIR}/Source_Files/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Source_Files/usb/usb_device.o: Source_Files/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_device.c  -o ${OBJECTDIR}/Source_Files/usb/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o: Source_Files/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_function_cdc.c  -o ${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_function_cdc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o: Source_Files/usb/usb_hal_dspic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/usb" 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb/usb_hal_dspic33e.c  -o ${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb/usb_hal_dspic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/autorange.o: Source_Files/WFS210/autorange.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/autorange.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/autorange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/autorange.c  -o ${OBJECTDIR}/Source_Files/WFS210/autorange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/autorange.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/autorange.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/buffer.o: Source_Files/WFS210/buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/buffer.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/buffer.c  -o ${OBJECTDIR}/Source_Files/WFS210/buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/buffer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/calibration.o: Source_Files/WFS210/calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/calibration.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/calibration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/calibration.c  -o ${OBJECTDIR}/Source_Files/WFS210/calibration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/calibration.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/calibration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/checksum.o: Source_Files/WFS210/checksum.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/checksum.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/checksum.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/checksum.c  -o ${OBJECTDIR}/Source_Files/WFS210/checksum.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/checksum.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/checksum.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/low_voltage.o: Source_Files/WFS210/low_voltage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/low_voltage.c  -o ${OBJECTDIR}/Source_Files/WFS210/low_voltage.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/low_voltage.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/parser.o: Source_Files/WFS210/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/parser.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/parser.c  -o ${OBJECTDIR}/Source_Files/WFS210/parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/parser.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210.o: Source_Files/WFS210/wfs210.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o: Source_Files/WFS210/wfs210_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_rx.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_rx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o: Source_Files/WFS210/wfs210_scope.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_scope.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_scope.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o: Source_Files/WFS210/wfs210_setting.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_setting.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_setting.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o: Source_Files/WFS210/wfs210_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_tx.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_tx.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o: Source_Files/WFS210/wfs210_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wfs210_usb.c  -o ${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wfs210_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wifi.o: Source_Files/WFS210/wifi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wifi.c  -o ${OBJECTDIR}/Source_Files/WFS210/wifi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wifi.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wifi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o: Source_Files/WFS210/wifi_cmd_reply_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files/WFS210" 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/WFS210/wifi_cmd_reply_parser.c  -o ${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/WFS210/wifi_cmd_reply_parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/main.o: Source_Files/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files" 
	@${RM} ${OBJECTDIR}/Source_Files/main.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/main.c  -o ${OBJECTDIR}/Source_Files/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source_Files/usb_descriptors.o: Source_Files/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Source_Files" 
	@${RM} ${OBJECTDIR}/Source_Files/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/Source_Files/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Source_Files/usb_descriptors.c  -o ${OBJECTDIR}/Source_Files/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source_Files/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -Os -I"./Header_files" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Source_Files/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    linker/p33EP256MU806.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   linker/p33EP256MU806.gld bootloader/bootloader.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
	@echo "Creating unified hex file"
	@"C:/Program Files (x86)/Microchip/MPLABX/v4.01/mplab_ide/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files (x86)/Microchip/MPLABX/v4.01/mplab_ide/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/WFS210-Firmware.${IMAGE_TYPE}.hex bootloader/bootloader.hex -odist/${CND_CONF}/production/WFS210-Firmware.production.unified.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
