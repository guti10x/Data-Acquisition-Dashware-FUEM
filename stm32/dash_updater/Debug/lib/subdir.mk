################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/nextion_comunication.c 

OBJS += \
./lib/nextion_comunication.o 

C_DEPS += \
./lib/nextion_comunication.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su lib/%.cyclo: ../lib/%.c lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/34673/dash_FUEM/dashware_FUEM_V2/dashware_FUEM/stm32/nextion_comunication_lib/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/nextion_comunication.cyclo ./lib/nextion_comunication.d ./lib/nextion_comunication.o ./lib/nextion_comunication.su

.PHONY: clean-lib

