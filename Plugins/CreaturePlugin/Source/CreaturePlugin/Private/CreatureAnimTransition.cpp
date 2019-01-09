
#include "CreaturePluginPCH.h"
#include "CreatureAnimTransition.h"
#include "CreatureAnimStateMachineInstance.h"

bool UCreatureAnimTransition::Translate(UCreatureAnimStateMachineInstance *forInstance)
{
	for (FCreatureTransitionCondition condition : TransitionConditions)
	{
		bool currentConditionValue = forInstance->GetConditionByName(condition.TransitionName);
		if (currentConditionValue != condition.TransitionFlag)
		{
			return false;
		}
		else
		{
			continue;
		}		
	}

	forInstance->SetCurrentState(TargetState);

	return true;
}

void UCreatureAnimTransition::AnimationEndTranslate(class UCreatureAnimStateMachineInstance *forInstance)
{
	//���ȼ�鵱ǰת���Ƿ�ΪAnimationEnd
	if (TransitionConditions[0].TransitionName == FName(TEXT("AnimationEnd")))
	{
		forInstance->SetCurrentState(TargetState);
	}
}
