# CreatureForPaperZD
Creature2D modified source and AnimSequences for PaperZD Support

This small public github contains the source code for the runtime modules for Creature2D (which KestrelMoon asked me to host). There're some small changes on Kestrel's source, namely:

- Moved a protected function UCreatureMeshComponent::StandardInit to be a public member (so we can initialize creature on an editor viewport, without registering the component to a parent component).
- Added DLL Linkage to 2 classes from the CreatureModule core api (CreatureAnimation and CreatureManager) so the resulting UPaperZDAnimSequence_Creature can make use of them (this last change isn't necessary for this specific release, due to we adding the AnimSequence as part of the Creature source code on this fork.

The idea is to incentivate Kestrel to add those 2 changes and only host here the needed AnimSequence files + instructions.


Instructions:
------------

For use of external animation sources for PaperZD first you need to have an inherited class from UPaperZDAnimSequence, this fork already gives one already configured class.

After creating the class, you must link the AnimSequence class with its render component, so the AnimPlayer (PaperZD class responsible of AnimSequence Playback) knows which child component to use when updating the playback.

For this, APaperZDCharacter inherits from IPaperZDAnimInstanceManager and provides the method ConfigurePlayer, which handles the created AnimInstance's player and expects the user to configure it. 

You must call: Player->RegisterRenderComponent(TSubclassOf<UPaperZDAnimInstance>,UPrimitiveComponent*) to link the Render+Sequence.
This is an BlueprintNativeEvent, so you can implement it on blueprint or in c++. Default implementation links Paper2D Flipbook component to the Flipbook sequences.
  
  Hope this small adition helps users with their 2D efforts on unreal.
  Cheers!
