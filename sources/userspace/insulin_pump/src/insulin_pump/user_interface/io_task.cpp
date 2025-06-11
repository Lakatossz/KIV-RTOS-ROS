#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <monitor.h>
#include <drivers/gpio.h>
#include "../../../include/insulin_pump/pump_settings/pump_settings.hpp"

constexpr uint32_t symbol_tick_delay = 8;
constexpr uint32_t char_tick_delay = 2;

uint32_t sos_led;
uint32_t ios[7];
uint32_t logpipe;
uint32_t oledpipe;
uint32_t io_task_output;
uint32_t io_sw_task_output;
uint32_t air_released;

void blink(bool short_blink)
{
    write(sos_led, "1", 1);
    sleep(short_blink ? 8 : 10);
    write(sos_led, "0", 1);
}

void update_settings_state(uint32_t pipe_id, uint32_t logpipe, uint32_t oledpipe, pump_setting& pump_settings)
{
    
}

void handle_up_button(uint32_t logpipe, uint32_t oledpipe, pump_setting& pump_settings)
{
    if (pump_settings.m_state == Basal) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        Change_Basal_Set(profile);
        pump_settings.m_temp_basal_profile = profile;

        if (pump_settings.m_temp_basal_profile.m_basal_set) {
            //write(oledpipe, "Basal dose V", strlen("Basal dose V"));
            char buf[16];
            int offset = strlen("Basal: ");
            bzero(buf + offset, 16 - offset);
            ftoa(profile.m_dose_unit, buf, 2);
            write(oledpipe, buf, 16);
        }
        else {
            write(oledpipe, "Basal dose X", strlen("Basal dose X"));
        }
    }
    else if (pump_settings.m_state == BasalValue) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        profile.m_dose_unit = Get_Higher_Value(profile.m_dose_unit);
        pump_settings.m_basal_profile = profile;
        char buf[16];
        int offset = strlen("Basal: ");
        bzero(buf + offset, 16 - offset);
        ftoa(profile.m_dose_unit, buf, 2);
        write(oledpipe, buf, 16);
    }
    else if (pump_settings.m_state == BolusValue) {
        float current_temp_bolus = pump_settings.m_temp_bolus_value;
        if ((current_temp_bolus + BOLUS_STEP) < MAX_BOLUS_DOSE) {
            current_temp_bolus += BOLUS_STEP;
            //bolus_programmed = true;
            pump_settings.m_temp_bolus_value = current_temp_bolus;
            //ui->DisplayMessage("Aktualni bolus: " + to_string(current_temp_bolus));
        }
        else {
            //bolus_programmed = false;
        }
    }
    else if (pump_settings.m_state == BasalTime) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        Add_Interval_Time(profile);
        pump_settings.m_temp_basal_profile = profile;
        //ui->DisplayMessage("Aktualni basal interval: " + to_string(pump_settings->Get_Temp_Basal_Profile()->Get_Interval()));
    }
}

void handle_down_button(uint32_t logpipe, uint32_t oledpipe, pump_setting& pump_settings)
{
    if (pump_settings.m_state == Basal) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        Change_Basal_Set(profile);
        pump_settings.m_temp_basal_profile = profile;

        if (pump_settings.m_temp_basal_profile.m_basal_set) {
            //ui->DisplayMessage("Basalni davka je nyni povolena");
        }
        else {
            //ui->DisplayMessage("Basalni davka je nyni zakazana");
        }
    }
    else if (pump_settings.m_state == BasalValue) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        profile.m_dose_unit = Get_Lower_Value(profile.m_dose_unit);
        pump_settings.m_basal_profile = profile;
        //ui->DisplayMessage("Aktualni basal: " + to_string(BasalProfile::Get_Basal_Value(pump_settings->Get_Temp_Basal_Profile()->Get_Dose_Unit())) + "\n");
    }
    else if (pump_settings.m_state == BolusValue) {
        float current_temp_bolus = pump_settings.m_temp_bolus_value;
        if ((current_temp_bolus - BOLUS_STEP) < MAX_BOLUS_DOSE) {
            current_temp_bolus -= BOLUS_STEP;
            //bolus_programmed = true;
            pump_settings.m_temp_bolus_value = current_temp_bolus;
            //ui->DisplayMessage("Aktualni bolus: " + to_string(current_temp_bolus));
        }
        else {
            //bolus_programmed = false;
        }
    }
    else if (pump_settings.m_state == BasalTime) {
        basal_profile profile = pump_settings.m_temp_basal_profile;
        Reduce_Interval_Time(profile);
        pump_settings.m_temp_basal_profile = profile;
        //ui->DisplayMessage("Aktualni basal interval: " + to_string(pump_settings->Get_Temp_Basal_Profile()->Get_Interval()));
    }

    //ui->DisplayMessage("Pro ulozeni nastaveni zmacknete OKAY.");
}

