/********************************************************************************
** auth�� God Of Pen
** desc�� ��δ��д����
** Ver.:  V1.0.0
*********************************************************************************/
#include "Engine.h"
#include "CreatureAnimationAsset.h"
#include "CreatureAnimationClip.generated.h"
#pragma  once
//////////////////////////////////////////////////////////////////////////
//��Ƭ�Σ�������Բ�ͬAsset�Ķ�Ƭ�ν������һ��������Ƭ�����ڲ���
//////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FCreatureAnimationShortClip
{
	GENERATED_USTRUCT_BODY()
	//ָ��ԴAnimationAsset��ָ��
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Creature")
	UCreatureAnimationAsset* SourceAsset;
		
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Creature")
	FName ClipNameInAsset;
};
//////////////////////////////////////////////////////////////////////////
//������ClipƬ��
//////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FCreatureAnimationClip
{
	GENERATED_USTRUCT_BODY()
	//ָ��ԴAnimationAsset��ָ��
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Creature")
	FName ClipName;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Creature")
	TArray<FCreatureAnimationShortClip> ShortClipList;


};