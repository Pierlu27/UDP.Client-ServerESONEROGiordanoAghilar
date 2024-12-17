################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/serverESONERO.c \
../src/support.c 

C_DEPS += \
./src/serverESONERO.d \
./src/support.d 

OBJS += \
./src/serverESONERO.o \
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
	-$(RM) ./src/serverESONERO.d ./src/serverESONERO.o ./src/support.d ./src/support.o

.PHONY: clean-src

