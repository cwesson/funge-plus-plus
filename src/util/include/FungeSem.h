/**
 * @file FungeSem.h
 * ...because github actions don't support C++20.
 * @author Conlan Wesson
 */

#pragma once

#include <condition_variable>
#include <mutex>

class FungeSem {
	public:
		explicit FungeSem(int v) :
			mutex(),
			cv(),
			value(v)
		{}
		
		void release(){
			std::unique_lock<std::mutex> guard(mutex);
			value = 1;
			cv.notify_all();
		}
		
		void acquire(){
			std::unique_lock<std::mutex> guard(mutex);
			while(!value){
				cv.wait(guard);
			}
			value = 0;
		}
	private:
		std::mutex mutex;
		std::condition_variable cv;
		int value;
};
