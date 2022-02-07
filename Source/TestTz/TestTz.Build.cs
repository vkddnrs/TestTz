// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestTz : ModuleRules
{
	public TestTz(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PublicIncludePaths.AddRange(new string[] {"TestTz/Public/Parameters"});
	}
}
