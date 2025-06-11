// ---------------------------------------------------------------------------------------------------------------------
/// \file insulin_pump.hpp
/// \date 19. 03. 2023
/// \author Jaroslav Rosa (rosajaro1352@gmail.com)
///
/// \brief This file defines a class of Insulin Pump
// ---------------------------------------------------------------------------------------------------------------------

#pragma once

// STL imports (excluded from Doxygen)
/// \cond
//#include <thread>
//#include <stdstring.h>
/// \endcond

// Project file imports

#include "../../../include/insulin_pump/pid_regulator/pid_regulator.hpp"
#include "../../../include/insulin_pump/cgm_sensor/cgm_sensor.hpp"
#include "../../../include/insulin_pump/motor/motor.hpp"
#include "../../../include/insulin_pump/user_interface/zero_mate_user_interface.hpp"
#include "../../../include/insulin_pump/user_interface/user_interface.hpp"
#include "../../../include/insulin_pump/definitions/definitions.hpp"
#include "../../../include/insulin_pump/pump_settings/pump_settings.hpp"

#include <cgm.h>
#include <motor.h>
#include <stdstring.h>

#define BASAL_DOSE_ALLOWED "Basalni davka je nyni povolena"
#define BASAL_DOSE_DISALLOWED "Basalni davka je nyni zakazana"
#define ACTUAL_BASAL_P1 "Aktualni basal: "
#define ACTUAL_BOLUS_P1 "Aktualni bolus: "
#define ACTUAL_BASAL_INTERVAL_P1 "Aktualni basal interval: "
#define BOLUS_DOSE_ALLOWED "Basalni davka je nyni povolena"
#define BOLUS_DOSE_DISALLOWED "Basalni davka je nyni zakazana"
#define REQUEST_OKAY "Pro ulozeni nastaveni zmacknete OKAY."
#define CURRENT_SETTINGS_P1 "Aktualni nastaveni: "
#define BASAL_PROFIL_SET_CONFIRMATION "Potvrdili jste zmenu nastaveni basalniho profilu."
#define BOLUS_DOSE_CONFIRMATION "Potvrdili jste hodnotu bolusove davky."

#define HYPOGLYCEMIA_NOTIFICATION "Nemuzu podat davku, jelikoz je pacient v hypoglykemii"

#define READ_GLYCEMIA_CONFIRMATION "Precetl jsem aktualni glykemii: "
#define READ_BASAL_DOSE_CONFIRMATION "Ziskal jsem mnozstvi potrebne bazalni davky: "
#define READ_TOTAL_DOSE_CONFIRMATION "Ziskal jsem mnozstvi potrebne celkove davky: "

#define GIVING_NECESSARY_DOSE "Podavam potrebnou davku"

#define GLYCEMIA_HISTORY_SIZE 100
#define INSULIN_HISTORY_SIZE 100

#define MAX_GLYCEMIA_DIF 10
#define MAX_HYPOGLYCEMIA_COUNTER 10
#define MAX_HYPERGLYCEMIA_COUNTER 20

extern "C" void* memcpy(void* dest, const void* src, size_t n);

enum class NInsulin_Pump_State : uint8_t
{
	TurnedOff = 0,
	Initializing = 1,
	Normal_State = 2,
	Warning_State = 3,
	Critical_State = 4
};

struct glycemia_context {
	float m_glycemia_history[GLYCEMIA_HISTORY_SIZE];	///< 
	float m_insulin_history[INSULIN_HISTORY_SIZE];		///< 
	float m_min_glycemia;								///< 
	float m_max_glycemia;								///< 
	float m_hypoglycemia;								///< 
	float m_hyperglycemia;								///< 
	float m_min_insulin;								///< 
	float m_max_insulin;								///< 
	float referenced_value;								///< 
};

struct insulin_pump {
	uint32_t m_logpipe; ///< Logger

	pid_regulator m_pid_regulator; ///< 

	CCgm m_cgm{"DEV:cgm"}; ///<

	CMotor m_motor{"DEV:motor"}; ///<

	//ZeroMate_Interface m_ui; ///<

	pump_setting m_pump_settings; ///<

	glycemia_context m_glycemia_context;

	NInsulin_Pump_State m_pump_state; ///<
	bool m_basal_perimted = BASAL_PERMITED; ///<
	bool m_bolus_permited = BOLUS_PERMITED; ///<
	bool m_bolus_programmed = BOLUS_PROGRAMMED; ///<
	float m_bolus_dose = BOLUS_DOSE; ///<
	float m_basal_dose = BASAL_DOSE; ///<
	float m_total_dose = 0.0f; ///<
	bool m_dose_to_give = DOSE_TO_GIVE; ///<
	float m_current_glycemia = 0.0f; ///<
	float m_hypoglycemia_treshold = HYPOGLYCEMIA_TRESHOLD; ///<
	float m_hyperglycemia_treshold = HYPERGLYCEMIA_TRESHOLD; ///<
	bool m_deliver_insulin = true; ///< 
};

// -------------------------------------------------------------------------------------------------------------
/// \brief Initialize pump before run
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
insulin_pump initialize();

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
int do_routine(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Read_Current_Glycemia(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Get_Current_Basal_Dose(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Get_Current_Dose(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Give_Dose(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Analyze_Given_Dose(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
//bool Is_Bolus_Programmed(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
bool Glycemia_Reached_Treshold(insulin_pump& pump);

// -------------------------------------------------------------------------------------------------------------
/// \brief Runs the pump
///
/// 
///
// -------------------------------------------------------------------------------------------------------------
void Stop_Dosing(insulin_pump& pump);