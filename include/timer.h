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
	void startPingTime(unsigned int milliseconds);
	bool pingTime();
	bool isPingTimeSet();
	
    private:
	unsigned int startTime,timePassed,pingTimeStart, timeToWait;
	bool started, paused;	
};

#endif
