/*
 * work_thread_manager.h
 *
 *  Created on: 2013. 12. 4.
 *      Author: dongbum
 */

#ifndef WORKTHREADMANAGER_H_
#define WORKTHREADMANAGER_H_

#include <boost/thread.hpp>

class WorkThreadManager
{
public:
	WorkThreadManager(void);
	WorkThreadManager(const unsigned int thread_count);
	virtual ~WorkThreadManager(void);

	void Run(void);
private:
	boost::thread_group thread_group_;
};

#endif /* WORKTHREADMANAGER_H_ */