void handle_next_button(uint32_t logpipe, uint32_t oledpipe, pump_setting& pump_settings)
{
    //ui->DisplayMessage("NEXT\r");
    Set_Next_State(pump_settings);
    basal_profile profile = pump_settings.m_basal_profile;
    Set_Dose_Unit(Get_Lower_Value(profile.m_dose_unit), profile);
    pump_settings.m_temp_basal_profile = profile;
    //ui->DisplayMessage("Aktualni nastaveni: " + Pump_Settings::Settings_State_To_String(pump_settings->Get_State()));
}

void handle_okay_button(uint32_t logpipe, uint32_t oledpipe, pump_setting& pump_settings)
{
    //ui->DisplayMessage("OKAY\r");
    if (pump_settings.m_state == Basal ||
        pump_settings.m_state == BasalValue ||
        pump_settings.m_state == BasalTime) {
        pump_settings.m_basal_profile = pump_settings.m_temp_basal_profile;
        pump_settings.m_basal_profile = pump_settings.m_temp_basal_profile;
        //ui->DisplayMessage("Potvrdili jste zmenu nastaveni basalniho profilu.\n");
    }
    else if (pump_settings.m_state == BolusValue) {
        pump_settings.m_bolus_value = pump_settings.m_temp_bolus_value;
        //ui->DisplayMessage("Potvrdili jste hodnotu bolusove davky.\n");
    }
    else if (pump_settings.m_state == Action_Required) {
        write(oledpipe, "CONTINUE", strlen("CONTINUE"));
    }
}

int main(int argc, char** argv)
{
    logpipe = pipe("log", 128);
    oledpipe = pipe("oled", 16);
    io_task_output = pipe("io_task_1", sizeof(pump_setting));
    io_sw_task_output = pipe("io_sw_pipe", sizeof(pump_setting));
    air_released = pipe("air_released", 1);

    sos_led = open("DEV:gpio/5", NFile_Open_Mode::Write_Only);
    ios[0] = open("DEV:gpio/16", NFile_Open_Mode::Read_Only);
    ios[1] = open("DEV:gpio/17", NFile_Open_Mode::Read_Only);
    ios[2] = open("DEV:gpio/22", NFile_Open_Mode::Read_Only);
    ios[3] = open("DEV:gpio/12", NFile_Open_Mode::Read_Only);
    //ios[4] = pipe("io_task_2", sizeof(pump_setting));
    ios[4] = pipe("emergency", 1);

    pump_setting m_pump_settings;

    settings_state m_temp_state;

    char state = '0';
    char oldstate = '0';

    uint32_t io_id = 0;

    NGPIO_Interrupt_Type irtype = NGPIO_Interrupt_Type::Rising_Edge;
    ioctl(ios[0], NIOCtl_Operation::Enable_Event_Detection, &irtype);
    ioctl(ios[1], NIOCtl_Operation::Enable_Event_Detection, &irtype);
    ioctl(ios[2], NIOCtl_Operation::Enable_Event_Detection, &irtype);
    ioctl(ios[3], NIOCtl_Operation::Enable_Event_Detection, &irtype);

    //CMonitor monitor = CMonitor();

    //monitor.Clear();

    while (true)
    {
        char buf[16];
        bzero(buf, 16);

        io_id = wait_multiple(reinterpret_cast<uint32_t>(&ios), 5, Indefinite);

        bzero(buf, 16);

        itoa(io_id, buf, 10);
        //write(logpipe, buf, 16);
        //monitor.Put(buf, 16);

        if (io_id == ios[0]) {
            write(logpipe, "Prislo preruseni tlacitka UP\n", strlen("Prislo preruseni tlacitka UP\n"));
            write(oledpipe, "UP", strlen("UP"));
            if (m_pump_settings.m_state != Action_Required) {
                //handle_up_button(logpipe, oledpipe, m_pump_settings);
            }
        }
        else if (io_id == ios[1]) {
            write(logpipe, "Prislo preruseni tlacitka DOWN\n", strlen("Prislo preruseni tlacitka DOWN\n"));
            write(oledpipe, "DOWN", strlen("DOWN"));
            if (m_pump_settings.m_state != Action_Required) {
                //handle_down_button(logpipe, oledpipe, m_pump_settings);
            }
        }
        else if (io_id == ios[2]) {
            write(logpipe, "Prislo preruseni tlacitka NEXT\n", strlen("Prislo preruseni tlacitka NEXT\n"));
            write(oledpipe, "NEXT", strlen("NEXT"));
            if (m_pump_settings.m_state != Action_Required) {
                //handle_next_button(logpipe, oledpipe, m_pump_settings);
            }
        }
        else if (io_id == ios[3]) {
            write(logpipe, "Prislo preruseni tlacitka OKAY\n", strlen("Prislo preruseni tlacitka OKAY\n"));
            write(oledpipe, "OKAY", strlen("OKAY"));
            handle_okay_button(logpipe, oledpipe, m_pump_settings);

            if (m_pump_settings.m_state != Action_Required) {
                //char* ptr = reinterpret_cast<char*>(&m_pump_settings);
                //write(io_task_output, ptr, sizeof(pump_setting));
                //write(io_sw_task_output, ptr, sizeof(pump_setting));
            } //else
                //m_pump_settings.m_state = m_temp_state;
        }
        //else if (io_id == ios[4]) {
        //    write(logpipe, "Prislo preruseni z pipy\n", strlen("Prislo preruseni z pipy\n"));
            //update_settings_state(io_id, logpipe, m_pump_settings);
        //}
        else if (io_id == ios[4]) {
            //monitor.Put("Prislo preruseni z emergency pipy\n", strlen("Prislo preruseni z emergency pipy\n"));
            //write(logpipe, "Prislo preruseni z emergency pipy\n", strlen("Prislo preruseni z emergency pipy\n"));
            m_temp_state = m_pump_settings.m_state;
            m_pump_settings.m_state = Action_Required;
            read(ios[4], buf, 1);
            write(oledpipe, "ACTION REQUIRED", strlen("ACTION REQUIRED"));
            write(air_released, "1", 1);
            //update_settings_state(io_id, logpipe, m_pump_settings);
        }

        sleep(10, 100);
    }

    close(ios[0]);
    close(ios[1]);
    close(ios[2]);
    close(ios[3]);
    close(ios[4]);
    //close(ios[5]);
    close(sos_led);
    close(logpipe);
    close(oledpipe);
    close(io_task_output);
    close(io_sw_task_output);
    close(air_released);

    return 0;
}

