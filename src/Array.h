#pragma once

#include "State.h"
#include <vector>
#include <iostream>

#include <Windows.h>

class Array {
private:
	State& m_state;
public:
	Array(State& state) : m_state(state) {};

	int& operator[](size_t index) { return m_state.anim.array[index]; }

	void wait(int ms) {
		printf("%d is sleep! \n", std::this_thread::get_id());
		Sleep(ms);

		while (m_state.anim.paused) {
			std::unique_lock<std::mutex> lock(m_state.pause);
			printf("paused! \n");

			m_state.cv.wait(lock);
			lock.unlock();
		}
	};

	int len() {
		return m_state.anim.array.size()-1;
	}

	void swap(int firstIndex, int secondIndex) {
		auto array = m_state.anim.array;

		int temp = array[firstIndex];
		array[firstIndex] = array[secondIndex];
		array[secondIndex] = temp;
	};

	void dump() {
		for (auto i = m_state.anim.array.begin(); i != m_state.anim.array.end(); ++i)
			std::cout << *i << ' ';
		printf("\n");
	}
};

