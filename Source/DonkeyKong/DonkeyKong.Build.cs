// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DonkeyKong : ModuleRules
{
	public DonkeyKong(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "UMG",
            "Slate",
            "SlateCore"
        });
	}
}
