 
#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"
#endif

// add or remove necessary headers as you please


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
// If the worker is not valid, we will backtrack and try the next worker
// If we reach the end of the schedule, we will return true
bool scheduler(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t row,
		size_t col
)
{


    // base case: we reached the end of the schedule
    if (row == sched.size())
    {
      return true;
    }

    // each worker

    // if we are at the end of the column, that means the next call must start on new row (day + 1)
    if (col == dailyNeed)
    {
      return scheduler(avail, dailyNeed, maxShifts, sched, row + 1, 0);
    }

    // if we still have space in this row, increment the column (worker + 1)
    else
    {
      for (size_t i = 0; i < avail[0].size(); ++i)
      {
        if (avail[row][i])
        {
          // if this worker is already scheduled for today, move on
          if (find(sched[row].begin(), sched[row].end(), i) != sched[row].end())
          {
            continue;
          }

          // schedule worker and test if valid for this and following iteration
          sched[row][col] = i;
          if (isWorkerValid(avail, dailyNeed, maxShifts, sched, row, col, i))
          {
            if (scheduler(avail, dailyNeed, maxShifts, sched, row, col + 1))
            {
              return true;
            }
          }
        }
      }
    }

    // if not valid after trying all workers, backtrace
    sched[row][col] = INVALID_ID;

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
    // Add your code below


    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    return scheduler(avail, dailyNeed, maxShifts, sched, 0, 0);

    


}
