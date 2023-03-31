

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Prototypes for helper functions
bool scheduleHelper( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t currentDay, size_t currentWorkers );

bool isValid(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t currentDay, size_t currentWorkers, Worker_T id );

// Add your implementation of schedule() and other helper functions here

bool isValid( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t currentDay, size_t currentWorkers, Worker_T id )
{
	size_t count = 0;
	for (size_t i = 0; i < sched.size(); ++i)
	{
		for (size_t j = 0; j < dailyNeed; ++j)
		{
			if (sched[i][j] == id)
			{
				count++;
			}
		}
	}
	return (count <= maxShifts);
}

bool scheduleHelper( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t currentDay, size_t currentWorkers )
{
	if (currentDay == sched.size())
	{
		return true;
	}
		for (size_t i = 0; i < avail[0].size(); ++i)
		{
			if (avail[currentDay][i]){
				if (find(sched[currentDay].begin(), sched[currentDay].end(), i) != sched[currentDay].end())
				{
					continue;
				}
				sched[currentDay][currentWorkers] = i;
				if (isValid(avail, dailyNeed, maxShifts, sched, currentDay, currentWorkers, i))
				{
					if (currentWorkers == dailyNeed - 1)
					{
						if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay + 1, 0))
						{
							return true;
						}
					}
					else
					{
						if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay, currentWorkers + 1))
						{
							return true;
						}
					}
				}
			}
		}
		sched[currentDay][currentWorkers] = INVALID_ID;
		return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
		std::vector<Worker_T> init(dailyNeed, INVALID_ID);
    for (size_t row = 0; row < avail.size(); ++row)
    {
				sched.push_back(init);
    }
		return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);
}
