#include <interrupt_controller.h>
#include <drivers/timer.h>
#include <process/process_manager.h>
#include <fs/filesystem.h>

#include <drivers/mcp9808.h>
#include <drivers/a810_bubble_sensor.h>
#include <drivers/max6864.h>
#include <drivers/i2c.h>
#include <drivers/cgm_sensor.h>
#include <drivers/ads1115_pbmh.h>
#include <drivers/bq25120a.h>
#include <drivers/ds3231.h>
#include <drivers/pca9685_mg996r.h>
#include <drivers/oled_ssd1306.h>

#include "../../userspace/insulin_pump/include/insulin_pump/insulin_pump/insulin_pump.hpp"

extern "C" void Timer_Callback()
{
	sProcessMgr.Schedule();
}

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_init_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_init_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_io_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_io_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_display_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_display_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_insulin_pump_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_insulin_pump_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_hw_control_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_hw_control_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_sw_control_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_sw_control_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_air_in_line_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_air_in_line_task_len;

extern "C" unsigned char _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_logger_task[];
extern "C" unsigned int _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_logger_task_len;

bool power_on_self_test() {

	CA810_Bubble_Sensor testA810_Bubble_Sensor(26);

	CMax6864 testMax6864(23, 24);

	CI2C testI2C1(hal::BSC1_Base, 2, 3);
	CMcp9808 testMcp9808(testI2C1);
	CCgm_Sensor testCgm_Sensor(testI2C1);
	CAds1115_Pbmh testAds1115_Pbmh(testI2C1);
	CBattery_System_BQ25120A testBattery_System_BQ25120A(testI2C1);
	CDs3231 testDs3231(testI2C1);
	CPca9685_Mg996r testPca9685_Mg996r(testI2C1);

	testMcp9808.Open();
	testA810_Bubble_Sensor.Open();
	testMax6864.Open();
	testI2C1.Open();
	testCgm_Sensor.Open();
	testAds1115_Pbmh.Open();
	testBattery_System_BQ25120A.Open();
	testDs3231.Open();
	testPca9685_Mg996r.Open();
	testPca9685_Mg996r.Open();

	bool test_result = testMcp9808.Test_Peripheral()
		&& testA810_Bubble_Sensor.Test_Peripheral()
		&& testMax6864.Test_Peripheral()
		&& testCgm_Sensor.Test_Peripheral()
		&& testAds1115_Pbmh.Test_Peripheral()
		&& testBattery_System_BQ25120A.Test_Peripheral()
		&& testDs3231.Test_Peripheral()
		&& testPca9685_Mg996r.Test_Peripheral();

	testMcp9808.Close();
	testA810_Bubble_Sensor.Close();
	testMax6864.Close();
	testI2C1.Close();
	testCgm_Sensor.Close();
	testAds1115_Pbmh.Close();
	testBattery_System_BQ25120A.Close();
	testDs3231.Close();
	testPca9685_Mg996r.Close();
	testPca9685_Mg996r.Close();

	return test_result;
}

extern "C" int _kernel_main(void)
{
	if (true/*power_on_self_test()*/) {
		// inicializace souboroveho systemu
		sFilesystem.Initialize();

		//Insulin_Pump insulin_pump();

		// vytvoreni hlavniho systemoveho (idle) procesu
		sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_init_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_init_task_len, true);
		sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_logger_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_logger_task_len, false);
		sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_io_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_io_task_len, false);
		//sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_display_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_display_task_len, false);
		sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_insulin_pump_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_insulin_pump_task_len, false);
		//sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_hw_control_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_hw_control_task_len, false);
		//sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_sw_control_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_sw_control_task_len, false);
		sProcessMgr.Create_Process(_mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_air_in_line_task, _mnt_c_users_rosaj_source_repos_KIV_RTOS_sources_userspace_build_air_in_line_task_len, false);

		// vytvoreni vsech tasku
		// TODO: presunuti do init procesu a nejake inicializacni sekce

		// zatim zakazeme IRQ casovace
		sInterruptCtl.Disable_Basic_IRQ(hal::IRQ_Basic_Source::Timer);

		// nastavime casovac - v callbacku se provadi planovani procesu
		sTimer.Enable(Timer_Callback, 0x80, NTimer_Prescaler::Prescaler_1);

		// povolime IRQ casovace
		sInterruptCtl.Enable_Basic_IRQ(hal::IRQ_Basic_Source::Timer);

		// povolime IRQ (nebudeme je maskovat) a od tohoto momentu je vse v rukou planovace
		sInterruptCtl.Set_Mask_IRQ(false);

		// vynutime prvni spusteni planovace
		sProcessMgr.Schedule();

		// tohle uz se mockrat nespusti - dalsi IRQ preplanuje procesor na nejaky z tasku (bud systemovy nebo uzivatelsky)
		while (true)
			;
	}
	else {
		return 1;
	}

	return 0;
}
