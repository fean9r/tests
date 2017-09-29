#ifndef cern_vme_VMESensorsManager_h_INCLUDED
#define cern_vme_VMESensorsManager_h_INCLUDED

#include "Event.h"
#include "Supervisable.h"
#include "SafeQueue.hpp"
#include <vector>
#include <memory>
#include <thread>

namespace cern
{
class Encoder;
class Sensor;

//template<class T> using PtrVector = std::vector<std::unique_ptr<T>>;
typedef typename std::unique_ptr<Sensor> SensorPtr;
typedef typename std::vector<SensorPtr> SensorVector;

class VMESensorsManager : public Supervisable
{
public:

	VMESensorsManager();
	virtual ~VMESensorsManager();

	void addSensor(uint16_t address, bool type);
	void removeSensor(uint16_t address);
	void setConversionFactors(uint16_t address, double scalingFactor, double offset);
	std::vector<uint16_t> getSensorList() const;
	void setOutStream(std::ostream& stream);

	void stop();

private:
	void run();
	void notify_all();

	SensorVector sensors_;
	std::thread producerThread_;
	SafeQueue<Event> queue_;
	std::unique_ptr<Encoder> encoder_;
	bool stop_;
};

} // namespace cern

#endif /* cern_vme_Sensor_h_INCLUDED */
