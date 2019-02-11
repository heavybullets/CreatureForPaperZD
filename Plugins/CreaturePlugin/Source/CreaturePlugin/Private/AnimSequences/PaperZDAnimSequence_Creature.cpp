// Copyright 2017-2019 CriticalFailure Studio
#include "CreaturePluginPCH.h"
#include "PaperZDAnimSequence_Creature.h"
#include "CreatureMeshComponent.h"

UPaperZDAnimSequence_Creature::UPaperZDAnimSequence_Creature() : Super()
{
	SpeedOverride = 2.0f;
	BlendTime = 0.25f;
}

#if WITH_EDITOR
void UPaperZDAnimSequence_Creature::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == TEXT("AnimationAsset"))
	{
		CachedAnimationData = nullptr;
		
		//This needs a rebuild of the Core
		if (AnimationAsset)
		{
			Core.pJsonData = &AnimationAsset->GetJsonString();
			Core.InitCreatureRender();
			CachedAnimationData = Core.GetCreatureManager()->GetAnimation(AnimationName);
		}

	}
	else if (PropertyChangedEvent.GetPropertyName() == TEXT("AnimationName"))
	{
		//If only the name changes, we're still using the same animation asset
		if (AnimationAsset)
		{
			CachedAnimationData = Core.GetCreatureManager()->GetAnimation(AnimationName);
		}
	}
}
#endif

void UPaperZDAnimSequence_Creature::PostLoad()
{
	Super::PostLoad();

	if (AnimationAsset)
	{
		Core.pJsonData = &AnimationAsset->GetJsonString();
		Core.InitCreatureRender();
		CachedAnimationData = Core.GetCreatureManager()->GetAnimation(AnimationName);
	}
}

void UPaperZDAnimSequence_Creature::BeginSequencePlayback(class UPrimitiveComponent* RenderComponent, bool bLooping, bool bIsPreviewPlayback /* = false */) const
{
	//Cast it to a UCreatureMeshComponent
	UCreatureMeshComponent* CreatureMesh = Cast<UCreatureMeshComponent>(RenderComponent);
	if (CreatureMesh && CachedAnimationData)
	{
		//First validate we have the same setup as the render component, this works as forced initialization or when we change animation asset (although that should be avoided)
		if (!CreatureMesh->GetCore().GetCreatureManager() || CreatureMesh->creature_animation_asset != AnimationAsset)
		{
			CreatureMesh->creature_animation_asset = AnimationAsset;
			CreatureMesh->StandardInit();
		}

		//Make sure we have the render is using the same animation
		if (CreatureMesh->GetBluePrintActiveAnimationName() != AnimationName)
		{
			if (bIsPreviewPlayback)
			{
				CreatureMesh->SetBluePrintActiveAnimation_Name(AnimationName);
				CreatureMesh->SetBluePrintAnimationPlay(false);
			}
			else
			{
				CreatureMesh->SetBluePrintBlendActiveAnimation_Name(AnimationName, BlendTime);
			}
		}

		//Material should be the same
		if (CreatureMesh->GetMaterial(0) != Material)
		{
			CreatureMesh->SetMaterial(0, Material);
		}

		//Update common values
		CreatureMesh->SetBluePrintAnimationLoop(bLooping);
		CreatureMesh->animation_speed = SpeedOverride;
	}
}

void UPaperZDAnimSequence_Creature::UpdateRenderPlayback(class UPrimitiveComponent* RenderComponent, const float Time, bool bIsPreviewPlayback /* = false */) const
{
	//Cast it to a UCreatureMeshComponent
	UCreatureMeshComponent* CreatureMesh = Cast<UCreatureMeshComponent>(RenderComponent);
	if (CreatureMesh && CachedAnimationData)
	{
		//Only change preview playback time, CreatureRender manages the runtime updates
		if (bIsPreviewPlayback)
		{
			const float StartFrame = CachedAnimationData->getStartTime();
			const float CurrentFrame = StartFrame + Time * GetFramesPerSecond();
			CreatureMesh->SetBluePrintAnimationFrame(CurrentFrame);
		}
	}
}

float UPaperZDAnimSequence_Creature::GetTotalDuration() const
{
	if (CachedAnimationData)
	{
		return (CachedAnimationData->getEndTime() - CachedAnimationData->getStartTime()) / GetFramesPerSecond();
	}

	//Non valid
	return 0.0f;
}

TSubclassOf<UPrimitiveComponent> UPaperZDAnimSequence_Creature::GetRenderComponentClass() const
{
	return UCreatureMeshComponent::StaticClass();
}

void UPaperZDAnimSequence_Creature::ConfigureRenderComponent(class UPrimitiveComponent* RenderComponent, bool bIsPreviewPlayback /* = false */) const
{
	//Should be a creature mesh component
	UCreatureMeshComponent* CreatureMesh = Cast<UCreatureMeshComponent>(RenderComponent);
	if (CreatureMesh && bIsPreviewPlayback)
	{
		//Playback time and looping should not be managed by the mesh for full support
		CreatureMesh->SetBluePrintAnimationPlay(false);
		CreatureMesh->SetBluePrintAnimationLoop(false);
	}
}

float UPaperZDAnimSequence_Creature::GetFramesPerSecond() const
{
	//Default value for Creature2D is 30fps, hard coded except for the speed override
	return 30.0f * SpeedOverride;
}
