################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/client.c \
../src/command.c \
../src/fileShare.c \
../src/fileopt.c \
../src/global.c \
../src/select.c \
../src/server.c \
../src/utils.c 

OBJS += \
./src/client.o \
./src/command.o \
./src/fileShare.o \
./src/fileopt.o \
./src/global.o \
./src/select.o \
./src/server.o \
./src/utils.o 

C_DEPS += \
./src/client.d \
./src/command.d \
./src/fileShare.d \
./src/fileopt.d \
./src/global.d \
./src/select.d \
./src/server.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


