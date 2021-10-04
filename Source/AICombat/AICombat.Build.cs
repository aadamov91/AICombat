// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AICombat : ModuleRules
{
	public AICombat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "ALSV4_CPP", "UMG", "SlateCore", "Slate" });
	}
}
