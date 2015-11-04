################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837xS_GlobalVariableDefs.obj: C:/ti/controlSUITE/device_support/F2837xS/v170/F2837xS_headers/source/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v170/F2837xS_headers/include" --include_path="C:/ti/controlSUITE/libs/dsp/FixedPointLib/v1_20_00_00/include" --advice:performance=all -g --c99 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2837xS_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fir16.obj: C:/ti/controlSUITE/libs/dsp/FixedPointLib/v1_20_00_00/source/fir16.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v170/F2837xS_headers/include" --include_path="C:/ti/controlSUITE/libs/dsp/FixedPointLib/v1_20_00_00/include" --advice:performance=all -g --c99 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fir16.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --cla_support=cla1 --vcu_support=vcu2 -O4 --opt_for_speed=5 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/ti/controlSUITE/device_support/F2837xS/v170/F2837xS_headers/include" --include_path="C:/ti/controlSUITE/libs/dsp/FixedPointLib/v1_20_00_00/include" --advice:performance=all -g --c99 --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


