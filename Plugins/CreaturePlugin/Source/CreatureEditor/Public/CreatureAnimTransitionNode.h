/********************************************************************************
** auth�� God Of Pen
** desc�����ڱ�ʾһ������״̬ת����Node
** Ver.:  V1.0.0
*********************************************************************************/
#include "Engine.h"
#include "EdGraph/EdGraphNode.h"
#include "SGraphNode.h"
#include "CreatureAnimTransition.h"
#include "CreatureAnimTransitionNode.generated.h"
#pragma  once


class UEdGraphPin;
class UCreatureAnimTransitionNode;
class SCreatureGraphNodeAnimState : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SCreatureGraphNodeAnimState){}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UCreatureAnimTransitionNode* InNode);

	// SGraphNode interface
	virtual void UpdateGraphNode() override;

};

UCLASS()
class UCreatureAnimTransitionNode :public UEdGraphNode{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = "CreaturePlugin")
	FName TransitionCondition;
	UPROPERTY(EditAnyWhere, Category = "CreaturePlugin")
	bool	TransitionFlag;
	UPROPERTY()
	FEdGraphPinReference InputPin;
	UPROPERTY()
	FEdGraphPinReference OutputPin;
	UPROPERTY()
	class	UCreatureAnimStateNode* TransitionTargetNode;
	UPROPERTY()
	UCreatureAnimTransition* CompiledTransition;
public:
	UCreatureAnimTransitionNode();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const;
	virtual FLinearColor GetNodeTitleColor() const override;
#ifdef WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};