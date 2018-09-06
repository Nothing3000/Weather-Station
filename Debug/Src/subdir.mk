################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/KeepAliveLED.c \
../Src/freertos.c \
../Src/main.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_hal_timebase_TIM.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c 

OBJS += \
./Src/KeepAliveLED.o \
./Src/freertos.o \
./Src/main.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_hal_timebase_TIM.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o 

C_DEPS += \
./Src/KeepAliveLED.d \
./Src/freertos.d \
./Src/main.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_hal_timebase_TIM.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F030x8 -I"/home/marlon/Weather-Station/Inc" -I"/home/marlon/Weather-Station/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/home/marlon/Weather-Station/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/home/marlon/Weather-Station/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"/home/marlon/Weather-Station/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/home/marlon/Weather-Station/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/marlon/Weather-Station/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/marlon/Weather-Station/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


