/*************************************************************************
> File Name: FluidMeshBuffer.hpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Buffer wrapper class for fluid mesh inherited by RoundRobinAsyncBuffer.
> Created Time: 2020/07/26
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#ifndef CUBBYFLOW_VOX_FLUID_MESH_BUFFER_HPP
#define CUBBYFLOW_VOX_FLUID_MESH_BUFFER_HPP

#include <Vox/RoundRobinAsyncBuffer.hpp>
#include <memory>
#include <vector>

namespace Vox {

    /**
     * Buffer wrapper class for fluid mesh inherited by RoundRobinAsyncBuffer.
     * Each vertex array have vertex buffer object and element buffer object.
     * vertex buffer have two attributes for position and normal.
     **/
    class FluidMeshBuffer : public RoundRobinAsyncBuffer
    {
    public:
        //! Default Constructor.
        FluidMeshBuffer();
        //! Constructor with number of the buffers.
        FluidMeshBuffer(const size_t numBuffer);
        //! Default destructor.
        ~FluidMeshBuffer();
    
    protected:
        void OnAsyncBufferTransfer(const std::shared_ptr<GeometryCacheManager>& cacheManager) override;
        void OnDrawFrame(const std::shared_ptr<FrameContext>& ctx) override;
    private:
        std::vector<GLuint> _vaos;
        std::vector<GLuint> _vbos;
        std::vector<GLuint> _ebos;
        size_t _numIndices { 0 };
    };
};

#endif