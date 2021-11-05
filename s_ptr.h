#ifndef S_PTR_H
#define S_PTR_H

template<class T>
class control_Blck {

	T* data = nullptr;
	unsigned int useCnt = 0;
public:

	control_Blck(T* d) {
		data = d;
		inc();
	}
	
	void inc() {
		useCnt++;
	}
	void dec() {
		useCnt--;
	}
	unsigned int getUseCnt() {
		return useCnt;
	}

};

template<class T>
class s_ptr{
	T* data = nullptr;
	control_Blck<T>* cBL = nullptr;	

	void clear() {
		this->control_Blck->dec();
		if (this->control_Blck->getUseCnt() == 0) {
			delete control_Blck;
			delete data;
		}
	}
public:
	s_ptr(T* d) {
		data = d;
		cBL = new control_Blck<T>(d);	
	}
	s_ptr(s_ptr &ptr) {
		data = ptr.data;
		control_Blck = ptr.control_Blck;
		ptr.control_Blck->inc();
	}
	s_ptr& operator= (s_ptr& ptr) {
		if (this->data == ptr.data)
			return *this;
		clear();
		data = ptr.data;
		control_Blck = ptr.control_Blck;
		this->control_Blck->inc();
		return *this;
	}
	~s_ptr() {
		clear();
	}

	T& operator*() { return *data; }
	T* operator->() { return data; }
};

#endif S_PTR_H
