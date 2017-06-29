// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyOverwatch : ModuleRules
{
	public MyOverwatch(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore" });


	}
}
