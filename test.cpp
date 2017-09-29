#include "vmod.h"
#include <iostream>

#include <algorithm>
#include <queue>


https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
template <class T>
struct SafeQueue 
{
	SafeQueue() :
		queue_(),
		buf_(std::unique_ptr<T[]>(new T[size])),
		size_(size)
	{
		//empty constructor
	}
	~SafeQueue()
	{}
    void enqueue(T item) 
    {
    	// handle here the lock
    	queue_.push(item);
    }

    T dequeue(void)
    {
    	// handle here the lock
    	T value = queue_.front();
    	queue_.pop();
    	return item;
    }
    private:
    	std::queue<T> queue_;
};

struct SensorState
{
	uint16_t address;
	double max_temp;
	double min_temp;
	double current_temp;
};

void addTemperature(SensorState state, double temp)
{
	if ( state.max_temp < temp ) 
			state.max_temp = temp;
	if ( state.min_temp > temp ) 
			state.min_temp = temp;
	state.current_temp = temp;
};

struct Sensor 
{
	Sensor(uint16_t address, SafeQueue<SensorState> & queue) : 
		sensor_address_(address),
		state_(),  
		queue_(queue)
	{
		state_.address=_sensor_address;
	}
	virtual ~Sensor() {};
	
	void setCalibrator(double scalingFactor, double offset) 
	{
		scalingFactor_ = scalingFactor; 
		offset_ = offset;
	}
	
	void read();

	friend bool operator== ( const Sensor &s1, const Sensor &s2);

private:
	double applyCalibration(double analog_val);

	uint16_t sensor_address_;
	double scalingFactor_;
	double offset_;
	SensorState state_;
	SafeQueue<SensorState> & queue_;
};

bool operator== ( const Sensor &s1, const Sensor &s2) 
{
        return s1._sensor_address == s2._sensor_address;
}

double Sensor::applyCalibration(double analog_val)
{
	return scalingFactor * (analog_val - offset_);
}

Sensor::read()
{
	double readout = readHardware(sensor_address_);
	addTemperature(state_, applyCalibration(readout));
	queue.put(state_);
}

class Supervisable 
{
	virtual void addSensor(uint16_t address, bool type) = 0;
	virtual void removeSensor(uint16_t address) = 0;
	virtual void setConversionFactors(uint16_t address double scalingFactor, double offset) = 0;
	virtual const uint16_t* getSensorList() = 0;
	virtual void setOutStream(ostream& stream) = 0;
	virtual void stop() = 0;
};

class VMESensorsManager : Supervisable 
{
public:

	VMESensorsManager() : stop_(false){}
	virtual ~VMESensorsManager() {}

	void addSensor(uint16_t address, bool type) ;
	void removeSensor(uint16_t address) ;
	void setConversionFactors(uint16_t address double scalingFactor, double offset) ;
	const uint16_t* getSensorList();
	void setOutStream(ostream& stream){ out_stream_ = stream;}
	void stop() { stop_ = true; }

private:
	void run();
	void notify_all();

	// how to hangle this ? vector of unique_ptr ?
	std::vector<Sensor* > sensors_;

	std::thread producerThread_;
	SafeQueue<SensorState> queue_;
	ostream& out_stream_;// non può essere non inizializzato !
	bool stop_;
}

void VMESensorsManager::addSensor(uint16_t address, bool type)
{
	if (sensors_.size() < 8 )
	{
		// how to hangle this ? vector of unique_ptr ?
		Sensor s(address, queue_); // after this it should start filling the queue
		sensors_.push_back(s);
	}
	else throw exception();
}

void VMESensorsManager::removeSensor(uint16_t address)
{
	// how to do this?
	std::vector<Sensor* >::iterator it = std::remove(sensors_.begin(),sensors_.end(), Sensor(address));	
	sensors_.erase(it, sensors_.end());
}

void VMESensorsManager::setConversionFactors(uint16_t address double scalingFactor, double offset)
{
	std::vector<Sensor* >::iterator it;
	it = std::find(sensors_.begin(), sensors_.end(), Sensor(address) );
	if (it != sensors_.end())
    	*it->setCalibrator(scalingFactor, offset);
  	else
    	std::cout << "Element not found in myvector\n";
}

VMESensorsManager::run()
{
	while(!stop_)
	{
		for(Sensor s : sensors_)
		{
			s.read();
		}

		// where should I put this??
		SensorState state = queue_.dequeue();
		out_stream_ << Encode(state);

 wait for 1 second timer arrives

	}
}

int main() 
{
	// We are here in the supervisor
	VMESensorsManager sensor_manager;


	sensor_manager.setOutStream(std::cout);

	// after this xml formatted data should be printed each second
	// one for each sensor 
	sensor_manager.addSensor(0xAAAA);
	sensor_manager.setConversionFactors(0xAAAA,2.5,70);

	sensor_manager.addSensor(0xBBBB);
	sensor_manager.setConversionFactors(0xBBBB,3.5,-50);

	sensor_manager.addSensor(0xCCCC);
	sensor_manager.setConversionFactors(0xCCCC,-2.5,20);
	
	sensor_manager.addSensor(0xDDDD);
	// what happens if there is no conversion factor?

	for(auto sen : sensor_manager.getSensorList())
	{ 
		std::cout << sen << cout::endl;	
	}
	
	sensor_manager.removeSensor(0xDDDD);

	for(auto sen : sensor_manager.getSensorList())
	{ 
		std::cout << sen << cout::endl;	
	}

	// all data should stop now
	sensor_manager.stop();
}

