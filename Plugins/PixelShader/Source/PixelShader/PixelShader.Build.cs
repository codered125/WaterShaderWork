using UnrealBuildTool;
using System.IO;

public class PixelShader : ModuleRules
{
    public PixelShader(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateIncludePaths.AddRange(new string[] { "PixelShader/Private" });
        PublicIncludePaths.AddRange(new string[] { "PixelShader/Public" });

        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core" });
    }
}