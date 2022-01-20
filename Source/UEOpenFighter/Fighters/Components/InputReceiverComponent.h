#pragma once
#include "UEOpenFighter/ECF/Component.h"

#define INPUT_BUFFER_SIZE 8

enum EInputButtons:uint32
{
    UpButton=1,
    DownButton=2,
    LeftButton=4,
    RightButton=8,
    KickButton=16,
    PunchButton=32,
    
};

struct InputReceiverData{
public:
    InputReceiverData(){
        Input=0;
        PreviousInput=0;
        AssignedGamepad=-1;
        for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
        {
            InputBuffer[i]=0;
        }
    }
    int Input;
    int PreviousInput;
    int AssignedGamepad;
    int InputBuffer[INPUT_BUFFER_SIZE];
    
};
class InputReceiverComponent: public RollbackComponent<InputReceiverData> {
public:
    void Update(Entity* entity) override;
    bool IsPressed(EInputButtons Button);
    bool JustPressed(EInputButtons Button);
    bool JustReleased(EInputButtons Button);
    bool WasPressed(EInputButtons Button);

    bool WasPressedBuffer(int time,EInputButtons Button);
};