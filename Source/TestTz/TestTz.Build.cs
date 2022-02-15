// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestTz : ModuleRules
{
	public TestTz(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });

		PublicIncludePaths.AddRange(new string[] {"TestTz/Public/Parameters"});
		PublicIncludePaths.AddRange(new string[] {"TestTz/Public/UI"});
	}
}
