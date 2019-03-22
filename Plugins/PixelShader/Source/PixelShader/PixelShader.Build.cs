using UnrealBuildTool;
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class PixelShader : ModuleRules
    {
       // PrivatePCHHeaderFile = "Public/ShooterGame.h";
        public PixelShader(ReadOnlyTargetRules Target) : base(Target)
        {
            PrivateIncludePaths.AddRange(new string[] { "PixelShader/Private" });

            PublicIncludePaths.AddRange(new string[] { "PixelShader/Public" });

            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "RenderCore", "ShaderCore", "RHI" });
        }
    }
}