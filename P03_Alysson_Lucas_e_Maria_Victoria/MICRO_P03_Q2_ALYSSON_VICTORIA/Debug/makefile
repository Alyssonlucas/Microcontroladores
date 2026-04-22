################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MICRO_P03_Q2_ALYSSON_VICTORIA
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MICRO_P03_Q2_ALYSSON_VICTORIA.elf \

MAP_FILES += \
MICRO_P03_Q2_ALYSSON_VICTORIA.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MICRO_P03_Q2_ALYSSON_VICTORIA.list \


# All Target
all: main-build

# Main-build Target
main-build: MICRO_P03_Q2_ALYSSON_VICTORIA.elf secondary-outputs

# Tool invocations
MICRO_P03_Q2_ALYSSON_VICTORIA.elf MICRO_P03_Q2_ALYSSON_VICTORIA.map: $(OBJS) $(USER_OBJS) C:\Users\lucas\Desktop\Disciplinas\2026.1\ (atual)\microcontroladores\Microcontroladores\P03_Alysson_Lucas_e_Maria_Victoria\MICRO_P03_Q2_ALYSSON_VICTORIA\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "MICRO_P03_Q2_ALYSSON_VICTORIA.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\lucas\Desktop\Disciplinas\2026.1 (atual)\microcontroladores\Microcontroladores\P03_Alysson_Lucas_e_Maria_Victoria\MICRO_P03_Q2_ALYSSON_VICTORIA\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MICRO_P03_Q2_ALYSSON_VICTORIA.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MICRO_P03_Q2_ALYSSON_VICTORIA.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MICRO_P03_Q2_ALYSSON_VICTORIA.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MICRO_P03_Q2_ALYSSON_VICTORIA.elf MICRO_P03_Q2_ALYSSON_VICTORIA.list MICRO_P03_Q2_ALYSSON_VICTORIA.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
