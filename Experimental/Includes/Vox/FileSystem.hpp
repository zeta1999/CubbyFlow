/*************************************************************************
> File Name: FileSystem.hpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Simple filesystem class
> Created Time: 2020/07/29
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#ifndef CUBBYFLOW_VOX_FILESYSTEM_HPP
#define CUBBYFLOW_VOX_FILESYSTEM_HPP

#include <vector>
#include <string>

namespace Vox {
    
    class Path
    {
    public:
        //! Declare constructor as non-explicit.
        Path(const char* path);
        //! Return string of the path;
        std::string ToString() const;
        //! Return whether if path is nullptr or not.
        bool IsNullPath() const;
        //! operator bool() overloading for if(path) idiom.
        operator bool() const;
        bool operator==(const Path& path);
    protected:
        const char* _path = nullptr;
    private:
    };

    class SourcePath : public Path
    {
    public:
        SourcePath(const char* function, const char* file, const int line);
        //! Return combination of member strings ( file::function(line) )
        std::string ToVerboseString() const;
    private:
        const char* _function = nullptr;
        const int _line = 0;
    };

    /**
     * FileSystem class usage scenario.
     * ---------------------------------
     * application.exe
     * - Resource
     *   - particle_scene.json
     *   - test.json
     *   - Image
     *     - texture.png
     * - Binary
     *   - foo.txt
     * ---------------------------------
     * FileSystem::AddDirectory("Resource");
     * FileSystem::AddDirectory("Binary");
     * auto path = FileSystem::FindPath("texture.png");
     * if (path) 
     *      LoadTexture(path);
     */
    class FileSystem
    {
    public:
        //! Add directory to searching target list.
        //! Allow const char* argument by not declare Path constructor as explicit
        static void AddDirectory(const Path& path); 

        //! Find relative path from the list of directories. 
        //! If File exists, return absolute file path.
        //! Otherwise, return NullPath.
        static Path FindPath(const Path& path);
    protected:
    private:
        static std::vector<Path> kTargetRange; //! Represents search target range

        static Path LoopDirectory(const Path& dir, const Path& path);
    };

};

#define CURRENT_SRC_PATH (Vox::SourcePath(__FUNCTION__, __FILE__, __LINE__))
#define CURRENT_SRC_PATH_TO_STR (Vox::SourcePath(__FUNCTION__, __FILE__, __LINE__).ToVerboseString().c_str())

#endif