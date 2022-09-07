#!/bin/bash

openocd -f ./drivers/stm32f4discovery.cfg -c "program build/stm32-test.elf verify reset exit"

