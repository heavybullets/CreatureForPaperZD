using System.IO;

namespace UnrealBuildTool.Rules
{
    public class CreaturePlugin : ModuleRules
    {
        private string ModulePath
        {
            //get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
            get { 

                
                string ModuleCSFilename = RulesCompiler.GetFileNameFromType(GetType());
                string ModuleBaseDirectory = Path.GetDirectoryName(ModuleCSFilename);

                return ModuleBaseDirectory;
            }
        }

        private string ThirdPartyPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/")); }
        }

        public bool LoadCreatureLib(ReadOnlyTargetRules Target)
        {
            PublicDefinitions.Add("GLM_FORCE_RADIANS");
            PublicDefinitions.Add("CREATURE_NO_USE_ZIP");
            PublicDefinitions.Add("CREATURE_NO_USE_EXCEPTIONS");
            PublicDefinitions.Add("CREATURE_MULTICORE");
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Includes"));

            return true;
        }

        public CreaturePlugin(ReadOnlyTargetRules Target)
            : base(Target)
        {
            PublicIncludePaths.AddRange(new string[] { ModulePath + "/Public", });
            PrivateIncludePaths.AddRange(new string[] { ModulePath + "/Private", });

            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "PaperZD" });

            PrivateDependencyModuleNames.AddRange(new string[] { "RHI", "RenderCore", "ShaderCore", "Json", "JsonUtilities" });

            LoadCreatureLib(Target);
        }
    }
}
