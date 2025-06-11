#!/bin/bash

rm "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/insulin_pump_task.elf"
rm "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/init_task.elf"
rm "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/logger_task.elf"

echo "Spoustim kernel build..."
./build.sh

cd userspace

echo "Spoustim userspace build..."
./build.sh || { echo "build1.sh selhal"; exit 1; }

cd ..

echo "Spoustim kernel build..."
./build.sh || { echo "build2.sh selhal"; exit 1; }

mv "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/insulin_pump_task" "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/insulin_pump_task.elf"
mv "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/init_task" "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/init_task.elf"
mv "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/logger_task" "/mnt/c/users/rosaj/source/repos/KIV-RTOS/sources/userspace/build/logger_task.elf"

echo "Vsechny buildy probehly uspesne."