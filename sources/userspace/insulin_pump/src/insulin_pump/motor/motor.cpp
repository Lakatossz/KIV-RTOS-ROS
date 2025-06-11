#include "../../../include/insulin_pump/motor/motor.hpp"

Motor::Motor()
	: m_motor { CMotor("DEV:motor") }
{
	
}

Motor::~Motor()
{

}

void Motor::Initialize()
{
	m_motor.Init();
}

bool Motor::Test()
{
	return m_motor.Test();
}

void Motor::Give_Dose(uint16_t ml)
{
	char total_buffer[10] = {};

	itoa(ml, total_buffer, 10);

	//m_logger.Debug(GIVING_DOSE_NOTIFICATION, strlen(GIVING_DOSE_NOTIFICATION));
	//m_logger.Debug(total_buffer, strlen(total_buffer));

	Give_Dose(Ml_To_Revolutions(ml));
}

uint32_t Motor::Ml_To_Revolutions(uint16_t ml)
{
	return static_cast<uint32_t>(ml / MICRO_REVOLUTION_TO_ML_RATIO);
}

void Motor::Give_Dose(uint32_t revolutions)
{
	m_micro_revolutions_counter += revolutions;
	m_motor.Move_Forward(revolutions);
}

void Motor::Move_Back()
{
	uint32_t revolutions = 1;

	m_micro_revolutions_counter -= revolutions;
	m_motor.Move_Forward(revolutions);
}

