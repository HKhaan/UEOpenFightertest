#include "InputReceiverComponent.h"

#include "BodyComponent.h"
#include "UEOpenFighter/Characters/UEOpenFighterCharacter.h"
#include "UEOpenFighter/ECF/Entity.h"
#include "UEOpenFighter/ECF/World.h"

void InputReceiverComponent::Update(Entity* Entity)
{
	if (GetData()->AssignedGamepad < 0)
	{
		GetData()->InputBuffer[0] = GetData()->Input;
		for (int i = 1; i < INPUT_BUFFER_SIZE; i++)
		{
			GetData()->InputBuffer[i] = GetData()->InputBuffer[i-1];
		}
	}
}

bool InputReceiverComponent::IsPressed(EInputButtons Button)
{
	return ((GetData()->Input & Button) != 0);
}


bool InputReceiverComponent::JustPressed(EInputButtons Button)
{
	return ((GetData()->Input & Button) != 0) && ((GetData()->PreviousInput & Button) == 0);
}

bool InputReceiverComponent::JustReleased(EInputButtons Button)
{
	return ((GetData()->Input & Button) == 0) && ((GetData()->PreviousInput & Button) != 0);
}

bool InputReceiverComponent::WasPressed(EInputButtons Button)
{
	return ((GetData()->PreviousInput & Button) != 0);
}

bool InputReceiverComponent::WasPressedBuffer(int time, EInputButtons Button)
{
	return ((GetData()->InputBuffer[time] & Button) != 0);
}
