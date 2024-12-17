################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/checkClient.c \
../src/clientESONERO.c \
../src/support.c 

C_DEPS += \
./src/checkClient.d \
./src/clientESONERO.d \
./src/support.d 

OBJS += \
./src/checkClient.o \
./src/clientESONERO.o \
./src/support.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/checkClient.d ./src/checkClient.o ./src/clientESONERO.d ./src/clientESONERO.o ./src/support.d ./src/support.o

.PHONY: clean-src

