 
#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// Check if the worker is valid for the current day and the current worker position
bool isWorkerValid(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t row,
		size_t col,
		Worker_T id
);

 
// in this function, we will try to schedule each worker for the current day
// if the worker is valid, we will recursively call the function to schedule the next worker
// if the worker is not valid, we will backtrack and try the next worker
bool scheduler(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t row,
		size_t col
);

// Add your implementation of schedule() and other helper functions here


// Check if the worker is valid for the current day and the current worker position
bool isWorkerValid(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t row,
		size_t col,
		Worker_T id
)
{
    // count how many times the worker has been scheduled
    // for the current day
    size_t count = 0;
    for (size_t i = 0; i < col; ++i)
    {
      if (sched[row][i] == id)
      {
        count++;
      }
    }

    // if the count is too high, then return false
    if (count >= maxShifts)
    {
      return false;
    }

    // count how many times the worker has been scheduled
    // for the current day
   count = 0;
for (size_t k = 0; k < row * dailyNeed; ++k)
{
    size_t i = k / dailyNeed;
    size_t j = k % dailyNeed;
    if (sched[i][j] == id)
    {
        count++;
    }
}


    // if the count is too high, then return false
    if (count >= maxShifts)
    {
      return false;
    }

    // if we get here, then the worker is valid
    return true;
}

// In this function, we will try to schedule each worker for the current day
// If the worker is valid, we will recursively call the function to schedule the next worker

// 7/11 tests
bool scheduler_helper(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
	DailySchedule& sched,
	size_t row,
	size_t col,
	size_t worker
)
{
	// base case: we reached the end of the schedule
	if (row == sched.size())
	{
		return true;
	}

	// if we are at the end of the column, that means the next call must start on new row (day + 1)
	if (col == dailyNeed)
	{
		return scheduler_helper(avail, dailyNeed, maxShifts, sched, row + 1, 0, 0);
	}

	if (worker >= avail[0].size())
	{
		// if not valid after trying all workers, backtrace
		sched[row][col] = INVALID_ID;
		return false;
	}

	// if this worker is already scheduled for today, move on
	if (find(sched[row].begin(), sched[row].end(), worker) != sched[row].end())
	{
		return scheduler_helper(avail, dailyNeed, maxShifts, sched, row, col, worker + 1);
	}

	// schedule worker and test if valid for this and following iteration
	sched[row][col] = worker;
	if (isWorkerValid(avail, dailyNeed, maxShifts, sched, row, col, worker))
	{
		if (scheduler_helper(avail, dailyNeed, maxShifts, sched, row, col + 1, 0))
		{
			return true;
		}
	}

	// backtrace
	sched[row][col] = INVALID_ID;
	return scheduler_helper(avail, dailyNeed, maxShifts, sched, row, col, worker + 1);
}

bool scheduler(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
	DailySchedule& sched,
	size_t row,
	size_t col
)
{
	return scheduler_helper(avail, dailyNeed, maxShifts, sched, row, col, 0);
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
    // Add your code below


    // initialize the schedule matrix
    sched.resize(avail.size());
    for (size_t i = 0; i < avail.size(); ++i)
    {
        sched[i].resize(dailyNeed, INVALID_ID);
    }


    // call the helper function
    return scheduler(avail, dailyNeed, maxShifts, sched, 0, 0);


}
