// ---------------------------------------------------------------------------------------------------------------------
/// \file definitions.hpp
/// \date 19. 03. 2023
/// \author Jaroslav Rosa (rosajaro1352@gmail.com)
///
/// \brief This file defines constants for the pump
// ---------------------------------------------------------------------------------------------------------------------


#pragma once

#define BASAL_PERMITED true					///< 
#define BOLUS_PERMITED true					///< 
#define BOLUS_PROGRAMMED true				///< 
#define BOLUS_DOSE 1.0f						///< 
#define BASAL_DOSE 0.1f						///< 
#define DOSE_TO_GIVE false					///< 
#define MAX_BASAL_DOSE 10.0f				///< 
#define MAX_BOLUS_DOSE 10.0f				///< 
#define HYPOGLYCEMIA_TRESHOLD 5				///< 
#define HYPERGLYCEMIA_TRESHOLD 8			///< 

#define BOLUS_STEP 0.5						///< Units
#define BASAL_TIME_STEP 0.5					///< Units

#define MAX_BASAL_TIME 120					///< Time

// Insulin set
#define MAX_TOTAL_DOSE 10.0f				///< 

// Motor
#define MICRO_REVOLUTION_TO_ML_RATIO 3200	///< 
#define TESTING_DOSE 1
