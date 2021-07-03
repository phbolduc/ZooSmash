// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZooSmash : ModuleRules
{
	public ZooSmash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "HeadMountedDisplay" });
	}
}
