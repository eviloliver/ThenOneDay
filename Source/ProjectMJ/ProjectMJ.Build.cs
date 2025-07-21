// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectMJ : ModuleRules
{
	public ProjectMJ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "ProjectMJ" });

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Niagara",
	        "AIModule", "GameplayAbilities", "GameplayTags", "GameplayTasks",
	        "NavigationSystem", "PhysicsCore", "Json", "JsonUtilities", "HTTP",
          "EnhancedInput", "MoviePlayer", "Slate", "SlateCore", "MotionWarping"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
