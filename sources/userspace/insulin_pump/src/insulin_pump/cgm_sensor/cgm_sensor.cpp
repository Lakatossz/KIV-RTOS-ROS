#include "../../../include/insulin_pump/cgm_sensor/cgm_sensor.hpp"

CGM_Sensor::CGM_Sensor() : m_cgm {CCgm("DEV:cgm")}
{

}

CGM_Sensor::~CGM_Sensor()
{

}

void CGM_Sensor::Initialize()
{
	m_cgm.Init();
}

bool CGM_Sensor::Test()
{
	return m_cgm.Test();
}

void CGM_Sensor::Read_Actuall_Glycemia(float& value)
{
	m_cgm.Read(value);

	//if (value <= 0) {
	//	return false;
	//}

	//return true;
}
