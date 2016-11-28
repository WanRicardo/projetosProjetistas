################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Oled_inicializa.c \
../Sensor.c \
../cr_startup_lpc17.c \
../main.c 

OBJS += \
./Oled_inicializa.o \
./Sensor.o \
./cr_startup_lpc17.o \
./main.o 

C_DEPS += \
./Oled_inicializa.d \
./Sensor.d \
./cr_startup_lpc17.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\Lib_EaBaseBoard\inc" -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\Lib_MCU\inc" -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\FreeRTOS_Library\demo_code" -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\FreeRTOS_Library\include" -I"C:\Users\Wanderson\Documents\Inatel\JavaScript\aaaaaaaaa\FreeRTOS_Library\portable" -I"C:\Programas\nxp\LPCXpresso_8.2.0_647\lpcxpresso\tools\lib\gcc\arm-none-eabi\5.3.1\include" -I"C:\Programas\nxp\LPCXpresso_8.2.0_647\lpcxpresso\tools\lib\gcc\arm-none-eabi\5.3.1\include-fixed" -I"C:\Programas\nxp\LPCXpresso_8.2.0_647\lpcxpresso\tools\arm-none-eabi\include" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


