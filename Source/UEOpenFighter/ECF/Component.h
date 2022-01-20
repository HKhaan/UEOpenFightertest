#pragma once
#include "VirtualMemory.h"

class Entity;

template <typename ObjType>
class ComponentDataCreator
{
public:

	int start=start = VirtualMemory::memorySize;;
	ObjType* data= VirtualMemory::NewStruct<ObjType>(); ;

	static ComponentDataCreator<ObjType>* CreateDataForComponent()
	{
    	auto instance = new ComponentDataCreator<ObjType>;
    	VirtualMemory::pointerFixCallbacks.push_back([instance]
        {
            instance->data = (ObjType*)(&VirtualMemory::memory[0] + instance->start);
        });
    	for (auto it = VirtualMemory::pointerFixCallbacks.begin(); it != VirtualMemory::pointerFixCallbacks.end(); ++it)
    	{
    		(*it)();
    	}
    	return instance;
    }
	
};




class Component
{
public:
	virtual ~Component() = default;

	virtual void BeginPlay(Entity* entity)
	{
	}
	virtual void Update(Entity* entity)
	{
	}
};


template <typename DataType>
class RollbackComponent : public Component
{
#ifndef WITH_EDITOR
private:
#endif
	ComponentDataCreator<DataType>* data = ComponentDataCreator<DataType>::CreateDataForComponent();
public:

	DataType* GetData()
	{
		return data->data;
	}

};
