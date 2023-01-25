// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DFM1 : ModuleRules
{
	public DFM1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
