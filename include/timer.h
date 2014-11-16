#ifndef TIMER_H_
#define TIMER_H_
class Timer
{
    public:
	Timer();
	~Timer();
	void start();
	void reset();
	void pause();
	void wait(unsigned int milliseconds);
	unsigned int getTime();
	int registerPingNumber();
	void releasePingNumber(int pingNumber);
	void startPingTime(unsigned int milliseconds, int pingNumber);
	bool pingTime(int pingNumber);
	bool isPingTimeSet(int pingNumber);
	void clearPingTime(int pingNumber);
	
    private:
	void initializePings();
	bool validPingNumber(int pingNumber);
	int pingsAllocated;
	const static int MAX_PINGS = 11;	
	bool isPingAllocated[MAX_PINGS];
	unsigned int startTime,timePassed;
	unsigned int pingTimeStart[MAX_PINGS],timeToWait[MAX_PINGS];
	bool started, paused;	
};

#endif
