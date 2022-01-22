// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEOpenFighter : ModuleRules
{
	public UEOpenFighter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.Never;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"GGPOUE4"
		});
		PublicDefinitions.Add("GAMESPEED_FPS=60.f");
		PublicDefinitions.Add("ANIMATION_BAKE_FPS=60.f");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
