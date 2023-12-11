#include "v5_api.h"

uint32_t comp_state = V5_COMP_BIT_EBL | V5_COMP_BIT_MODE | V5_COMP_BIT_COMP | V5_COMP_BIT_GAME; // disabled, auton, connected, field control

// comp status
uint32_t vexCompetitionStatus(void) { return comp_state; }