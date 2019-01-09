
#include "CreaturePluginPCH.h"
#include "CreatureMeshComponent.h"
#include "CreatureAnimationClip.h"
#include "CreatureAnimationClipsStore.h"

void UCreatureAnimationClipsStore::LoadAnimationDataToComponent(class UCreatureMeshComponent* MeshComponent)
{

	//////////////////////////////////////////////////////////////////////////
	//���棺�°汾�в��ܹ��������ֶ���ģʽ������
	MeshComponent->collectionClips.Empty();
	//����ClipList��׼��������ݵ�Component
	for (FCreatureAnimationClip Clip:ClipList)
	{
		FCreatureMeshCollectionClip MeshCollectionClip = FCreatureMeshCollectionClip();
		MeshCollectionClip.collection_name = Clip.ClipName;
		//���FCreatureMeshCollectionToken
		for (FCreatureAnimationShortClip ShortClip:Clip.ShortClipList)
		{
			//����ShortClip�е����ã�����CollectionData
			FCreatureMeshCollection CollectionData;
			CollectionData.creature_filename = FName(*ShortClip.SourceAsset->GetName());
			//ֱ�Ӹ���JsonString�����ã�����Ҫ�ٴ�����
			CollectionData.creature_core.pJsonData = &(ShortClip.SourceAsset->GetJsonString());
			
			CollectionData.animation_speed = ShortClip.SourceAsset->animation_speed;
			CollectionData.collection_material = ShortClip.SourceAsset->collection_material;

			//�����ǰData�Ѿ�������CollectionData����ֱ�ӷ���
			int32 Index = MeshComponent->collectionData.AddUnique(CollectionData);
			FCreatureMeshCollection &addedCollectionData = MeshComponent->collectionData[Index];
			addedCollectionData.creature_core.pJsonData = CollectionData.creature_core.pJsonData;
			addedCollectionData.source_asset = ShortClip.SourceAsset;

			FCreatureMeshCollectionToken Token = FCreatureMeshCollectionToken();
			Token.animation_name = ShortClip.ClipNameInAsset;
			Token.collection_data_index = Index;
			MeshCollectionClip.sequence_clips.Add(Token);
		}

		MeshComponent->collectionClips.AddUnique(MeshCollectionClip);
	}
}
