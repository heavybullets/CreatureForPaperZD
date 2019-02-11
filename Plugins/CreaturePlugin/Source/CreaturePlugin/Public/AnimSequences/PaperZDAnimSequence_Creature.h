// Copyright 2017-2019 CriticalFailure Studio

#pragma once

#include "CoreMinimal.h"
#include "CreatureModule.h"
#include "CreatureCore.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "PaperZDAnimSequence_Creature.generated.h"

class UCreatureAnimationAsset;
class UMaterialInterface;
/**
 * AnimSequence class that enables Creature2D skeletal mesh support for PaperZD
 */
UCLASS()
class CREATUREPLUGIN_API UPaperZDAnimSequence_Creature : public UPaperZDAnimSequence
{
	GENERATED_BODY()

public:
	/* Master Creature2D asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	UCreatureAnimationAsset* AnimationAsset;

	/* Name of the animation that is inside the .json file. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	FName AnimationName;

	/* The material to use for the asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	UMaterialInterface* Material;

	/* Holds the in which to play this creature sequence, overriding the mesh setting. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence", meta=(UIMin = "0.0", ClampMin = "0.0"))
	float SpeedOverride;

	/* How long to blend between this animation and the previous one. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))
	float BlendTime;

private:
	/* Animation object that holds the parsed information of the asset */
	CreatureModule::CreatureAnimation* CachedAnimationData;

	/* Core needed to parse the animation data */
	CreatureCore Core;
	
public:
	UPaperZDAnimSequence_Creature();

	//Required methods
	virtual void BeginSequencePlayback(class UPrimitiveComponent* RenderComponent, bool bLooping, bool bIsPreviewPlayback = false) const override;
	virtual void UpdateRenderPlayback(class UPrimitiveComponent* RenderComponent, const float Time, bool bIsPreviewPlayback = false) const override;
	virtual float GetTotalDuration() const override;
	virtual TSubclassOf<UPrimitiveComponent> GetRenderComponentClass() const override;
	virtual void ConfigureRenderComponent(class UPrimitiveComponent* RenderComponent, bool bIsPreviewPlayback = false) const override;
	virtual float GetFramesPerSecond() const override;

#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
	void PostLoad();
	
};
