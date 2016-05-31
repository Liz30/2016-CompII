################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Expression.o \
../Statement.o \
../Util.o \
../decaf_grammar.o \
../decaf_lexer.o \
../main.o 

CPP_SRCS += \
../Expression.cpp \
../Statement.cpp \
../Util.cpp \
../decaf_grammar.cpp \
../decaf_lexer.cpp \
../main.cpp 

OBJS += \
./Expression.o \
./Statement.o \
./Util.o \
./decaf_grammar.o \
./decaf_lexer.o \
./main.o 

CPP_DEPS += \
./Expression.d \
./Statement.d \
./Util.d \
./decaf_grammar.d \
./decaf_lexer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


