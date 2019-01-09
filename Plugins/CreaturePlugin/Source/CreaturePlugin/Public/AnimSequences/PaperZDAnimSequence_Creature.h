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
class UPaperZDAnimSequence_Creature : public UPaperZDAnimSequence
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	UCreatureAnimationAsset* AnimationAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	FName AnimationName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence")
	UMaterialInterface* Material;

	/* Holds the in which to play this creature sequence, overriding the mesh setting*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimSequence", meta=(UIMin = "0.0", ClampMin = "0.0"))
	float SpeedOverride;

private:
	/* Animation object that holds the parsed information of the asset */
	CreatureModule::CreatureAnimation* CachedAnimationData;

	/* Core needed to parse the animation data */
	CreatureCore Core;
	
public:
	UPaperZDAnimSequence_Creature();

	//Required methods
	virtual void UpdateRenderPlayback(class UPrimitiveComponent* RenderComponent, const float Time) const override;
	virtual float GetTotalDuration() const override;
	virtual TSubclassOf<UPrimitiveComponent> GetRenderComponentClass() const override;
	virtual void ConfigureRenderComponent(class UPrimitiveComponent* RenderComponent) const override;
	virtual float GetFramesPerSecond() const override;

#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
	void PostLoad();
	
};
