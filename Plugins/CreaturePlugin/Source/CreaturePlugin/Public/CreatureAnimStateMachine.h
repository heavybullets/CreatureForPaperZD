#pragma once
#include "Engine.h"
#include "AnimationRuntime.h"
#include "EdGraph/EdGraph.h"
#include "CreatureTransitionCondition.h"
#include "CreatureMeshComponent.h"
#include "CreatureAnimStateMachine.generated.h"

UCLASS(BlueprintType)
class CREATUREPLUGIN_API UCreatureAnimStateMachine :
	public UObject
{
	GENERATED_BODY()
public:

	UCreatureAnimStateMachine();

	UPROPERTY(EditAnywhere, Category = "CreatureAnimStateMachine")
	FString Name;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UEdGraph* StateMachineGraph=nullptr;

	UPROPERTY(Transient)
	class UCreatureAnimStateMachineInstance *InstanceBeingDebugged;
#endif /*WITH_EDITORONLY_DATA*/

	//���ڵ㣬���ڴӸ�State��ʼ����״̬ת��
	UPROPERTY()
	UCreatureAnimState* RootState;
	

};

