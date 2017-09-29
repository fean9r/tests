#ifndef cern_vme_Event_h_INCLUDED
#define cern_vme_Event_h_INCLUDED
#include <cstdint>

namespace cern
{

struct Event
{
	uint16_t address;
	double max_temp;
	double min_temp;
	double current_temp;
};

} // namespace cern

#endif /* cern_vme_Event_h_INCLUDED */