/*char buf[16];
bzero(buf, 16);

io_id = wait_multiple(reinterpret_cast<uint32_t>(ios), 6, 10);

itoa(io_id, buf, 10);
write(logpipe, buf, 16);

if (io_id == ios[0]) {
    write(logpipe, "Prislo preruseni tlacitka UP\n", strlen("Prislo preruseni tlacitka UP\n"));
    write(oledpipe, "UP", strlen("Tlacitko UP"));
    handle_up_button(logpipe, oledpipe, m_pump_settings);
}
else if (io_id == ios[1]) {
    write(logpipe, "Prislo preruseni tlacitka DOWN\n", strlen("Prislo preruseni tlacitka DOWN\n"));
    write(oledpipe, "DOWN", strlen("DOWN"));
    handle_down_button(logpipe, oledpipe, m_pump_settings);
}
else if (io_id == ios[2]) {
    write(logpipe, "Prislo preruseni tlacitka NEXT\n", strlen("Prislo preruseni tlacitka NEXT\n"));
    write(oledpipe, "NEXT", strlen("NEXT"));
    handle_next_button(logpipe, oledpipe, m_pump_settings);
}
else if (io_id == ios[3]) {
    write(logpipe, "Prislo preruseni tlacitka OKAY\n", strlen("Prislo preruseni tlacitka OKAY\n"));
    write(oledpipe, "OKAY", strlen("OKAY"));
    handle_up_button(logpipe, oledpipe, m_pump_settings);
    char* ptr = reinterpret_cast<char*>(&m_pump_settings);
    write(io_task_output, ptr, sizeof(pump_setting));
}
else if (io_id == ios[4]) {
    write(logpipe, "Prislo preruseni z pipy\n", strlen("Prislo preruseni z pipy\n"));
    //update_settings_state(io_id, logpipe, m_pump_settings);
}
else if (io_id == ios[5]) {
    read(ios[5], buf, 1);
    write(logpipe, "Prislo preruseni z emergency pipy\n", strlen("Prislo preruseni z emergency pipy\n"));
    //update_settings_state(io_id, logpipe, m_pump_settings);
}
else {
    write(logpipe, "Nevim, co me probudilo\n", strlen("Nevim, co me probudilo\n"));
    write(oledpipe, "Haha", strlen("Haha"));
}*/
